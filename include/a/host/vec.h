/*!
 @file vec.h
 @brief basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_HOST_VEC_H__
#define __A_HOST_VEC_H__

#include "../a.h"

#if __STDC_HOSTED__

#include <stdlib.h>

/*!
 @ingroup A
 @addtogroup A_VEC basic vector library
 @{
*/

/*!
 @brief instance structure for basic vector
*/
typedef struct a_vec_s
{
    a_vptr_t __ptr; /*! address of vector */
    a_size_t __num; /*! number of element */
    a_size_t __mem; /*! memory of element */
    a_size_t __siz; /*! size of a element */
} a_vec_s;

/*!
 @brief access address of vector for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_vptr_t a_vec_ptr(const a_vec_s *ctx) { return ctx->__ptr; }

/*!
 @brief access number of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vec_num(const a_vec_s *ctx) { return ctx->__num; }

/*!
 @brief access memory of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vec_mem(const a_vec_s *ctx) { return ctx->__mem; }

/*!
 @brief access size of a element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vec_get(const a_vec_s *ctx) { return ctx->__siz; }

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than memory
 @note should check for out of bounds
 @return element pointer
*/
A_INLINE a_vptr_t a_vec_at_(const a_vec_s *ctx, a_size_t idx)
{
    return a_cast_s(a_byte_t *, ctx->__ptr) + ctx->__siz * idx;
}

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than memory
 @return element pointer
  @retval 0 out of bounds
*/
A_INLINE a_vptr_t a_vec_at(const a_vec_s *ctx, a_size_t idx)
{
    return a_likely(idx < ctx->__mem) ? a_vec_at_(ctx, idx) : a_null;
}

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @note should check if vector is empty
 @return element pointer
*/
A_INLINE a_vptr_t a_vec_top_(const a_vec_s *ctx)
{
    return a_cast_s(a_byte_t *, ctx->__ptr) + ctx->__siz * (ctx->__num - 1);
}

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 empty vector
*/
A_INLINE a_vptr_t a_vec_top(const a_vec_s *ctx)
{
    return a_likely(ctx->__num) ? a_vec_top_(ctx) : a_null;
}

/*!
 @brief access end pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @note should check if vector is empty
 @return vector end pointer
*/
A_INLINE a_vptr_t a_vec_end_(const a_vec_s *ctx)
{
    return a_cast_s(a_byte_t *, ctx->__ptr) + ctx->__siz * ctx->__num;
}

/*!
 @brief access end pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return vector end pointer
  @retval 0 empty vector
*/
A_INLINE a_vptr_t a_vec_end(const a_vec_s *ctx)
{
    return a_likely(ctx->__ptr) ? a_vec_end_(ctx) : ctx->__ptr;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to vector structure from memory
 @param[in] size size of element
*/
A_PUBLIC a_vec_s *a_vec_new(a_size_t size);

/*!
 @brief deallocate a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_PUBLIC a_noret_t a_vec_die(a_vec_s *ctx, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief constructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size size of element
*/
A_PUBLIC a_noret_t a_vec_ctor(a_vec_s *ctx, a_size_t size);

/*!
 @brief destructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_PUBLIC a_noret_t a_vec_dtor(a_vec_s *ctx, a_noret_t (*dtor)(a_vptr_t));

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
A_PUBLIC a_int_t a_vec_copy(a_vec_s *ctx, const a_vec_s *obj, a_int_t (*dup)(a_vptr_t, a_cptr_t));

/*!
 @brief initialize a pointer to vector structure by moving
 @param[in] ctx points to an instance of vector structure
 @param[in] obj input source pointing to an instance
*/
A_PUBLIC a_vec_s *a_vec_move(a_vec_s *ctx, a_vec_s *obj);

/*!
 @brief modify size of a element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size the size of the new element
 @param[in] dtor previous element destructor
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_vec_set(a_vec_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief drop all the elements for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor current element destructor
*/
A_PUBLIC a_noret_t a_vec_drop(a_vec_s *ctx, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief swap elements lhs and rhs for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] lhs element index on the left
 @param[in] rhs element index on the right
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_vec_swap(a_vec_s *ctx, a_size_t lhs, a_size_t rhs);

/*!
 @brief insert an element into the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
  @arg 0 @ref a_vec_push_fore
  @arg n @ref a_vec_push_back
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vec_insert(a_vec_s *ctx, a_size_t idx);

/*!
 @brief push an element into the vector forward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vec_push_fore(a_vec_s *ctx);

/*!
 @brief push an element into the vector backward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vec_push_back(a_vec_s *ctx);

/*!
 @brief remove an element from the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element in this vector
  @arg 0 @ref a_vec_pull_fore
  @arg n @ref a_vec_pull_back
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vec_remove(a_vec_s *ctx, a_size_t idx);

/*!
 @brief pull an element from the vector forward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vec_pull_fore(a_vec_s *ctx);

/*!
 @brief pull an element from the vector backward
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vec_pull_back(a_vec_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief push an element into the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_INLINE a_vptr_t a_vec_push(a_vec_s *ctx) { return a_vec_push_back(ctx); }

/*!
 @brief pull an element from the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_INLINE a_vptr_t a_vec_pull(a_vec_s *ctx) { return a_vec_pull_back(ctx); }

/*!
 @brief iterate over a vector
 @code{.c}
 a_vec_forenum(i, ctx)
 {
     T *it = (T *)a_vec_at(ctx, i);
     assert(a_vec_get(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vec_forenum(i, ctx) a_forenum(a_size_t, i, (ctx)->__num)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vec_forenum_reverse(i, ctx)
 {
     T *it = (T *)a_vec_at(ctx, i);
     assert(a_vec_get(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vec_forenum_reverse(i, ctx) a_forenum_reverse(a_size_t, i, (ctx)->__num)

/*!
 @brief iterate over a vector
 @code{.c}
 a_vec_foreach(T, it, ctx)
 {
     assert(a_vec_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vec_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vec_foreach(T, it, ctx) a_foreach(T, it, (ctx)->__ptr, (ctx)->__num)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vec_foreach_reverse(T, it, ctx)
 {
     assert(a_vec_get(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vec_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vec_foreach_reverse(T, it, ctx) a_foreach_reverse(T, it, (ctx)->__ptr, (ctx)->__num)

/*! @} A_VEC */

#endif /* __STDC_HOSTED__ */

#endif /* __A_HOST_VEC_H__ */
