/*!
 @file vec.h
 @brief basic vector library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#ifndef __VEC_H__
#define __VEC_H__

#include <stddef.h>
#include <stdlib.h>

#define VEC_S(type, type_) \
    typedef struct type    \
    {                      \
        size_t mem;        \
        size_t num;        \
        type_ *vec;        \
    } type

#define VEC_F(scope, name, type, type_) \
    scope type *name##_new(void);       \
    scope void name##_die(type *ctx);   \
    scope void name##_ctor(type *ctx);  \
    scope void name##_dtor(type *ctx);  \
    scope type_ *name##_pop(type *ctx); \
    scope type_ *name##_push(type *ctx);

#define VEC_MEM(type, func) \
    static inline size_t func(type *ctx) { return ctx->mem; }
#define VEC_NUM(type, func) \
    static inline size_t func(type *ctx) { return ctx->num; }
#define VEC_AT(type, func, type_) \
    static inline type_ *func(type *ctx, size_t index) { return ctx->vec + index; }

#define VEC_NEW(type, func, ctor)                 \
    type *func(void)                              \
    {                                             \
        type *ctx = (type *)malloc(sizeof(type)); \
        if (ctx)                                  \
        {                                         \
            ctor(ctx);                            \
        }                                         \
        return ctx;                               \
    }

#define VEC_DIE(type, func, dtor) \
    void func(type *ctx)          \
    {                             \
        if (ctx)                  \
        {                         \
            dtor(ctx);            \
            free(ctx);            \
        }                         \
    }

#define VEC_CTOR(type, func) \
    void func(type *ctx)     \
    {                        \
        ctx->mem = 0;        \
        ctx->num = 0;        \
        ctx->vec = 0;        \
    }

#define VEC_DTOR_NO(...)

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
            ctx->vec = 0;                  \
        }                                  \
        ctx->num = 0;                      \
        ctx->mem = 0;                      \
    }

#define VEC_PUSH(type, func, type_)                      \
    type_ *func(type *ctx)                               \
    {                                                    \
        if (ctx->mem <= ctx->num)                        \
        {                                                \
            size_t mem = ctx->mem + (ctx->mem >> 1) + 1; \
            type_ *vec = (type_ *)                       \
                realloc(ctx->vec, sizeof(type_) * mem);  \
            if (vec == 0)                                \
            {                                            \
                return 0;                                \
            }                                            \
            ctx->mem = mem;                              \
            ctx->vec = vec;                              \
        }                                                \
        return ctx->vec + ctx->num++;                    \
    }

#define VEC_POP(type, func, type_)                   \
    type_ *func(type *ctx)                           \
    {                                                \
        return ctx->num ? ctx->vec + --ctx->num : 0; \
    }

#endif /* __VEC_H__ */
