/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "xmacro.h"
#include "list.h"

#define __SMALLOC_C__
#include "smalloc.h"

typedef struct __smalloc_node {
    list_node_t *node;
    size_t size;
    int magic;
} smalloc_t;

static LIST_STATIC_INIT(smalloc_list);
static int atexit_free_flag = 1;

void *smalloc(size_t size)
{
    smalloc_t *header;

    if (size <= 0)
        return NULL;
    MALLOC(header, sizeof(smalloc_t) + size);
    if (header == NULL)
        return NULL;
    header->node = list_add_tail(&smalloc_list, header);
    header->size = size;
    header->magic = XMAGIC;
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
        if (header->node == NULL || header->magic != XMAGIC)
            return;
        list_del_node(header->node);
        FREE(header);
    }
}

void *scalloc(size_t nmemb, size_t size)
{
    void *ptr;

    if (nmemb <= 0 || size <= 0)
        return NULL;
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

    if (ptr == NULL || size <= 0)
        return NULL;
    header = (smalloc_t *) ptr - 1;
    if (header->node == NULL || header->magic != XMAGIC)
        return NULL;
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

    if (str == NULL)
        return NULL;
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
