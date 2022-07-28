/*!
 @file for.h
 @brief Test basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_HOST_VEC_H__
#define __TEST_HOST_VEC_H__

#include "a/host/vec.h"

#include "../test.h"
#include "../for.h"

/*!
 @brief iterate over a vector
 @code{.c}
 if(a_vec_num(ctx))
 {
     T *it;
     a_vec_forboth(T, i, it, ctx)
     {
         assert(a_vec_at(ctx, i) == it);
     }
 }
 @endcode
 @param T type of elements in the vector
 @param i index of elements in the vector
 @param it the &a_vec_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vec_forboth(T, i, it, ctx) a_forboth(size_t, i, T, it, (ctx)->__ptr, (ctx)->__number)

/*!
 @brief iterate over a vector in reverse
 @code{.c}
 if(a_vec_num(ctx))
 {
     T *it;
     a_vec_forboth_reverse(T, i, it, ctx)
     {
         assert(a_vec_at(ctx, i) == it);
     }
 }
 @endcode
 @param T type of elements in the vector
 @param i index of elements in the vector
 @param it the &a_vec_s to use as a loop counter
 @param ctx points to an instance of vector structure
*/
#define a_vec_forboth_reverse(T, i, it, ctx) a_forboth_reverse(size_t, i, T, it, (ctx)->__ptr, (ctx)->__number)

#include "../src/host/vec.h"

#define vec_forboth(i, it, ctx) \
    for (size_t i = 0; (void)((it) = (ctx)->ptr + i), i != (ctx)->num; ++i)
#define vec_forboth_reverse(i, it, ctx) \
    for (size_t i = (ctx)->num; i ? ((void)((it) = (ctx)->ptr + --i), 1) : 0;)

#endif /* __TEST_HOST_VEC_H__ */
