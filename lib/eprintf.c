/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "smalloc.h"
#include "eprintf.h"

void eprintf(char *fmt, ...)
{
    va_list ap;

    fflush(stdout);             /* in case stdout and stderr are the same */
    if (progname() != NULL)
        fprintf(stderr, "%s: ", progname());
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    if (fmt[0] != '\0' && fmt[strlen(fmt) - 1] == ':')
        fprintf(stderr, " %s", strerror(errno));
    fprintf(stderr, "\n");
    fflush(NULL);               /* flushes all stdio output streams */

    exit(EXIT_FAILURE);
}

char *estrdup(char *str, const char *file, const int line, const char *caller)
{
    char *t = sstrdup(str);

    if (t == NULL)
        eprintf("%s:%d: %s: %s(\"%.20s\") failed:", file, line, caller,
                __func__, str);
    return t;
}

void *emalloc(size_t size, const char *file, const int line, const char *caller)
{
    void *ptr = smalloc(size);

    if (ptr == NULL)
        eprintf("%s:%d: %s: %s(%d) failed:", file, line, caller, __func__,
                size);
    return ptr;
}

void *ecalloc(size_t nmemb, size_t size, const char *file, const int line,
              const char *caller)
{
    void *ptr = scalloc(nmemb, size);

    if (ptr == NULL)
        eprintf("%s:%d: %s: %s(%d, %d) failed:", file, line, caller, __func__,
                nmemb, size);
    return ptr;
}

void *erealloc(void *ptr, size_t size, const char *file, const int line,
               const char *caller)
{
    void *nptr = srealloc(ptr, size);

    if (nptr == NULL)
        eprintf("%s:%d: %s: %s(%p, %d) failed:", file, line, caller, __func__,
                ptr, size);
    return nptr;
}

size_t efree(void *ptr, const char *file, const int line, const char *caller)
{
    return sfree(ptr);
}

static char *name = NULL;       /* program name for messages. */

/* set stored name of program. */
void setprogname(char *str)
{
    name = estrdup(str, __FILE__, __LINE__, __func__);
}

/* return stored name of program. */
char *progname(void)
{
    return name;
}

/* vim:set ft=c ts=4 sw=4: */
