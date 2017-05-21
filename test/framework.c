/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include "framework.h"

int main_ret = 0;
int test_count = 0;
int test_pass = 0; 
int test_fail = 0;

static void run_test(UnitTest test)
{
    test();
}

void run_tests(UnitTest *tests)
{
    for (int i = 0; tests[i] != NULL; i++)
        run_test(tests[i]);
}

/* vim:set ft=c ts=4 sw=4: */
