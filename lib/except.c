/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "except.h"

except_frame_t *Except_stack = NULL;

void except_raise(const except_t *e, const char *file, int line)
{
    except_frame_t *p = Except_stack;

    assert(e);
    if (p == NULL) {
        fprintf(stderr, "Uncaught exception");
        if (e->reason)
            fprintf(stderr, " %s", e->reason);
        else
            fprintf(stderr, " at 0x%p\n", e);
        if (file && line > 0)
            fprintf(stderr, " raise at %s:%d\n", file, line);
        fprintf(stderr, "aborting...\n");
        fflush(stderr);
        abort();
    }
    p->except = e;
    p->file = file;
    p->line = line;
    EXCEPT_STACK_POP(Except_stack);
    longjmp(p->env, Except_raised);
}

/* vim:set ft=c ts=4 sw=4: */
