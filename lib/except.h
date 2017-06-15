/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#include <setjmp.h>

typedef struct except_t except_t;
struct except_t {
    const char *reason;
};

typedef struct except_frame_t except_frame_t;
struct except_frame_t {
    except_frame_t *prev;
    jmp_buf env;
    const char *file;
    int line;
    const except_t *except;
};
extern except_frame_t *Except_stack;
extern const except_t Assert_Failed;

enum {
    Except_entered = 0,
    Except_raised,
    Except_handled,
    Except_finalized,
};

void except_raise(const except_t *e, const char *file, int line);

#define RAISE(e) \
    except_raise(&(e), __FILE__, __LINE__)
#define RERAISE \
    except_raise(Except_frame.except, Except_frame.file, Except_frame.line)
#define EXCEPT_STACK_PUSH(s, f) (f).prev = (s); (s) = &(f)
#define EXCEPT_STACK_POP(s) (s) = (s)->prev

#define TRY \
    do { \
        volatile int Except_flag; \
        except_frame_t Except_frame; \
        Except_frame.prev = Except_stack; \
        EXCEPT_STACK_PUSH(Except_stack, Except_frame); \
        Except_flag = setjmp(Except_frame.env); \
        if (Except_flag == Except_entered) {

#define CATCH(e) \
            if (Except_flag == Except_entered) \
                EXCEPT_STACK_POP(Except_stack); \
        } else if (Except_frame.except == &(e)) { \
            Except_flag = Except_handled;

#define CATCH_ELSE \
            if (Except_flag == Except_entered) \
                EXCEPT_STACK_POP(Except_stack); \
        } else { \
            Except_flag = Except_handled;

#define FINALLY \
            if (Except_flag == Except_entered) \
                EXCEPT_STACK_POP(Except_stack); \
        } { \
            if (Except_flag == Except_entered) \
                Except_flag = Except_finalized;

#define END_TRY \
            if (Except_flag == Except_entered) \
                EXCEPT_STACK_POP(Except_stack); \
        } if (Except_flag == Except_raised) RERAISE; \
    } while (0)

#endif /* End of include guard: __EXCEPT_H__ */

/* vim:set ft=c ts=4 sw=4: */
