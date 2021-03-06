/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h>
#include "xmacro.h"

typedef struct __list_node list_node_t;
typedef struct __list_node list_t;
typedef void *list_data_t;

struct __list_node {
    list_node_t *prev;
    list_node_t *next;
    list_data_t data;
};

#define LIST_STATIC_INIT(list)   \
    list_t list = {&list, &list, NULL}

#define LIST_FOR_EACH_DIR(pos, list, dir) \
    for ((pos) = (list)->dir; (pos) != (list); pos = (pos)->dir)

#define LIST_FOR_EACH(pos, list) \
    LIST_FOR_EACH_DIR((pos), (list), next)

#define LIST_FOR_EACH_PREV(pos, list) \
    LIST_FOR_EACH_DIR((pos), (list), prev)

#define LIST_FOR_EACH_SAFE_DIR(pos, save, list, dir) \
    for ((pos) = (list)->dir; (save) = (pos)->dir, (pos) != (list); (pos) = (save))

#define LIST_FOR_EACH_SAFE(pos, save, list) \
    LIST_FOR_EACH_SAFE_DIR((pos), (save), (list), next)

#define LIST_FOR_EACH_SAFE_PREV(pos, save, list) \
    LIST_FOR_EACH_SAFE_DIR((pos), (save), (list), prev)

extern list_t *list_new(void);
extern list_t *list_vnew(list_data_t x, ...);
extern list_t *list_copy(list_t * list);
extern list_t *list_from_array(list_data_t * array, size_t size);
extern list_data_t *list_to_array(list_t * list);
extern void list_free(list_t * list);
extern void list_node_free(list_t * list);
extern list_node_t *list_add_head(list_t * list, list_data_t data);
extern list_node_t *list_add_tail(list_t * list, list_data_t data);
extern list_data_t list_del_node(list_node_t * node);
extern list_data_t list_del_tail(list_t * list);
extern list_data_t list_del_head(list_t * list);
extern int list_is_empty(list_t * list);
extern int list_rotate(list_t * list);
extern int list_length(list_t * list);
extern void list_map(list_t * list, void apply(list_data_t * data, void *aux),
                     void *aux);

#define LIST_NEW(list) list = list_new()
#define LIST_VNEW(list, x, ...) list = list_vnew(x, ##__VA_ARGS__)
#define LIST_COPY(dest, src) dest = list_copy((src))
#define LIST_FREE(list) list_free(list), list = NULL

#define LIST_FROM_ARRAY(list, array) \
    list = list_from_array((list_data_t *)(array), NELEM(array))

#define LIST_TO_ARRAY(array, list) array = list_to_array(list)

#endif /* End of include guard: __LIST_H__ */

/* vim:set ft=c ts=4 sw=4: */
