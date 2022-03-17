/*!
 @file a_mempool.c
 @brief memory pool library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_mempool.h"

#include "a_object.h"

#undef ARGS
#define ARGS size_t size
A_OBJECT_NEW_VA(a_mempool_s, a_mempool_new, a_mempool_ctor, ARGS, size)
#undef ARGS
#define ARGS void (*func)(void *)
A_OBJECT_DELETE_VA(a_mempool_s, a_mempool_delete, a_mempool_dtor, ARGS, func)
#undef ARGS

void a_mempool_ctor(a_mempool_s *ctx, size_t size)
{
    AASSERT(ctx);
    AASSERT(size);
    ctx->capacity = 0;
    ctx->length = 0;
    ctx->count = 0;
    ctx->size = size;
    ctx->ptr = 0;
}

void a_mempool_dtor(a_mempool_s *ctx, void (*func)(void *))
{
    AASSERT(ctx);
    func = func ? func : free;
    while (ctx->length)
    {
        func(ctx->ptr[--ctx->length]);
    }
    ctx->capacity = 0;
    free(ctx->ptr);
    ctx->count = 0;
    ctx->size = 0;
    ctx->ptr = 0;
}

void *a_mempool_alloc(a_mempool_s *ctx)
{
    AASSERT(ctx);
    ++ctx->count;
    return ctx->length ? ctx->ptr[--ctx->length] : malloc(ctx->size);
}

int a_mempool_free(a_mempool_s *ctx, void *ptr)
{
    AASSERT(ctx);
    if (ptr == 0)
    {
        return ~0;
    }
    if (ctx->capacity <= ctx->length)
    {
        size_t capacity = ctx->capacity + (ctx->capacity >> 1) + 1;
        void **p = (void **)realloc(ctx->ptr, sizeof(void *) * capacity);
        if (p == 0)
        {
            return ~0;
        }
        ctx->capacity = capacity;
        ctx->ptr = p;
    }
    ctx->ptr[ctx->length++] = ptr;
    --ctx->count;
    return 0;
}
