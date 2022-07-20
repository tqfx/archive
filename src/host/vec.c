/*!
 @file vec.c
 @brief basic vector library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#if __STDC_HOSTED__

#include "a/host/vec.h"
#include "a/oop.h"

#include <assert.h>
#include <string.h>

#undef ARGS
#define ARGS size_t size
A_OOP_NEW_VA(a_vec_s, a_vec_new, a_vec_ctor, ARGS, size)
#undef ARGS
#define ARGS void (*dtor)(void *)
A_OOP_DIE_VA(a_vec_s, a_vec_die, a_vec_dtor, ARGS, dtor)
#undef ARGS

void a_vec_ctor(a_vec_s *ctx, size_t size)
{
    assert(ctx);
    ctx->__size = size;
    ctx->__capacity = 0;
    ctx->__number = 0;
    ctx->__ptr = 0;
}

void a_vec_dtor(a_vec_s *ctx, void (*dtor)(void *))
{
    assert(ctx);
    if (ctx->__ptr)
    {
        if (dtor)
        {
            while (ctx->__number)
            {
                dtor(a_vec_at(ctx, --ctx->__number));
            }
        }
        free(ctx->__ptr);
        ctx->__ptr = 0;
    }
    ctx->__capacity = 0;
    ctx->__number = 0;
    ctx->__size = 0;
}

int a_vec_copy(a_vec_s *ctx, const a_vec_s *vec)
{
    assert(ctx);
    assert(vec);
    ctx->__ptr = malloc(vec->__capacity * vec->__size);
    if (ctx->__ptr == 0)
    {
        return ~0;
    }
    memcpy(ctx->__ptr, vec->__ptr, vec->__number * vec->__size);
    ctx->__capacity = vec->__capacity;
    ctx->__number = vec->__number;
    ctx->__size = vec->__size;
    return 0;
}

a_vec_s *a_vec_move(a_vec_s *ctx, a_vec_s *vec)
{
    assert(ctx);
    assert(vec);
    memcpy(ctx, vec, sizeof(a_vec_s));
    memset(vec, 0, sizeof(a_vec_s));
    return ctx;
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
    ctx->__number = 0;
    return 0;
}

void *a_vec_push(a_vec_s *ctx)
{
    assert(ctx);
    if (ctx->__capacity <= ctx->__number)
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
    return a_vec_at(ctx, ctx->__number++);
}

void *a_vec_pop(a_vec_s *ctx)
{
    assert(ctx);
    return ctx->__number ? a_vec_at(ctx, --ctx->__number) : 0;
}

#endif /* __STDC_HOSTED__ */
