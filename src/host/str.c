/*!
 @file str.c
 @brief basic string library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#if __STDC_HOSTED__

#include "a/host/str.h"
#include "a/oop.h"

#include <assert.h>
#include <stdio.h>

A_OOP_NEW(a_str_s, a_str_new, a_str_ctor)
A_OOP_DIE(a_str_s, a_str_die, a_str_dtor)

void a_str_ctor(a_str_s *ctx)
{
    assert(ctx);
    ctx->__mem = 0;
    ctx->__num = 0;
    ctx->__str = 0;
}

void a_str_dtor(a_str_s *ctx)
{
    assert(ctx);
    ctx->__mem = 0;
    ctx->__num = 0;
    if (ctx->__str)
    {
        free(ctx->__str);
        ctx->__str = 0;
    }
}

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

int a_str_init(a_str_s *ctx, const void *pdata, size_t nbyte)
{
    assert(ctx);
    ctx->__num = nbyte;
    ctx->__mem = nbyte + 1;
    roundup32(ctx->__mem);
    ctx->__str = (char *)malloc(ctx->__mem);
    if (ctx->__str == 0)
    {
        return ~0;
    }
    if (pdata && nbyte)
    {
        memcpy(ctx->__str, pdata, nbyte);
    }
    ctx->__str[ctx->__num] = 0;
    return 0;
}

int a_str_copy(a_str_s *ctx, const a_str_s *str)
{
    assert(ctx);
    assert(str);
    return a_str_init(ctx, str->__str, str->__num);
}

a_str_s *a_str_move(a_str_s *ctx, a_str_s *str)
{
    assert(ctx);
    assert(str);
    memcpy(ctx, str, sizeof(a_str_s));
    memset(str, 0, sizeof(a_str_s));
    return ctx;
}

char *a_str_exit(a_str_s *ctx)
{
    assert(ctx);
    char *str = ctx->__str;
    if (ctx->__str)
    {
        ctx->__str[ctx->__num] = 0;
        ctx->__str = 0;
    }
    ctx->__mem = 0;
    ctx->__num = 0;
    return str;
}

int a_str_resize_(a_str_s *ctx, size_t mem)
{
    assert(ctx);
    roundup32(mem);
    char *str = (char *)realloc(ctx->__str, mem);
    if (!str && mem)
    {
        return ~0;
    }
    ctx->__str = str;
    ctx->__mem = mem;
    return 0;
}

int a_str_resize(a_str_s *ctx, size_t mem)
{
    assert(ctx);
    if (ctx->__mem < mem)
    {
        return a_str_resize_(ctx, mem);
    }
    return 0;
}

int a_str_putc_(a_str_s *ctx, int c)
{
    assert(ctx);
    if (a_str_resize(ctx, ctx->__num + 1))
    {
        return ~0;
    }
    ctx->__str[ctx->__num++] = (char)c;
    return c;
}

int a_str_putc(a_str_s *ctx, int c)
{
    assert(ctx);
    if (c == 0)
    {
        return a_str_putc_(ctx, c);
    }
    if (a_str_resize(ctx, ctx->__num + 2))
    {
        return ~0;
    }
    ctx->__str[ctx->__num++] = (char)c;
    ctx->__str[ctx->__num] = 0;
    return c;
}

int a_str_putn_(a_str_s *ctx, const void *pdata, size_t nbyte)
{
    assert(ctx);
    if (pdata && nbyte)
    {
        if (a_str_resize(ctx, ctx->__num + nbyte))
        {
            return ~0;
        }
        memcpy(ctx->__str + ctx->__num, pdata, nbyte);
        ctx->__num += nbyte;
    }
    return 0;
}

int a_str_putn(a_str_s *ctx, const void *pdata, size_t nbyte)
{
    assert(ctx);
    if (pdata)
    {
        if (a_str_resize(ctx, ctx->__num + nbyte + 1))
        {
            return ~0;
        }
        if (nbyte)
        {
            memcpy(ctx->__str + ctx->__num, pdata, nbyte);
            ctx->__num += nbyte;
        }
        ctx->__str[ctx->__num] = 0;
    }
    return 0;
}

int a_str_puts(a_str_s *ctx, const void *str)
{
    assert(ctx);
    assert(str);
    return a_str_putn(ctx, str, strlen((const char *)str));
}

int a_str_vprintf(a_str_s *ctx, const char *fmt, va_list va)
{
    assert(ctx);
    assert(fmt);
    va_list ap;
    va_copy(ap, va);
    char *str = ctx->__str ? (ctx->__str + ctx->__num) : 0;
    int ret = vsnprintf(str, ctx->__mem - ctx->__num, fmt, ap);
    va_end(ap);
    size_t size = (size_t)ret + 1;
    if (ctx->__mem - ctx->__num < size)
    {
        if (a_str_resize_(ctx, ctx->__num + size))
        {
            return ~0;
        }
        va_copy(ap, va);
        str = ctx->__str + ctx->__num;
        ret = vsnprintf(str, ctx->__mem - ctx->__num, fmt, ap);
        va_end(ap);
    }
    ctx->__num += (size_t)ret;
    return ret;
}

int a_str_printf(a_str_s *ctx, const char *fmt, ...)
{
    assert(ctx);
    assert(fmt);
    va_list ap;
    va_start(ap, fmt);
    int ret = a_str_vprintf(ctx, fmt, ap);
    va_end(ap);
    return ret;
}

#endif /* __STDC_HOSTED__ */
