/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __SMALLOC_H__
#define __SMALLOC_H__

#include <stddef.h>

#if defined (__SMALLOC_C__) || defined (USE_STD_ALLOC)
#include <stdlib.h>
#else
#define malloc  smalloc
#define free    sfree
#define calloc  scalloc
#define realloc srealloc
#define strdup  sstrdup
#endif

extern void *smalloc(size_t size);
extern void sfree(void *ptr);
extern void *scalloc(size_t nmemb, size_t size);
extern void *srealloc(void *ptr, size_t size);
extern char *sstrdup(const char *str);
extern void sfree_all(void);

#endif /* End of include guard: __SMALLOC_H__ */

/* vim:set ft=c ts=4 sw=4: */
