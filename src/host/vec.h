/*!
 @file vec.h
 @brief basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __HOST_VEC_H__
#define __HOST_VEC_H__

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

#undef align
#define align(addr, base) (((addr) + (base)-1) & ~((base)-1))

#undef VEC_S
#define VEC_S(def, type) \
    typedef struct def   \
    {                    \
        type *ptr;       \
        size_t num;      \
        size_t mem;      \
    } def

#undef VEC_PTR
#define VEC_PTR(def, func, type) \
    static inline type *func(def *ctx) { return ctx->ptr; }

#undef VEC_NUM
#define VEC_NUM(def, func) \
    static inline size_t func(def *ctx) { return ctx->num; }

#undef VEC_MEM
#define VEC_MEM(def, func) \
    static inline size_t func(def *ctx) { return ctx->mem; }

#undef VEC_AT
#define VEC_AT(def, func, type) \
    static inline type *func(def *ctx, size_t idx) { return ctx->ptr + idx; }

#undef VEC_END
#define VEC_END(def, func, type) \
    static inline type *func(def *ctx) { return ctx->num ? ctx->ptr + ctx->num : null; }

#undef VEC_TOP
#define VEC_TOP(def, func, type) \
    static inline type *func(def *ctx) { return ctx->num ? ctx->ptr + ctx->num - 1 : null; }

#undef VEC_F
#define VEC_F(scope, name, def, type)           \
    scope def *name##_new(void);                \
    scope void name##_die(def *ctx);            \
    scope void name##_ctor(def *ctx);           \
    scope void name##_dtor(def *ctx);           \
    scope void name##_drop(def *ctx);           \
    scope type *name##_pop(def *ctx);           \
    scope type *name##_push(def *ctx);          \
    scope def *name##_move(def *ctx, def *obj); \
    scope int name##_copy(def *ctx, const def *obj, int (*dup)(type *, const type *));

#undef VEC_NEW
#define VEC_NEW(def, func, ctor)                     \
    def *func(void)                                  \
    {                                                \
        def *ctx = cast(def *, malloc(sizeof(def))); \
        if (ctx)                                     \
        {                                            \
            ctor(ctx);                               \
        }                                            \
        return ctx;                                  \
    }

#undef VEC_DIE
#define VEC_DIE(def, func, dtor) \
    void func(def *ctx)          \
    {                            \
        if (ctx)                 \
        {                        \
            dtor(ctx);           \
            free(ctx);           \
        }                        \
    }

#undef VEC_CTOR
#define VEC_CTOR(def, func) \
    void func(def *ctx)     \
    {                       \
        ctx->mem = zero;    \
        ctx->num = zero;    \
        ctx->ptr = null;    \
    }

#undef VEC_NODTOR
#define VEC_NODTOR(...) (void)(0)

#undef VEC_DTOR
#define VEC_DTOR(def, func, dtor)          \
    void func(def *ctx)                    \
    {                                      \
        if (ctx->ptr)                      \
        {                                  \
            while (ctx->num)               \
            {                              \
                --ctx->num;                \
                dtor(ctx->ptr + ctx->num); \
            }                              \
            free(ctx->ptr);                \
            ctx->ptr = null;               \
        }                                  \
        ctx->num = zero;                   \
        ctx->mem = zero;                   \
    }

#undef VEC_MOVE
#define VEC_MOVE(def, func)            \
    def *func(def *ctx, def *obj)      \
    {                                  \
        memcpy(ctx, obj, sizeof(def)); \
        memset(obj, 000, sizeof(def)); \
        return ctx;                    \
    }

#undef VEC_COPY
#define VEC_COPY(def, func, type)                                        \
    int func(def *ctx, const def *obj, int (*dup)(type *, const type *)) \
    {                                                                    \
        ctx->ptr = cast(type *, malloc(sizeof(type) * obj->mem));        \
        if (ctx->ptr == null)                                            \
        {                                                                \
            return ~0;                                                   \
        }                                                                \
        ctx->num = obj->num;                                             \
        ctx->mem = obj->mem;                                             \
        if (dup)                                                         \
        {                                                                \
            for (size_t idx = 0; idx != obj->num; ++idx)                 \
            {                                                            \
                dup(ctx->ptr + idx, obj->ptr + idx);                     \
            }                                                            \
        }                                                                \
        else                                                             \
        {                                                                \
            memcpy(ctx->ptr, obj->ptr, sizeof(type) * obj->num);         \
        }                                                                \
        return 0;                                                        \
    }

#undef VEC_DROP
#define VEC_DROP(def, func, dtor)      \
    void func(def *ctx)                \
    {                                  \
        while (ctx->num)               \
        {                              \
            --ctx->num;                \
            dtor(ctx->ptr + ctx->num); \
        }                              \
    }

#undef VEC_POP
#define VEC_POP(def, func, type)                        \
    type *func(def *ctx)                                \
    {                                                   \
        return ctx->num ? ctx->ptr + --ctx->num : null; \
    }

#undef VEC_PUSH
#define VEC_PUSH(def, func, type)                                   \
    type *func(def *ctx)                                            \
    {                                                               \
        if (ctx->num >= ctx->mem)                                   \
        {                                                           \
            size_t mem = ctx->mem + (ctx->mem >> 1) + 1;            \
            size_t siz = align(mem * sizeof(type), sizeof(void *)); \
            type *ptr = cast(type *, realloc(ctx->ptr, siz));       \
            if (ptr == null)                                        \
            {                                                       \
                return null;                                        \
            }                                                       \
            ctx->mem = mem;                                         \
            ctx->ptr = ptr;                                         \
        }                                                           \
        return ctx->ptr + ctx->num++;                               \
    }

#define vec_forenum(i, ctx) for (size_t i = 0; i != (ctx)->num; ++i)
#define vec_forenum_reverse(i, ctx) for (size_t i = (ctx)->num; i--;)
#define vec_foreach(T, it, ctx)                                    \
    for (T *it = (ctx)->ptr, *it##_ = it ? it + (ctx)->num : null; \
         it != it##_; ++it)
#define vec_foreach_reverse(T, it, ctx)                  \
    for (T *it##_ = (ctx)->ptr ? (ctx)->ptr - 1 : null,  \
           *it = (ctx)->ptr ? it##_ + (ctx)->num : null; \
         it != it##_; --it)

#endif /* __STDC_HOSTED__ */

#endif /* __HOST_VEC_H__ */
