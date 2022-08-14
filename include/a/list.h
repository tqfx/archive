/*!
 @file list.h
 @brief circular doubly linked list implementation.
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_LIST_H__
#define __A_LIST_H__

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_LIST circular doubly linked list
 @{
*/

/*!
 @brief instance structure for circular doubly linked list
*/
typedef struct a_list_s
{
    struct a_list_s *next, *prev;
} a_list_s;

/*!
 @brief access the struct for this entry
 @param ptr the &a_list_s pointer
 @param type the type of the struct this is embedded in
 @param member the name of the a_list_s within the struct
*/
#define a_list_entry(ptr, type, member) a_container_of(ptr, type, member)
#define a_list_entry_next(ptr, type, member) a_list_entry((ptr)->next, type, member)
#define a_list_entry_prev(ptr, type, member) a_list_entry((ptr)->prev, type, member)

/*!
 @brief iterate over a list
 @param it the &a_list_s to use as a loop counter
 @param ctx points to circular doubly linked list
 @param next the direction of loop iteration
  @arg prev the backward iteration
  @arg next the forward iteration
*/
#define a_list_foreach_(it, ctx, next) \
    for (a_list_s *it = (ctx)->next; it != (ctx); it = it->next)
#define a_list_foreach_next(it, ctx) a_list_foreach_(it, ctx, next)
#define a_list_foreach_prev(it, ctx) a_list_foreach_(it, ctx, prev)

/*!
 @brief iterate over a list safe against removal of list entry
 @param it the &a_list_s to use as a loop counter
 @param at another &a_list_s to use as temporary storage
 @param ctx points to circular doubly linked list
 @param next the direction of loop iteration
  @arg prev the backward iteration
  @arg next the forward iteration
*/
#define a_list_forsafe_(it, at, ctx, next) \
    for (a_list_s *it = (ctx)->next, *at = it->next; it != (ctx); it = at, at = it->next)
#define a_list_forsafe_next(it, at, ctx) a_list_forsafe_(it, at, ctx, next)
#define a_list_forsafe_prev(it, at, ctx) a_list_forsafe_(it, at, ctx, prev)

/*!
 @brief constructor for circular doubly linked list
 @param[in,out] ctx points to circular doubly linked list
*/
A_INLINE a_noret_t a_list_ctor(a_list_s *ctx) { ctx->prev = ctx->next = ctx; }

/*!
 @brief initialize for circular doubly linked list
 @param[in,out] ctx points to circular doubly linked list
*/
A_INLINE a_noret_t a_list_init(a_list_s *ctx) { ctx->prev = ctx->next = ctx; }

/*!
 @brief destructor for circular doubly linked list
 @param[in,out] ctx points to circular doubly linked list
*/
A_INLINE a_noret_t a_list_dtor(a_list_s *ctx) { ctx->prev = ctx->next = ctx; }

/*!
 @brief test whether a list is null
 @param[in] ctx points to circular doubly linked list
 @return int bool
  @retval 0 non-null
  @retval 1 null
*/
A_INLINE a_bool_t a_list_null(const a_list_s *ctx) { return ctx->next == ctx; }

/*!
 @brief test whether a list is used
 @param[in] ctx points to circular doubly linked list
 @return int bool
  @retval 0 unused
  @retval 1 used
*/
A_INLINE a_bool_t a_list_used(const a_list_s *ctx) { return ctx->next != ctx; }

/*!
 @brief link head node and tail node
 @dot
 digraph a_list_link {
     node[shape="record"]
     nodehead[label="{<prev>prev|<addr>head|<next>next}"]
     nodetail[label="{<prev>prev|<addr>tail|<next>next}"]
     nodehead:next -> nodetail:addr [color=green]
     nodetail:prev -> nodehead:addr [color=green]
     nodehead -> "..." -> nodetail
 }
 @enddot
 @param[in,out] head the head node of a list
 @param[in,out] tail the tail node of a list
*/
A_INLINE a_noret_t a_list_link(a_list_s *head, a_list_s *tail)
{
    head->next = tail;
    tail->prev = head;
}

