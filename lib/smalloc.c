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
    void *ptr;
} smalloc_t;

static LIST_STATIC_INIT(smalloc_list);
static size_t smalloc_count = 0;
static size_t smalloc_size = 0;
static int atexit_free_flag = 1;

void *smalloc(size_t size)
{
    smalloc_t *header;

    if (size == 0)
        return NULL;
    MALLOC(header, sizeof(smalloc_t) + size);
    assert(header);
    header->node = list_add_tail(&smalloc_list, header);
    header->size = size;
    header->magic = XMAGIC;
    header->ptr = header + 1;
    if (atexit_free_flag) {
        atexit(sfree_all);
        atexit_free_flag = 0;
    }
    smalloc_count++;
    smalloc_size += size;
    return header->ptr;
}

void sfree(void *ptr)
{
    smalloc_t *header;

    if (ptr) {
        header = (smalloc_t *) ptr - 1;
        if (header->magic != XMAGIC)
            return;
        list_del_node(header->node);
        smalloc_size -= header->size;
        smalloc_count--;
        FREE(header);
    }
}

void *scalloc(size_t nmemb, size_t size)
{
    size_t total;
    void *ptr;

    if (nmemb == 0 || size == 0)
        return NULL;
    total = nmemb * size;
    if (total > UINT32_MAX)
        return NULL;
    ptr = smalloc(total);
    if (ptr == NULL)
        return NULL;
    memset(ptr, 0, total);
    return ptr;
}

void *srealloc(void *ptr, size_t size)
{
    size_t copy_size;
    void *new_ptr;
    smalloc_t *header;

    if (ptr == NULL || size == 0)
        return NULL;
    header = (smalloc_t *) ptr - 1;
    if (header->node == NULL || header->magic != XMAGIC)
        return NULL;
    copy_size = header->size;
    new_ptr = smalloc(size);
    if (new_ptr == NULL)
        return NULL;
    memcpy(new_ptr, ptr, copy_size < size ? copy_size : size);
    sfree(ptr);
    return new_ptr;
}

char *sstrdup(const char *str)
{
    char *new_str;

    if (str == NULL)
        return NULL;
    new_str = smalloc(strlen(str) + 1);
    if (new_str == NULL)
        return NULL;
    strcpy(new_str, str);
    return new_str;
}

void sfree_all(void)
{
    list_t *list, *pos;

    if (list_is_empty(&smalloc_list))
        return;
    list = &smalloc_list;
    LIST_FOR_EACH(pos, list) {
        FREE(pos->data);
        list_del_node(pos);
    }
    smalloc_size = 0;
    smalloc_count = 0;
}

/* vim:set ft=c ts=4 sw=4: */
