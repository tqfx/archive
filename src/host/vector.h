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

#undef VECTOR_S
#define VECTOR_S(type, type_) \
    typedef struct type       \
    {                         \
        type_ *head;          \
        type_ *last;          \
        type_ *tail;          \
    } type

#undef VECTOR_F
#define VECTOR_F(scope, name, type, type_) \
    scope type *name##_new(void);          \
    scope void name##_die(type *ctx);      \
    scope void name##_ctor(type *ctx);     \
    scope void name##_dtor(type *ctx);     \
    scope type_ *name##_pop(type *ctx);    \
    scope type_ *name##_push(type *ctx);

#undef VECTOR_PTR
#define VECTOR_PTR(type, func, type_) \
    static inline type_ *func(type *ctx) { return ctx->head; }
#undef VECTOR_END
#define VECTOR_END(type, func, type_) \
    static inline type_ *func(type *ctx) { return ctx->tail; }
#undef VECTOR_NUM
#define VECTOR_NUM(type, func) \
    static inline size_t func(type *ctx) { return cast(size_t, ctx->last - ctx->head); }
#undef VECTOR_MEM
#define VECTOR_MEM(type, func) \
    static inline size_t func(type *ctx) { return cast(size_t, ctx->tail - ctx->head); }
#undef VECTOR_AT
#define VECTOR_AT(type, func, type_) \
    static inline type_ *func(type *ctx, size_t index) { return ctx->head + index; }
#undef VECTOR_TOP
#define VECTOR_TOP(type, func, type_) \
    static inline type_ *func(type *ctx) { return ctx->head != ctx->last ? ctx->last - 1 : null; }

#undef VECTOR_NEW
#define VECTOR_NEW(type, func, ctor)                    \
    type *func(void)                                    \
    {                                                   \
        type *ctx = cast(type *, malloc(sizeof(type))); \
        if (ctx)                                        \
        {                                               \
            ctor(ctx);                                  \
        }                                               \
        return ctx;                                     \
    }

#undef VECTOR_DIE
#define VECTOR_DIE(type, func, dtor) \
    void func(type *ctx)             \
    {                                \
        if (ctx)                     \
        {                            \
            dtor(ctx);               \
            free(ctx);               \
        }                            \
    }

#undef VECTOR_CTOR
#define VECTOR_CTOR(type, func) \
    void func(type *ctx)        \
    {                           \
        ctx->head = null;       \
        ctx->last = null;       \
        ctx->tail = null;       \
    }

#undef VECTOR_DTOR_NIL
#define VECTOR_DTOR_NIL(...) (void)(0)

#undef VECTOR_DTOR
#define VECTOR_DTOR(type, func, dtor)      \
    void func(type *ctx)                   \
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

#undef VECTOR_PUSH
#define VECTOR_PUSH(type, func, type_)                                               \
    type_ *func(type *ctx)                                                           \
    {                                                                                \
        if (ctx->tail <= ctx->last)                                                  \
        {                                                                            \
            a_size_t number = cast(a_size_t, ctx->last - ctx->head);                 \
            a_size_t memory = cast(a_size_t, ctx->tail - ctx->head);                 \
            memory = (memory + (memory >> 1) + 1);                                   \
            type_ *head = cast(type_ *, realloc(ctx->head, sizeof(type_) * memory)); \
            if (head == null)                                                        \
            {                                                                        \
                return null;                                                         \
            }                                                                        \
            ctx->head = head;                                                        \
            ctx->last = head + number;                                               \
            ctx->tail = head + memory;                                               \
        }                                                                            \
        return ctx->last++;                                                          \
    }

#undef VECTOR_POP
#define VECTOR_POP(type, func, type_)                       \
    type_ *func(type *ctx)                                  \
    {                                                       \
        return ctx->head != ctx->last ? ++ctx->last : null; \
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
