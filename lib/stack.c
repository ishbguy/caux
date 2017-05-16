/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include <string.h>
#include "stack.h"
#include "smalloc.h"

struct __stack {
    stack_data_t *store;
    size_t size;
    size_t depth;
};

stack_t *stack_new(size_t size)
{
    if (size == 0)
        return NULL;

    /*
     * Allocate memory for stack itself and its data, then
     * initialize size of its data and stack depth.
     */
    stack_t *stack = (stack_t *) malloc(sizeof(stack_t));

    if (stack == NULL)
        return NULL;
    stack->store = (stack_data_t *) calloc(size, sizeof(stack_data_t));
    if (stack->store == NULL)
        return NULL;
    stack->size = size;
    stack->depth = 0;
    return stack;
}

static stack_data_t *stack_grow(stack_t * stack)
{
    if (stack == NULL)
        return NULL;

    /*
     * Base on the original stack size, reallocate a two time size
     * memory to enlarge the stack.
     */
    stack_data_t *newstore =
        (stack_data_t *) calloc(stack->size * 2, sizeof(stack_data_t));
    if (newstore == NULL)
        return NULL;

    /*
     * Copy the old data to new memory space, and free the old space.
     */
    memmove(newstore, stack->store, stack->size * sizeof(stack_data_t));
    free(stack->store);

    /*
     * Update status 
     */
    stack->store = newstore;
    stack->size *= 2;
    return newstore;
}

size_t stack_free(stack_t * stack)
{
    if (stack == NULL)
        return 0;

    /*
     * Free data space and stack itself. 
     */
    size_t size = stack->size;

    free(stack->store);
    free(stack);
    return size;
}

size_t stack_push(stack_t * stack, stack_data_t data)
{
    if (stack == NULL || data == NULL)
        return 0;

    /*
     * Check and enlarge the data space. 
     */
    if (stack->depth >= stack->size)
        if (stack_grow(stack) == NULL)
            return 0;

    /*
     * Store data and update depth. 
     */
    stack->store[stack->depth] = data;
    stack->depth++;
    return stack->depth;
}

stack_data_t stack_pop(stack_t * stack)
{
    if (stack == NULL || stack->depth == 0)
        return NULL;

    /*
     * Update depth and pop data ptr out from stack. 
     */
    stack->depth--;
    stack_data_t data = stack->store[stack->depth];

    /*
     * Clean up data ptr. 
     */
    stack->store[stack->depth] = NULL;
    return data;
}

/* vim:set ft=c ts=4 sw=4: */
