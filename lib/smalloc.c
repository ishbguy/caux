/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include "xmacro.h"
#include "list.h"

#define __SMALLOC_C__
#include "smalloc.h"

typedef struct __smalloc_node {
    list_node_t *node;
    size_t size;
    void *ptr;
} smalloc_t;

static LIST_STATIC_INIT(smalloc_list);
static int atexit_free_flag = 1;

void *smalloc(size_t size)
{
    smalloc_t *header;

    /* Make sure that the size will not overflow. */
    if (size <= 0 || size + sizeof(*header) < size) {
        errno = EINVAL;
        return NULL;
    }
    header = malloc(sizeof(*header) + size);
    if (header == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    header->node = list_add_tail(&smalloc_list, header);
    header->size = size;
    header->ptr = header + 1;
    if (atexit_free_flag) {
        atexit(sfree_all);
        atexit_free_flag = 0;
    }
    return header + 1;
}

void sfree(void *ptr)
{
    smalloc_t *header;

    if (ptr) {
        header = (smalloc_t *) ptr - 1;
        if (header->node == NULL || header->ptr != ptr) {
            errno = EINVAL;
            return;
        }
        list_del_node(header->node);
        FREE(header);
    }
}

void *scalloc(size_t nmemb, size_t size)
{
    void *ptr;

    if (nmemb <= 0 || size <= 0) {
        errno = EINVAL;
        return NULL;
    }
    ptr = smalloc(nmemb * size);
    if (ptr)
        memset(ptr, 0, nmemb * size);
    return ptr;
}

void *srealloc(void *ptr, size_t size)
{
    size_t copy_size;
    void *new_ptr;
    smalloc_t *header;

    if (ptr == NULL || size <= 0) {
        errno = EINVAL;
        return NULL;
    }
    header = (smalloc_t *) ptr - 1;
    if (header->node == NULL || header->ptr != ptr) {
        errno = EINVAL;
        return NULL;
    }
    copy_size = header->size;
    new_ptr = smalloc(size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, copy_size < size ? copy_size : size);
        sfree(ptr);
    }
    return new_ptr;
}

char *sstrdup(const char *str)
{
    char *new_str;

    if (str == NULL) {
        errno = EINVAL;
        return NULL;
    }
    new_str = smalloc(strlen(str) + 1);
    if (new_str)
        strcpy(new_str, str);
    return new_str;
}

void sfree_all(void)
{
    list_t *list, *pos, *save;

    if (list_is_empty(&smalloc_list))
        return;
    list = &smalloc_list;
    LIST_FOR_EACH_SAFE(pos, save, list) {
        FREE(pos->data);
        list_del_node(pos);
    }
}

/* vim:set ft=c ts=4 sw=4: */
