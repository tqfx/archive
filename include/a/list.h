/*!
 @file list.h
 @brief circular doubly linked list implementation.
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#ifndef __A_LIST_H__
#define __A_LIST_H__

#include "def.h"

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
#define a_list_entry(ptr, type, member) container_of(ptr, type, member)
#define a_list_entry_next(ptr, type, member) a_list_entry((ptr)->next, type, member)
#define a_list_entry_prev(ptr, type, member) a_list_entry((ptr)->prev, type, member)

/*!
 @brief iterate over a list
 @param ptr the &a_list_s to use as a loop counter
 @param ctx points to circular doubly linked list
 @param next the direction of loop iteration
  @arg prev the backward iteration
  @arg next the forward iteration
*/
#define a_list_foreach_(ptr, ctx, next) \
    for ((ptr) = (ctx)->next; (ptr) != (ctx); (ptr) = (ptr)->next)
#define a_list_foreach_next(ptr, ctx) a_list_foreach_(ptr, ctx, next)
#define a_list_foreach_prev(ptr, ctx) a_list_foreach_(ptr, ctx, prev)

/*!
 @brief iterate over a list safe against removal of list entry
 @param ptr the &a_list_s to use as a loop counter
 @param pre another &a_list_s to use as temporary storage
 @param ctx points to circular doubly linked list
 @param next the direction of loop iteration
  @arg prev the backward iteration
  @arg next the forward iteration
*/
#define a_list_forsafe_(ptr, pre, ctx, next) \
    for ((ptr) = (ctx)->next, (pre) = (ptr)->next; (ptr) != (ctx); (ptr) = (pre), (pre) = (ptr)->next)
#define a_list_forsafe_next(ptr, pre, ctx) a_list_forsafe_(ptr, pre, ctx, next)
#define a_list_forsafe_prev(ptr, pre, ctx) a_list_forsafe_(ptr, pre, ctx, prev)

/*!
 @brief constructor for circular doubly linked list
 @param[in,out] ctx points to circular doubly linked list
*/
A_INLINE void a_list_ctor(a_list_s *ctx) { ctx->prev = ctx->next = ctx; }
/*!
 @brief initialize for circular doubly linked list
 @param[in,out] ctx points to circular doubly linked list
*/
A_INLINE void a_list_init(a_list_s *ctx) { ctx->prev = ctx->next = ctx; }
/*!
 @brief destructor for circular doubly linked list
 @param[in,out] ctx points to circular doubly linked list
*/
A_INLINE void a_list_dtor(a_list_s *ctx) { ctx->prev = ctx->next = ctx; }

/*!
 @brief test whether a list is null
 @param[in] ctx points to circular doubly linked list
 @return int bool
  @retval 0 non-null
  @retval 1 null
*/
A_INLINE int a_list_null(const a_list_s *ctx) { return ctx->next == ctx; }
/*!
 @brief test whether a list is used
 @param[in] ctx points to circular doubly linked list
 @return int bool
  @retval 0 unused
  @retval 1 used
*/
A_INLINE int a_list_used(const a_list_s *ctx) { return ctx->next != ctx; }

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
A_INLINE void a_list_link(a_list_s *head, a_list_s *tail)
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
A_INLINE void a_list_loop(a_list_s *head, a_list_s *tail)
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
     tail2:next -> head1:addr [color=green]
     head1:prev -> tail2:addr [color=green]
 }
 @enddot
 @param[in,out] head1 the head node of the list1
 @param[in,out] tail1 the tail node of the list1
 @param[in,out] head2 the head node of the list2
 @param[in,out] tail2 the tail node of the list2
*/
A_INLINE void a_list_add_(a_list_s *head1, a_list_s *tail1, a_list_s *head2, a_list_s *tail2)
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
A_INLINE void a_list_add_node(a_list_s *head, a_list_s *tail, a_list_s *node) { a_list_add_(head, tail, node, node); }

/*!
 @brief append a node to a list forward
 @param[in,out] ctx points to circular doubly linked list
 @param[in] node a list node
*/
A_INLINE void a_list_add_next(a_list_s *ctx, a_list_s *node) { a_list_add_(ctx->next, ctx, node, node); }
/*!
 @brief append a node to a list backward
 @param[in,out] ctx points to circular doubly linked list
 @param[in] node a list node
*/
A_INLINE void a_list_add_prev(a_list_s *ctx, a_list_s *node) { a_list_add_(ctx, ctx->prev, node, node); }

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
A_INLINE void a_list_del_(a_list_s *head, a_list_s *tail) { a_list_link(head->prev, tail->next); }
/*!
 @brief delete a node from a list
 @param[in] node a list node
*/
A_INLINE void a_list_del_node(a_list_s *node) { a_list_del_(node, node); }

/*!
 @brief remove a node from a list forward
 @param[in] node a list node
*/
A_INLINE void a_list_del_next(a_list_s *node) { a_list_del_(node->next, node->next); }
/*!
 @brief remove a node from a list backward
 @param[in] node a list node
*/
A_INLINE void a_list_del_prev(a_list_s *node) { a_list_del_(node->prev, node->prev); }

/*!
 @brief moving a list to another list forward
 @param[in,out] ctx points to circular doubly linked list
 @param[in] src source list
*/
A_INLINE void a_list_mov_next(a_list_s *ctx, a_list_s *src) { a_list_add_(ctx->next, ctx, src->next, src->prev); }
/*!
 @brief moving a list to another list backward
 @param[in,out] ctx points to circular doubly linked list
 @param[in] src source list
*/
A_INLINE void a_list_mov_prev(a_list_s *ctx, a_list_s *src) { a_list_add_(ctx, ctx->prev, src->next, src->prev); }

/*!
 @brief rotate a node in the list forward
 @param[in,out] ctx points to circular doubly linked list
*/
A_INLINE void a_list_rot_next(a_list_s *ctx)
{
    a_list_s *node = ctx->prev;
    a_list_del_(node, node);
    a_list_add_next(ctx, node);
}
/*!
 @brief rotate a node in the list backward
 @param[in,out] ctx points to circular doubly linked list
*/
A_INLINE void a_list_rot_prev(a_list_s *ctx)
{
    a_list_s *node = ctx->next;
    a_list_del_(node, node);
    a_list_add_prev(ctx, node);
}

/*! @} A_LIST */

#endif /* __A_LIST_H__ */
