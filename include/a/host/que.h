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
    a_list_s __node[1]; /*!< element node */
    a_vptr_t __vptr; /*!< element data */
} a_que_node_s;

/*!
 @brief reinterpret a pointer to T into a pointer to a_list_s
 @param[in] ctx points to an instance of T
 @return a pointer to a_list_s
*/
A_INLINE a_list_s *a_que_tolist(a_vptr_t ctx) { return a_cast_s(a_list_s *, ctx); }

/*!
 @brief reinterpret a pointer to T into a pointer to a_que_node_s
 @param[in] ctx points to an instance of T
 @return a pointer to a_que_node_s
*/
A_INLINE a_que_node_s *a_que_tonode(a_vptr_t ctx) { return a_cast_s(a_que_node_s *, ctx); }

/*!
 @brief instance structure for basic queue
*/
typedef struct a_que_s
{
    a_que_node_s **__ptr; /*!< mempool vector */
    a_list_s __head[1]; /*!< element head */
    a_size_t __size; /*!< element data */
    a_size_t __num; /*!< element number */
    a_size_t __cur; /*!< mempool cursor */
    a_size_t __mem; /*!< mempool memory */
} a_que_s;

/*!
 @brief access size of a element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
*/
A_INLINE a_size_t a_que_get(const a_que_s *ctx) { return ctx->__size; }

/*!
 @brief access number of element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
*/
A_INLINE a_size_t a_que_num(const a_que_s *ctx) { return ctx->__num; }

/*!
 @brief access foremost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @note need to check if queue is empty
 @return element pointer
*/
A_INLINE a_vptr_t a_que_fore_(const a_que_s *ctx)
{
    return a_cast_r(a_que_node_s *, ctx->__head->next)->__vptr;
}

/*!
 @brief access backmost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @note need to check if queue is empty
 @return element pointer
*/
A_INLINE a_vptr_t a_que_back_(const a_que_s *ctx)
{
    return a_cast_r(a_que_node_s *, ctx->__head->prev)->__vptr;
}

/*!
 @brief access foremost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 empty vector
*/
A_INLINE a_vptr_t a_que_fore(const a_que_s *ctx)
{
    return a_likely(a_list_used(ctx->__head)) ? a_que_fore_(ctx) : a_null;
}

/*!
 @brief access backmost element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 empty vector
*/
A_INLINE a_vptr_t a_que_back(const a_que_s *ctx)
{
    return a_likely(a_list_used(ctx->__head)) ? a_que_back_(ctx) : a_null;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to queue structure from memory
 @param[in] size size of element
*/
a_que_s *a_que_new(a_size_t size);

/*!
 @brief deallocate a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] dtor element destructor
*/
a_noret_t a_que_die(a_que_s *ctx, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief constructor for queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] size size of element
*/
a_noret_t a_que_ctor(a_que_s *ctx, a_size_t size);

/*!
 @brief destructor for queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] dtor element destructor
*/
a_noret_t a_que_dtor(a_que_s *ctx, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief initialize a pointer to queue structure by moving
 @param[in] ctx points to an instance of queue structure
 @param[in] obj input source pointing to an instance
*/
a_que_s *a_que_move(a_que_s *ctx, a_que_s *obj);

/*!
 @brief modify size of a element for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] size the size of the new element
 @param[in] dtor previous element destructor
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
a_int_t a_que_set(a_que_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief drop all the elements for a pointer to queue structure
 @param[in] ctx points to an instance of queue structure
 @param[in] dtor current element destructor
*/
a_noret_t a_que_drop(a_que_s *ctx, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief push an element into the queue forward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
a_vptr_t a_que_push_fore(a_que_s *ctx);

/*!
 @brief push an element into the queue backward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
a_vptr_t a_que_push_back(a_que_s *ctx);

/*!
 @brief pull an element from the queue forward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
a_vptr_t a_que_pull_fore(a_que_s *ctx);

/*!
 @brief pull an element from the queue backward
 @param[in] ctx points to an instance of queue structure
 @return element pointer
  @retval 0 failure
*/
a_vptr_t a_que_pull_back(a_que_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief iterate over a queue
 @code{.c}
 a_que_foreach(T, it, ctx)
 {
     assert(a_que_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the queue
 @param it the &a_que_s to use as a loop counter
 @param ctx points to an instance of queue structure
*/
#define a_que_foreach(T, it, ctx)                                        \
    for (T *it = a_cast_r(T *, (ctx)->__head->next),                     \
           *it##_ = a_cast_r(T *, a_que_tolist(it)->next);               \
         it != a_cast_r(T *, (ctx)->__head)                              \
             ? ((void)(it = a_cast_s(T *, a_que_tonode(it)->__vptr)), 1) \
             : (0);                                                      \
         it = it##_, it##_ = a_cast_r(T *, a_que_tolist(it)->next))

/*!
 @brief iterate over a queue in reverse
 @code{.c}
 a_que_foreach_reverse(T, it, ctx)
 {
     assert(a_que_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the queue
 @param it the &a_que_s to use as a loop counter
 @param ctx points to an instance of queue structure
*/
#define a_que_foreach_reverse(T, it, ctx)                                \
    for (T *it = a_cast_r(T *, (ctx)->__head->prev),                     \
           *it##_ = a_cast_r(T *, a_que_tolist(it)->prev);               \
         it != a_cast_r(T *, (ctx)->__head)                              \
             ? ((void)(it = a_cast_s(T *, a_que_tonode(it)->__vptr)), 1) \
             : (0);                                                      \
         it = it##_, it##_ = a_cast_r(T *, a_que_tolist(it)->prev))

/*! @} A_QUE */

#endif /* __STDC_HOSTED__ */

#endif /* __A_HOST_QUE_H__ */
