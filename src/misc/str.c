/*!
 @file str.c
 @brief basic string library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/misc/str.h"
#include "a/oop.h"

#include <assert.h>
#include <stdio.h>

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

A_OOP_NEW(a_str_s, a_str_new, a_str_ctor)
A_OOP_DIE(a_str_s, a_str_die, a_str_dtor)

void a_str_ctor(a_str_s *ctx)
{
    assert(ctx);
    ctx->__m = 0;
    ctx->__n = 0;
    ctx->__s = 0;
}

void a_str_dtor(a_str_s *ctx)
{
    assert(ctx);
    ctx->__m = 0;
    ctx->__n = 0;
    if (ctx->__s)
    {
        free(ctx->__s);
        ctx->__s = 0;
    }
}

int a_str_init(a_str_s *ctx, const void *pdata, size_t nbyte)
{
    assert(ctx);
    ctx->__n = nbyte;
    ctx->__m = nbyte + 1;
    roundup32(ctx->__m);
    ctx->__s = (char *)malloc(ctx->__m);
    if (ctx->__s == 0)
    {
        return ~0;
    }
    if (pdata && nbyte)
    {
        memcpy(ctx->__s, pdata, nbyte);
    }
    ctx->__s[ctx->__n] = 0;
    return 0;
}

int a_str_copy(a_str_s *ctx, const a_str_s *in)
{
    assert(in);
    assert(ctx);
    return a_str_init(ctx, in->__s, in->__n);
}

void a_str_move(a_str_s *ctx, a_str_s *in)
{
    assert(in);
    assert(ctx);
    memcpy(ctx, in, sizeof(a_str_s));
    memset(in, 0, sizeof(a_str_s));
}

char *a_str_done(a_str_s *ctx)
{
    assert(ctx);
    char *s = ctx->__s;
    if (ctx->__s)
    {
        ctx->__s[ctx->__n] = 0;
        ctx->__s = 0;
    }
    ctx->__m = 0;
    ctx->__n = 0;
    return s;
}

int a_str_resize_(a_str_s *ctx, size_t m)
{
    assert(ctx);
    roundup32(m);
    char *s = (char *)realloc(ctx->__s, m);
    if (!s && m)
    {
        return ~0;
    }
    ctx->__s = s;
    ctx->__m = m;
    return 0;
}

int a_str_resize(a_str_s *ctx, size_t m)
{
    assert(ctx);
    if (ctx->__m < m)
    {
        return a_str_resize_(ctx, m);
    }
    return 0;
}

int a_str_putc_(a_str_s *ctx, int c)
{
    assert(ctx);
    if (a_str_resize(ctx, ctx->__n + 1))
    {
        return ~0;
    }
    ctx->__s[ctx->__n++] = (char)c;
    return c;
}

int a_str_putc(a_str_s *ctx, int c)
{
    assert(ctx);
    if (c == 0)
    {
        return a_str_putc_(ctx, c);
    }
    if (a_str_resize(ctx, ctx->__n + 2))
    {
        return ~0;
    }
    ctx->__s[ctx->__n++] = (char)c;
    ctx->__s[ctx->__n] = 0;
    return c;
}

int a_str_putn_(a_str_s *ctx, const void *pdata, size_t nbyte)
{
    assert(ctx);
    if (pdata && nbyte)
    {
        if (a_str_resize(ctx, ctx->__n + nbyte))
        {
            return ~0;
        }
        memcpy(ctx->__s + ctx->__n, pdata, nbyte);
        ctx->__n += nbyte;
    }
    return 0;
}

int a_str_putn(a_str_s *ctx, const void *pdata, size_t nbyte)
{
    assert(ctx);
    if (pdata)
    {
        if (a_str_resize(ctx, ctx->__n + nbyte + 1))
        {
            return ~0;
        }
        if (nbyte)
        {
            memcpy(ctx->__s + ctx->__n, pdata, nbyte);
            ctx->__n += nbyte;
        }
        ctx->__s[ctx->__n] = 0;
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
    char *s = ctx->__s ? (ctx->__s + ctx->__n) : 0;
    int ret = vsnprintf(s, ctx->__m - ctx->__n, fmt, ap);
    va_end(ap);
    if (ctx->__m - ctx->__n < (size_t)ret + 1)
    {
        if (a_str_resize_(ctx, ctx->__n + (size_t)ret + 1))
        {
            return ~0;
        }
        va_copy(ap, va);
        s = ctx->__s + ctx->__n;
        ret = vsnprintf(s, ctx->__m - ctx->__n, fmt, ap);
        va_end(ap);
    }
    ctx->__n += (size_t)ret;
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
