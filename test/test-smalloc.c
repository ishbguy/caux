/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include <stdio.h>
#include "../lib/xmacro.h"
#include "../lib/smalloc.h"
#include "../lib/cunit.h"

void test_smalloc(void)
{
    
}

UnitTest tests[] = {
    test_smalloc,
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
