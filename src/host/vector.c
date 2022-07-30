/*!
 @file vector.c
 @brief basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#if __STDC_HOSTED__

#include "a/host/vector.h"
#include "a/oop.h"

#include <assert.h>
#include <string.h>

#undef ARGS
#define ARGS a_size_t size
A_OOP_NEW_VA(a_vector_s, a_vector_new, a_vector_ctor, ARGS, size)
#undef ARGS
#define ARGS a_noret_t (*dtor)(a_vptr_t)
A_OOP_DIE_VA(a_vector_s, a_vector_die, a_vector_dtor, ARGS, dtor)
#undef ARGS

A_INLINE_FORCE a_vptr_t a_vector_inc_(a_vector_s *ctx)
{
    a_vptr_t last = ctx->__tail;
    ctx->__tail = (a_byte_t *)ctx->__tail + ctx->__size;
    return last;
}

A_INLINE_FORCE a_vptr_t a_vector_dec_(a_vector_s *ctx)
{
    ctx->__tail = (a_byte_t *)ctx->__tail - ctx->__size;
    return ctx->__tail;
}

A_INLINE_FORCE a_size_t a_vector_num_(const a_vector_s *ctx)
{
    return (a_size_t)((a_byte_t *)ctx->__tail - (a_byte_t *)ctx->__head);
}

A_INLINE_FORCE a_size_t a_vector_mem_(const a_vector_s *ctx)
{
    return (a_size_t)((a_byte_t *)ctx->__last - (a_byte_t *)ctx->__head);
}

a_noret_t a_vector_ctor(a_vector_s *ctx, a_size_t size)
{
    assert(ctx);
    assert(size);
    ctx->__head = a_null;
    ctx->__tail = a_null;
    ctx->__last = a_null;
    ctx->__size = size;
}

a_noret_t a_vector_dtor(a_vector_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (ctx->__head)
    {
        a_vector_drop(ctx, dtor);
        free(ctx->__head);
        ctx->__head = a_null;
    }
    ctx->__tail = a_null;
    ctx->__last = a_null;
    ctx->__size = a_zero;
}

a_int_t a_vector_copy(a_vector_s *ctx, const a_vector_s *obj, a_int_t (*dup)(a_vptr_t, a_cptr_t))
{
    assert(ctx);
    assert(obj);
    a_size_t num = a_vector_num_(obj);
    a_size_t mem = a_vector_mem_(obj);
    ctx->__head = malloc(mem);
    if (a_unlikely(ctx->__head == a_null))
    {
        return A_FAILURE;
    }
    ctx->__size = obj->__size;
    ctx->__tail = (a_byte_t *)ctx->__head + num;
    ctx->__last = (a_byte_t *)ctx->__head + mem;
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
        memcpy(ctx->__head, obj->__head, num);
    }
    return A_SUCCESS;
}

a_vector_s *a_vector_move(a_vector_s *ctx, a_vector_s *obj)
{
    assert(ctx);
    assert(obj);
    memcpy(ctx, obj, sizeof(a_vector_s));
    memset(obj, 000, sizeof(a_vector_s));
    return ctx;
}

a_int_t a_vector_resize(a_vector_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (a_unlikely(size == a_zero))
    {
        return A_FAILURE;
    }
    a_vector_drop(ctx, dtor);
    ctx->__size = size;
    return A_SUCCESS;
}

a_noret_t a_vector_drop(a_vector_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (dtor)
    {
        while (ctx->__head != ctx->__tail)
        {
            dtor(a_vector_dec_(ctx));
        }
    }
    else
    {
        ctx->__tail = ctx->__head;
    }
}

static a_int_t a_vector_alloc(a_vector_s *ctx, a_size_t num)
{
    a_size_t mem = a_vector_mem_(ctx) / ctx->__size;
    if (mem <= num)
    {
        a_size_t num_ = a_vector_num_(ctx);
        do
        {
            mem += (mem >> 1) + 1;
        } while (mem < num);
        a_size_t mem_ = ctx->__size * mem;
        a_size_t size = a_align(mem_, sizeof(a_vptr_t));
        a_vptr_t head = realloc(ctx->__head, size);
        if (a_unlikely(head == a_null))
        {
            return A_FAILURE;
        }
        ctx->__head = head;
        ctx->__tail = (a_byte_t *)head + num_;
        ctx->__last = (a_byte_t *)head + mem_;
    }
    return A_SUCCESS;
}

a_vptr_t a_vector_insert(a_vector_s *ctx, a_size_t idx)
{
    assert(ctx);
    a_size_t num = a_vector_num_(ctx) / ctx->__size;
    if (a_unlikely(a_vector_alloc(ctx, num)))
    {
        return a_null;
    }
    if (idx < num)
    {
        a_byte_t *ptr = (a_byte_t *)ctx->__tail;
        a_byte_t *src = (a_byte_t *)ctx->__head + ctx->__size * (idx + 0);
        a_byte_t *dst = (a_byte_t *)ctx->__head + ctx->__size * (idx + 1);
        memmove(dst, src, (a_size_t)(ptr - src));
        a_vector_inc_(ctx);
        return src;
    }
    return a_vector_inc_(ctx);
}

a_vptr_t a_vector_push_front(a_vector_s *ctx)
{
    assert(ctx);
    return a_vector_insert(ctx, 0);
}

a_vptr_t a_vector_push_back(a_vector_s *ctx)
{
    assert(ctx);
    a_size_t num = a_vector_num_(ctx) / ctx->__size;
    if (a_unlikely(a_vector_alloc(ctx, num)))
    {
        return a_null;
    }
    return a_vector_inc_(ctx);
}

a_vptr_t a_vector_remove(a_vector_s *ctx, a_size_t idx)
{
    assert(ctx);
    a_size_t num_ = a_vector_num_(ctx);
    a_size_t num = num_ / ctx->__size;
    if (idx + 1 < num)
    {
        if (a_unlikely(a_vector_alloc(ctx, num + 1)))
        {
            return a_null;
        }
        a_byte_t *ptr = (a_byte_t *)ctx->__tail;
        a_byte_t *dst = (a_byte_t *)ctx->__head + ctx->__size * (idx + 0);
        a_byte_t *src = (a_byte_t *)ctx->__head + ctx->__size * (idx + 1);
        memcpy(ptr, dst, ctx->__size);
        memmove(dst, src, (a_size_t)(ptr - src));
        a_vector_dec_(ctx);
        return ptr;
    }
    return a_likely(ctx->__head != ctx->__tail) ? a_vector_dec_(ctx) : a_null;
}

a_vptr_t a_vector_pop_front(a_vector_s *ctx)
{
    assert(ctx);
    return a_vector_remove(ctx, 0);
}

a_vptr_t a_vector_pop_back(a_vector_s *ctx)
{
    assert(ctx);
    return a_likely(ctx->__head != ctx->__tail) ? a_vector_dec_(ctx) : a_null;
}

#endif /* __STDC_HOSTED__ */
