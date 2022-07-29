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
    a_vptr_t __ptr; /*! vector pointer */
    a_size_t __size; /*! size of element */
    a_size_t __number; /*! number of element */
    a_size_t __capacity; /*! capacity of element */
} a_vec_s;

/*!
 @brief access vector pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_vptr_t a_vec_ptr(const a_vec_s *ctx) { return ctx->__ptr; }
/*!
 @brief access size of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vec_size(const a_vec_s *ctx) { return ctx->__size; }
/*!
 @brief access number of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vec_num(const a_vec_s *ctx) { return ctx->__number; }
/*!
 @brief access capacity of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vec_mem(const a_vec_s *ctx) { return ctx->__capacity; }

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than capacity
 @note need to check for out of bounds
 @return element pointer
*/
A_INLINE a_vptr_t a_vec_at_(const a_vec_s *ctx, a_size_t idx) { return a_cast(a_byte_t *, ctx->__ptr) + idx * ctx->__size; }
/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than capacity
 @return element pointer
  @retval 0 out of bounds
*/
A_INLINE a_vptr_t a_vec_at(const a_vec_s *ctx, a_size_t idx) { return a_likely(idx < ctx->__capacity) ? a_vec_at_(ctx, idx) : a_null; }
/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @note need to check if vector is empty
 @return element pointer
*/
A_INLINE a_vptr_t a_vec_top_(const a_vec_s *ctx) { return a_cast(a_byte_t *, ctx->__ptr) + (ctx->__number - 1) * ctx->__size; }
/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 empty vector
*/
A_INLINE a_vptr_t a_vec_top(const a_vec_s *ctx) { return a_likely(ctx->__number != a_zero) ? a_vec_top_(ctx) : a_null; }
/*!
 @brief access end pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @note need to check if vector is empty
 @return vector end pointer
*/
A_INLINE a_vptr_t a_vec_end_(const a_vec_s *ctx) { return a_cast(a_byte_t *, ctx->__ptr) + ctx->__number * ctx->__size; }
/*!
 @brief access end pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return vector end pointer
  @retval 0 empty vector
*/
A_INLINE a_vptr_t a_vec_end(const a_vec_s *ctx) { return a_likely(ctx->__ptr != a_null) ? a_vec_end_(ctx) : a_null; }

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
 @brief resize the elements in the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] size the size of the new element
 @param[in] dtor previous element destructor
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_vec_resize(a_vec_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief initialize a pointer to vector structure by copying
 @param[in] ctx points to an instance of vector structure
 @param[in] obj input source pointing to an instance
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_vec_copy(a_vec_s *ctx, const a_vec_s *obj);

/*!
 @brief initialize a pointer to vector structure by moving
 @param[in] ctx points to an instance of vector structure
 @param[in] obj input source pointing to an instance
*/
A_PUBLIC a_vec_s *a_vec_move(a_vec_s *ctx, a_vec_s *obj);

/*!
 @brief push an element into the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vec_push(a_vec_s *ctx);

/*!
 @brief pop an element from the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vec_pop(a_vec_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief iterate over a vector
 @code{.c}
 a_vec_forenum(i, ctx)
 {
     T *it = (T *)a_vec_at(ctx, i);
     assert(a_vec_size(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vec_forenum(i, ctx) a_forenum(size_t, i, (ctx)->__number)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vec_forenum_reverse(i, ctx)
 {
     T *it = (T *)a_vec_at(ctx, i);
     assert(a_vec_size(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vec_forenum_reverse(i, ctx) a_forenum_reverse(size_t, i, (ctx)->__number)

/*!
 @brief iterate over a vector
 @code{.c}
 a_vec_foreach(T, it, ctx)
 {
     assert(a_vec_size(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vec_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vec_foreach(T, it, ctx) a_foreach(T, it, (ctx)->__ptr, (ctx)->__number)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vec_foreach_reverse(T, it, ctx)
 {
     assert(a_vec_size(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vec_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vec_foreach_reverse(T, it, ctx) a_foreach_reverse(T, it, (ctx)->__ptr, (ctx)->__number)

/*! @} A_VEC */

#endif /* __STDC_HOSTED__ */

#endif /* __A_HOST_VEC_H__ */
