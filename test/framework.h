/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int main_ret;
extern int test_count;
extern int test_pass; 
extern int test_fail;

#define EXPECT_EQ_BASE(equality, expect, actual, format)                      \
    do {                                                                      \
        test_count++;                                                         \
        if (equality)                                                         \
            test_pass++;                                                      \
        else {                                                                \
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", \
                    __FILE__, __LINE__, expect, actual);                      \
            test_fail++;                                                      \
            main_ret = 1;                                                     \
        }                                                                     \
    } while(0)

#define EXPECT_EQ_INT(expect, actual)                                         \
    EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

#define EXPECT_EQ_PTR(expect, actual)                                         \
    EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%p")

#define EXPECT_EQ_NULL(actual)                                                \
    EXPECT_EQ_BASE((NULL) == (actual), NULL, actual, "%p")

#define EXPECT_EQ_FLOAT(expect, actual, prec)                                 \
    EXPECT_EQ_BASE((abs((expect) - (actual)) < (prec)),                       \
            expect, actual, "%f")

#define EXPECT_EQ_STR(expect, actual)                                         \
    EXPECT_EQ_BASE((!strcmp((expect), (actual))), expect, actual, "%s")

#define EXPECT_NE_INT(expect, actual)                                         \
    EXPECT_EQ_BASE((expect) != (actual), expect, actual, "%d")

#define EXPECT_NE_PTR(expect, actual)                                         \
    EXPECT_EQ_BASE((expect) != (actual), expect, actual, "%p")

#define EXPECT_NE_NULL(actual)                                                \
    EXPECT_EQ_BASE((NULL) != (actual), NULL, actual, "%p")

#define EXPECT_NE_FLOAT(expect, actual, prec)                                 \
    EXPECT_EQ_BASE((abs((expect) - (actual)) > (prec)),                       \
            expect, actual, "%f")

#define EXPECT_NE_STR(expect, actual)                                         \
    EXPECT_EQ_BASE((strcmp((expect), (actual))), expect, actual, "%s")

#define EXPECT_BOOL(expr)                                                     \
    do {                                                                      \
        test_count++;                                                         \
        if (expr)                                                             \
            test_pass++;                                                      \
        else {                                                                \
            fprintf(stderr, "%s:%d: " #expr "failed.\n", __FILE__, __LINE__); \
            test_fail++;                                                      \
            main_ret = 1;                                                     \
        }                                                                     \
    } while(0)

#define EXPECT_TRUE(expr) EXPECT_BOOL((expr))
#define EXPECT_FLASE(expr) EXPECT_BOOL(!(expr))

/**
 * @brief   UnitTest function type.
 *
 */
typedef void (*UnitTest)(void);

/**
 * @brief       Run all given test function.
 *
 * @param tests The given test function array.
 */
extern void run_tests(UnitTest *tests);

#endif /* End of include guard: __FRAMEWORK_H__ */

/* vim:set ft=c ts=4 sw=4: */
