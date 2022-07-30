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

#undef ARGS
#define ARGS a_size_t size
A_OOP_NEW_VA(a_vec_s, a_vec_new, a_vec_ctor, ARGS, size)
#undef ARGS
#define ARGS a_noret_t (*dtor)(a_vptr_t)
A_OOP_DIE_VA(a_vec_s, a_vec_die, a_vec_dtor, ARGS, dtor)
#undef ARGS

A_INLINE_FORCE a_vptr_t a_vec_inc_(a_vec_s *ctx)
{
    return (a_byte_t *)ctx->__ptr + ctx->__size * ctx->__number++;
}

A_INLINE_FORCE a_vptr_t a_vec_dec_(a_vec_s *ctx)
{
    return (a_byte_t *)ctx->__ptr + ctx->__size * --ctx->__number;
}

a_noret_t a_vec_ctor(a_vec_s *ctx, a_size_t size)
{
    assert(ctx);
    assert(size);
    ctx->__capacity = a_zero;
    ctx->__number = a_zero;
    ctx->__ptr = a_null;
    ctx->__size = size;
}

a_noret_t a_vec_dtor(a_vec_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (ctx->__ptr)
    {
        a_vec_drop(ctx, dtor);
        free(ctx->__ptr);
        ctx->__ptr = a_null;
    }
    ctx->__capacity = a_zero;
    ctx->__size = a_zero;
}

a_int_t a_vec_copy(a_vec_s *ctx, const a_vec_s *obj, a_int_t (*dup)(a_vptr_t, a_cptr_t))
{
    assert(ctx);
    assert(obj);
    ctx->__ptr = malloc(obj->__capacity * obj->__size);
    if (a_unlikely(ctx->__ptr == a_null))
    {
        return A_FAILURE;
    }
    ctx->__size = obj->__size;
    ctx->__number = obj->__number;
    ctx->__capacity = obj->__capacity;
    a_size_t size = obj->__number * obj->__size;
    if (dup)
    {
        a_byte_t *dst = (a_byte_t *)ctx->__ptr;
        a_byte_t *src = (a_byte_t *)obj->__ptr;
        for (a_size_t idx = 0; idx != size; idx += obj->__size)
        {
            dup(dst + idx, src + idx);
        }
    }
    else
    {
        memcpy(ctx->__ptr, obj->__ptr, size);
    }
    return A_SUCCESS;
}

a_vec_s *a_vec_move(a_vec_s *ctx, a_vec_s *obj)
{
    assert(ctx);
    assert(obj);
    memcpy(ctx, obj, sizeof(a_vec_s));
    memset(obj, 000, sizeof(a_vec_s));
    return ctx;
}

a_int_t a_vec_resize(a_vec_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (a_unlikely(size == a_zero))
    {
        return A_FAILURE;
    }
    a_vec_drop(ctx, dtor);
    ctx->__capacity = ctx->__size * ctx->__capacity / size;
    ctx->__size = size;
    return A_SUCCESS;
}

a_noret_t a_vec_drop(a_vec_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (dtor)
    {
        while (ctx->__number)
        {
            dtor(a_vec_dec_(ctx));
        }
    }
    else
    {
        ctx->__number = a_zero;
    }
}

static a_int_t a_vec_alloc(a_vec_s *ctx, a_size_t num)
{
    if (ctx->__capacity <= num)
    {
        a_size_t capacity = ctx->__capacity;
        do
        {
            capacity += (capacity >> 1) + 1;
        } while (capacity < num);
        a_size_t mem = a_align(capacity * ctx->__size, sizeof(a_vptr_t));
        a_vptr_t ptr = realloc(ctx->__ptr, mem);
        if (a_unlikely(ptr == a_null))
        {
            return A_FAILURE;
        }
        ctx->__capacity = capacity;
        ctx->__ptr = ptr;
    }
    return A_SUCCESS;
}

a_vptr_t a_vec_insert(a_vec_s *ctx, a_size_t idx)
{
    assert(ctx);
    if (a_unlikely(a_vec_alloc(ctx, ctx->__number)))
    {
        return a_null;
    }
    if (idx < ctx->__number)
    {
        a_byte_t *src = (a_byte_t *)ctx->__ptr + ctx->__size * idx;
        a_byte_t *dst = src + ctx->__size;
        memmove(dst, src, (ctx->__number - idx) * ctx->__size);
        ++ctx->__number;
        return src;
    }
    return a_vec_inc_(ctx);
}

a_vptr_t a_vec_push_front(a_vec_s *ctx)
{
    assert(ctx);
    return a_vec_insert(ctx, 0);
}

a_vptr_t a_vec_push_back(a_vec_s *ctx)
{
    assert(ctx);
    if (a_unlikely(a_vec_alloc(ctx, ctx->__number)))
    {
        return a_null;
    }
    return a_vec_inc_(ctx);
}

a_vptr_t a_vec_remove(a_vec_s *ctx, a_size_t idx)
{
    assert(ctx);
    if (idx + 1 < ctx->__number)
    {
        if (a_unlikely(a_vec_alloc(ctx, ctx->__number + 1)))
        {
            return a_null;
        }
        a_byte_t *ptr = (a_byte_t *)ctx->__ptr + ctx->__size * ctx->__number;
        a_byte_t *dst = (a_byte_t *)ctx->__ptr + ctx->__size * idx;
        a_byte_t *src = dst + ctx->__size;
        memcpy(ptr, dst, ctx->__size);
        memmove(dst, src, (a_size_t)(ptr - src));
        --ctx->__number;
        return ptr;
    }
    return a_likely(ctx->__number != a_zero) ? a_vec_dec_(ctx) : a_null;
}

a_vptr_t a_vec_pop_front(a_vec_s *ctx)
{
    assert(ctx);
    return a_vec_remove(ctx, 0);
}

a_vptr_t a_vec_pop_back(a_vec_s *ctx)
{
    assert(ctx);
    return a_likely(ctx->__number != a_zero) ? a_vec_dec_(ctx) : a_null;
}

#endif /* __STDC_HOSTED__ */
