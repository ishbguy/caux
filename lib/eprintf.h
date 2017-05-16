/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 *
 * Functions with exit action when encounter error.
 */

#ifndef __EPRINTF_H__
#define __EPRINTF_H__

#include <stddef.h>
#include <stdarg.h>

extern void eprintf(char *fmt, ...);
extern char *estrdup(char *str, const char *file, const int line,
                     const char *caller);
extern void *emalloc(size_t size, const char *file, const int line,
                     const char *caller);
extern void *ecalloc(size_t nmemb, size_t size, const char *file,
                     const int line, const char *caller);
extern void *erealloc(void *ptr, size_t size, const char *file, const int line,
                      const char *caller);
extern size_t efree(void *ptr, const char *file, const int line,
                    const char *caller);
extern char *progname(void);
extern void setprogname(char *str);

#define XPRINTF(fmt, ...) \
    eprintf("%s:%d: %s: " #fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define XSTRDUP(str) \
    estrdup((str), __FILE__, __LINE__, __func__)
#define XMALLOC(size) \
    emalloc((size), __FILE__, __LINE__, __func__)
#define XCALLOC(nmemb, size) \
    ecalloc((nmemb), (size), __FILE__, __LINE__, __func__)
#define XREALLOC(ptr, size) \
    erealloc((ptr), (size), __LINE__, __LINE__, __func__)
#define XFREE(ptr) \
    efree((ptr), __FILE__, __LINE__, __func__)

#endif /* End of include guard: __EPRINTF_H__ */

/* vim:set ft=c ts=4 sw=4: */
