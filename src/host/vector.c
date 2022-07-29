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
    a_vptr_t last = ctx->__last;
    ctx->__last = (a_byte_t *)ctx->__last + ctx->__size;
    return last;
}

A_INLINE_FORCE a_vptr_t a_vector_dec_(a_vector_s *ctx)
{
    ctx->__last = (a_byte_t *)ctx->__last - ctx->__size;
    return ctx->__last;
}

A_INLINE_FORCE a_size_t a_vector_num_(a_vector_s *ctx)
{
    return (a_size_t)((a_byte_t *)ctx->__last - (a_byte_t *)ctx->__head);
}

A_INLINE_FORCE a_size_t a_vector_mem_(a_vector_s *ctx)
{
    return (a_size_t)((a_byte_t *)ctx->__tail - (a_byte_t *)ctx->__head);
}

a_noret_t a_vector_ctor(a_vector_s *ctx, a_size_t size)
{
    assert(ctx);
    ctx->__head = a_null;
    ctx->__last = a_null;
    ctx->__tail = a_null;
    ctx->__size = size;
}

a_noret_t a_vector_dtor(a_vector_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (ctx->__head)
    {
        if (dtor)
        {
            while (ctx->__head != ctx->__last)
            {
                dtor(a_vector_dec_(ctx));
            }
        }
        free(ctx->__head);
        ctx->__head = a_null;
    }
    ctx->__last = a_null;
    ctx->__tail = a_null;
    ctx->__size = a_zero;
}

a_int_t a_vector_resize(a_vector_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (size == a_zero)
    {
        return A_FAILURE;
    }
    if (dtor)
    {
        while (ctx->__head != ctx->__last)
        {
            dtor(a_vector_dec_(ctx));
        }
    }
    ctx->__last = ctx->__head;
    ctx->__size = size;
    return A_SUCCESS;
}

a_int_t a_vector_copy(a_vector_s *ctx, const a_vector_s *obj)
{
    assert(ctx);
    assert(obj);
    a_size_t num = a_vector_num_(ctx);
    a_size_t mem = a_vector_mem_(ctx);
    ctx->__head = malloc(mem);
    if (ctx->__head == a_null)
    {
        return A_FAILURE;
    }
    memcpy(ctx->__head, obj->__head, num);
    ctx->__last = (a_byte_t *)ctx->__head + num;
    ctx->__tail = (a_byte_t *)ctx->__head + mem;
    ctx->__size = obj->__size;
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

a_vptr_t a_vector_push(a_vector_s *ctx)
{
    assert(ctx);
    if (ctx->__last >= ctx->__tail)
    {
        a_size_t num = a_vector_num_(ctx);
        a_size_t mem = a_vector_mem_(ctx) / ctx->__size;
        mem = (mem + (mem >> 1) + 1) * ctx->__size;
        a_vptr_t head = realloc(ctx->__head, a_align(mem, sizeof(a_vptr_t)));
        if (head == a_null)
        {
            return a_null;
        }
        ctx->__head = head;
        ctx->__last = (a_byte_t *)head + num;
        ctx->__tail = (a_byte_t *)head + mem;
    }
    return a_vector_inc_(ctx);
}

a_vptr_t a_vector_pop(a_vector_s *ctx)
{
    assert(ctx);
    return a_likely(ctx->__head != ctx->__last) ? a_vector_dec_(ctx) : a_null;
}

#endif /* __STDC_HOSTED__ */