/*!
 @brief loop head node to tail node
 @dot
 digraph a_list_loop {
     node[shape="record"]
     nodehead[label="{<prev>prev|<addr>head|<next>next}"]
     nodetail[label="{<prev>prev|<addr>tail|<next>next}"]
     nodehead:prev -> nodetail:addr [color=green]
     nodetail:next -> nodehead:addr [color=green]
     nodehead -> "..." -> nodetail
 }
 @enddot
 @param[in,out] head the head node of a list
 @param[in,out] tail the tail node of a list
*/
A_INLINE a_noret_t a_list_loop(a_list_s *head, a_list_s *tail)
{
    head->prev = tail;
    tail->next = head;
}

/*!
 @brief connect list1 and list2
 @dot
 digraph a_list_add_ {
     node[shape="record"]
     subgraph cluster0 {
         head1[label="<prev>prev|<addr>head1|<next>next"]
         tail1[label="<prev>prev|<addr>tail1|<next>next"]
     }
     subgraph cluster1 {
         head2[label="<prev>prev|<addr>head2|<next>next"]
         tail2[label="<prev>prev|<addr>tail2|<next>next"]
     }
     tail1:next -> head2:addr [color=green]
     head2:prev -> tail1:addr [color=green]
     tail2:next -> head1:addr [color=blue]
     head1:prev -> tail2:addr [color=blue]
 }
 @enddot
 @param[in,out] head1 the head node of the list1
 @param[in,out] tail1 the tail node of the list1
 @param[in,out] head2 the head node of the list2
 @param[in,out] tail2 the tail node of the list2
*/
A_INLINE a_noret_t a_list_add_(a_list_s *head1, a_list_s *tail1, a_list_s *head2, a_list_s *tail2)
{
    a_list_link(tail1, head2);
    a_list_link(tail2, head1);
}

/*!
 @brief insert a node to a list
 @param[in,out] head the head node of a list
 @param[in,out] tail the tail node of a list
 @param[in] node a list node
*/
A_INLINE a_noret_t a_list_add_node(a_list_s *head, a_list_s *tail, a_list_s *node)
{
    a_list_add_(head, tail, node, node);
}

/*!
 @brief append a node to a list forward
 @param[in,out] ctx points to circular doubly linked list
 @param[in] node a list node
*/
A_INLINE a_noret_t a_list_add_next(a_list_s *ctx, a_list_s *node)
{
    a_list_add_(ctx->next, ctx, node, node);
}

/*!
 @brief append a node to a list backward
 @param[in,out] ctx points to circular doubly linked list
 @param[in] node a list node
*/
A_INLINE a_noret_t a_list_add_prev(a_list_s *ctx, a_list_s *node)
{
    a_list_add_(ctx, ctx->prev, node, node);
}

/*!
 @brief delete a section of a list
 @dot
 digraph a_list_del_ {
     node[shape="record"]
     head[label="<prev>prev|<addr>head-prev|<next>next"]
     tail[label="<prev>prev|<addr>tail-next|<next>next"]
     nodehead[label="<prev>prev|<addr>head|<next>next"]
     nodetail[label="<prev>prev|<addr>tail|<next>next"]
     head:addr -> nodehead:addr -> "..." -> nodetail:addr -> tail:addr [dir=both]
     head:next -> tail:addr [color=green]
     tail:prev -> head:addr [color=green]
 }
 @enddot
 @param[in,out] head the head node of a list
 @param[in,out] tail the tail node of a list
*/
A_INLINE a_noret_t a_list_del_(a_list_s *head, a_list_s *tail)
{
    a_list_link(head->prev, tail->next);
}

/*!
 @brief delete a node from a list
 @param[in] node a list node
*/
A_INLINE a_noret_t a_list_del_node(a_list_s *node) { a_list_del_(node, node); }

/*!
 @brief remove a node from a list forward
 @param[in] node a list node
*/
A_INLINE a_noret_t a_list_del_next(a_list_s *node) { a_list_del_(node->next, node->next); }

/*!
 @brief remove a node from a list backward
 @param[in] node a list node
*/
A_INLINE a_noret_t a_list_del_prev(a_list_s *node) { a_list_del_(node->prev, node->prev); }

