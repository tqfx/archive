/*!
 @file vec.c
 @brief basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#if __STDC_HOSTED__

#include "a/host/vec.h"
#include "a/oop.h"

#include <assert.h>
#include <string.h>

#undef nil
#define nil 0

#undef ARGS
#define ARGS a_size_t size
A_OOP_NEW_VA(a_vec_s, a_vec_new, a_vec_ctor, ARGS, size)
#undef ARGS
#define ARGS a_noret_t (*dtor)(a_vptr_t)
A_OOP_DIE_VA(a_vec_s, a_vec_die, a_vec_dtor, ARGS, dtor)
#undef ARGS

a_noret_t a_vec_ctor(a_vec_s *ctx, a_size_t size)
{
    assert(ctx);
    ctx->__capacity = a_zero;
    ctx->__number = a_zero;
    ctx->__ptr = a_null;
    ctx->__size = size;
}

A_INLINE_FORCE a_vptr_t a_vec_inc_(a_vec_s *ctx) { return (a_byte_t *)ctx->__ptr + ctx->__size * ctx->__number++; }
A_INLINE_FORCE a_vptr_t a_vec_dec_(a_vec_s *ctx) { return (a_byte_t *)ctx->__ptr + ctx->__size * --ctx->__number; }

a_noret_t a_vec_dtor(a_vec_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (ctx->__ptr)
    {
        if (dtor)
        {
            while (ctx->__number)
            {
                dtor(a_vec_dec_(ctx));
            }
        }
        free(ctx->__ptr);
        ctx->__ptr = a_null;
    }
    ctx->__capacity = a_zero;
    ctx->__number = a_zero;
    ctx->__size = a_zero;
}

a_int_t a_vec_resize(a_vec_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (size == a_zero)
    {
        return A_FAILURE;
    }
    if (dtor)
    {
        while (ctx->__number)
        {
            dtor(a_vec_dec_(ctx));
        }
    }
    ctx->__capacity = ctx->__size * ctx->__capacity / size;
    ctx->__number = a_zero;
    ctx->__size = size;
    return A_SUCCESS;
}

a_int_t a_vec_copy(a_vec_s *ctx, const a_vec_s *obj)
{
    assert(ctx);
    assert(obj);
    ctx->__ptr = malloc(obj->__capacity * obj->__size);
    if (ctx->__ptr == a_null)
    {
        return A_FAILURE;
    }
    memcpy(ctx->__ptr, obj->__ptr, obj->__number * obj->__size);
    ctx->__capacity = obj->__capacity;
    ctx->__number = obj->__number;
    ctx->__size = obj->__size;
    return A_SUCCESS;
}

a_vec_s *a_vec_move(a_vec_s *ctx, a_vec_s *obj)
{
    assert(ctx);
    assert(obj);
    memcpy(ctx, obj, sizeof(a_vec_s));
    memset(obj, nil, sizeof(a_vec_s));
    return ctx;
}

a_vptr_t a_vec_push(a_vec_s *ctx)
{
    assert(ctx);
    if (ctx->__number >= ctx->__capacity)
    {
        a_size_t capacity = ctx->__capacity + (ctx->__capacity >> 1) + 1;
        a_vptr_t ptr = realloc(ctx->__ptr, capacity * ctx->__size);
        if (ptr == a_null)
        {
            return a_null;
        }
        ctx->__capacity = capacity;
        ctx->__ptr = ptr;
    }
    return a_vec_inc_(ctx);
}

a_vptr_t a_vec_pop(a_vec_s *ctx)
{
    assert(ctx);
    return a_likely(ctx->__number != a_zero) ? a_vec_dec_(ctx) : a_null;
}

#endif /* __STDC_HOSTED__ */
