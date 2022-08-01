/*!
 @file __vector__.c
 @brief __brief__
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#if __STDC_HOSTED__

#include "__vector__.h"

__inline__ __T__ *__vector___inc_(__type__ *ctx) { return ctx->tail++; }
__inline__ __T__ *__vector___dec_(__type__ *ctx) { return --ctx->tail; }

__inline__ size_t __vector___num_(const __type__ *ctx)
{
    return (size_t)(ctx->tail - ctx->head);
}
__inline__ size_t __vector___mem_(const __type__ *ctx)
{
    return (size_t)(ctx->last - ctx->head);
}

__type__ *__vector___new(void)
{
    __type__ *ctx = (__type__ *)malloc(sizeof(__type__));
    if (ctx)
    {
        __vector___ctor(ctx);
    }
    return ctx;
}

void __vector___die(__type__ *ctx)
{
    if (ctx)
    {
        __vector___dtor(ctx);
        free(ctx);
    }
}

void __vector___ctor(__type__ *ctx)
{
    ctx->head = 0;
    ctx->tail = 0;
    ctx->last = 0;
}

void __vector___dtor(__type__ *ctx)
{
    if (ctx->head)
    {
        __vector___drop(ctx);
        free(ctx->head);
        ctx->head = 0;
    }
    ctx->tail = 0;
    ctx->last = 0;
}

int __vector___copy(__type__ *ctx, const __type__ *obj)
{
    size_t num = __vector___num_(obj);
    size_t mem = __vector___mem_(obj);
    ctx->head = (__T__ *)malloc(sizeof(__T__) * mem);
    if (ctx->head == 0)
    {
        return __failure__;
    }
    ctx->tail = ctx->head + num;
    ctx->last = ctx->head + mem;
#if defined(__dup__)
    __T__ *dst = ctx->head;
    __T__ *src = obj->head;
    for (; src != obj->last; ++dst, ++src)
    {
        __dup__(dst, src);
    }
#else /* !__dup__ */
    memcpy(ctx->head, obj->head, sizeof(__T__) * mem);
#endif /* __dup__ */
    return __success__;
}

__type__ *__vector___move(__type__ *ctx, __type__ *obj)
{
    memcpy(ctx, obj, sizeof(__type__));
    memset(obj, 0, sizeof(__type__));
    return ctx;
}

void __vector___drop(__type__ *ctx)
{
#if defined(__dtor__)
    while (ctx->head != ctx->tail)
    {
        --ctx->tail;
        __dtor__(ctx->tail);
    }
#else /* !__dtor__ */
    ctx->tail = ctx->head;
#endif /* __dtor__ */
}

#undef align
#define align(x) ((sizeof(__T__) * (x) + sizeof(void *) - 1) & ~(sizeof(void *) - 1))

static int __vector___alloc(__type__ *ctx, size_t num)
{
    size_t mem = __vector___mem_(ctx);
    if (mem <= num)
    {
        size_t n = __vector___num_(ctx);
        do
        {
            mem += (mem >> 1) + 1;
        } while (mem < num);
        __T__ *head = (__T__ *)realloc(ctx->head, align(mem));
        if (head == 0)
        {
            return __failure__;
        }
        ctx->head = head;
        ctx->tail = head + n;
        ctx->last = head + mem;
    }
    return __success__;
}

#undef align

int __vector___swap(__type__ *ctx, size_t lhs, size_t rhs)
{
    const size_t num = __vector___num_(ctx);
    lhs = lhs < num ? lhs : num - 1;
    rhs = rhs < num ? rhs : num - 1;
    if (lhs == rhs)
    {
        return __success__;
    }
    if (__vector___alloc(ctx, num))
    {
        return __failure__;
    }
    memcpy(ctx->head + num, ctx->head + lhs, sizeof(__T__));
    memcpy(ctx->head + lhs, ctx->head + rhs, sizeof(__T__));
    memcpy(ctx->head + rhs, ctx->head + num, sizeof(__T__));
    return __success__;
}

__T__ *__vector___insert(__type__ *ctx, size_t idx)
{
    size_t num = __vector___num_(ctx);
    if (__vector___alloc(ctx, num))
    {
        return 0;
    }
    if (idx < num)
    {
        __T__ *ptr = ctx->tail;
        __T__ *src = ctx->head + idx + 0;
        __T__ *dst = ctx->head + idx + 1;
        memmove(dst, src, sizeof(__T__) * (size_t)(ptr - src));
        __vector___inc_(ctx);
        return src;
    }
    return __vector___inc_(ctx);
}

__T__ *__vector___push_front(__type__ *ctx)
{
    return __vector___insert(ctx, 0);
}

__T__ *__vector___push_back(__type__ *ctx)
{
    size_t num = __vector___num_(ctx);
    if (__vector___alloc(ctx, num))
    {
        return 0;
    }
    return __vector___inc_(ctx);
}

__T__ *__vector___remove(__type__ *ctx, size_t idx)
{
    size_t num = __vector___num_(ctx);
    if (idx + 1 < num)
    {
        if (__vector___alloc(ctx, num))
        {
            return 0;
        }
        __T__ *ptr = ctx->tail;
        __T__ *dst = ctx->head + idx + 0;
        __T__ *src = ctx->head + idx + 1;
        memcpy(ptr, dst, sizeof(__T__));
        memmove(dst, src, sizeof(__T__) * (size_t)(ptr - src));
        __vector___dec_(ctx);
        return ptr;
    }
    return ctx->head != ctx->tail ? __vector___inc_(ctx) : 0;
}

__T__ *__vector___pop_front(__type__ *ctx)
{
    return __vector___remove(ctx, 0);
}

__T__ *__vector___pop_back(__type__ *ctx)
{
    return ctx->head != ctx->tail ? __vector___dec_(ctx) : 0;
}

#endif /* __STDC_HOSTED__ */
