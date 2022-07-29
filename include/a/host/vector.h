/*!
 @file vector.h
 @brief basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_HOST_VECTOR_H__
#define __A_HOST_VECTOR_H__

#include "../a.h"

#if __STDC_HOSTED__

#include <stdlib.h>

/*!
 @ingroup A
 @addtogroup A_VECTOR basic vector library
 @{
*/

/*!
 @brief instance structure for basic vector
*/
typedef struct a_vector_s
{
    a_vptr_t __head; /* head address */
    a_vptr_t __last; /* last address */
    a_vptr_t __tail; /* tail address */
    a_size_t __size; /* size element */
} a_vector_s;

/*!
 @brief access vector pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_vptr_t a_vector_ptr(const a_vector_s *ctx) { return ctx->__head; }

/*!
 @brief access end pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_vptr_t a_vector_end(const a_vector_s *ctx) { return ctx->__last; }

/*!
 @brief access size of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vector_size(const a_vector_s *ctx) { return ctx->__size; }

/*!
 @brief access number of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vector_num(const a_vector_s *ctx)
{
    return a_cast(a_size_t, a_cast(a_byte_t *, ctx->__last) - a_cast(a_byte_t *, ctx->__head)) / ctx->__size;
}

/*!
 @brief access capacity of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE a_size_t a_vector_mem(const a_vector_s *ctx)
{
    return a_cast(a_size_t, a_cast(a_byte_t *, ctx->__tail) - a_cast(a_byte_t *, ctx->__head)) / ctx->__size;
}

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than capacity
 @note need to check for out of bounds
 @return element pointer
*/
A_INLINE a_vptr_t a_vector_at_(const a_vector_s *ctx, a_size_t idx)
{
    return a_cast(a_byte_t *, ctx->__head) + idx * ctx->__size;
}

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] idx index of element less than capacity
 @return element pointer
  @retval 0 out of bounds
*/
A_INLINE a_vptr_t a_vector_at(const a_vector_s *ctx, a_size_t idx)
{
    a_vptr_t at = a_vector_at_(ctx, idx);
    return a_likely(at < ctx->__tail) ? at : a_null;
}

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @note need to check if vector is empty
 @return element pointer
*/
A_INLINE a_vptr_t a_vector_top_(const a_vector_s *ctx)
{
    return a_cast(a_byte_t *, ctx->__last) - ctx->__size;
}

/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 empty vector
*/
A_INLINE a_vptr_t a_vector_top(const a_vector_s *ctx)
{
    return a_likely(ctx->__head != ctx->__last) ? a_vector_top_(ctx) : a_null;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to vector structure from memory
 @param[in] size size of element
*/
A_PUBLIC a_vector_s *a_vector_new(a_size_t size);

/*!
 @brief deallocate a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_PUBLIC a_noret_t a_vector_die(a_vector_s *ctx, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief constructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size size of element
*/
A_PUBLIC a_noret_t a_vector_ctor(a_vector_s *ctx, a_size_t size);

/*!
 @brief destructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_PUBLIC a_noret_t a_vector_dtor(a_vector_s *ctx, a_noret_t (*dtor)(a_vptr_t));

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
A_PUBLIC a_int_t a_vector_copy(a_vector_s *ctx, const a_vector_s *obj, a_int_t (*dup)(a_vptr_t, a_cptr_t));

/*!
 @brief initialize a pointer to vector structure by moving
 @param[in] ctx points to an instance of vector structure
 @param[in] obj input source pointing to an instance
*/
A_PUBLIC a_vector_s *a_vector_move(a_vector_s *ctx, a_vector_s *obj);

/*!
 @brief resize the elements in the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] size the size of the new element
 @param[in] dtor previous element destructor
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_vector_resize(a_vector_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief drop all elements in the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor current element destructor
*/
A_PUBLIC a_noret_t a_vector_drop(a_vector_s *ctx, a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief push an element into the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vector_push(a_vector_s *ctx);

/*!
 @brief pop an element from the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC a_vptr_t a_vector_pop(a_vector_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief iterate over a vector
 @code{.c}
 a_vector_forenum(i, ctx)
 {
     T *it = (T *)a_vector_at(ctx, i);
     assert(a_vector_size(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vector_forenum(i, ctx) a_forenum(size_t, i, a_vector_num(ctx))

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vector_forenum_reverse(i, ctx)
 {
     T *it = (T *)a_vector_at(ctx, i);
     assert(a_vector_size(ctx) == sizeof(*it));
 }
 @endcode
 @param i index of elements in the vector
 @param ctx points to an instance of vector structure
*/
#define a_vector_forenum_reverse(i, ctx) a_forenum_reverse(size_t, i, a_vector_num(ctx))

/*!
 @brief iterate over a vector
 @code{.c}
 a_vector_foreach(T, it, ctx)
 {
     assert(a_vector_size(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vector_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vector_foreach(T, it, ctx) a_iterate(T, it, (ctx)->__head, (ctx)->__last)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 a_vector_foreach_reverse(T, it, ctx)
 {
     assert(a_vector_size(ctx) == sizeof(*it));
 }
 @endcode
 @param T type of elements in the vector
 @param it the &a_vector_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vector_foreach_reverse(T, it, ctx) a_iterate_reverse(T, it, (ctx)->__head, (ctx)->__last)

/*! @} A_VECTOR */

#endif /* __STDC_HOSTED__ */

#endif /* __A_HOST_VECTOR_H__ */
