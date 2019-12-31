/*!
 @file mempool.h
 @brief memory pool library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_MEMPOOL_H__
#define __A_MEMPOOL_H__

#include "../def.h"

typedef struct a_mempool_s
{
    void **__ptr;
    size_t __size;
    size_t __count;
    size_t __length;
    size_t __capacity;
} a_mempool_s;

A_INLINE size_t a_mempool_size(const a_mempool_s *ctx) { return ctx->__size; }
A_INLINE size_t a_mempool_count(const a_mempool_s *ctx) { return ctx->__count; }
A_INLINE size_t a_mempool_length(const a_mempool_s *ctx) { return ctx->__length; }
A_INLINE size_t a_mempool_capacity(const a_mempool_s *ctx) { return ctx->__capacity; }

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC a_mempool_s *a_mempool_new(size_t size);
A_PUBLIC void a_mempool_die(a_mempool_s *ctx, void (*func)(void *));

A_PUBLIC void a_mempool_ctor(a_mempool_s *ctx, size_t size);
A_PUBLIC void a_mempool_dtor(a_mempool_s *ctx, void (*func)(void *));

/*!
 @retval 0 failure
*/
A_PUBLIC void *a_mempool_alloc(a_mempool_s *ctx);
/*!
 @retval 0 success
 @retval -1 failure
*/
A_PUBLIC int a_mempool_free(a_mempool_s *ctx, void *ptr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_MEMPOOL_H__ */
