/*!
 @file str.c
 @brief basic string library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#if __STDC_HOSTED__

#include "a/host/str.h"

#include <assert.h>
#include <stdio.h>

a_str_s *a_str_new(a_noarg_t)
{
    a_str_s *ctx = (a_str_s *)malloc(sizeof(a_str_s));
    if (ctx)
    {
        a_str_ctor(ctx);
    }
    return ctx;
}

a_noret_t a_str_die(a_str_s *ctx)
{
    if (ctx)
    {
        a_str_dtor(ctx);
        free(ctx);
    }
}

a_noret_t a_str_ctor(a_str_s *ctx)
{
    assert(ctx);
    ctx->__str = a_null;
    ctx->__num = a_zero;
    ctx->__mem = a_zero;
}

a_noret_t a_str_dtor(a_str_s *ctx)
{
    assert(ctx);
    if (ctx->__str)
    {
        free(ctx->__str);
        ctx->__str = a_null;
    }
    ctx->__num = a_zero;
    ctx->__mem = a_zero;
}

#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wcomma"
#endif /* __clang__ */

#ifndef roundup32
#define roundup32(x)     \
    (--(x),              \
     (x) |= (x) >> 0x01, \
     (x) |= (x) >> 0x02, \
     (x) |= (x) >> 0x04, \
     (x) |= (x) >> 0x08, \
     (x) |= (x) >> 0x10, \
     ++(x))
#endif /* roundup32 */

a_int_t a_str_init(a_str_s *ctx, a_cptr_t pdata, a_size_t nbyte)
{
    assert(ctx);
    ctx->__num = nbyte;
    ctx->__mem = nbyte + 1;
    ctx->__str = (a_str_t)malloc(roundup32(ctx->__mem));
    if (a_unlikely(ctx->__str == a_null))
    {
        return A_FAILURE;
    }
    if (pdata && nbyte)
    {
        memcpy(ctx->__str, pdata, nbyte);
    }
    ctx->__str[ctx->__num] = 0;
    return A_SUCCESS;
}

a_int_t a_str_copy(a_str_s *ctx, const a_str_s *obj)
{
    assert(ctx);
    assert(obj);
    return a_str_init(ctx, obj->__str, obj->__num);
}

a_str_s *a_str_move(a_str_s *ctx, a_str_s *obj)
{
    assert(ctx);
    assert(obj);
    memcpy(ctx, obj, sizeof(a_str_s));
    memset(obj, 000, sizeof(a_str_s));
    return ctx;
}

a_str_t a_str_exit(a_str_s *ctx)
{
    assert(ctx);
    a_str_t str = ctx->__str;
    if (ctx->__str)
    {
        ctx->__str[ctx->__num] = 0;
        ctx->__str = a_null;
    }
    ctx->__mem = a_zero;
    ctx->__num = a_zero;
    return str;
}

a_int_t a_str_cmp(const a_str_s *lhs, const a_str_s *rhs)
{
    assert(lhs);
    assert(rhs);
    a_int_t ok = 0;
    if (lhs->__str && rhs->__str)
    {
        a_size_t num = lhs->__num < rhs->__num ? lhs->__num : rhs->__num;
        ok = memcmp(lhs->__str, rhs->__str, num);
    }
    if (ok)
    {
        return ok;
    }
    if (lhs->__num == rhs->__num)
    {
        return a_zero;
    }
    return lhs->__num < rhs->__num ? -1 : 1;
}

a_int_t a_str_resize_(a_str_s *ctx, a_size_t mem)
{
    assert(ctx);
    a_str_t str = (a_str_t)realloc(ctx->__str, roundup32(mem));
    if (a_unlikely(!str && mem))
    {
        return A_FAILURE;
    }
    ctx->__str = str;
    ctx->__mem = mem;
    return A_SUCCESS;
}

a_int_t a_str_resize(a_str_s *ctx, a_size_t mem)
{
    assert(ctx);
    return ctx->__mem < mem ? a_str_resize_(ctx, mem) : A_SUCCESS;
}

a_int_t a_str_putc_(a_str_s *ctx, a_int_t c)
{
    assert(ctx);
    if (a_unlikely(a_str_resize(ctx, ctx->__num + 1)))
    {
        return EOF;
    }
    ctx->__str[ctx->__num++] = (a_char_t)c;
    return c;
}

a_int_t a_str_putc(a_str_s *ctx, a_int_t c)
{
    assert(ctx);
    if (a_unlikely(c == 0))
    {
        return a_str_putc_(ctx, c);
    }
    if (a_unlikely(a_str_resize(ctx, ctx->__num + 2)))
    {
        return EOF;
    }
    ctx->__str[ctx->__num++] = (a_char_t)c;
    ctx->__str[ctx->__num] = 0;
    return c;
}

a_int_t a_str_putn_(a_str_s *ctx, a_cptr_t pdata, a_size_t nbyte)
{
    assert(ctx);
    if (pdata && nbyte)
    {
        if (a_unlikely(a_str_resize(ctx, ctx->__num + nbyte)))
        {
            return A_FAILURE;
        }
        memcpy(ctx->__str + ctx->__num, pdata, nbyte);
        ctx->__num += nbyte;
    }
    return A_SUCCESS;
}

a_int_t a_str_putn(a_str_s *ctx, a_cptr_t pdata, a_size_t nbyte)
{
    assert(ctx);
    if (pdata)
    {
        if (a_unlikely(a_str_resize(ctx, ctx->__num + nbyte + 1)))
        {
            return A_FAILURE;
        }
        if (nbyte)
        {
            memcpy(ctx->__str + ctx->__num, pdata, nbyte);
            ctx->__num += nbyte;
        }
        ctx->__str[ctx->__num] = 0;
    }
    return A_SUCCESS;
}

a_int_t a_str_puts(a_str_s *ctx, a_cptr_t str)
{
    assert(ctx);
    assert(str);
    return a_str_putn(ctx, str, strlen((a_cstr_t)str));
}

a_int_t a_str_cat(a_str_s *ctx, const a_str_s *obj)
{
    assert(ctx);
    assert(obj);
    return a_str_putn(ctx, obj->__str, obj->__num);
}

a_int_t a_str_vprintf(a_str_s *ctx, a_cstr_t fmt, va_list va)
{
    assert(ctx);
    assert(fmt);
    va_list ap;
    va_copy(ap, va);
    a_str_t str = ctx->__str ? ctx->__str + ctx->__num : a_null;
    a_int_t num = vsnprintf(str, ctx->__mem - ctx->__num, fmt, ap);
    va_end(ap);
    a_size_t size = (a_size_t)num + 1;
    if (ctx->__mem - ctx->__num < size)
    {
        if (a_unlikely(a_str_resize_(ctx, ctx->__num + size)))
        {
            return EOF;
        }
        va_copy(ap, va);
        str = ctx->__str + ctx->__num;
        num = vsnprintf(str, ctx->__mem - ctx->__num, fmt, ap);
        va_end(ap);
    }
    ctx->__num += (a_size_t)num;
    return num;
}

a_int_t a_str_printf(a_str_s *ctx, a_cstr_t fmt, ...)
{
    assert(ctx);
    assert(fmt);
    va_list ap;
    va_start(ap, fmt);
    a_int_t num = a_str_vprintf(ctx, fmt, ap);
    va_end(ap);
    return num;
}

#endif /* __STDC_HOSTED__ */
