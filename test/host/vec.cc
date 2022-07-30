/*!
 @file vec.cc
 @brief Test basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "vec.h"

#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

static a_noret_t dtor(a_vptr_t ptr)
{
    a_u32_t *p = a_cast(a_u32_t *, ptr);
    printf("%" PRIu32 " ", *p);
}

static a_int_t u32dup(a_vptr_t dst, a_cptr_t src)
{
    *a_cast(a_u32_t *, dst) = *a_cast(const a_u32_t *, src);
    printf("%" PRIu32 " ", *a_cast(const a_u32_t *, src));
    return 0;
}

static a_noret_t test(a_noarg_t)
{
    a_vec_s *ctx = a_vec_new(sizeof(a_u64_t));
    a_vec_foreach(a_u64_t, it, ctx);
    a_vec_foreach_reverse(a_u64_t, it, ctx);
    for (a_u64_t i = 0; i != 10; ++i)
    {
        a_u64_t *p = a_cast(a_u64_t *, a_vec_push(ctx));
        if (p)
        {
            *p = i;
        }
    }
    a_vec_resize(ctx, sizeof(a_u32_t), a_null);
    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *p = a_cast(a_u32_t *, a_vec_push(ctx));
        if (p)
        {
            *p = i;
        }
    }
    for (a_u32_t i = 0; i != 10; ++i)
    {
        a_vec_pop(ctx);
    }

    {
        a_byte_t *end = a_cast(a_byte_t *, a_vec_end(ctx));
        a_byte_t *top = a_cast(a_byte_t *, a_vec_top(ctx));
        TEST_BUG(a_vec_size(ctx) == a_cast(a_size_t, end - top));
    }

    a_vec_forenum(i, ctx)
    {
        a_u32_t *it = a_cast(a_u32_t *, a_vec_at(ctx, i));
        assert(a_vec_size(ctx) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_vec_forenum_reverse(i, ctx)
    {
        a_u32_t *it = a_cast(a_u32_t *, a_vec_at(ctx, i));
        assert(a_vec_size(ctx) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    a_vec_foreach(a_u32_t, it, ctx)
    {
        assert(a_vec_size(ctx) == sizeof(*it));
        static_assert(sizeof(a_u32_t) == sizeof(*it), "bug in a_vec_foreach");
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_vec_foreach_reverse(a_u32_t, it, ctx)
    {
        assert(a_vec_size(ctx) == sizeof(*it));
        static_assert(sizeof(a_u32_t) == sizeof(*it), "bug in a_vec_foreach_reverse");
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    {
        a_vec_s obj[1];
        a_vec_copy(obj, ctx, u32dup);
        putchar('\n');
        a_vec_dtor(ctx, a_null);
        a_vec_move(ctx, obj);
    }

    a_vec_die(ctx, dtor);
    putchar('\n');

    {
        ctx = a_vec_new(sizeof(a_u32_t));
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vec_insert(ctx, i));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vec_insert(ctx, i));
            if (p)
            {
                *p = i;
            }
        }
        a_vec_foreach(a_u32_t, it, ctx)
        {
            printf("%" PRIu32 " ", *it);
        }
        putchar('\n');
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vec_remove(ctx, i));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vec_remove(ctx, 0));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        putchar('\n');
        a_vec_die(ctx, a_null);
    }
    {
        ctx = a_vec_new(sizeof(a_u32_t));
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vec_push_back(ctx));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vec_pop_back(ctx));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vec_push_front(ctx));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vec_pop_front(ctx));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        putchar('\n');
        a_vec_die(ctx, a_null);
    }
}

VEC_S(int_s, int);
VEC_MEM(int_s, int_mem)
VEC_NUM(int_s, int_num)
VEC_PTR(int_s, int_ptr, int)
VEC_AT(int_s, int_at, int)
VEC_TOP(int_s, int_top, int)
VEC_F(static, int, int_s, int)
VEC_CTOR(int_s, int_ctor)
VEC_DTOR(int_s, int_dtor, VEC_NODTOR)
VEC_DROP(int_s, int_drop, VEC_NODTOR)
VEC_NEW(int_s, int_new, int_ctor)
VEC_DIE(int_s, int_die, int_dtor)
VEC_COPY(int_s, int_copy, int)
VEC_PUSH(int_s, int_push, int)
VEC_POP(int_s, int_pop, int)
VEC_MOVE(int_s, int_move)

A_INLINE int intdup(int *dst, const int *src)
{
    *dst = *src;
    return 0;
}

static a_noret_t test_intern(a_noarg_t)
{
    int_s *ctx = int_new();
    vec_foreach(int, it, ctx);
    vec_foreach_reverse(int, it, ctx);
    for (a_int_t i = 0; i != 0x100; ++i)
    {
        a_int_t *p = int_push(ctx);
        if (p)
        {
            *p = i;
        }
    }
    for (a_int_t i = 0; i != 0x10; ++i)
    {
        int_pop(ctx);
    }
    vec_forenum(i, ctx)
    {
        *int_at(ctx, i) = 0;
    }
    vec_forenum_reverse(i, ctx)
    {
        *int_at(ctx, i) = 0;
    }
    vec_foreach(int, it, ctx)
    {
        *it = 0;
    }
    vec_foreach_reverse(int, it, ctx)
    {
        *it = 0;
    }
    *int_ptr(ctx) = 0;
    a_int_t *p = int_top(ctx);
    if (p)
    {
        *p = 0;
    }
    for (size_t i = int_num(ctx); i != int_mem(ctx); ++i)
    {
        *int_at(ctx, i) = 0;
    }

    {
        int_s obj[1];
        int_copy(obj, ctx, intdup);
        int_dtor(ctx);
        int_move(ctx, obj);
        int_drop(ctx);
    }

    int_die(ctx);
}

a_int_t main(a_noarg_t)
{
    test();
    test_intern();
    return A_SUCCESS;
}
