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
    a_noret_t (*ctor)(a_vptr_t); /*!< element constructor */
    a_noret_t (*dtor)(a_vptr_t); /*!< element destructor */
    a_vptr_t __head; /*!< head address */
    a_vptr_t __tail; /*!< tail address */
    a_vptr_t __last; /*!< last address */
    a_size_t __size; /*!< size element */
    a_size_t __num; /*!< count number */
    a_size_t __mem; /*!< count memory */
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
    return a_likely(ctx->__num) ? a_vectors_top_(ctx) : a_null;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to vector structure from memory
 @param[in] size the size of the element
 @param[in] ctor element constructor
 @param[in] dtor element destructor
*/
A_PUBLIC a_vectors_s *a_vectors_new(a_size_t size,
                                    a_noret_t (*ctor)(a_vptr_t),
                                    a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief deallocate a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_PUBLIC a_noret_t a_vectors_die(a_vectors_s *ctx);

/*!
 @brief constructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size the size of the element
 @param[in] ctor element constructor
 @param[in] dtor element destructor
*/
A_PUBLIC a_noret_t a_vectors_ctor(a_vectors_s *ctx, a_size_t size,
                                  a_noret_t (*ctor)(a_vptr_t),
                                  a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief destructor for vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_PUBLIC a_noret_t a_vectors_dtor(a_vectors_s *ctx);

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
 @brief sort all elements for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_PUBLIC a_noret_t a_vectors_sort(const a_vectors_s *ctx, a_int_t (*cmp)(a_cptr_t, a_cptr_t));

/*!
 @brief insert sort foremost element for a pointer to vector structure
 @code{.c}
 T *obj = a_vectors_push_fore(T, ctx);
 if (obj)
 {
     CTOR(obj);
     INIT(obj);
     a_vectors_sort_fore(ctx, cmp);
 }
 @endcode
 @param[in] ctx points to an instance of vector structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_PUBLIC a_noret_t a_vectors_sort_fore(const a_vectors_s *ctx, a_int_t (*cmp)(a_cptr_t, a_cptr_t));

/*!
 @brief insert sort backmost element for a pointer to vector structure
 @code{.c}
 T *obj = a_vectors_push_back(T, ctx);
 if (obj)
 {
     CTOR(obj);
     INIT(obj);
     a_vectors_sort_back(ctx, cmp);
 }
 @endcode
 @param[in] ctx points to an instance of vector structure
 @param[in] cmp a function that compares two elements
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
*/
A_PUBLIC a_noret_t a_vectors_sort_back(const a_vectors_s *ctx, a_int_t (*cmp)(a_cptr_t, a_cptr_t));

/*!
 @brief modify element number for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] num number of all elements in the vector
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_vectors_set_num(a_vectors_s *ctx, a_size_t num);

/*!
 @brief modify size of a element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] size the size of the new element
 @param[in] ctor current element constructor
 @param[in] dtor current element destructor
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_vectors_set(a_vectors_s *ctx, a_size_t size,
                               a_noret_t (*ctor)(a_vptr_t),
                               a_noret_t (*dtor)(a_vptr_t));

/*!
 @brief drop all the elements for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_PUBLIC a_noret_t a_vectors_drop(a_vectors_s *ctx);

/*!
 @brief swap elements lhs and rhs for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] lhs element index on the left
 @param[in] rhs element index on the right
*/
A_PUBLIC a_noret_t a_vectors_swap(a_vectors_s *ctx, a_size_t lhs, a_size_t rhs);

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

#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"
#endif /* __clang__ */

#define a_vectors_ptr(T, ctx) a_cast_s(T *, a_vectors_ptr(ctx))
#define a_vectors_end(T, ctx) a_cast_s(T *, a_vectors_end(ctx))
#define a_vectors_top(T, ctx) a_cast_s(T *, a_vectors_top(ctx))
#define a_vectors_top_(T, ctx) a_cast_s(T *, a_vectors_top_(ctx))
#define a_vectors_at(T, ctx, idx) a_cast_s(T *, a_vectors_at(ctx, idx))
#define a_vectors_at_(T, ctx, idx) a_cast_s(T *, a_vectors_at_(ctx, idx))
#define a_vectors_insert(T, ctx, idx) a_cast_s(T *, a_vectors_insert(ctx, idx))
#define a_vectors_remove(T, ctx, idx) a_cast_s(T *, a_vectors_remove(ctx, idx))
#define a_vectors_push_fore(T, ctx) a_cast_s(T *, a_vectors_push_fore(ctx))
#define a_vectors_push_back(T, ctx) a_cast_s(T *, a_vectors_push_back(ctx))
#define a_vectors_pull_fore(T, ctx) a_cast_s(T *, a_vectors_pull_fore(ctx))
#define a_vectors_pull_back(T, ctx) a_cast_s(T *, a_vectors_pull_back(ctx))
#define a_vectors_push(T, ctx) a_cast_s(T *, a_vectors_push(ctx))
#define a_vectors_pull(T, ctx) a_cast_s(T *, a_vectors_pull(ctx))

/*! @} A_VECTORS */

#endif /* __STDC_HOSTED__ */

#endif /* __A_HOST_VECTORS_H__ */
