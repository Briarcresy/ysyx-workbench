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

#include "sdb.h"

static WP wp_pool[NR_WP] = { };
static WP *head = NULL, *free_ = NULL;

void init_wp_pool()
{
    int i;
    for (i = 0; i < NR_WP; i++) {
        wp_pool[i].NO = i;
        wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
    }

    head = NULL;
    free_ = wp_pool;
}

WP* new_wp(const char* expr, word_t old_val)
{
    if (free_ == NULL) {
        printf("No free watchpoints available.\n");
        assert(0);
    }

    WP* wp = free_;
    free_ = free_->next;

    wp->next = head;
    wp->expr = strdup(expr);
    assert(wp->expr != NULL); // Ensure memory allocation was successful
    wp->old_val = old_val;
    head = wp;

    return wp;
}

void free_wp(WP* wp)
{
    if (wp == NULL) {
        return;
    }

    // Remove wp from the linked list
    if (head == wp) {
        head = wp->next;
    } else {
        WP* prev = head;
        while (prev != NULL && prev->next != wp) {
            prev = prev->next;
        }
        assert(prev != NULL); // Ensure wp is in the list
        prev->next = wp->next;
    }

    free(wp->expr); // Free the allocated expression string
    wp->expr = NULL; // Avoid dangling pointer
    // Add wp back to the free list
    wp->next = free_;
    free_ = wp;
}

bool check_watchpoints(void)
{
    WP* wp = head;
    bool any_changed = false;

    while (wp != NULL) {
        bool success = true;
        word_t new_val = expr(wp->expr, &success);
        if (!success) {
            printf("Failed to evaluate expression '%s' for watchpoint %d.\n", wp->expr, wp->NO);
            wp = wp->next;
            continue;
        }

        if (new_val != wp->old_val) {
            printf("Watchpoint %d triggered: %s\n", wp->NO, wp->expr);
            printf("Old value: " FMT_WORD ", New value: " FMT_WORD "\n", wp->old_val, new_val);
            wp->old_val = new_val; // Update the old value
            any_changed = true;
        }

        wp = wp->next;
    }

    return any_changed;
}

void print_watchpoints()
{
    WP* wp = head;
    if (wp == NULL) {
        printf("No watchpoints set.\n");
        return;
    }

    printf("Watchpoints:\n");
    while (wp != NULL) {
        printf("  Watchpoint %d: %s, Current value: " FMT_WORD "\n", wp->NO, wp->expr, wp->old_val);
        wp = wp->next;
    }
}

void delete_watchpoint(int no)
{
    WP* wp = head;

    while (wp != NULL) {
        if (wp->NO == no) {
            free_wp(wp); // Free the watchpoint
            printf("Watchpoint %d deleted.\n", no);
            return;
        }
        wp = wp->next;
    }

    printf("No watchpoint with number %d found.\n", no);
}

/* TODO: Implement the functionality of watchpoint */
