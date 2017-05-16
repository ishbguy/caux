/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved
 */

#include "list.h"
#include "smalloc.h"

enum {
    FLASE = 0,
    TRUE = 1,
    NULL_PTR = -1,
    FAILED = 0,
    SUCCESS = 1,
};

struct __list_node {
    ListNode *prev;
    ListNode *next;
    ListDataPtr data;
};

#define LIST_INIT(name)   \
    const ListNode name = {&name, &name, NULL}

ListNode *list_new(void)
{
    ListNode *list = (ListNode *)malloc(sizeof(ListNode));
    if (list == NULL)
        return NULL;
    list->prev = list;
    list->next = list;
    list->data = NULL;
    return list;
}

void list_free(ListNode *list)
{
    if (list == NULL)
        return;
    free(list);
}

static inline void __list_add(ListNode *prev, ListNode *curr, ListNode *next)
{
    curr->prev = prev;
    curr->next = next;
    prev->next = curr;
    next->prev = curr;
}

static inline void __list_add_head(ListNode *list, ListNode *new)
{
    __list_add(list, new, list->next);
}

ListNode *list_add_head(ListNode *list, ListDataPtr data)
{
    if (list == NULL || data == NULL)
        return NULL;

    /* Allocate memory for new node. */
    ListNode *new = (ListNode *)malloc(sizeof(ListNode));
    if (new == NULL)
        return NULL;
    __list_add_head(list, new);
    new->data = data;
    return new;
}

static inline void __list_add_tail(ListNode *list, ListNode *new)
{
    __list_add(list->prev, new, list);
}

ListNode *list_add_tail(ListNode *list, ListNode *data)
{
    if (list == NULL || data == NULL)
        return NULL;

    /* Allocate memory for new node. */
    ListNode *new = (ListNode *)malloc(sizeof(ListNode));
    if (new == NULL)
        return NULL;
    __list_add_tail(list, new);
    new->data = data;
    return new;
}

static inline void __list_del(ListNode *prev, ListNode *next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void __list_del_node(ListNode *node)
{
    __list_del(node->prev, node->next);
}

static inline int __list_is_empty(ListNode *list)
{
    return (list->prev == list->next && list->prev == list);
}

int list_is_empty(ListNode *list)
{
    if (list == NULL)
        return NULL_PTR;
    return __list_is_empty(list);
}

ListDataPtr *list_del_node(ListNode *node)
{
    if (node == NULL)
        return NULL;
    ListDataPtr data = node->data;
    __list_del_node(node);
    node->prev = NULL;
    node->next = NULL;
    free(node);
    return data;
}

ListDataPtr list_del_tail(ListNode *list)
{
    if (list == NULL || __list_is_empty(list))
        return NULL;
    ListNode *tail = list->prev;
    return list_del_node(tail);
}

ListDataPtr list_del_head(ListNode *list)
{
    if (list == NULL)
        return FAILED;
    if (__list_is_empty(list))
        return FAILED;
    ListNode *head = list->next;
    return list_del_node(head);
}

static inline void __list_repalce_node(ListNode *new, ListNode *old)
{
    new->prev = old->prev;
    new->prev->next = new;
    new->next = old->next;
    new->next->prev = new;
}

int list_replace_node(ListNode *new, ListNode *old)
{
    if (new == NULL || old == NULL)
        return FAILED;
    __list_repalce_node(new, old);
    return SUCCESS;
}

int list_move_node(ListNode *list, ListNode *node)
{
    if (node == NULL || list == NULL)
        return FAILED;
    __list_del_node(node);
    __list_add_head(list, node);
    return SUCCESS;
}

int list_move_tail_node(ListNode *list, ListNode *node)
{
    if (node == NULL || list == NULL)
        return FAILED;
    __list_del_node(node);
    __list_add_tail(list, node);
    return SUCCESS;
}

int list_rotate_node(ListNode *list)
{
    if (list == NULL)
        return FAILED;
    if (__list_is_empty(list))
        return FAILED;
    ListNode *head = list->next;
    __list_del_node(head);
    __list_add_tail(list, head);
    return SUCCESS;
}

static inline void __list_cut(ListNode *list, ListNode *new_list,
        ListNode *prev, ListNode *next)
{
    ListNode *tail = list->prev;
    list->prev = prev;
    prev->next = list;
    new_list->prev = tail;
    new_list->next = next;
    next->prev = new_list;
    tail->next = new_list;
}

/* vim:set ft=c ts=4 sw=4: */
