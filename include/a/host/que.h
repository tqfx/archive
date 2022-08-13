/*!
 @file que.h
 @brief basic queue library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_HOST_QUE_H__
#define __A_HOST_QUE_H__

#include "../list.h"

#if __STDC_HOSTED__

#include <stdlib.h>

/*!
 @ingroup A
 @addtogroup A_QUE basic queue library
 @{
*/

/*!
 @brief instance structure for basic queue node
*/
typedef struct a_que_node_s
{
    a_list_s __node[1];
    a_vptr_t __vptr;
} a_que_node_s;

/*!
 @brief instance structure for basic queue
*/
typedef struct a_que_s
{
    a_que_node_s **__ptr;
    a_list_s __head[1];
    a_size_t __size;
    a_size_t __num;
    a_size_t __mem;
    a_size_t __cnt;
} a_que_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

a_que_s *a_que_new(a_size_t size);
a_noret_t a_que_die(a_que_s *ctx, a_noret_t (*dtor)(a_vptr_t));

a_noret_t a_que_ctor(a_que_s *ctx, a_size_t size);
a_noret_t a_que_dtor(a_que_s *ctx, a_noret_t (*dtor)(a_vptr_t));

a_que_s *a_que_move(a_que_s *ctx, a_que_s *obj);

a_int_t a_que_set(a_que_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t));

a_noret_t a_que_drop(a_que_s *ctx, a_noret_t (*dtor)(a_vptr_t));

a_vptr_t a_que_push_fore(a_que_s *ctx);
a_vptr_t a_que_push_back(a_que_s *ctx);

a_vptr_t a_que_pull_fore(a_que_s *ctx);
a_vptr_t a_que_pull_back(a_que_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#if !defined __cplusplus
#define a_que_foreach(T, it, ctx)                                                                   \
    for (T *it = (T *)(ctx)->__head->next, *it_ = (T *)((a_list_s *)it)->next;                      \
         (a_list_s *)it != (ctx)->__head ? ((void)(it = (T *)((a_que_node_s *)it)->__vptr), 1) : 0; \
         it = it_, it_ = (T *)((a_list_s *)it)->next)
#else /* !__cplusplus */
#define a_que_foreach(T, it, ctx)                                                                    \
    for (T *it = reinterpret_cast<T *>((ctx)->__head->next),                                         \
           *it_ = reinterpret_cast<T *>(reinterpret_cast<a_list_s *>(it)->next);                     \
         reinterpret_cast<a_list_s *>(it) != (ctx)->__head                                           \
             ? ((void)(it = reinterpret_cast<T *>(reinterpret_cast<a_que_node_s *>(it)->__vptr)), 1) \
             : 0;                                                                                    \
         it = it_, it_ = reinterpret_cast<T *>(reinterpret_cast<a_list_s *>(it)->next))
#endif /* __cplusplus */

#if !defined __cplusplus
#define a_que_foreach_reverse(T, it, ctx)                                                           \
    for (T *it = (T *)(ctx)->__head->prev, *it_ = (T *)((a_list_s *)it)->prev;                      \
         (a_list_s *)it != (ctx)->__head ? ((void)(it = (T *)((a_que_node_s *)it)->__vptr), 1) : 0; \
         it = it_, it_ = (T *)((a_list_s *)it)->prev)
#else /* !__cplusplus */
#define a_que_foreach_reverse(T, it, ctx)                                                            \
    for (T *it = reinterpret_cast<T *>((ctx)->__head->prev),                                         \
           *it_ = reinterpret_cast<T *>(reinterpret_cast<a_list_s *>(it)->prev);                     \
         reinterpret_cast<a_list_s *>(it) != (ctx)->__head                                           \
             ? ((void)(it = reinterpret_cast<T *>(reinterpret_cast<a_que_node_s *>(it)->__vptr)), 1) \
             : 0;                                                                                    \
         it = it_, it_ = reinterpret_cast<T *>(reinterpret_cast<a_list_s *>(it)->prev))
#endif /* __cplusplus */

/*! @} A_QUE */

#endif /* __STDC_HOSTED__ */

#endif /* __A_HOST_QUE_H__ */
