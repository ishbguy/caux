/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved
 */

#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "list.h"

#define NEW(ptr) ptr = malloc(sizeof(*(ptr)))
#define FREE(ptr) free((ptr)), ptr = NULL

enum {
    FLASE = 0,
    TRUE = 1,
    FAILED = 0,
    SUCCESS = 1,
};

static inline void __list_add(list_node_t * prev, list_node_t * curr,
                              list_node_t * next);
static inline void __list_add_head(list_t * list, list_node_t * node);
static inline void __list_add_tail(list_t * list, list_node_t * node);
static inline void __list_del(list_node_t * prev, list_node_t * next);
static inline void __list_del_node(list_node_t * node);
static list_data_t list_del_node(list_node_t * node);
static inline void __list_repalce_node(list_node_t * new_node,
                                       list_node_t * old_node);
static inline int __list_is_empty(list_t * list);

list_t *list_new(void)
{
    list_t *list;

    NEW(list);
    assert(list);
    list->prev = list;
    list->next = list;
    list->data = NULL;
    return list;
}

list_t *list_vnew(list_data_t x, ...)
{
    va_list ap;
    list_t *list;
    list_node_t *tmp;

    va_start(ap, x);
    list = list_new();
    assert(list);
    for (; x; x = va_arg(ap, list_data_t)) {
        NEW(tmp);
        tmp->data = x;
        __list_add_tail(list, tmp);
    }
    va_end(ap);
    return list;
}

list_t *list_copy(list_t * list)
{
    list_t *new_list;
    list_node_t *pos, *tmp;

    if (list == NULL)
        return NULL;
    if (__list_is_empty(list))
        return NULL;
    new_list = list_new();
    assert(new_list);
    LIST_FOR_EACH(pos, list) {
        NEW(tmp);
        assert(tmp);
        tmp->data = pos->data;
        __list_add_tail(new_list, tmp);
    }
    return new_list;
}

list_t *list_from_array(list_data_t * array, size_t size)
{
    list_t *list;
    list_node_t *tmp;
    int i;

    if (array == NULL || size == 0)
        return NULL;
    list = list_new();
    assert(list);
    for (i = 0; i < size; i++) {
        NEW(tmp);
        tmp->data = *array++;
        __list_add_tail(list, tmp);
    }
    return list;
}

list_data_t *list_to_array(list_t * list)
{
    list_node_t *pos;
    list_data_t *array;
    int len;

    if (list == NULL)
        return NULL;
    if (__list_is_empty(list))
        return NULL;
    len = list_length(list);
    array = malloc(sizeof(list_data_t) * len);
    assert(array);
    LIST_FOR_EACH(pos, list)
        * array++ = pos->data;
    return array;
}

void list_free_node(list_t * list)
{
    list_node_t *pos, *save;

    if (list)
        LIST_FOR_EACH_SAFE(pos, save, list)
            list_del_node(pos);
}

void list_free(list_t ** list)
{
    if (list) {
        list_free_node(*list);
        FREE(*list);
    }
}

static inline void __list_add(list_node_t * prev, list_node_t * curr,
                              list_node_t * next)
{
    curr->prev = prev;
    curr->next = next;
    prev->next = curr;
    next->prev = curr;
}

static inline void __list_add_head(list_t * list, list_node_t * node)
{
    __list_add(list, node, list->next);
}

list_node_t *list_add_head(list_t * list, list_data_t data)
{
    list_node_t *node;

    assert(list && data);

    NEW(node);
    assert(node);
    __list_add_head(list, node);
    node->data = data;
    return node;
}

static inline void __list_add_tail(list_t * list, list_node_t * node)
{
    __list_add(list->prev, node, list);
}

list_node_t *list_add_tail(list_t * list, list_data_t data)
{
    list_node_t *node;

    assert(list && data);

    NEW(node);
    assert(node);
    __list_add_tail(list, node);
    node->data = data;
    return node;
}

static inline void __list_del(list_node_t * prev, list_node_t * next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void __list_del_node(list_node_t * node)
{
    __list_del(node->prev, node->next);
}

static list_data_t list_del_node(list_node_t * node)
{
    list_data_t data;

    assert(node);

    data = node->data;
    __list_del_node(node);
    node->prev = NULL;
    node->next = NULL;
    FREE(node);
    return data;
}

list_data_t list_del_tail(list_t * list)
{
    list_node_t *tail;

    assert(list);

    if (__list_is_empty(list))
        return NULL;
    tail = list->prev;
    return list_del_node(tail);
}

list_data_t list_del_head(list_t * list)
{
    list_node_t *head;

    assert(list);

    if (__list_is_empty(list))
        return NULL;
    head = list->next;
    return list_del_node(head);
}

static inline void __list_repalce_node(list_node_t * new_node,
                                       list_node_t * old_node)
{
    new_node->prev = old_node->prev;
    new_node->prev->next = new_node;
    new_node->next = old_node->next;
    new_node->next->prev = new_node;
}

int list_replace_node(list_node_t * new_node, list_node_t * old_node)
{
    assert(new_node && old_node);

    __list_repalce_node(new_node, old_node);
    return SUCCESS;
}

int list_move_head_node(list_t * list, list_node_t * node)
{
    assert(list && node);

    if (__list_is_empty(list))
        return FAILED;
    __list_del_node(node);
    __list_add_head(list, node);
    return SUCCESS;
}

int list_move_tail_node(list_t * list, list_node_t * node)
{
    assert(list && node);

    if (__list_is_empty(list))
        return FAILED;
    __list_del_node(node);
    __list_add_tail(list, node);
    return SUCCESS;
}

static inline int __list_is_empty(list_t * list)
{
    return (list->prev == list->next && list->prev == list);
}

int list_is_empty(list_t * list)
{
    if (list)
        return __list_is_empty(list);
    return FLASE;
}

int list_rotate(list_t * list)
{
    list_node_t *head;

    assert(list);

    if (__list_is_empty(list))
        return FAILED;
    head = list->next;
    __list_del_node(head);
    __list_add_tail(list, head);
    return SUCCESS;
}

int list_length(list_t * list)
{
    int count;
    list_node_t *pos;

    count = 0;
    if (list) {
        LIST_FOR_EACH(pos, list)
            count++;
    }
    return count;
}

void list_map(list_t * list, void apply(list_data_t * data, void *aux),
              void *aux)
{
    list_node_t *pos;

    if (list) {
        LIST_FOR_EACH(pos, list)
            apply(&(pos->data), aux);
    }
}

/* vim:set ft=c ts=4 sw=4: */
