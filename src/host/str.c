#if __STDC_HOSTED__

#include "a/host/str.h"
#include <assert.h>
#include <stdio.h>

a_str_s *a_str_new(void)
{
    a_str_s *ctx = (a_str_s *)malloc(sizeof(a_str_s));
    if (ctx)
    {
        a_str_ctor(ctx);
    }
    return ctx;
}

a_void_t a_str_die(a_str_s *ctx)
{
    if (ctx)
    {
        a_str_dtor(ctx);
        free(ctx);
    }
}

a_void_t a_str_ctor(a_str_s *ctx)
{
    A_ASSERT(ctx);
    ctx->_str = 0;
    ctx->_num = 0;
    ctx->_mem = 0;
}

a_void_t a_str_dtor(a_str_s *ctx)
{
    A_ASSERT(ctx);
    if (ctx->_str)
    {
        free(ctx->_str);
        ctx->_str = 0;
    }
    ctx->_num = 0;
    ctx->_mem = 0;
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
    A_ASSERT(ctx);
    ctx->_num = nbyte;
    ctx->_mem = nbyte + 1;
    ctx->_str = (a_str_t)malloc(roundup32(ctx->_mem));
    if (a_unlikely(ctx->_str == 0))
    {
        return A_FAILURE;
    }
    if (pdata && nbyte)
    {
        memcpy(ctx->_str, pdata, nbyte);
    }
    ctx->_str[ctx->_num] = 0;
    return A_SUCCESS;
}

a_int_t a_str_copy(a_str_s *ctx, const a_str_s *obj)
{
    A_ASSERT(ctx);
    A_ASSERT(obj);
    return a_str_init(ctx, obj->_str, obj->_num);
}

a_str_s *a_str_move(a_str_s *ctx, a_str_s *obj)
{
    A_ASSERT(ctx);
    A_ASSERT(obj);
    memcpy(ctx, obj, sizeof(*obj));
    memset(obj, 0, sizeof(*obj));
    return ctx;
}

a_str_t a_str_exit(a_str_s *ctx)
{
    A_ASSERT(ctx);
    a_str_t str = ctx->_str;
    if (ctx->_str)
    {
        ctx->_str[ctx->_num] = 0;
        ctx->_str = 0;
    }
    ctx->_mem = 0;
    ctx->_num = 0;
    return str;
}

a_int_t a_str_cmp(const a_str_s *lhs, const a_str_s *rhs)
{
    A_ASSERT(lhs);
    A_ASSERT(rhs);
    a_int_t ok = 0;
    if (lhs->_str && rhs->_str)
    {
        a_size_t num = lhs->_num < rhs->_num ? lhs->_num : rhs->_num;
        ok = memcmp(lhs->_str, rhs->_str, num);
    }
    if (ok)
    {
        return ok;
    }
    if (lhs->_num == rhs->_num)
    {
        return 0;
    }
    return lhs->_num < rhs->_num ? -1 : 1;
}

a_int_t a_str_alloc_(a_str_s *ctx, a_size_t mem)
{
    A_ASSERT(ctx);
    a_str_t str = (a_str_t)realloc(ctx->_str, roundup32(mem));
    if (a_unlikely(!str && mem))
    {
        return A_FAILURE;
    }
    ctx->_str = str;
    ctx->_mem = mem;
    return A_SUCCESS;
}

a_int_t a_str_alloc(a_str_s *ctx, a_size_t mem)
{
    A_ASSERT(ctx);
    return ctx->_mem < mem ? a_str_alloc_(ctx, mem) : A_SUCCESS;
}

a_int_t a_str_getc_(a_str_s *ctx)
{
    a_int_t c = EOF;
    if (ctx->_num)
    {
        c = (a_u8_t)ctx->_str[--ctx->_num];
    }
    return c;
}

a_int_t a_str_getc(a_str_s *ctx)
{
    a_int_t c = EOF;
    if (ctx->_num)
    {
        c = (a_u8_t)ctx->_str[--ctx->_num];
        ctx->_str[ctx->_num] = 0;
    }
    return c;
}

a_int_t a_str_putc_(a_str_s *ctx, a_int_t c)
{
    A_ASSERT(ctx);
    if (a_unlikely(a_str_alloc(ctx, ctx->_num + 1)))
    {
        return EOF;
    }
    ctx->_str[ctx->_num++] = (a_char_t)c;
    return c;
}

a_int_t a_str_putc(a_str_s *ctx, a_int_t c)
{
    A_ASSERT(ctx);
    if (a_unlikely(a_str_alloc(ctx, ctx->_num + 2)))
    {
        return EOF;
    }
    ctx->_str[ctx->_num++] = (a_char_t)c;
    ctx->_str[ctx->_num] = 0;
    return c;
}

a_int_t a_str_putn_(a_str_s *ctx, a_cptr_t pdata, a_size_t nbyte)
{
    A_ASSERT(ctx);
    if (pdata && nbyte)
    {
        if (a_unlikely(a_str_alloc(ctx, ctx->_num + nbyte)))
        {
            return A_FAILURE;
        }
        memcpy(ctx->_str + ctx->_num, pdata, nbyte);
        ctx->_num += nbyte;
    }
    return A_SUCCESS;
}

a_int_t a_str_putn(a_str_s *ctx, a_cptr_t pdata, a_size_t nbyte)
{
    A_ASSERT(ctx);
    if (pdata)
    {
        if (a_unlikely(a_str_alloc(ctx, ctx->_num + nbyte + 1)))
        {
            return A_FAILURE;
        }
        if (nbyte)
        {
            memcpy(ctx->_str + ctx->_num, pdata, nbyte);
            ctx->_num += nbyte;
        }
        ctx->_str[ctx->_num] = 0;
    }
    return A_SUCCESS;
}

a_int_t a_str_puts(a_str_s *ctx, a_cptr_t str)
{
    A_ASSERT(ctx);
    A_ASSERT(str);
    return a_str_putn(ctx, str, strlen((a_cstr_t)str));
}

a_int_t a_str_cat(a_str_s *ctx, const a_str_s *obj)
{
    A_ASSERT(ctx);
    A_ASSERT(obj);
    return a_str_putn(ctx, obj->_str, obj->_num);
}

a_int_t a_str_vprintf(a_str_s *ctx, a_cstr_t fmt, va_list va)
{
    A_ASSERT(ctx);
    A_ASSERT(fmt);
    a_size_t siz;
    a_size_t mem;
    a_str_t str;
    a_int_t num;
    va_list ap;
    va_copy(ap, va);
    mem = ctx->_mem - ctx->_num;
    str = ctx->_str ? ctx->_str + ctx->_num : 0;
    num = vsnprintf(str, mem, fmt, ap);
    va_end(ap);
    siz = (a_size_t)num + 1;
    if (siz > mem)
    {
        if (a_unlikely(a_str_alloc_(ctx, ctx->_num + siz)))
        {
            return EOF;
        }
        va_copy(ap, va);
        mem = ctx->_mem - ctx->_num;
        str = ctx->_str + ctx->_num;
        num = vsnprintf(str, mem, fmt, ap);
        va_end(ap);
    }
    ctx->_num += (a_size_t)num;
    return num;
}

a_int_t a_str_printf(a_str_s *ctx, a_cstr_t fmt, ...)
{
    A_ASSERT(ctx);
    A_ASSERT(fmt);
    va_list va;
    va_start(va, fmt);
    a_int_t num = a_str_vprintf(ctx, fmt, va);
    va_end(va);
    return num;
}

#endif /* __STDC_HOSTED__ */
