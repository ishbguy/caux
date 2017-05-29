/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __SCOPE_H__
#define __SCOPE_H__

#include "stack.h"
#include "xmacro.h"

/*
 * Create a stack to store resource release functions.
 */
#define SCOPE_INIT() stack_t *__scope = stack_new(2)

/*
 * Add resource release functions to scope stack.
 */
#define SCOPE_GUARD(callback) \
    stack_push(__scope, LAMBDA(void, (void), {callback;}))

/*
 * Use resource release functions in the scope stack to recycle
 * resource, then free scope stack.
 */
#define SCOPE_CLEAN() do {                       \
    for (void (*fn)(void) = stack_pop(__scope);  \
            fn != NULL; fn = stack_pop(__scope)) \
        fn();                                    \
    stack_free(__scope);                         \
} while(0)

#endif /* End of include guard: __SCOPE_H__ */

/* vim:set ft=c ts=4 sw=4: */
