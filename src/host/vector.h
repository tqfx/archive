/*!
 @file vector.h
 @brief basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __HOST_VECTOR_H__
#define __HOST_VECTOR_H__

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

#undef VECTOR_S
#define VECTOR_S(def, type) \
    typedef struct def      \
    {                       \
        type *head;         \
        type *last;         \
        type *tail;         \
    } def

#undef VECTOR_PTR
#define VECTOR_PTR(def, func, type) \
    static inline type *func(def *ctx) { return ctx->head; }

#undef VECTOR_END
#define VECTOR_END(def, func, type) \
    static inline type *func(def *ctx) { return ctx->tail; }

#undef VECTOR_AT
#define VECTOR_AT(def, func, type) \
    static inline type *func(def *ctx, size_t idx) { return ctx->head + idx; }

#undef VECTOR_NUM
#define VECTOR_NUM(def, func) \
    static inline size_t func(def *ctx) { return cast(size_t, ctx->last - ctx->head); }

#undef VECTOR_MEM
#define VECTOR_MEM(def, func) \
    static inline size_t func(def *ctx) { return cast(size_t, ctx->tail - ctx->head); }

#undef VECTOR_TOP
#define VECTOR_TOP(def, func, type) \
    static inline type *func(def *ctx) { return ctx->head != ctx->last ? ctx->last - 1 : null; }

#undef VECTOR_F
#define VECTOR_F(scope, name, def, type)        \
    scope def *name##_new(void);                \
    scope void name##_die(def *ctx);            \
    scope void name##_ctor(def *ctx);           \
    scope void name##_dtor(def *ctx);           \
    scope type *name##_pop(def *ctx);           \
    scope type *name##_push(def *ctx);          \
    scope def *name##_move(def *ctx, def *obj); \
    scope int name##_copy(def *ctx, const def *obj);

#undef VECTOR_NEW
#define VECTOR_NEW(def, func, ctor)                  \
    def *func(void)                                  \
    {                                                \
        def *ctx = cast(def *, malloc(sizeof(def))); \
        if (ctx)                                     \
        {                                            \
            ctor(ctx);                               \
        }                                            \
        return ctx;                                  \
    }

#undef VECTOR_DIE
#define VECTOR_DIE(def, func, dtor) \
    void func(def *ctx)             \
    {                               \
        if (ctx)                    \
        {                           \
            dtor(ctx);              \
            free(ctx);              \
        }                           \
    }

#undef VECTOR_CTOR
#define VECTOR_CTOR(def, func) \
    void func(def *ctx)        \
    {                          \
        ctx->head = null;      \
        ctx->last = null;      \
        ctx->tail = null;      \
    }

#undef VECTOR_DTOR_NIL
#define VECTOR_DTOR_NIL(...) (void)(0)

#undef VECTOR_DTOR
#define VECTOR_DTOR(def, func, dtor)       \
    void func(def *ctx)                    \
    {                                      \
        if (ctx->head)                     \
        {                                  \
            while (ctx->head != ctx->last) \
            {                              \
                --ctx->last;               \
                dtor(ctx->last);           \
            }                              \
            free(ctx->head);               \
            ctx->head = null;              \
        }                                  \
        ctx->last = null;                  \
        ctx->tail = null;                  \
    }

#undef VECTOR_MOVE
#define VECTOR_MOVE(def, func)         \
    def *func(def *ctx, def *obj)      \
    {                                  \
        memcpy(ctx, obj, sizeof(def)); \
        memset(obj, 000, sizeof(def)); \
        return ctx;                    \
    }

#undef VECTOR_COPY
#define VECTOR_COPY(def, func, type)                          \
    int func(def *ctx, const def *obj)                        \
    {                                                         \
        size_t num = cast(size_t, obj->last - obj->head);     \
        size_t mem = cast(size_t, obj->tail - obj->head);     \
        ctx->head = cast(type *, malloc(sizeof(type) * mem)); \
        if (ctx->head == null)                                \
        {                                                     \
            return ~0;                                        \
        }                                                     \
        memcpy(ctx->head, obj->head, sizeof(type) * num);     \
        ctx->last = ctx->head + num;                          \
        ctx->tail = ctx->head + mem;                          \
        return 0;                                             \
    }

#undef VECTOR_POP
#define VECTOR_POP(def, func, type)                         \
    type *func(def *ctx)                                    \
    {                                                       \
        return ctx->head != ctx->last ? ++ctx->last : null; \
    }

#undef VECTOR_PUSH
#define VECTOR_PUSH(def, func, type)                                 \
    type *func(def *ctx)                                             \
    {                                                                \
        if (ctx->last >= ctx->tail)                                  \
        {                                                            \
            size_t num = cast(size_t, ctx->last - ctx->head);        \
            size_t mem = cast(size_t, ctx->tail - ctx->head);        \
            mem = (mem + (mem >> 1) + 1);                            \
            size_t size = align(mem * sizeof(type), sizeof(void *)); \
            type *head = cast(type *, realloc(ctx->head, size));     \
            if (head == null)                                        \
            {                                                        \
                return null;                                         \
            }                                                        \
            ctx->head = head;                                        \
            ctx->last = head + num;                                  \
            ctx->tail = head + mem;                                  \
        }                                                            \
        return ctx->last++;                                          \
    }

#define vector_forenum(i, ctx) for (size_t i = 0; i != cast(size_t, (ctx)->last - (ctx)->head); ++i)
#define vector_forenum_reverse(i, ctx) for (size_t i = cast(size_t, (ctx)->last - (ctx)->head); i--;)
#define vector_foreach(T, it, ctx) for (T *it = (ctx)->head, *it##_ = (ctx)->last; it != it##_; ++it)
#define vector_foreach_reverse(T, it, ctx)                \
    for (T *it##_ = (ctx)->head ? (ctx)->head - 1 : null, \
           *it = (ctx)->last ? (ctx)->last - 1 : null;    \
         it != it##_; --it)

#endif /* __STDC_HOSTED__ */

#endif /* __HOST_VECTOR_H__ */
