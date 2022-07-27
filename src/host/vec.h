/*!
 @file vec.h
 @brief basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __VEC_H__
#define __VEC_H__

#include <stddef.h>

#if __STDC_HOSTED__

#include <stdlib.h>

#undef cast
#undef null
#undef zero
#define zero 0
#if defined(__cplusplus)
#define null nullptr
#define cast(T, ...) static_cast<T>(__VA_ARGS__)
#else /* !__cplusplus */
#define cast(T, ...) (T)(__VA_ARGS__)
#define null NULL
#endif /* __cplusplus */

#undef VEC_S
#define VEC_S(type, type_) \
    typedef struct type    \
    {                      \
        size_t mem;        \
        size_t num;        \
        type_ *vec;        \
    } type

#undef VEC_F
#define VEC_F(scope, name, type, type_) \
    scope type *name##_new(void);       \
    scope void name##_die(type *ctx);   \
    scope void name##_ctor(type *ctx);  \
    scope void name##_dtor(type *ctx);  \
    scope type_ *name##_pop(type *ctx); \
    scope type_ *name##_push(type *ctx);

#undef VEC_MEM
#define VEC_MEM(type, func) \
    static inline size_t func(type *ctx) { return ctx->mem; }
#undef VEC_NUM
#define VEC_NUM(type, func) \
    static inline size_t func(type *ctx) { return ctx->num; }
#undef VEC_PTR
#define VEC_PTR(type, func, type_) \
    static inline type_ *func(type *ctx) { return ctx->vec; }
#undef VEC_AT
#define VEC_AT(type, func, type_) \
    static inline type_ *func(type *ctx, size_t index) { return ctx->vec + index; }
#undef VEC_TOP
#define VEC_TOP(type, func, type_) \
    static inline type_ *func(type *ctx) { return ctx->num ? ctx->vec + ctx->num - 1 : null; }

#undef VEC_NEW
#define VEC_NEW(type, func, ctor)                       \
    type *func(void)                                    \
    {                                                   \
        type *ctx = cast(type *, malloc(sizeof(type))); \
        if (ctx)                                        \
        {                                               \
            ctor(ctx);                                  \
        }                                               \
        return ctx;                                     \
    }

#undef VEC_DIE
#define VEC_DIE(type, func, dtor) \
    void func(type *ctx)          \
    {                             \
        if (ctx)                  \
        {                         \
            dtor(ctx);            \
            free(ctx);            \
        }                         \
    }

#undef VEC_CTOR
#define VEC_CTOR(type, func) \
    void func(type *ctx)     \
    {                        \
        ctx->mem = zero;     \
        ctx->num = zero;     \
        ctx->vec = null;     \
    }

#undef VEC_DTOR_NONE
#define VEC_DTOR_NONE(...) (void)(0)

#undef VEC_DTOR
#define VEC_DTOR(type, func, dtor)         \
    void func(type *ctx)                   \
    {                                      \
        if (ctx->vec)                      \
        {                                  \
            while (ctx->num)               \
            {                              \
                --ctx->num;                \
                dtor(ctx->vec + ctx->num); \
            }                              \
            free(ctx->vec);                \
            ctx->vec = null;               \
        }                                  \
        ctx->num = zero;                   \
        ctx->mem = zero;                   \
    }

#undef VEC_PUSH
#define VEC_PUSH(type, func, type_)                                             \
    type_ *func(type *ctx)                                                      \
    {                                                                           \
        if (ctx->mem <= ctx->num)                                               \
        {                                                                       \
            size_t mem = ctx->mem + (ctx->mem >> 1) + 1;                        \
            type_ *vec = cast(type_ *, realloc(ctx->vec, sizeof(type_) * mem)); \
            if (vec == null)                                                    \
            {                                                                   \
                return null;                                                    \
            }                                                                   \
            ctx->mem = mem;                                                     \
            ctx->vec = vec;                                                     \
        }                                                                       \
        return ctx->vec + ctx->num++;                                           \
    }

#undef VEC_POP
#define VEC_POP(type, func, type_)                      \
    type_ *func(type *ctx)                              \
    {                                                   \
        return ctx->num ? ctx->vec + --ctx->num : null; \
    }

#define vec_forenum(i, ctx) for (size_t i = 0; i != (ctx)->num; ++i)
#define vec_forenum_reverse(i, ctx) for (size_t i = (ctx)->num; i--;)

#define vec_foreach(T, it, ctx) \
    for (T *it = (ctx)->vec, *it##_ = it + (ctx)->num; it != it##_; ++it)
#define vec_foreach_reverse(T, it, ctx) \
    for (T *it##_ = (ctx)->vec - 1, *it = it##_ + (ctx)->num; it != it##_; --it)

#define vec_forboth(i, it, ctx) \
    for (size_t i = 0; (void)((it) = (ctx)->vec + i), i != (ctx)->num; ++i)
#define vec_forboth_reverse(i, it, ctx) \
    for (size_t i = (ctx)->num; i ? ((void)((it) = (ctx)->vec + --i), 1) : 0;)

#endif /* __STDC_HOSTED__ */

#endif /* __VEC_H__ */
