/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __XMACRO_H__
#define __XMACRO_H__

#include <stdlib.h>
#include <string.h>

/* compile as c++ code */
#ifdef __cplusplus
#define XDECL_BEGIN extern "C" {
#define XDECL_END }
#else
#define XDECL_BEGIN
#define XDECL_END
#endif

#ifdef __HP_cc
#define inline __inline
#endif

#ifdef _WIN32
#endif

#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
#endif

#define XMAGIC (19910915)

/**
 * @brief LAMBDA -  Create a anonymous function then return it's pointer.
 *
 * @param rt_type   Return type of function.
 * @param arg_list  Argument list of function which must wrap with ().
 * @param fn_body   Function body which must wrap with {}.
 *
 * @return          Anonymous function ptr.
 */
#ifdef __GNUC__
#define LAMBDA(rt_type, arg_list, fn_body) ({ \
        rt_type fn arg_list                   \
        fn_body                               \
        &fn;                                  \
        })
#else
#define LAMBDA(rt_type, arg_list, fn_body) (rt_type)(0)
#endif

/**
 * @brief CONTAINER_OF - cast a member of a structure out to the 
 *                       containing structure 
 *
 * @param ptr       the pointer to the member.
 * @param type      the type of the container struct this is embedded in. 
 * @param member    the name of the member within the struct. 
 *
 * @return          Pointer of the container.
 */
#ifdef __GNUC__
#define CONTAINER_OF(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})
#else
#define CONTAINER_OF(ptr, type, member) (type *)(0)
#endif

#define STR(X) #X
#define XSTR(X) STR(X)
#define CAT(X, Y) X##Y
#define XCAT(X, Y) CAT(X, Y)

/**
 * @brief UNAME Generate a uniq variable name depend on __LINE__
 *
 * @param name      Variable's prefix name of the uniq name.
 */
#define UNAME(name) XCAT(name, __LINE__)

/**
 * @brief NELEM Calculate an array's number of elements.
 *
 * @param a         An array's name.
 */
#define NELEM(a) (sizeof(a)/sizeof(*a))

#define ARRAY_FOR_EACH(i, a) \
    for (i = 0; i < NELEM(a); i++)

/* a is an ptr array whose last element is NULL pointer */
#define ARRAY_FOR_EACH_PTR(ptr, a) \
    for (ptr = a; ptr && *ptr; ptr++)

/* memory allocated functions macros. */
#define MALLOC(ptr, size) ptr = malloc(size)
#define CALLOC(ptr, num, size) ptr = calloc(num, size)
#define REALLOC(ptr, size) ptr = realloc(ptr, size)
#define STRDUP(dest, src) dest = strdup(src)
#define NEW(ptr) ptr = malloc(sizeof(*(ptr)))
#define NEW0(ptr) ptr = calloc(1, sizeof(*(ptr)))
#define FREE(ptr) free((ptr)), ptr = NULL

/* define generic xmacro list */
struct __xlist_node {
    void *data;
    struct __xlist_node *next;
};

#define XLIST_NEW(l) struct __xlist_node *l = NULL

#define XLIST_ADD(l, d) do {         \
    struct __xlist_node *n;          \
    NEW0(n);                         \
    n->data = d;                     \
    n->next = l;                     \
    l = n;                           \
} while (0)

#define XLIST_DEL(l, d) do {         \
    struct __xlist_node *n;          \
    if (l) {                         \
        n = l;                       \
        d = n->data;                 \
        l = n->next;                 \
        FREE(n);                     \
    }                                \
} while (0)

#define XLIST_FREE(l) do {           \
    struct __xlist_node *n;          \
    while (l) {                      \
        n = l;                       \
        l = n->next;                 \
        free(n);                     \
    }                                \
} while (0)

#define XLIST_FOR_EACH(n, l)         \
    for (n = l; n; n = n->next)
#define XLIST_FOR_EACH_SAFE(n, s, l) \
    for (n = l; n? s = n->next, n: n; n = s)

#define XSTACK_T struct __xlist_node
#define XSTACK_NODE_T struct __xlist_node
#define XSTACK_NEW(s) XLIST_NEW(s)
#define XSTACK_PUSH(s, d) XLIST_ADD((s), (d))
#define XSTACK_POP(s, d) XLIST_DEL((s), (d))
#define XSTACK_FREE(s) XLIST_FREE(s)

#endif /* End of include guard: __XMACRO_H__ */

/* vim:set ft=c ts=4 sw=4: */