/*!
 @brief moving a list to another list forward
 @param[in,out] ctx points to circular doubly linked list
 @param[in] obj source list
*/
A_INLINE a_noret_t a_list_mov_next(a_list_s *ctx, a_list_s *obj)
{
    a_list_add_(ctx->next, ctx, obj->next, obj->prev);
}

/*!
 @brief moving a list to another list backward
 @param[in,out] ctx points to circular doubly linked list
 @param[in] obj source list
*/
A_INLINE a_noret_t a_list_mov_prev(a_list_s *ctx, a_list_s *obj)
{
    a_list_add_(ctx, ctx->prev, obj->next, obj->prev);
}

/*!
 @brief rotate a node in the list forward
 @param[in,out] ctx points to circular doubly linked list
*/
A_INLINE a_noret_t a_list_rot_next(a_list_s *ctx)
{
    a_list_s *node = ctx->prev;
    a_list_del_(node, node);
    a_list_add_next(ctx, node);
}

/*!
 @brief rotate a node in the list backward
 @param[in,out] ctx points to circular doubly linked list
*/
A_INLINE a_noret_t a_list_rot_prev(a_list_s *ctx)
{
    a_list_s *node = ctx->next;
    a_list_del_(node, node);
    a_list_add_prev(ctx, node);
}

/*!
 @brief shift a section of one list to a section of another list
 @dot
 digraph a_list_shift_ {
     node[shape="record"]
     subgraph cluster0 {
         1[label="<prev>prev|<head>head|<tail>tail|<next>next"]
     }
     subgraph cluster1 {
         2[label="<prev>prev|<head>head|<tail>tail|<next>next"]
     }
     1:prev -> 2:head [color=green]
     2:tail -> 1:next [color=green]
 }
 @enddot
 @param[in,out] head1 the head node of the list1
 @param[in,out] tail1 the tail node of the list1
 @param[in,out] head2 the head node of the list2
 @param[in,out] tail2 the tail node of the list2
*/
A_INLINE a_noret_t a_list_shift_(a_list_s *head1, a_list_s *tail1, a_list_s *head2, a_list_s *tail2)
{
    a_list_add_(tail1->next, head1->prev, head2, tail2);
}

/*!
 @brief shift the node rhs to the node lhs
 @param[in,out] lhs the old node
 @param[in,out] rhs the new node
*/
A_INLINE a_noret_t a_list_shift_node(a_list_s *lhs, a_list_s *rhs)
{
    a_list_shift_(lhs, lhs, rhs, rhs);
}

/*!
 @brief swap a section of one list and a section of another list
 @dot
 digraph a_list_swap_ {
     node[shape="record"]
     subgraph cluster0 {
         1[label="<prev>prev|<head>head|<tail>tail|<next>next"]
     }
     subgraph cluster1 {
         2[label="<prev>prev|<head>head|<tail>tail|<next>next"]
     }
     1:prev -> 2:head [color=green]
     2:tail -> 1:next [color=green]
     2:prev -> 1:head [color=blue]
     1:tail -> 2:next [color=blue]
 }
 @enddot
 @param[in,out] head1 the head node of the list1
 @param[in,out] tail1 the tail node of the list1
 @param[in,out] head2 the head node of the list2
 @param[in,out] tail2 the tail node of the list2
*/
A_INLINE a_noret_t a_list_swap_(a_list_s *head1, a_list_s *tail1, a_list_s *head2, a_list_s *tail2)
{
    a_list_s *head = tail2->next, *tail = head2->prev;
    a_list_add_(tail1->next, head1->prev, head2, tail2);
    a_list_add_(head, tail, head1, tail1);
}

/*!
 @brief swap the node lhs and the node rhs
 @param[in,out] lhs a node on the left
 @param[in,out] rhs a node on the right
*/
A_INLINE a_noret_t a_list_swap_node(a_list_s *lhs, a_list_s *rhs)
{
    a_list_swap_(lhs, lhs, rhs, rhs);
}

/* inline function for generic */
A_INLINE a_noret_t a_list_ctor_(a_vptr_t vctx) { a_list_ctor(a_cast_s(a_list_s *, vctx)); }
A_INLINE a_noret_t a_list_dtor_(a_vptr_t vctx) { a_list_dtor(a_cast_s(a_list_s *, vctx)); }

/*! @} A_LIST */

#endif /* __A_LIST_H__ */
