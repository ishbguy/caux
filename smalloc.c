/* 
 * Copyright (c) 2016 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved
 */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define __SMALLOC_C__
#include "smalloc.h"

/* TODO: Make correct precondition and postcondition with on size. */
/* TODO: Add magic code to check whether a ptr is allocated by smalloc. */
typedef struct __smalloc_header SmallocHeader;
struct __smalloc_header {
    SmallocHeader *prev;
    SmallocHeader *next;
    size_t size;
};

static SmallocHeader smalloc_list = {&smalloc_list, &smalloc_list, 0};
static size_t smalloc_count = 0;
static size_t smalloc_size = 0;
static int atexit_free = 1;
static void atexit_sfree_all(void);

static inline void __list_add(SmallocHeader *prev,
        SmallocHeader *curr, SmallocHeader *next)
{
    curr->prev = prev;
    curr->next = next;
    prev->next = curr;
    next->prev = curr;
}

static inline void list_add(SmallocHeader *list, SmallocHeader *new)
{
    __list_add(list, new, list->next);
}

static inline void list_add_tail(SmallocHeader *list, SmallocHeader *new)
{
    __list_add(list->prev, new, list);
}

static inline int list_is_empty(SmallocHeader *list)
{
    return (list->prev == list->next && list->next == list);
}

static inline void __list_del(SmallocHeader *prev, SmallocHeader *next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void list_del(SmallocHeader *curr)
{
    __list_del(curr->prev, curr->next);
}

static inline SmallocHeader *list_del_tail(SmallocHeader *list)
{
    SmallocHeader *tail = list->next;
    list_del(tail);
    return tail;
}

static inline SmallocHeader *list_del_head(SmallocHeader *list)
{
    SmallocHeader *head = list->next;
    list_del(head);
    return head;
}

static inline void *smalloc_get_store_ptr(SmallocHeader *header)
{
    return header + 1;
}

static inline void *smalloc_get_header_ptr(void *ptr)
{
    return (SmallocHeader *)ptr - 1;
}

void *smalloc(size_t size)
{
    if (size == 0)
        return NULL;
    SmallocHeader *header =
        (SmallocHeader *)malloc(size + sizeof(SmallocHeader));
    if (header == NULL)
        return NULL;
    list_add_tail(&smalloc_list, header);
    if (atexit_free) {
        atexit(atexit_sfree_all);
        atexit_free = 0;
    }
    header->size = size;
    void *ptr = smalloc_get_store_ptr(header);
    smalloc_count++;
    smalloc_size += size;
    return ptr;
}

size_t sfree(void *ptr)
{
    if (ptr == NULL)
        return 0;
    SmallocHeader *header = smalloc_get_header_ptr(ptr);
    if (header->prev == NULL || header->next == NULL)
        return 0;
    size_t size = header->size;
    list_del(header);
    free(header);
    smalloc_count--;
    smalloc_size -= size;
    return size;
}

void *scalloc(size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0)
        return NULL;
    size_t total = nmemb * size;
    if (total > UINT32_MAX)
        return NULL;
    void *ptr = smalloc(total);
    if (ptr == NULL)
        return NULL;
    memset(ptr, 0, total);
    return ptr;
}

void *srealloc(void *ptr, size_t size)
{
    if (ptr == NULL || size == 0)
        return NULL;
    SmallocHeader *header = smalloc_get_header_ptr(ptr);
    if (header->prev == NULL || header->next == NULL)
        return NULL;
    size_t copy_size = header->size;
    void *nptr = smalloc(size);
    if (nptr == NULL)
        return NULL;
    if (copy_size > size)
        copy_size = size;
    memcpy(nptr, ptr, copy_size);
    sfree(ptr);
    return nptr;
}

char *sstrdup(const char *str)
{
    if (str == NULL)
        return NULL;
    char *nstr = smalloc(strlen(str) + 1);
    if (nstr == NULL)
        return NULL;
    strcpy(nstr, str);
    return nstr;
}

size_t sfree_all(void)
{
    if (list_is_empty(&smalloc_list))
        return 0;
    SmallocHeader *list = &smalloc_list;
    SmallocHeader *node;
    for (node = list->prev; node != list; node = list->prev) {
        list_del(node);
        free(node);
    }
    size_t total= smalloc_size;
    smalloc_count = 0;
    smalloc_size = 0;
    return total;
}

static void atexit_sfree_all(void)
{
    sfree_all();
}
