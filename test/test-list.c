/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include <stdio.h>
#include "../lib/list.h"
#include "framework.h"

void test_list(void)
{
    list_t *list, *copy;

    EXPECT_NE_NULL(list = list_new());
    EXPECT_TRUE(list_is_empty(list));
    EXPECT_EQ_INT(0, list_length(list));
    EXPECT_FLASE(list_rotate(list));
    EXPECT_NE_NULL(list_add_head(list, "hello"));
    EXPECT_NE_NULL(list_add_tail(list, "world"));
    EXPECT_FLASE(list_is_empty(list));
    EXPECT_EQ_INT(2, list_length(list));
    EXPECT_TRUE(list_rotate(list));
    EXPECT_EQ_STR("world", list_del_head(list));
    EXPECT_EQ_STR("hello", list_del_tail(list));
    EXPECT_TRUE(list_is_empty(list));
    EXPECT_EQ_INT(0, list_length(list));
    list_free(list);

    EXPECT_NE_NULL(list = list_vnew("This", "is", "a", "test", NULL));
    EXPECT_FLASE(list_is_empty(list));
    EXPECT_NE_NULL(copy = list_copy(list));
    EXPECT_FLASE(list_is_empty(copy));
    EXPECT_EQ_STR("This", list_del_head(copy));
    EXPECT_EQ_STR("is", list_del_head(copy));
    EXPECT_EQ_STR("a", list_del_head(copy));
    EXPECT_EQ_STR("test", list_del_head(copy));
    EXPECT_TRUE(list_is_empty(copy));
    list_free(list);
    list_free(copy);
}

UnitTest tests[] = {
    test_list,
    NULL, /* array end indicator */
};

int main(void)
{
    run_tests(tests);
    printf("total: %d, pass: %d, fail: %d.\n", test_count, test_pass,
           test_fail);
    return main_ret;
}

/* vim:set ft=c ts=4 sw=4: */
