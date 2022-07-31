/*!
 @file __vector__.h
 @brief __brief__
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef ____VECTOR___H__
#define ____VECTOR___H__

#include "../__a__.h"

#if __STDC_HOSTED__

#include <stdlib.h>
#include <string.h>

#define __vector___forenum(i, ctx) for (size_t i = 0; i != __cast__(size_t, (ctx)->tail - (ctx)->head); ++i)

#define __vector___forenum_reverse(i, ctx) for (size_t i = __cast__(size_t, (ctx)->tail - (ctx)->head); i--;)

#define __vector___foreach(it, ctx) for (__T__ *it = (ctx)->head, *it##_ = (ctx)->tail; it != it##_; ++it)

#define __vector___foreach_reverse(it, ctx)                       \
    for (__T__ *it##_ = (ctx)->head ? (ctx)->head - 1 : __null__, \
               *it = (ctx)->tail ? (ctx)->tail - 1 : __null__;    \
         it != it##_; --it)

typedef struct __type__
{
    __T__ *head;
    __T__ *tail;
    __T__ *last;
} __type__;

__inline__ __T__ *__vector___ptr(const __type__ *ctx) { return ctx->head; }

__inline__ __T__ *__vector___end(const __type__ *ctx) { return ctx->tail; }

__inline__ __T__ *__vector___at(const __type__ *ctx, size_t idx)
{
    return ctx->head + idx;
}

__inline__ size_t __vector___num(const __type__ *ctx)
{
    return __cast__(size_t, ctx->tail - ctx->head);
}

__inline__ size_t __vector___mem(const __type__ *ctx)
{
    return __cast__(size_t, ctx->last - ctx->head);
}

__inline__ __T__ *__vector___top(const __type__ *ctx)
{
    return ctx->head != ctx->tail ? ctx->tail - 1 : __null__;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

__public__ __type__ *__vector___new(void);

__public__ void __vector___die(__type__ *ctx);

__public__ void __vector___ctor(__type__ *ctx);

__public__ void __vector___dtor(__type__ *ctx);

__public__ int __vector___copy(__type__ *ctx, const __type__ *obj);

__public__ __type__ *__vector___move(__type__ *ctx, __type__ *obj);

__public__ void __vector___drop(__type__ *ctx);

__public__ int __vector___swap(__type__ *ctx, size_t lhs, size_t rhs);

__public__ __T__ *__vector___insert(__type__ *ctx, size_t idx);

__public__ __T__ *__vector___push_front(__type__ *ctx);

__public__ __T__ *__vector___push_back(__type__ *ctx);

__public__ __T__ *__vector___remove(__type__ *ctx, size_t idx);

__public__ __T__ *__vector___pop_front(__type__ *ctx);

__public__ __T__ *__vector___pop_back(__type__ *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

__inline__ __T__ *__vector___push(__type__ *ctx)
{
    return __vector___push_back(ctx);
}

__inline__ __T__ *__vector___pop(__type__ *ctx)
{
    return __vector___pop_back(ctx);
}

#endif /* __STDC_HOSTED__ */

#endif /* ____VECTOR___H__ */
