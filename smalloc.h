/* 
 * Copyright (c) 2016 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved
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
extern size_t sfree(void *ptr);
extern void *scalloc(size_t nmemb, size_t size);
extern void *srealloc(void *ptr, size_t size);
extern char *sstrdup(const char *str);
extern size_t sfree_all(void);/* What to do */

#endif /* End of include guard: __SMALLOC_H__ */
