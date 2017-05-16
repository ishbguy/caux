/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>

typedef void *stack_data_t;
typedef struct __stack stack_t;

/**
 * @brief       Initialize a new stack.
 *
 * @param size  Number of data you want to save.
 *
 * @return      Pointer of the new stack.
 */
extern stack_t *stack_new(size_t size);

/**
 * @brief       Free a stack.
 *
 * @param stack Pointer of the stack you want to free.
 *
 * @return      Number of data handle by stack.
 */
extern size_t stack_free(stack_t * stack);

/**
 * @brief       Push data into a stack.
 *
 * @param stack Pointer of a stack.
 * @param data  Pointer of your data. 
 *
 * @return      The depth of the stack.
 */
extern size_t stack_push(stack_t * stack, stack_data_t data);

/**
 * @brief       Pop data out from a stack.
 *
 * @param stack Pointer of a stack.
 *
 * @return      Pointer of a data.
 */
extern stack_data_t stack_pop(stack_t * stack);

#endif /* End of include guard: __STACK_H__ */

/* vim:set ft=c ts=4 sw=4: */
