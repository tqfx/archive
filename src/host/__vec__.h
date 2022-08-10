/*!
 @file __vec__.h
 @brief __brief__
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef ____VEC___H__
#define ____VEC___H__

#include "../__a__.h"

#if __STDC_HOSTED__

#include <stdlib.h>
#include <string.h>

#define __vec___forenum(i, ctx) for (size_t i = 0; i != (ctx)->num; ++i)

#define __vec___forenum_reverse(i, ctx) for (size_t i = (ctx)->num; i--;)

#define __vec___foreach(it, ctx) \
    for (__T__ *it = (ctx)->ptr, *it##_ = it ? it + (ctx)->num : __null__; it != it##_; ++it)

#define __vec___foreach_reverse(it, ctx)                         \
    for (__T__ *it##_ = (ctx)->ptr ? (ctx)->ptr - 1 : __null__,  \
               *it = (ctx)->ptr ? it##_ + (ctx)->num : __null__; \
         it != it##_; --it)

typedef struct __type__
{
    __T__ *ptr;
    size_t num;
    size_t mem;
} __type__;

__inline__ __T__ *__vec___ptr(const __type__ *ctx) { return ctx->ptr; }

__inline__ size_t __vec___num(const __type__ *ctx) { return ctx->num; }

__inline__ size_t __vec___mem(const __type__ *ctx) { return ctx->mem; }

__inline__ __T__ *__vec___top(const __type__ *ctx)
{
    return ctx->num ? ctx->ptr + ctx->num - 1 : __null__;
}

__inline__ __T__ *__vec___end(const __type__ *ctx)
{
    return ctx->ptr + ctx->num;
}

__inline__ __T__ *__vec___at(const __type__ *ctx, size_t idx)
{
    return ctx->ptr + idx;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

__public__ __type__ *__vec___new(void);

__public__ void __vec___die(__type__ *ctx);

__public__ void __vec___ctor(__type__ *ctx);

__public__ void __vec___dtor(__type__ *ctx);

__public__ int __vec___copy(__type__ *ctx, const __type__ *obj);

__public__ __type__ *__vec___move(__type__ *ctx, __type__ *obj);

__public__ void __vec___drop(__type__ *ctx);

__public__ int __vec___swap(__type__ *ctx, size_t lhs, size_t rhs);

__public__ __T__ *__vec___insert(__type__ *ctx, size_t idx);

__public__ __T__ *__vec___push_front(__type__ *ctx);

__public__ __T__ *__vec___push_back(__type__ *ctx);

__public__ __T__ *__vec___remove(__type__ *ctx, size_t idx);

__public__ __T__ *__vec___pop_front(__type__ *ctx);

__public__ __T__ *__vec___pop_back(__type__ *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

__inline__ __T__ *__vec___push(__type__ *ctx)
{
    __T__ *obj = __vec___push_back(ctx);

    return obj;
}

__inline__ __T__ *__vec___pop(__type__ *ctx)
{
    __T__ *obj = __vec___pop_back(ctx);

    return obj;
}

#endif /* __STDC_HOSTED__ */

#endif /* ____VEC___H__ */
