/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h>

typedef struct __list_node list_node_t;
typedef struct __list_node list_t;
typedef void *list_data_t;

extern list_t *list_new(void);
extern list_t *list_vnew(list_data_t x, ...);
extern list_t *list_copy(list_t * list);
extern list_t *list_from_array(list_data_t * array, size_t size);
extern list_data_t *list_to_array(list_t * list);
extern void list_free(list_t * list);
extern void list_free_node(list_t * list);
extern list_node_t *list_add_head(list_t * list, list_data_t data);
extern list_node_t *list_add_tail(list_t * list, list_data_t data);
extern list_data_t list_del_tail(list_t * list);
extern list_data_t list_del_head(list_t * list);
extern int list_is_empty(list_t * list);
extern int list_rotate(list_t * list);
extern int list_length(list_t * list);
extern void list_map(list_t * list, void apply(list_data_t * data, void *aux),
                     void *aux);

#endif /* End of include guard: __LIST_H__ */

/* vim:set ft=c ts=4 sw=4: */
