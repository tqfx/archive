/*!
 @file vec.c
 @brief basic vector library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/misc/vec.h"
#include "a/oop.h"

#include <assert.h>

#undef ARGS
#define ARGS size_t size
A_OOP_NEW_VA(a_vec_s, a_vec_new, a_vec_ctor, ARGS, size)
#undef ARGS
#define ARGS void (*func)(void *)
A_OOP_DIE_VA(a_vec_s, a_vec_die, a_vec_dtor, ARGS, func)
#undef ARGS

void a_vec_ctor(a_vec_s *ctx, size_t size)
{
    assert(ctx);
    ctx->__size = size;
    ctx->__capacity = 0;
    ctx->__length = 0;
    ctx->__ptr = 0;
}

void a_vec_dtor(a_vec_s *ctx, void (*func)(void *))
{
    assert(ctx);
    if (ctx->__ptr)
    {
        if (func)
        {
            while (a_vec_len(ctx))
            {
                func(a_vec_at(ctx, a_vec_dec(ctx)));
            }
        }
        free(ctx->__ptr);
        ctx->__ptr = 0;
    }
    ctx->__capacity = 0;
    ctx->__length = 0;
    ctx->__size = 0;
}

void *a_vec_push(a_vec_s *ctx)
{
    assert(ctx);
    if (ctx->__capacity <= ctx->__length)
    {
        size_t capacity = ctx->__capacity + (ctx->__capacity >> 1) + 1;
        void *ptr = realloc(ctx->__ptr, capacity * ctx->__size);
        if (ptr == 0)
        {
            return 0;
        }
        ctx->__capacity = capacity;
        ctx->__ptr = ptr;
    }
    return a_vec_at(ctx, a_vec_inc(ctx));
}

void *a_vec_pop(a_vec_s *ctx)
{
    assert(ctx);
    return a_vec_len(ctx) ? a_vec_at(ctx, a_vec_dec(ctx)) : 0;
}

int a_vec_resize(a_vec_s *ctx, size_t size)
{
    assert(ctx);
    if (size == 0)
    {
        return ~0;
    }
    ctx->__capacity = ctx->__size * ctx->__capacity / size;
    ctx->__size = size;
    ctx->__length = 0;
    return 0;
}
