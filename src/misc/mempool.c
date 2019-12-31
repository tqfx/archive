/*!
 @file mempool.c
 @brief memory pool library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/misc/mempool.h"
#include "a/oop.h"

#include <assert.h>

#undef ARGS
#define ARGS size_t size
A_OOP_NEW_VA(a_mempool_s, a_mempool_new, a_mempool_ctor, ARGS, size)
#undef ARGS
#define ARGS void (*func)(void *)
A_OOP_DIE_VA(a_mempool_s, a_mempool_die, a_mempool_dtor, ARGS, func)
#undef ARGS

void a_mempool_ctor(a_mempool_s *ctx, size_t size)
{
    assert(ctx);
    assert(size);
    ctx->__capacity = 0;
    ctx->__length = 0;
    ctx->__count = 0;
    ctx->__size = size;
    ctx->__ptr = 0;
}

void a_mempool_dtor(a_mempool_s *ctx, void (*func)(void *))
{
    assert(ctx);
    func = func ? func : free;
    while (ctx->__length)
    {
        func(ctx->__ptr[--ctx->__length]);
    }
    ctx->__capacity = 0;
    free(ctx->__ptr);
    ctx->__count = 0;
    ctx->__size = 0;
    ctx->__ptr = 0;
}

void *a_mempool_alloc(a_mempool_s *ctx)
{
    assert(ctx);
    ++ctx->__count;
    return ctx->__length ? ctx->__ptr[--ctx->__length] : malloc(ctx->__size);
}

int a_mempool_free(a_mempool_s *ctx, void *ptr)
{
    assert(ctx);
    if (ptr == 0)
    {
        return ~0;
    }
    if (ctx->__capacity <= ctx->__length)
    {
        size_t capacity = ctx->__capacity + (ctx->__capacity >> 1) + 1;
        void **p = (void **)realloc(ctx->__ptr, sizeof(void *) * capacity);
        if (p == 0)
        {
            return ~0;
        }
        ctx->__capacity = capacity;
        ctx->__ptr = p;
    }
    ctx->__ptr[ctx->__length++] = ptr;
    --ctx->__count;
    return 0;
}
