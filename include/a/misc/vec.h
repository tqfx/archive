/*!
 @file vec.h
 @brief basic vector library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_VEC_H__
#define __A_VEC_H__

#include "../def.h"

#include <stdlib.h>

typedef struct a_vec_s
{
    void *__ptr;
    size_t __size;
    size_t __length;
    size_t __capacity;
} a_vec_s;

A_INLINE size_t a_vec_size(const a_vec_s *ctx) { return ctx->__size; }
A_INLINE size_t a_vec_mem(const a_vec_s *ctx) { return ctx->__capacity; }
A_INLINE size_t a_vec_len(const a_vec_s *ctx) { return ctx->__length; }
A_INLINE size_t a_vec_inc(a_vec_s *ctx) { return ctx->__length++; }
A_INLINE size_t a_vec_dec(a_vec_s *ctx) { return --ctx->__length; }
A_INLINE void *a_vec_ptr(const a_vec_s *ctx) { return ctx->__ptr; }
A_INLINE void *a_vec_at(const a_vec_s *ctx, size_t index)
{
    return (char *)ctx->__ptr + index * ctx->__size;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC a_vec_s *a_vec_new(size_t size);
A_PUBLIC void a_vec_die(a_vec_s *ctx, void (*func)(void *));

A_PUBLIC void a_vec_ctor(a_vec_s *ctx, size_t size);
A_PUBLIC void a_vec_dtor(a_vec_s *ctx, void (*func)(void *));

A_PUBLIC void *a_vec_push(a_vec_s *ctx);
A_PUBLIC void *a_vec_pop(a_vec_s *ctx);

A_PUBLIC int a_vec_resize(a_vec_s *ctx, size_t size);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_VEC_H__ */
