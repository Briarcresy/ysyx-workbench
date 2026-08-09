/***************************************************************************************
 * Copyright (c) 2014-2024 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#include <isa.h>
#include <memory/vaddr.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <errno.h>
#include <regex.h>

enum {
    TK_NOTYPE = 256,
    TK_EQ,
    TK_NEQ,
    TK_AND,
    TK_NUM,
    TK_NUM_HEX,
    TK_REG,
    TK_NEG,
    TK_DEREF,
    /* TODO: Add more token types */

};

static struct rule {
    const char* regex;
    int token_type;
} rules[] = {

    /* TODO: Add more rules.
     * Pay attention to the precedence level of different rules.
     */

    { " +", TK_NOTYPE }, // spaces
    { "\\+", '+' }, // plus
    { "==", TK_EQ }, // equal
    { "!=", TK_NEQ }, // not equal
    { "&&", TK_AND }, // logical AND
    { "0x[0-9a-fA-F]+", TK_NUM_HEX }, // hexadecimal numbers
    { "[0-9]+", TK_NUM }, // numbers
    { "-", '-' }, // minus
    { "\\*", '*' }, // multiply
    { "/", '/' }, // divide
    { "\\(", '(' }, // left parenthesis
    { "\\)", ')' }, // right parenthesis
    { "\\$[a-zA-Z0-9]+", TK_REG }, // register
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = { };

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
    int i;
    char error_msg[128];
    int ret;

    for (i = 0; i < NR_REGEX; i++) {
        ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
        if (ret != 0) {
            regerror(ret, &re[i], error_msg, 128);
            panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
        }
    }
}

typedef struct token {
    int type;
    char str[32];
} Token;

static Token tokens[1024] __attribute__((used)) = { };
static int nr_token __attribute__((used)) = 0;
static bool quiet = false;

void expr_set_quiet(bool value)
{
    quiet = value;
}

static bool make_token(const char* e)
{
    int position = 0;
    int i;
    regmatch_t pmatch;

    nr_token = 0;

    while (e[position] != '\0') {
        /* Try all rules one by one. */
        for (i = 0; i < NR_REGEX; i++) {
            if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
                const char* substr_start = e + position;
                int substr_len = pmatch.rm_eo;

                if (!quiet) {
                    Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
                        i, rules[i].regex, position, substr_len, substr_len, substr_start);
                }

                position += substr_len;

                /* TODO: Now a new token is recognized with rules[i]. Add codes
                 * to record the token in the array `tokens'. For certain types
                 * of tokens, some extra actions should be performed.
                 */
                if (rules[i].token_type == TK_NOTYPE) {
                    break;
                }

                if (nr_token >= ARRLEN(tokens)) {
                    printf("too many tokens\n");
                    return false;
                }
                tokens[nr_token].type = rules[i].token_type;
                switch (rules[i].token_type) {
                case TK_NUM:
                case TK_NUM_HEX:
                case TK_REG:
                    if (substr_len >= sizeof(tokens[nr_token].str)) {
                        printf("token too long: %.*s\n", substr_len, substr_start);
                        return false;
                    }
                    memcpy(tokens[nr_token].str, substr_start, substr_len);
                    tokens[nr_token].str[substr_len] = '\0';
                    nr_token++;
                    break;
                default:
                    nr_token++;
                    break;
                }
                break;
            }
        }

        if (i == NR_REGEX) {
            printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
            return false;
        }
    }

    return true;
}

static bool check_parentheses(int p, int q, bool* success)
{
    int depth = 0;
    bool surrounded = tokens[p].type == '(' && tokens[q].type == ')';

    for (int i = p; i <= q; i++) {
        if (tokens[i].type == '(') {
            depth++;
        } else if (tokens[i].type == ')') {
            depth--;
            if (depth < 0) {
                *success = false;
                return false;
            }
        }

        if (depth == 0 && i < q) {
            surrounded = false;
        }
    }

    if (depth != 0) {
        *success = false;
        return false;
    }

    return surrounded;
}

static int precedence(int type)
{
    switch (type) {
    case TK_AND:
        return 1;
    case TK_EQ:
    case TK_NEQ:
        return 2;
    case '+':
    case '-':
        return 3;
    case '*':
    case '/':
        return 4;
    default:
        return 0;
    }
}

static word_t parse_number(const char* str, int base, bool* success)
{
    char* end = NULL;
    errno = 0;
    unsigned long long value = strtoull(str, &end, base);

    if (errno == ERANGE || *end != '\0' || value > UINT32_MAX) {
        *success = false;
        return 0;
    }

    return (word_t)value;
}

static word_t eval(int p, int q, bool* success)
{
    if (p > q) {
        *success = false;
        return 0;
    }

    if (p == q) {
        switch (tokens[p].type) {
        case TK_NUM:
            return parse_number(tokens[p].str, 10, success);
        case TK_NUM_HEX:
            return parse_number(tokens[p].str, 16, success);
        case TK_REG:
            return isa_reg_str2val(tokens[p].str + 1, success);
        default:
            *success = false;
            return 0;
        }
    }

    bool surrounded = check_parentheses(p, q, success);
    if (!*success) {
        return 0;
    }
    if (surrounded) {
        return eval(p + 1, q - 1, success);
    }

    int depth = 0;
    int op = -1;
    int op_precedence = 5;

    for (int i = p; i <= q; i++) {
        if (tokens[i].type == '(') {
            depth++;
        } else if (tokens[i].type == ')') {
            depth--;
        } else if (depth == 0) {
            int current_precedence = precedence(tokens[i].type);
            if (current_precedence != 0 && current_precedence <= op_precedence) {
                op = i;
                op_precedence = current_precedence;
            }
        }
    }

    if (op == -1) {
        if (tokens[p].type != TK_NEG && tokens[p].type != TK_DEREF) {
            *success = false;
            return 0;
        }

        word_t value = eval(p + 1, q, success);
        if (!*success) {
            return 0;
        }

        if (tokens[p].type == TK_NEG) {
            return (word_t)(0 - value);
        }
        return vaddr_read((vaddr_t)value, 4);
    }

    word_t val1 = eval(p, op - 1, success);
    if (!*success) {
        return 0;
    }
    if (tokens[op].type == TK_AND && val1 == 0) {
        return 0;
    }
    word_t val2 = eval(op + 1, q, success);
    if (!*success) {
        return 0;
    }

    switch (tokens[op].type) {
    case '+':
        return val1 + val2;
    case '-':
        return val1 - val2;
    case '*':
        return val1 * val2;
    case '/':
        if (val2 == 0) {
            *success = false;
            return 0;
        }
        return val1 / val2;
    case TK_EQ:
        return val1 == val2;
    case TK_NEQ:
        return val1 != val2;
    case TK_AND:
        return val1 && val2;
    default:
        *success = false;
        return 0;
    }
}

static bool is_operand_end(int type)
{
    return type == TK_NUM || type == TK_NUM_HEX || type == TK_REG || type == ')';
}

word_t expr(const char* e, bool* success)
{
    if (!make_token(e)) {
        *success = false;
        return 0;
    }

    for (int i = 0; i < nr_token; i++) {
        if (tokens[i].type == '-' && (i == 0 || !is_operand_end(tokens[i - 1].type))) {
            tokens[i].type = TK_NEG;
        }
        if (tokens[i].type == '*' && (i == 0 || !is_operand_end(tokens[i - 1].type))) {
            tokens[i].type = TK_DEREF;
        }
    }

    *success = true;
    return eval(0, nr_token - 1, success);
}
