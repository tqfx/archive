/*!
 @file vectors.h
 @brief basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_HOST_VECTORS_H__
#define __A_HOST_VECTORS_H__

#include "../a.h"

#if __STDC_HOSTED__

#include <stdlib.h>

/*!
 @ingroup A
 @addtogroup A_VECTORS basic vector library
 @{
*/

/*!
 @brief instance structure for basic vector
*/
typedef struct a_vectors_s
{
    a_vptr_t __head; /* head address */
    a_vptr_t __tail; /* tail address */
    a_vptr_t __last; /* last address */
    a_size_t __size; /* size element */
    a_size_t __num; /*! count number */
    a_size_t __mem; /*! count memory */
} a_vectors_s;

/*!
 @brief access vector head pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_vptr_t a_vectors_ptr(const a_vectors_s *ctx) { return ctx->__head; }

/*!
 @brief access vector tail pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_vptr_t a_vectors_end(const a_vectors_s *ctx) { return ctx->__tail; }

/*!
 @brief access size of a element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vectors_get(const a_vectors_s *ctx) { return ctx->__size; }

/*!
 @brief access number of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vectors_num(const a_vectors_s *ctx) { return ctx->__num; }

/*!
 @brief access capacity of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vectors_mem(const a_vectors_s *ctx) { return ctx->__mem; }

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than capacity
 @note should check for out of bounds
 @return element pointer
*/
A_INLINE a_vptr_t a_vectors_at_(const a_vectors_s *ctx, a_size_t idx)
{
    return a_cast_s(a_byte_t *, ctx->__head) + ctx->__size * idx;
}

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than capacity
 @return element pointer
  @retval 0 out of bounds
*/
A_INLINE a_vptr_t a_vectors_at(const a_vectors_s *ctx, a_size_t idx)
{
    return a_likely(idx < ctx->__mem) ? a_vectors_at_(ctx, idx) : a_null;
}

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @note should check if vector is empty
 @return element pointer
*/
A_INLINE a_vptr_t a_vectors_top_(const a_vectors_s *ctx)
{
    return a_cast_s(a_byte_t *, ctx->__tail) - ctx->__size;
}

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 empty vector
*/
A_INLINE a_vptr_t a_vectors_top(const a_vectors_s *ctx)
{
    return a_likely(ctx->__head != ctx->__tail) ? a_vectors_top_(ctx) : a_null;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to vector structure from memory
 @param[in] size size of element
*/
A_PUBLIC a_vectors_s *a_vectors_new(a_size_t size);

/*!
 @brief deallocate a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_PUBLIC a_noret_t a_vectors_die(a_vectors_s *ctx, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief constructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size size of element
*/
A_PUBLIC a_noret_t a_vectors_ctor(a_vectors_s *ctx, a_size_t size);

/*!
 @brief destructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_PUBLIC a_noret_t a_vectors_dtor(a_vectors_s *ctx, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief initialize a pointer to vector structure by copying
 @param[in] ctx points to an instance of vector structure
 @param[in] obj input source pointing to an instance
 @param[in] dup a function that copies elements
  @arg 0 use function memcpy to copy elements
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_vectors_copy(a_vectors_s *ctx, const a_vectors_s *obj, a_int_t (*dup)(a_vptr_t, a_cptr_t));

/*!
 @brief initialize a pointer to vector structure by moving
 @param[in] ctx points to an instance of vector structure
 @param[in] obj input source pointing to an instance
*/
A_PUBLIC a_vectors_s *a_vectors_move(a_vectors_s *ctx, a_vectors_s *obj);

/*!
 @brief modify size of a element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size the size of the new element
 @param[in] dtor previous element destructor
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_vectors_set(a_vectors_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief drop all the elements for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor current element destructor
*/
A_PUBLIC a_noret_t a_vectors_drop(a_vectors_s *ctx, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief swap elements lhs and rhs for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] lhs element index on the left
 @param[in] rhs element index on the right
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_vectors_swap(a_vectors_s *ctx, a_size_t lhs, a_size_t rhs);

/*!
 @brief insert an element into the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
  @arg 0 @ref a_vectors_push_fore
  @arg n @ref a_vectors_push_back
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vectors_insert(a_vectors_s *ctx, a_size_t idx);

/*!
 @brief push an element into the vector forward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vectors_push_fore(a_vectors_s *ctx);

/*!
 @brief push an element into the vector backward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vectors_push_back(a_vectors_s *ctx);

/*!
 @brief remove an element from the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
  @arg 0 @ref a_vectors_pull_fore
  @arg n @ref a_vectors_pull_back
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vectors_remove(a_vectors_s *ctx, a_size_t idx);

/*!
 @brief pull an element from the vector forward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vectors_pull_fore(a_vectors_s *ctx);

/*!
 @brief pull an element from the vector backward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vectors_pull_back(a_vectors_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief push an element into the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_INLINE a_vptr_t a_vectors_push(a_vectors_s *ctx) { return a_vectors_push_back(ctx); }

/*!
 @brief pull an element from the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_INLINE a_vptr_t a_vectors_pull(a_vectors_s *ctx) { return a_vectors_pull_back(ctx); }

/*!
 @brief iterate over a vector
 @code{.c}
 a_vectors_forenum(i, ctx)
 {
     T *it = (T *)a_vectors_at(ctx, i);
     assert(a_vectors_get(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vectors_forenum(i, ctx) a_forenum(a_size_t, i, (ctx)->__num)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vectors_forenum_reverse(i, ctx)
 {
     T *it = (T *)a_vectors_at(ctx, i);
     assert(a_vectors_get(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vectors_forenum_reverse(i, ctx) a_forenum_reverse(a_size_t, i, (ctx)->__num)

/*!
 @brief iterate over a vector
 @code{.c}
 a_vectors_foreach(T, it, ctx)
 {
     assert(a_vectors_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vectors_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vectors_foreach(T, it, ctx) a_iterate(T, it, (ctx)->__head, (ctx)->__tail)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vectors_foreach_reverse(T, it, ctx)
 {
     assert(a_vectors_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vectors_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vectors_foreach_reverse(T, it, ctx) a_iterate_reverse(T, it, (ctx)->__head, (ctx)->__tail)

/*! @} A_VECTORS */

#endif /* __STDC_HOSTED__ */

#endif /* __A_HOST_VECTORS_H__ */
