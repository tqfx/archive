/*!
 @file a_mempool.h
 @brief memory pool library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_MEMPOOL_H__
#define __A_MEMPOOL_H__

#include "liba.h"

typedef struct a_mempool_s
{
    void **ptr;
    size_t size;
    size_t count;
    size_t length;
    size_t capacity;
} a_mempool_s;

__NONNULL_ALL
__STATIC_INLINE
size_t a_mempool_size(const a_mempool_s *ctx)
{
    AASSERT(ctx);
    return ctx->size;
}

__NONNULL_ALL
__STATIC_INLINE
size_t a_mempool_count(const a_mempool_s *ctx)
{
    AASSERT(ctx);
    return ctx->count;
}

__NONNULL_ALL
__STATIC_INLINE
size_t a_mempool_length(const a_mempool_s *ctx)
{
    AASSERT(ctx);
    return ctx->length;
}

__NONNULL_ALL
__STATIC_INLINE
size_t a_mempool_capacity(const a_mempool_s *ctx)
{
    AASSERT(ctx);
    return ctx->capacity;
}

__BEGIN_DECLS

a_mempool_s *a_mempool_new(size_t size) __NONNULL_ALL __RESULT_USE_CHECK;
void a_mempool_delete(a_mempool_s *ctx, void (*func)(void *));

void a_mempool_ctor(a_mempool_s *ctx, size_t size) __NONNULL_ALL;
void a_mempool_dtor(a_mempool_s *ctx, void (*func)(void *)) __NONNULL((1));

/*!
 @retval 0 failure
*/
void *a_mempool_alloc(a_mempool_s *ctx) __NONNULL_ALL;
/*!
 @retval 0 success
 @retval -1 failure
*/
int a_mempool_free(a_mempool_s *ctx, void *ptr);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_MEMPOOL_H__ */
