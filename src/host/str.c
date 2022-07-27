/*!
 @file str.c
 @brief basic string library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#if __STDC_HOSTED__

#include "a/host/str.h"
#include "a/oop.h"

#include <assert.h>
#include <stdio.h>

A_OOP_NEW(a_str_s, a_str_new, a_str_ctor)
A_OOP_DIE(a_str_s, a_str_die, a_str_dtor)

a_noret_t a_str_ctor(a_str_s *ctx)
{
    assert(ctx);
    ctx->__mem = a_zero;
    ctx->__num = a_zero;
    ctx->__str = a_null;
}

a_noret_t a_str_dtor(a_str_s *ctx)
{
    assert(ctx);
    ctx->__mem = a_zero;
    ctx->__num = a_zero;
    if (ctx->__str)
    {
        free(ctx->__str);
        ctx->__str = a_null;
    }
}

#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wcomma"
#endif /* __clang__ */

#undef nil
#define nil 0

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
    if (ctx->__str == a_null)
    {
        return A_FAILURE;
    }
    if (pdata && nbyte)
    {
        memcpy(ctx->__str, pdata, nbyte);
    }
    ctx->__str[ctx->__num] = nil;
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
    memset(obj, nil, sizeof(a_str_s));
    return ctx;
}

a_str_t a_str_exit(a_str_s *ctx)
{
    assert(ctx);
    a_str_t str = ctx->__str;
    if (ctx->__str)
    {
        ctx->__str[ctx->__num] = nil;
        ctx->__str = a_null;
    }
    ctx->__mem = a_zero;
    ctx->__num = a_zero;
    return str;
}

a_int_t a_str_resize_(a_str_s *ctx, a_size_t mem)
{
    assert(ctx);
    a_str_t str = (a_str_t)realloc(ctx->__str, roundup32(mem));
    if (!str && mem)
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
    if (a_str_resize(ctx, ctx->__num + 1))
    {
        return EOF;
    }
    ctx->__str[ctx->__num++] = (a_char_t)c;
    return c;
}

a_int_t a_str_putc(a_str_s *ctx, a_int_t c)
{
    assert(ctx);
    if (c == nil)
    {
        return a_str_putc_(ctx, c);
    }
    if (a_str_resize(ctx, ctx->__num + 2))
    {
        return EOF;
    }
    ctx->__str[ctx->__num++] = (a_char_t)c;
    ctx->__str[ctx->__num] = nil;
    return c;
}

a_int_t a_str_putn_(a_str_s *ctx, a_cptr_t pdata, a_size_t nbyte)
{
    assert(ctx);
    if (pdata && nbyte)
    {
        if (a_str_resize(ctx, ctx->__num + nbyte))
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
        if (a_str_resize(ctx, ctx->__num + nbyte + 1))
        {
            return A_FAILURE;
        }
        if (nbyte)
        {
            memcpy(ctx->__str + ctx->__num, pdata, nbyte);
            ctx->__num += nbyte;
        }
        ctx->__str[ctx->__num] = nil;
    }
    return A_SUCCESS;
}

a_int_t a_str_puts(a_str_s *ctx, a_cptr_t str)
{
    assert(ctx);
    assert(str);
    return a_str_putn(ctx, str, strlen((a_cstr_t)str));
}

a_int_t a_str_vprintf(a_str_s *ctx, a_cstr_t fmt, va_list va)
{
    assert(ctx);
    assert(fmt);
    va_list ap;
    va_copy(ap, va);
    a_str_t str = ctx->__str ? ctx->__str + ctx->__num : a_null;
    a_int_t ret = vsnprintf(str, ctx->__mem - ctx->__num, fmt, ap);
    va_end(ap);
    a_size_t size = (a_size_t)ret + 1;
    if (ctx->__mem - ctx->__num < size)
    {
        if (a_str_resize_(ctx, ctx->__num + size))
        {
            return EOF;
        }
        va_copy(ap, va);
        str = ctx->__str + ctx->__num;
        ret = vsnprintf(str, ctx->__mem - ctx->__num, fmt, ap);
        va_end(ap);
    }
    ctx->__num += (a_size_t)ret;
    return ret;
}

a_int_t a_str_printf(a_str_s *ctx, a_cstr_t fmt, ...)
{
    assert(ctx);
    assert(fmt);
    va_list ap;
    va_start(ap, fmt);
    a_int_t ret = a_str_vprintf(ctx, fmt, ap);
    va_end(ap);
    return ret;
}

#endif /* __STDC_HOSTED__ */
