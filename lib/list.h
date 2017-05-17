/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __LIST_H__
#define __LIST_H__

typedef struct __list_node list_node_t;
typedef struct __list_node list_t;
typedef void *list_data_t;

#define LIST_INIT(name)   \
    const list_t name = {&name, &name, NULL}

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
extern void list_free(list_t * list);
extern void list_free_node(list_t * list);
extern list_t *list_add_head(list_t * list, list_data_t data);
extern list_t *list_add_tail(list_t * list, list_data_t data);
extern int list_is_empty(list_t * list);
extern list_data_t list_del_tail(list_t * list);
extern list_data_t list_del_head(list_t * list);
extern int list_rotate(list_t * list);
extern int list_length(list_t * list);
extern list_t *list_copy(list_t * list);
extern void list_map(list_t * list, void apply(void **data, void *aux),
                     void *aux);
extern list_data_t *list_to_array(list_t * list);
extern list_t *list_from_array(list_data_t * array, size_t size);
extern list_t *list_vnew(list_data_t x, ...);

#endif /* End of include guard: __LIST_H__ */

/* vim:set ft=c ts=4 sw=4: */
