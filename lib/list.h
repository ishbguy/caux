/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __LIST_H__
#define __LIST_H__

typedef struct __list_node ListNode;
typedef void * ListDataPtr;

extern ListNode *list_new(void);
extern void list_free(ListNode * list);
extern ListNode *list_add_head(ListNode * list, ListDataPtr data);
extern ListNode *list_add_tail(ListNode * list, ListNode * data);
extern int list_is_empty(ListNode * list);
extern ListDataPtr *list_del_node(ListNode * node);
extern ListDataPtr list_del_tail(ListNode * list);
extern ListDataPtr list_del_head(ListNode * list);
extern int list_replace_node(ListNode * new, ListNode * old);
extern int list_move_node(ListNode * list, ListNode * node);
extern int list_move_tail_node(ListNode * list, ListNode * node);
extern int list_rotate_node(ListNode * list);

#endif /* End of include guard: __LIST_H__ */

/* vim:set ft=c ts=4 sw=4: */
