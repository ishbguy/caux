/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved
 */

#include <stdlib.h>
#include "list.h"

enum {
    FLASE = 0,
    TRUE = 1,
    NULL_PTR = -1,
    FAILED = 0,
    SUCCESS = 1,
};

struct __list_node {
    list_node_t *prev;
    list_node_t *next;
    list_data_t data;
};

list_t *list_new(void)
{
    list_t *list = (list_t *) malloc(sizeof(list_node_t));

    if (list == NULL)
        return NULL;
    list->prev = list;
    list->next = list;
    list->data = NULL;
    return list;
}

void list_free(list_t * list)
{
    if (list == NULL)
        return;
    free(list);
}

static inline void __list_add(list_node_t * prev, list_node_t * curr,
                              list_node_t * next)
{
    curr->prev = prev;
    curr->next = next;
    prev->next = curr;
    next->prev = curr;
}

static inline void __list_add_head(list_t * list, list_node_t * new)
{
    __list_add(list, new, list->next);
}

list_t *list_add_head(list_t * list, list_data_t data)
{
    if (list == NULL || data == NULL)
        return NULL;

    /*
     * Allocate memory for new node. 
     */
    list_node_t *new = (list_node_t *) malloc(sizeof(list_node_t));

    if (new == NULL)
        return NULL;
    __list_add_head(list, new);
    new->data = data;
    return new;
}

static inline void __list_add_tail(list_t * list, list_node_t * new)
{
    __list_add(list->prev, new, list);
}

list_t *list_add_tail(list_t * list, list_data_t data)
{
    if (list == NULL || data == NULL)
        return NULL;

    /*
     * Allocate memory for new node. 
     */
    list_node_t *new = (list_node_t *) malloc(sizeof(list_node_t));

    if (new == NULL)
        return NULL;
    __list_add_tail(list, new);
    new->data = data;
    return new;
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

static inline int __list_is_empty(list_t * list)
{
    return (list->prev == list->next && list->prev == list);
}

int list_is_empty(list_t * list)
{
    if (list == NULL)
        return NULL_PTR;
    return __list_is_empty(list);
}

list_data_t list_del_node(list_node_t * node)
{
    if (node == NULL)
        return NULL;
    list_data_t data = node->data;

    __list_del_node(node);
    node->prev = NULL;
    node->next = NULL;
    free(node);
    return data;
}

list_data_t list_del_tail(list_t * list)
{
    if (list == NULL || __list_is_empty(list))
        return NULL;
    list_node_t *tail = list->prev;

    return list_del_node(tail);
}

list_data_t list_del_head(list_t * list)
{
    if (list == NULL)
        return FAILED;
    if (__list_is_empty(list))
        return FAILED;
    list_node_t *head = list->next;

    return list_del_node(head);
}

static inline void __list_repalce_node(list_node_t * new, list_node_t * old)
{
    new->prev = old->prev;
    new->prev->next = new;
    new->next = old->next;
    new->next->prev = new;
}

int list_replace_node(list_node_t * new, list_node_t * old)
{
    if (new == NULL || old == NULL)
        return FAILED;
    __list_repalce_node(new, old);
    return SUCCESS;
}

int list_move_head_node(list_t * list, list_node_t * node)
{
    if (node == NULL || list == NULL)
        return FAILED;
    __list_del_node(node);
    __list_add_head(list, node);
    return SUCCESS;
}

int list_move_tail_node(list_t * list, list_node_t * node)
{
    if (node == NULL || list == NULL)
        return FAILED;
    __list_del_node(node);
    __list_add_tail(list, node);
    return SUCCESS;
}

int list_rotate_node(list_t * list)
{
    if (list == NULL)
        return FAILED;
    if (__list_is_empty(list))
        return FAILED;
    list_node_t *head = list->next;

    __list_del_node(head);
    __list_add_tail(list, head);
    return SUCCESS;
}

static inline void __list_cut(list_t * list, list_node_t * new_list,
                              list_node_t * prev, list_node_t * next)
{
    list_node_t *tail = list->prev;

    list->prev = prev;
    prev->next = list;
    new_list->prev = tail;
    new_list->next = next;
    next->prev = new_list;
    tail->next = new_list;
}

/* vim:set ft=c ts=4 sw=4: */
