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

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <errno.h>
#include <regex.h>

enum {
    TK_NOTYPE = 256,
    TK_EQ,
    TK_NUM,
    TK_NEG,
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
    { "[0-9]+", TK_NUM }, // numbers
    { "-", '-' }, // minus
    { "\\*", '*' }, // multiply
    { "/", '/' }, // divide
    { "\\(", '(' }, // left parenthesis
    { "\\)", ')' }, // right parenthesis
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

static bool make_token(char* e)
{
    int position = 0;
    int i;
    regmatch_t pmatch;

    nr_token = 0;

    while (e[position] != '\0') {
        /* Try all rules one by one. */
        for (i = 0; i < NR_REGEX; i++) {
            if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
                char* substr_start = e + position;
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
                if (rules[i].token_type != TK_NOTYPE && nr_token >= ARRLEN(tokens)) {
                    printf("too many tokens\n");
                    return false;
                }
                tokens[nr_token].type = rules[i].token_type;
                switch (rules[i].token_type) {
                case TK_NUM:
                    if (substr_len >= sizeof(tokens[nr_token].str)) {
                        printf("token too long: %.*s\n", substr_len, substr_start);
                        return false;
                    }
                    memcpy(tokens[nr_token].str, substr_start, substr_len);
                    tokens[nr_token].str[substr_len] = '\0';
                    nr_token++;
                    break;
                case TK_NOTYPE:
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
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

static word_t eval(int p, int q, bool* success)
{
    if (p > q) {
        *success = false;
        return 0;
    }

    if (p == q) {
        if (tokens[p].type != TK_NUM) {
            *success = false;
            return 0;
        }

        char* end = NULL;
        errno = 0;
        unsigned long long value = strtoull(tokens[p].str, &end, 10);
        if (errno != 0 || *end != '\0' || value > UINT32_MAX) {
            *success = false;
            return 0;
        }
        return (word_t)value;
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
    int op_precedence = 3;

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
        if (tokens[p].type != TK_NEG) {
            *success = false;
            return 0;
        }

        word_t value = eval(p + 1, q, success);
        return *success ? (word_t)(0 - value) : 0;
    }

    word_t val1 = eval(p, op - 1, success);
    if (!*success) {
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
    default:
        *success = false;
        return 0;
    }
}

word_t expr(char* e, bool* success)
{
    if (!make_token(e)) {
        *success = false;
        return 0;
    }

    for (int i = 0; i < nr_token; i++) {
        if (tokens[i].type == '-' && (i == 0 || (tokens[i - 1].type != TK_NUM && tokens[i - 1].type != ')'))) {
            tokens[i].type = TK_NEG;
        }
    }

    *success = true;
    return eval(0, nr_token - 1, success);
}
