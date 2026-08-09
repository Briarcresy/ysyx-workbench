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

#include <common.h>

#ifndef CONFIG_TARGET_AM
#include <ctype.h>
#include <errno.h>
#endif

void init_monitor(int, char*[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

#ifndef CONFIG_TARGET_AM
void init_regex();
word_t expr(char* e, bool* success);
void expr_set_quiet(bool value);

static int run_expr_tests(const char* input_file)
{
    FILE* fp = fopen(input_file, "r");
    if (fp == NULL) {
        perror(input_file);
        return 1;
    }

    init_regex();
    expr_set_quiet(true);

    char* line = NULL;
    size_t capacity = 0;
    ssize_t length;
    int line_number = 0;
    int passed = 0;
    int failed = 0;

    while ((length = getline(&line, &capacity, fp)) != -1) {
        line_number++;
        while (length > 0 && (line[length - 1] == '\n' || line[length - 1] == '\r')) {
            line[--length] = '\0';
        }

        errno = 0;
        char* expression = NULL;
        unsigned long long expected_raw = strtoull(line, &expression, 10);
        while (isspace((unsigned char)*expression)) {
            expression++;
        }

        if (errno != 0 || expression == line || expected_raw > UINT32_MAX || *expression == '\0') {
            printf("[line %d] malformed test case: %s\n", line_number, line);
            failed++;
            continue;
        }

        bool success = false;
        word_t actual = expr(expression, &success);
        word_t expected = (word_t)expected_raw;

        if (!success || actual != expected) {
            printf("[line %d] FAIL\n", line_number);
            printf("  expression: %s\n", expression);
            printf("  expected:   " FMT_WORD "\n", expected);
            if (success) {
                printf("  actual:     " FMT_WORD "\n", actual);
            } else {
                printf("  actual:     evaluation failed\n");
            }
            failed++;
        } else {
            passed++;
        }
    }

    if (ferror(fp)) {
        perror(input_file);
        failed++;
    }

    free(line);
    fclose(fp);

    printf("Expression tests: %d passed, %d failed.\n", passed, failed);
    return failed == 0 ? 0 : 1;
}
#endif

int main(int argc, char* argv[])
{
#ifndef CONFIG_TARGET_AM
    if (argc == 3 && strcmp(argv[1], "--expr-test") == 0) {
        return run_expr_tests(argv[2]);
    }
#endif

    /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
    am_init_monitor();
#else
    init_monitor(argc, argv);
#endif

    /* Start engine. */
    engine_start();

    return is_exit_status_bad();
}
