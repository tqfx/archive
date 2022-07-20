/*!
 @file vec.h
 @brief basic vector library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#ifndef __A_VEC_H__
#define __A_VEC_H__

#include "../def.h"

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
    void *__ptr; /*! vector pointer */
    size_t __size; /*! size of element */
    size_t __number; /*! number of element */
    size_t __capacity; /*! capacity of element */
} a_vec_s;

/*!
 @brief access vector pointer for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE void *a_vec_ptr(const a_vec_s *ctx) { return ctx->__ptr; }
/*!
 @brief access size of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE size_t a_vec_size(const a_vec_s *ctx) { return ctx->__size; }
/*!
 @brief access number of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE size_t a_vec_num(const a_vec_s *ctx) { return ctx->__number; }
/*!
 @brief access capacity of element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_INLINE size_t a_vec_mem(const a_vec_s *ctx) { return ctx->__capacity; }

/*!
 @brief access specified element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] index index of element
 @return element pointer
*/
A_INLINE void *a_vec_at(const a_vec_s *ctx, size_t index) { return (char *)ctx->__ptr + index * ctx->__size; }
/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @note need to check if vector is empty
 @return element pointer
*/
A_INLINE void *a_vec_top_(const a_vec_s *ctx) { return (char *)ctx->__ptr + (ctx->__number - 1) * ctx->__size; }
/*!
 @brief access top element for a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 empty vector
*/
A_INLINE void *a_vec_top(const a_vec_s *ctx) { return ctx->__number ? a_vec_top_(ctx) : 0; }

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to vector structure from memory
 @param[in] size size of element
*/
A_PUBLIC a_vec_s *a_vec_new(size_t size);

/*!
 @brief deallocate a pointer to vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_PUBLIC void a_vec_die(a_vec_s *ctx, void (*dtor)(void *));

/*!
 @brief constructor for vector structure
 @param[in] ctx points to an instance of vector structure
*/
A_PUBLIC void a_vec_ctor(a_vec_s *ctx, size_t size);

/*!
 @brief destructor for vector structure
 @param[in] ctx points to an instance of vector structure
 @param[in] dtor element destructor
*/
A_PUBLIC void a_vec_dtor(a_vec_s *ctx, void (*dtor)(void *));

/*!
 @brief initialize a pointer to vector structure by copying
 @param[in] ctx points to an instance of vector structure
 @param[in] vec input source pointing to an instance
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
A_PUBLIC int a_vec_copy(a_vec_s *ctx, const a_vec_s *vec);

/*!
 @brief initialize a pointer to vector structure by moving
 @param[in] ctx points to an instance of vector structure
 @param[in] vec input source pointing to an instance
*/
A_PUBLIC a_vec_s *a_vec_move(a_vec_s *ctx, a_vec_s *vec);

/*!
 @brief resize the elements in the vector
 @param[in] ctx points to an instance of vector structure
 @param[in] size the size of the new element
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
A_PUBLIC int a_vec_resize(a_vec_s *ctx, size_t size);

/*!
 @brief push an element into the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC void *a_vec_push(a_vec_s *ctx);

/*!
 @brief pop an element from the vector
 @param[in] ctx points to an instance of vector structure
 @return element pointer
  @retval 0 failure
*/
A_PUBLIC void *a_vec_pop(a_vec_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_VEC */

#endif /* __STDC_HOSTED__ */

#endif /* __A_VEC_H__ */
