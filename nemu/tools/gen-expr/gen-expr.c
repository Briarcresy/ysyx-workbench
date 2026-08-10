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

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// this should be enough
static char buf[256] = { };
static char c_expr_buf[256] = { };
static char code_buf[256 + 128] = { }; // a little larger than `buf`
static char* code_format = "#include <stdio.h>\n"
                           "int main() { "
                           "  unsigned result = %s; "
                           "  printf(\"%%u\", result); "
                           "  return 0; "
                           "}";

static size_t buf_pos;
static size_t c_expr_pos;
static bool overflow;

static uint32_t choose(uint32_t n)
{
    return (uint32_t)rand() % n;
}

static void append_char(char* dst, size_t size, size_t* position, char ch)
{
    if (overflow) {
        return;
    }

    if (*position >= size - 1) {
        overflow = true;
        return;
    }

    dst[*position] = ch;
    (*position)++;
    dst[*position] = '\0';
}

// static void append_text(char* dst, size_t size, size_t* position, const char* text)
// {
//     if (overflow) {
//         return;
//     }

//     size_t length = strlen(text);
//     if (length >= size - *position) {
//         overflow = true;
//         return;
//     }

//     memcpy(dst + *position, text, length);
//     dst[*position + length] = '\0';
//     *position += length;
// }

static void append_uint(char* dst, size_t size, size_t* position, uint32_t number)
{
    static char digits[10];
    int count = 0;

    do {
        digits[count] = '0' + number % 10;
        count++;
        number /= 10;
    } while (number != 0);

    for (int i = count - 1; i >= 0; i--) {
        append_char(dst, size, position, digits[i]);
    }
}

static void gen_space()
{
    int count = (int)choose(3);
    for (int i = 0; i < count; i++) {
        append_char(buf, sizeof(buf), &buf_pos, ' ');
        append_char(c_expr_buf, sizeof(c_expr_buf), &c_expr_pos, ' ');
    }
}

static void gen_num()
{
    uint32_t number = ((uint32_t)rand() << 16) ^ (uint32_t)rand();
    append_uint(buf, sizeof(buf), &buf_pos, number);

    // append_text(c_expr_buf, sizeof(c_expr_buf), &c_expr_pos, "((unsigned)");
    append_uint(c_expr_buf, sizeof(c_expr_buf), &c_expr_pos, number);
    append_char(c_expr_buf, sizeof(c_expr_buf), &c_expr_pos, 'u');
}

static void gen_rand_op()
{
    static const char operators[] = { '+', '-', '*', '/' };
    char op = operators[choose(sizeof(operators) / sizeof(operators[0]))];

    gen_space();
    append_char(buf, sizeof(buf), &buf_pos, op);
    append_char(c_expr_buf, sizeof(c_expr_buf), &c_expr_pos, op);
    gen_space();
}

static void gen_expr(int depth)
{
    if (depth >= 6) {
        gen_num();
        return;
    }

    switch (choose(3)) {
    case 0:
        gen_num();
        break;
    case 1:
        append_char(buf, sizeof(buf), &buf_pos, '(');
        append_char(c_expr_buf, sizeof(c_expr_buf), &c_expr_pos, '(');
        gen_space();
        gen_expr(depth + 1);
        gen_space();
        append_char(buf, sizeof(buf), &buf_pos, ')');
        append_char(c_expr_buf, sizeof(c_expr_buf), &c_expr_pos, ')');
        break;
    default:
        gen_expr(depth + 1);
        gen_rand_op();
        gen_expr(depth + 1);
        break;
    }
}

static bool gen_rand_expr()
{
    buf_pos = 0;
    c_expr_pos = 0;
    overflow = false;
    buf[0] = '\0';
    c_expr_buf[0] = '\0';

    gen_expr(0);
    return !overflow;
}

int main(int argc, char* argv[])
{
    srand(time(0));
    int loop = 1;
    if (argc > 1) {
        sscanf(argv[1], "%d", &loop);
    }
    int generated = 0;
    while (generated < loop) {
        if (!gen_rand_expr()) {
            continue;
        }

        int length = snprintf(code_buf, sizeof(code_buf), code_format, c_expr_buf);
        if (length < 0 || (size_t)length >= sizeof(code_buf)) {
            continue;
        }

        FILE* fp = fopen("/tmp/.code.c", "w");
        assert(fp != NULL);
        fputs(code_buf, fp);
        fclose(fp);

        int ret = system("gcc -w /tmp/.code.c -o /tmp/.expr");
        if (ret != 0)
            continue;

        fp = popen("/tmp/.expr 2>/dev/null", "r");
        assert(fp != NULL);

        unsigned result;
        ret = fscanf(fp, "%u", &result);
        int status = pclose(fp);
        if (ret != 1 || status != 0) {
            continue;
        }

        printf("%u %s\n", result, buf);
        generated++;
    }
    return 0;
}
