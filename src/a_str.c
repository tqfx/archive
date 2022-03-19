/*!
 @file a_str.c
 @brief basic string library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_str.h"

#include "a_object.h"

#include <stdio.h> /* vsnprintf */

A_OBJECT_CREATE(a_str_s, a_str_new, a_str_ctor)
A_OBJECT_DELETE(a_str_s, a_str_delete, a_str_dtor)

void a_str_ctor(a_str_s *ctx)
{
    AASSERT(ctx);
    ctx->m = 0;
    ctx->n = 0;
    ctx->s = 0;
}

void a_str_dtor(a_str_s *ctx)
{
    AASSERT(ctx);
    ctx->m = 0;
    ctx->n = 0;
    if (ctx->s)
    {
        free(ctx->s);
        ctx->s = 0;
    }
}

void a_str_init(a_str_s *ctx, const void *pdata, size_t nbyte)
{
    AASSERT(ctx);
    ctx->n = nbyte;
    ctx->m = nbyte + 1;
    AROUNDUP32(ctx->m);
    ctx->s = (char *)malloc(ctx->m);
    if (pdata && nbyte)
    {
        memcpy(ctx->s, pdata, nbyte);
    }
    ctx->s[ctx->n] = 0;
}

char *a_str_done(a_str_s *ctx)
{
    AASSERT(ctx);
    char *s = ctx->s;
    if (ctx->s)
    {
        ctx->s[ctx->n] = 0;
        ctx->s = 0;
    }
    ctx->m = 0;
    ctx->n = 0;
    return s;
}

int a_str_resize_(a_str_s *ctx, size_t m)
{
    AASSERT(ctx);
    AROUNDUP32(m);
    char *s = (char *)realloc(ctx->s, m);
    if (!s && m)
    {
        return ~0;
    }
    ctx->s = s;
    ctx->m = m;
    return 0;
}

int a_str_resize(a_str_s *ctx, size_t m)
{
    AASSERT(ctx);
    if (ctx->m < m)
    {
        return a_str_resize_(ctx, m);
    }
    return 0;
}

int a_str_putc_(a_str_s *ctx, int c)
{
    AASSERT(ctx);
    if (a_str_resize(ctx, ctx->n + 1))
    {
        return ~0;
    }
    ctx->s[ctx->n++] = (char)c;
    return c;
}

int a_str_putc(a_str_s *ctx, int c)
{
    AASSERT(ctx);
    if (c == 0)
    {
        return a_str_putc_(ctx, c);
    }
    if (a_str_resize(ctx, ctx->n + 2))
    {
        return ~0;
    }
    ctx->s[ctx->n++] = (char)c;
    ctx->s[ctx->n] = 0;
    return c;
}

int a_str_putn_(a_str_s *ctx, const void *pdata, size_t nbyte)
{
    AASSERT(ctx);
    if (pdata && nbyte)
    {
        if (a_str_resize(ctx, ctx->n + nbyte))
        {
            return ~0;
        }
        memcpy(ctx->s + ctx->n, pdata, nbyte);
        ctx->n += nbyte;
    }
    return 0;
}

int a_str_putn(a_str_s *ctx, const void *pdata, size_t nbyte)
{
    AASSERT(ctx);
    if (pdata)
    {
        if (a_str_resize(ctx, ctx->n + nbyte + 1))
        {
            return ~0;
        }
        if (nbyte)
        {
            memcpy(ctx->s + ctx->n, pdata, nbyte);
            ctx->n += nbyte;
        }
        ctx->s[ctx->n] = 0;
    }
    return 0;
}

int a_str_puts(a_str_s *ctx, const void *str)
{
    AASSERT(ctx);
    AASSERT(str);
    return a_str_putn(ctx, str, strlen((const char *)str));
}

int a_str_vprintf(a_str_s *ctx, const char *fmt, va_list va)
{
    AASSERT(ctx);
    AASSERT(fmt);
    va_list ap;
    va_copy(ap, va);
    char *s = ctx->s ? (ctx->s + ctx->n) : 0;
    int ret = vsnprintf(s, ctx->m - ctx->n, fmt, ap);
    va_end(ap);
    if (ctx->m - ctx->n < (size_t)ret + 1)
    {
        if (a_str_resize_(ctx, ctx->n + (size_t)ret + 1))
        {
            return ~0;
        }
        va_copy(ap, va);
        s = ctx->s + ctx->n;
        ret = vsnprintf(s, ctx->m - ctx->n, fmt, ap);
        va_end(ap);
    }
    ctx->n += (size_t)ret;
    return ret;
}

int a_str_printf(a_str_s *ctx, const char *fmt, ...)
{
    AASSERT(ctx);
    AASSERT(fmt);
    va_list ap;
    va_start(ap, fmt);
    int ret = a_str_vprintf(ctx, fmt, ap);
    va_end(ap);
    return ret;
}
