/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include <string.h>
#include "stack.h"
#include "smalloc.h"

struct _stack {
    StackDataPtr *store;
    size_t size;
    size_t depth;
};

Stack *stack_new(size_t size)
{
    if (size == 0)
        return NULL;

    /*
     * Allocate memory for stack itself and its data, then
     * initialize size of its data and stack depth.
     */
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
        return NULL;
    stack->store = (StackDataPtr *)calloc(size, sizeof(StackDataPtr));
    if (stack->store == NULL)
        return NULL;
    stack->size = size;
    stack->depth = 0;
    return stack;
}

static StackDataPtr *stack_grow(Stack *stack)
{
    if (stack == NULL)
        return NULL;

    /*
     * Base on the original stack size, reallocate a two time size
     * memory to enlarge the stack.
     */
    StackDataPtr *newstore = (StackDataPtr *)calloc(stack->size * 2, sizeof(StackDataPtr));
    if (newstore == NULL)
        return NULL;

    /*
     * Copy the old data to new memory space, and free the old space.
     */
    memmove(newstore, stack->store, stack->size * sizeof(StackDataPtr));
    free(stack->store);

    /* Update status */
    stack->store = newstore;
    stack->size *= 2;
    return newstore;
}

size_t stack_free(Stack *stack)
{
    if (stack == NULL)
        return 0;

    /* Free data space and stack itself. */
    size_t size = stack->size;
    free(stack->store);
    free(stack);
    return size;
}

size_t stack_push(Stack *stack, StackDataPtr data)
{
    if (stack == NULL || data == NULL)
        return 0;

    /* Check and enlarge the data space. */
    if (stack->depth >= stack->size)
        if (stack_grow(stack) == NULL)
            return 0;

    /* Store data and update depth. */
    stack->store[stack->depth] = data;
    stack->depth++;
    return stack->depth;
}

StackDataPtr stack_pop(Stack *stack)
{
    if (stack == NULL || stack->depth == 0)
        return NULL;

    /* Update depth and pop data ptr out from stack. */
    stack->depth--;
    StackDataPtr data = stack->store[stack->depth];

    /* Clean up data ptr. */
    stack->store[stack->depth] = NULL;
    return data;
}

/* vim:set ft=c ts=4 sw=4: */
