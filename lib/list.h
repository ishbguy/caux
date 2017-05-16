/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __LIST_H__
#define __LIST_H__

typedef struct __list_node list_node_t;
typedef void *list_data_t;

extern list_node_t *list_new(void);
extern void list_free(list_node_t * list);
extern list_node_t *list_add_head(list_node_t * list, list_data_t data);
extern list_node_t *list_add_tail(list_node_t * list, list_data_t data);
extern int list_is_empty(list_node_t * list);
extern list_data_t list_del_node(list_node_t * node);
extern list_data_t list_del_tail(list_node_t * list);
extern list_data_t list_del_head(list_node_t * list);
extern int list_replace_node(list_node_t * new, list_node_t * old);
extern int list_move_head_node(list_node_t * list, list_node_t * node);
extern int list_move_tail_node(list_node_t * list, list_node_t * node);
extern int list_rotate_node(list_node_t * list);

#endif /* End of include guard: __LIST_H__ */

/* vim:set ft=c ts=4 sw=4: */
