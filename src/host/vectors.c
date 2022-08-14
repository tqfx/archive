/*!
 @file vectors.c
 @brief basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#if __STDC_HOSTED__

#include "a/host/vectors.h"

#include <assert.h>
#include <string.h>

A_INLINE_FORCE a_vptr_t a_vectors_inc_(a_vectors_s *ctx)
{
    a_vptr_t last = ctx->__tail;
    ctx->__tail = (a_byte_t *)ctx->__tail + ctx->__size;
    return (void)(++ctx->__num), last;
}

A_INLINE_FORCE a_vptr_t a_vectors_dec_(a_vectors_s *ctx)
{
    ctx->__tail = (a_byte_t *)ctx->__tail - ctx->__size;
    return (void)(--ctx->__num), ctx->__tail;
}

a_vectors_s *a_vectors_new(a_size_t size)
{
    a_vectors_s *ctx = (a_vectors_s *)malloc(sizeof(a_vectors_s));
    if (ctx)
    {
        a_vectors_ctor(ctx, size);
    }
    return ctx;
}

a_noret_t a_vectors_die(a_vectors_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    if (ctx)
    {
        a_vectors_dtor(ctx, dtor);
        free(ctx);
    }
}

a_noret_t a_vectors_ctor(a_vectors_s *ctx, a_size_t size)
{
    assert(ctx);
    assert(size);
    ctx->__size = size;
    ctx->__last = 0;
    ctx->__tail = 0;
    ctx->__head = 0;
    ctx->__num = 0;
    ctx->__mem = 0;
}

a_noret_t a_vectors_dtor(a_vectors_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (ctx->__head)
    {
        a_vectors_drop(ctx, dtor);
        free(ctx->__head);
        ctx->__head = 0;
    }
    ctx->__tail = 0;
    ctx->__last = 0;
    ctx->__size = 0;
    ctx->__num = 0;
    ctx->__mem = 0;
}

a_int_t a_vectors_copy(a_vectors_s *ctx, const a_vectors_s *obj, a_int_t (*dup)(a_vptr_t, a_cptr_t))
{
    assert(ctx);
    assert(obj);
    a_size_t num_ = obj->__num * obj->__size;
    a_size_t mem_ = obj->__mem * obj->__size;
    ctx->__head = malloc(mem_);
    if (a_unlikely(ctx->__head == 0))
    {
        return A_FAILURE;
    }
    ctx->__num = obj->__num;
    ctx->__mem = obj->__mem;
    ctx->__size = obj->__size;
    ctx->__tail = (a_byte_t *)ctx->__head + num_;
    ctx->__last = (a_byte_t *)ctx->__head + mem_;
    if (dup)
    {
        a_vptr_t dst = ctx->__head;
        a_vptr_t src = obj->__head;
        while (src != obj->__tail)
        {
            dup(dst, src);
            dst = (a_byte_t *)dst + obj->__size;
            src = (a_byte_t *)src + obj->__size;
        }
    }
    else
    {
        memcpy(ctx->__head, obj->__head, num_);
    }
    return A_SUCCESS;
}

a_vectors_s *a_vectors_move(a_vectors_s *ctx, a_vectors_s *obj)
{
    assert(ctx);
    assert(obj);
    memcpy(ctx, obj, sizeof(*obj));
    memset(obj, 0, sizeof(*obj));
    return ctx;
}

a_int_t a_vectors_set(a_vectors_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (a_unlikely(size == 0))
    {
        return A_FAILURE;
    }
    a_vectors_drop(ctx, dtor);
    ctx->__mem = ctx->__mem * ctx->__size / size;
    ctx->__size = size;
    return A_SUCCESS;
}

a_noret_t a_vectors_drop(a_vectors_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (dtor)
    {
        while (ctx->__head != ctx->__tail)
        {
            dtor(a_vectors_dec_(ctx));
        }
    }
    else
    {
        ctx->__tail = ctx->__head;
        ctx->__num = 0;
    }
}

static a_int_t a_vectors_alloc(a_vectors_s *ctx, a_size_t num)
{
    if (ctx->__mem <= num)
    {
        a_size_t mem = ctx->__mem;
        do
        {
            mem += (mem >> 1) + 1;
        } while (mem < num);
        a_size_t mem_ = mem * ctx->__size;
        a_size_t num_ = ctx->__num * ctx->__size;
        a_size_t size = a_align(sizeof(a_vptr_t), mem_);
        a_vptr_t head = realloc(ctx->__head, size);
        if (a_unlikely(head == 0))
        {
            return A_FAILURE;
        }
        ctx->__mem = mem;
        ctx->__head = head;
        ctx->__tail = (a_byte_t *)head + num_;
        ctx->__last = (a_byte_t *)head + mem_;
    }
    return A_SUCCESS;
}

a_int_t a_vectors_swap(a_vectors_s *ctx, a_size_t lhs, a_size_t rhs)
{
    assert(ctx);
    {
        const a_size_t num = ctx->__num - 1;
        lhs = lhs < ctx->__num ? lhs : num;
        rhs = rhs < ctx->__num ? rhs : num;
    }
    if (lhs == rhs)
    {
        return A_SUCCESS;
    }
    const a_size_t num = ctx->__num;
    if (a_unlikely(a_vectors_alloc(ctx, num)))
    {
        return A_FAILURE;
    }
    a_vptr_t pt = (a_byte_t *)ctx->__head + ctx->__size * num;
    a_vptr_t pl = (a_byte_t *)ctx->__head + ctx->__size * lhs;
    a_vptr_t pr = (a_byte_t *)ctx->__head + ctx->__size * rhs;
    memcpy(pt, pl, ctx->__size);
    memcpy(pl, pr, ctx->__size);
    memcpy(pr, pt, ctx->__size);
    return A_SUCCESS;
}

a_vptr_t a_vectors_insert(a_vectors_s *ctx, a_size_t idx)
{
    assert(ctx);
    if (a_unlikely(a_vectors_alloc(ctx, ctx->__num)))
    {
        return 0;
    }
    if (idx < ctx->__num)
    {
        a_byte_t *ptr = (a_byte_t *)ctx->__tail;
        a_byte_t *src = (a_byte_t *)ctx->__head + ctx->__size * (idx + 0);
        a_byte_t *dst = (a_byte_t *)ctx->__head + ctx->__size * (idx + 1);
        memmove(dst, src, (a_size_t)(ptr - src));
        a_vectors_inc_(ctx);
        return src;
    }
    return a_vectors_inc_(ctx);
}

a_vptr_t a_vectors_push_fore(a_vectors_s *ctx)
{
    assert(ctx);
    return a_vectors_insert(ctx, 0);
}

a_vptr_t a_vectors_push_back(a_vectors_s *ctx)
{
    assert(ctx);
    if (a_unlikely(a_vectors_alloc(ctx, ctx->__num)))
    {
        return 0;
    }
    return a_vectors_inc_(ctx);
}

a_vptr_t a_vectors_remove(a_vectors_s *ctx, a_size_t idx)
{
    assert(ctx);
    if (ctx->__num && idx < ctx->__num - 1)
    {
        if (a_unlikely(a_vectors_alloc(ctx, ctx->__num)))
        {
            return 0;
        }
        a_byte_t *ptr = (a_byte_t *)ctx->__tail;
        a_byte_t *dst = (a_byte_t *)ctx->__head + ctx->__size * (idx + 0);
        a_byte_t *src = (a_byte_t *)ctx->__head + ctx->__size * (idx + 1);
        memcpy(ptr, dst, ctx->__size);
        memmove(dst, src, (a_size_t)(ptr - src));
        a_vectors_dec_(ctx);
        return ptr;
    }
    return a_likely(ctx->__head != ctx->__tail) ? a_vectors_dec_(ctx) : 0;
}

a_vptr_t a_vectors_pull_fore(a_vectors_s *ctx)
{
    assert(ctx);
    return a_vectors_remove(ctx, 0);
}

a_vptr_t a_vectors_pull_back(a_vectors_s *ctx)
{
    assert(ctx);
    return a_likely(ctx->__head != ctx->__tail) ? a_vectors_dec_(ctx) : 0;
}

#endif /* __STDC_HOSTED__ */
