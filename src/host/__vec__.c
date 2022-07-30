/*!
 @file __vec__.c
 @brief __brief__
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#if __STDC_HOSTED__

#include "__vec__.h"

__inline__ __T__ *__vec___inc_(__type__ *ctx) { return ctx->ptr + ctx->num++; }
__inline__ __T__ *__vec___dec_(__type__ *ctx) { return ctx->ptr + --ctx->num; }

__type__ *__vec___new(void)
{
    __type__ *ctx = (__type__ *)malloc(sizeof(__type__));
    if (ctx)
    {
        __vec___ctor(ctx);
    }
    return ctx;
}

void __vec___die(__type__ *ctx)
{
    if (ctx)
    {
        __vec___dtor(ctx);
        free(ctx);
    }
}

void __vec___ctor(__type__ *ctx)
{
    ctx->ptr = __null__;
    ctx->num = __zero__;
    ctx->mem = __zero__;
}

void __vec___dtor(__type__ *ctx)
{
    if (ctx->ptr)
    {
        __vec___drop(ctx);
        free(ctx->ptr);
        ctx->ptr = __null__;
    }
    ctx->mem = __zero__;
}

int __vec___copy(__type__ *ctx, const __type__ *obj)
{
    ctx->ptr = (__T__ *)malloc(sizeof(__T__) * obj->mem);
    if (ctx->ptr == __null__)
    {
        return __failure__;
    }
    ctx->num = obj->num;
    ctx->mem = obj->mem;
#if defined(__dup__)
    for (size_t idx = __zero__; idx != obj->num; ++idx)
    {
        __dup__(ctx->ptr + idx, obj->ptr + idx);
    }
#else /* !__dup__ */
    memcpy(ctx->ptr, obj->ptr, sizeof(__T__) * obj->num);
#endif /* __dup__ */
    return __success__;
}

__type__ *__vec___move(__type__ *ctx, __type__ *obj)
{
    memcpy(ctx, obj, sizeof(__type__));
    memset(obj, 000, sizeof(__type__));
    return ctx;
}

void __vec___drop(__type__ *ctx)
{
#if defined(__dtor__)
    while (ctx->num)
    {
        --ctx->num;
        __dtor__(ctx->num);
    }
#else /* !__dtor__ */
    ctx->num = __zero__;
#endif /* __dtor__ */
}

#undef align
#define align(x) ((sizeof(__T__) * (x) + sizeof(void *) - 1) & ~(sizeof(void *) - 1))

static int __vec___alloc(__type__ *ctx, size_t num)
{
    if (ctx->mem <= num)
    {
        size_t mem = ctx->mem;
        do
        {
            mem += (mem >> 1) + 1;
        } while (mem < num);
        __T__ *ptr = (__T__ *)realloc(ctx->ptr, align(mem));
        if (ptr == __null__)
        {
            return __failure__;
        }
        ctx->ptr = ptr;
        ctx->mem = mem;
    }
    return __success__;
}

#undef align

__T__ *__vec___insert(__type__ *ctx, size_t idx)
{
    if (__vec___alloc(ctx, ctx->num))
    {
        return __null__;
    }
    if (idx < ctx->num)
    {
        __T__ *src = ctx->ptr + idx + 0;
        __T__ *dst = ctx->ptr + idx + 1;
        __T__ *ptr = ctx->ptr + ctx->num;
        memmove(dst, src, sizeof(__T__) * (size_t)(ptr - src));
        ++ctx->num;
        return src;
    }
    return __vec___inc_(ctx);
}

__T__ *__vec___push_front(__type__ *ctx)
{
    return __vec___insert(ctx, 0);
}

__T__ *__vec___push_back(__type__ *ctx)
{
    if (__vec___alloc(ctx, ctx->num))
    {
        return __null__;
    }
    return __vec___inc_(ctx);
}

__T__ *__vec___remove(__type__ *ctx, size_t idx)
{
    if (idx + 1 < ctx->num)
    {
        if (__vec___alloc(ctx, ctx->num))
        {
            return __null__;
        }
        __T__ *dst = ctx->ptr + idx + 0;
        __T__ *src = ctx->ptr + idx + 1;
        __T__ *ptr = ctx->ptr + ctx->num;
        memcpy(ptr, dst, sizeof(__T__));
        memmove(dst, src, sizeof(__T__) * (size_t)(ptr - src));
        --ctx->num;
        return ptr;
    }
    return ctx->num ? __vec___inc_(ctx) : __null__;
}

__T__ *__vec___pop_front(__type__ *ctx)
{
    return __vec___remove(ctx, 0);
}

__T__ *__vec___pop_back(__type__ *ctx)
{
    return ctx->num ? __vec___dec_(ctx) : __null__;
}

#endif /* __STDC_HOSTED__ */
