/*!
 @file vec.c
 @brief Test basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/host/vec.h"

#include "../src/host/vec.h"

#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

static a_noret_t dtor(a_vptr_t ptr)
{
    a_u32_t *p = a_cast(a_u32_t *, ptr);
    printf("%" PRIu32 " ", *p);
}

static a_noret_t test(a_noarg_t)
{
    a_vec_s *ctx = a_vec_new(sizeof(a_u64_t));
    a_vec_forsafe(a_u64_t, it, ctx);
    a_vec_forsafe_reverse(a_u64_t, it, ctx);
    for (a_u64_t i = 0; i != 10; ++i)
    {
        a_u64_t *p = a_cast(a_u64_t *, a_vec_push(ctx));
        if (p)
        {
            *p = i;
        }
    }
    a_vec_resize(ctx, sizeof(a_u32_t));
    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *p = a_cast(a_u32_t *, a_vec_push(ctx));
        if (p)
        {
            *p = i;
        }
    }
    a_vec_top(ctx);
    for (a_u32_t i = 0; i != 10; ++i)
    {
        a_vec_pop(ctx);
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
        a_u32_t *it = a_null;
        a_vec_forboth(a_u32_t, i, it, ctx)
        {
            assert(a_vec_at(ctx, i) == it);
            printf("(%zu,%" PRIu32 ") ", i, *it);
        }
        putchar('\n');
    }
    {
        a_u32_t *it = a_null;
        a_vec_forboth_reverse(a_u32_t, i, it, ctx)
        {
            assert(a_vec_at(ctx, i) == it);
            printf("(%zu,%" PRIu32 ") ", i, *it);
        }
        putchar('\n');
    }

    a_vec_die(ctx, dtor);
    putchar('\n');
}

VEC_S(int_s, int);
VEC_MEM(int_s, int_mem)
VEC_NUM(int_s, int_num)
VEC_PTR(int_s, int_ptr, int)
VEC_AT(int_s, int_at, int)
VEC_TOP(int_s, int_top, int)
VEC_F(static, int, int_s, int)
VEC_CTOR(int_s, int_ctor)
VEC_DTOR(int_s, int_dtor, VEC_DTOR_NIL)
VEC_NEW(int_s, int_new, int_ctor)
VEC_DIE(int_s, int_die, int_dtor)
VEC_PUSH(int_s, int_push, int)
VEC_POP(int_s, int_pop, int)

static a_noret_t test_intern(a_noarg_t)
{
    int_s *ctx = int_new();
    vec_forsafe(int, it, ctx);
    vec_forsafe_reverse(int, it, ctx);
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
    {
        a_int_t *it = a_null;
        vec_forboth(i, it, ctx)
        {
            *it = a_cast(a_int_t, i);
        }
    }
    {
        a_int_t *it = a_null;
        vec_forboth_reverse(i, it, ctx)
        {
            *it = a_cast(a_int_t, i);
        }
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

    int_die(ctx);
}

a_int_t main(a_noarg_t)
{
    test();
    test_intern();
    return A_SUCCESS;
}
