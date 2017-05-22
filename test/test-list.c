/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include <stdio.h>
#include "../lib/list.h"
#include "../lib/cunit.h"

void test_list(void)
{
    list_t *list, *copy;
    list_data_t *array;
    char * str[] = {
        "This",
        "is",
        "a",
        "test",
    };

    EXPECT_NE_NULL(LIST_NEW(list));
    EXPECT_TRUE(list_is_empty(list));
    EXPECT_EQ_INT(0, list_length(list));
    EXPECT_FLASE(list_rotate(list));
    EXPECT_EQ_STR(str[0], list_add_head(list, str[0])->data);
    EXPECT_EQ_STR(str[1], list_add_tail(list, str[1])->data);
    EXPECT_FLASE(list_is_empty(list));
    EXPECT_EQ_INT(2, list_length(list));
    EXPECT_TRUE(list_rotate(list));
    EXPECT_EQ_STR(str[1], list_del_head(list));
    EXPECT_EQ_STR(str[0], list_del_tail(list));
    EXPECT_TRUE(list_is_empty(list));
    EXPECT_EQ_INT(0, list_length(list));
    LIST_FREE(list);

    EXPECT_NE_NULL(LIST_VNEW(list, str[0], str[1], str[2], str[3], NULL));
    EXPECT_NE_NULL(LIST_COPY(copy, list));
    
    EXPECT_FLASE(list_is_empty(list));
    EXPECT_EQ_STR(str[0], list_del_head(list));
    EXPECT_EQ_STR(str[1], list_del_head(list));
    EXPECT_EQ_STR(str[2], list_del_head(list));
    EXPECT_EQ_STR(str[3], list_del_head(list));
    EXPECT_TRUE(list_is_empty(list));
    LIST_FREE(list);

    EXPECT_FLASE(list_is_empty(copy));
    EXPECT_EQ_STR(str[0], list_del_head(copy));
    EXPECT_EQ_STR(str[1], list_del_head(copy));
    EXPECT_EQ_STR(str[2], list_del_head(copy));
    EXPECT_EQ_STR(str[3], list_del_head(copy));
    EXPECT_TRUE(list_is_empty(copy));
    LIST_FREE(copy);

    EXPECT_NE_NULL(LIST_FROM_ARRAY(list, str));
    EXPECT_NE_NULL(LIST_TO_ARRAY(array, list));
    EXPECT_EQ_STR(str[0], array[0]);
    EXPECT_EQ_STR(str[1], array[1]);
    EXPECT_EQ_STR(str[2], array[2]);
    EXPECT_EQ_STR(str[3], array[3]);
    free(array);

    EXPECT_FLASE(list_is_empty(list));
    EXPECT_EQ_STR(str[0], list_del_head(list));
    EXPECT_EQ_STR(str[1], list_del_head(list));
    EXPECT_EQ_STR(str[2], list_del_head(list));
    EXPECT_EQ_STR(str[3], list_del_head(list));
    EXPECT_TRUE(list_is_empty(list));
    LIST_FREE(list);
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
