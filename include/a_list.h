/*!
 @file a_list.h
 @brief Circular double-linked list.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_LIST_H__
#define __A_LIST_H__

#include "liba.h"

typedef struct a_list_s
{
    struct a_list_s *next, *last;
} a_list_s;

#define A_LIST_HEAD_INIT(name) \
    {                          \
        &(name), &(name)       \
    }
#define A_LIST_HEAD(name) a_list_s name[1] = {{name, name}}

#define a_list_entry(ptr, type, member)      containerof(ptr, type, member)
#define a_list_entry_next(ptr, type, member) a_list_entry((ptr)->next, type, member)
#define a_list_entry_last(ptr, type, member) a_list_entry((ptr)->last, type, member)

#define a_list_for_(p, list, next) \
    for ((p) = (list)->next; (p) != (list); (p) = (p)->next)
#define a_list_for_next(p, list) a_list_for_(p, list, next)
#define a_list_for_last(p, list) a_list_for_(p, list, last)

#define a_list_forsafe_(p, n, list, next) \
    for ((p) = (list)->next, (n) = (p)->next; (p) != (list); (p) = (n), (n) = (p)->next)
#define a_list_forsafe_next(p, n, list) a_list_forsafe_(p, n, list, next)
#define a_list_forsafe_last(p, n, list) a_list_forsafe_(p, n, list, last)

__NONNULL_ALL
__STATIC_INLINE
void a_list_ctor(a_list_s *list)
{
    list->next = list->last = list;
}
__STATIC_INLINE
int a_list_empty(const a_list_s *list)
{
    return list && ((list == list->next) || (list == list->last));
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_link(a_list_s *head, a_list_s *tail)
{
    /*!
    \dot
    digraph a_list_link {
        node[shape="record"]
        nodehead[label="{<last>last|<addr>head|<next>next}"]
        nodetail[label="{<last>last|<addr>tail|<next>next}"]
        nodehead:next -> nodetail:addr [color=green]
        nodetail:last -> nodehead:addr [color=green]
        nodehead -> "..." -> nodetail
    }
    \enddot
    */
    head->next = tail;
    tail->last = head;
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_loop(a_list_s *head, a_list_s *tail)
{
    /*!
    \dot
    digraph a_list_loop {
        node[shape="record"]
        nodehead[label="{<last>last|<addr>head|<next>next}"]
        nodetail[label="{<last>last|<addr>tail|<next>next}"]
        nodehead:last -> nodetail:addr [color=green]
        nodetail:next -> nodehead:addr [color=green]
        nodehead -> "..." -> nodetail
    }
    \enddot
    */
    head->last = tail;
    tail->next = head;
}

__NONNULL_ALL
__STATIC_INLINE
void a_list_add_(a_list_s *head1, a_list_s *tail1,
                 a_list_s *head2, a_list_s *tail2)
{
    /*!
    \dot
    digraph a_list_add_ {
        node[shape="record"]
        subgraph cluster0 {
            head1[label="<last>last|<addr>head1|<next>next"]
            tail1[label="<last>last|<addr>tail1|<next>next"]
        }
        subgraph cluster1 {
            head2[label="<last>last|<addr>head2|<next>next"]
            tail2[label="<last>last|<addr>tail2|<next>next"]
        }
        tail1:next -> head2:addr [color=green]
        head2:last -> tail1:addr [color=green]
        tail2:next -> head1:addr [color=green]
        head1:last -> tail2:addr [color=green]
    }
    \enddot
    */
    a_list_link(tail1, head2);
    a_list_link(tail2, head1);
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_add_node(a_list_s *head, a_list_s *tail, a_list_s *node)
{
    a_list_add_(head, tail, node, node);
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_add_next(a_list_s *list, a_list_s *node)
{
    a_list_add_(list->next, list, node, node);
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_add_last(a_list_s *list, a_list_s *node)
{
    a_list_add_(list, list->last, node, node);
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_mov_next(a_list_s *list1, a_list_s *list2)
{
    a_list_add_(list1->next, list1, list2->next, list2->last);
    a_list_loop(list2, list2);
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_mov_last(a_list_s *list1, a_list_s *list2)
{
    a_list_add_(list1, list1->last, list2->next, list2->last);
    a_list_loop(list2, list2);
}

__NONNULL_ALL
__STATIC_INLINE
void a_list_del_(a_list_s *head, a_list_s *tail)
{
    /*!
    \dot
    digraph a_list_del_ {
        node[shape="record"]
        head[label="<last>last|<addr>head-last|<next>next"]
        tail[label="<last>last|<addr>tail-next|<next>next"]
        nodehead[label="<last>last|<addr>head|<next>next"]
        nodetail[label="<last>last|<addr>tail|<next>next"]
        head:addr -> nodehead:addr -> "..." -> nodetail:addr -> tail:addr [dir=both]
        head:next -> tail:addr [color=green]
        tail:last -> head:addr [color=green]
    }
    \enddot
    */
    a_list_link(head->last, tail->next);
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_del_node(a_list_s *node)
{
    a_list_del_(node, node);
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_rot_last(a_list_s *list)
{
    a_list_s *node = list->next;
    a_list_del_(node, node);
    a_list_add_last(list, node);
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_rot_next(a_list_s *list)
{
    a_list_s *node = list->last;
    a_list_del_(node, node);
    a_list_add_next(list, node);
}

__NONNULL_ALL
__STATIC_INLINE
void a_list_replace_(a_list_s *head1, a_list_s *tail1,
                     a_list_s *head2, a_list_s *tail2)
{
    a_list_add_(tail1->next, head1->last, head2, tail2);
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_replace_node(a_list_s *lold, a_list_s *lnew)
{
    (lold != lnew) ? a_list_replace_(lold, lold, lnew, lnew) : (void)0;
}

__NONNULL_ALL
__STATIC_INLINE
void a_list_swap_(a_list_s *head1, a_list_s *tail1,
                  a_list_s *head2, a_list_s *tail2)
{
    a_list_s *head = tail2->next, *tail = head2->last;
    a_list_add_(tail1->next, head1->last, head2, tail2);
    a_list_add_(head, tail, head1, tail1);
}
__NONNULL_ALL
__STATIC_INLINE
void a_list_swap_node(a_list_s *node1, a_list_s *node2)
{
    a_list_swap_(node1, node1, node2, node2);
}

/* Enddef to prevent recursive inclusion */
#endif /* __A_LIST_H__ */
