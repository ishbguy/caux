/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include <stdio.h>
#include <stdint.h>
#include "../lib/xmacro.h"
#include "../lib/smalloc.h"
#include "../lib/cunit.h"

void test_smalloc(void)
{
    void *ptr;

    EXPECT_EQ_NULL(MALLOC(ptr, 0));
    FREE(ptr);
    EXPECT_NE_NULL(NEW(ptr));
    FREE(ptr);
    EXPECT_EQ_NULL(MALLOC(ptr, UINT32_MAX - 12));
    FREE(ptr);
    EXPECT_EQ_NULL(MALLOC(ptr, UINT32_MAX - 13));
    FREE(ptr);
    EXPECT_EQ_NULL(MALLOC(ptr, UINT32_MAX + 1));
    FREE(ptr);
    EXPECT_EQ_NULL(MALLOC(ptr, -1));
    FREE(ptr);

    EXPECT_EQ_NULL(CALLOC(ptr, 1, 0));
    FREE(ptr);
    EXPECT_EQ_NULL(CALLOC(ptr, 0, 0));
    FREE(ptr);
    EXPECT_EQ_NULL(CALLOC(ptr, 0, 1));
    FREE(ptr);
    EXPECT_NE_NULL(NEW0(ptr));
    FREE(ptr);
    EXPECT_NE_NULL(CALLOC(ptr, 1, 1000));
    FREE(ptr);
    EXPECT_NE_NULL(CALLOC(ptr, 1000, 1000));
    FREE(ptr);

    EXPECT_NE_NULL(CALLOC(ptr, 1, 1000));
    EXPECT_NE_NULL(REALLOC(ptr, 100));
    EXPECT_NE_NULL(REALLOC(ptr, 1000));
    EXPECT_EQ_NULL(REALLOC(ptr, 0));
    FREE(ptr);
    EXPECT_EQ_STR("hello", strdup("hello"));
    EXPECT_EQ_NULL(STRDUP(ptr, NULL));
}

UnitTest tests[] = {
    test_smalloc,
    NULL,                       /* array end indicator */
};

int main(void)
{
    run_tests(tests);
    printf("total: %d, pass: %d, fail: %d.\n", test_count, test_pass,
           test_fail);
    return main_ret;
}

/* vim:set ft=c ts=4 sw=4: */
