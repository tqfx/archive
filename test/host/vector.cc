/*!
 @file vector.cc
 @brief Test basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "vector.h"

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
    a_vector_s *ctx = a_vector_new(sizeof(a_u64_t));
    for (a_u64_t i = 0; i != 10; ++i)
    {
        a_u64_t *p = a_cast(a_u64_t *, a_vector_push(ctx));
        if (p)
        {
            *p = i;
        }
    }
    a_vector_resize(ctx, sizeof(a_u32_t), a_null);
    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *p = a_cast(a_u32_t *, a_vector_push(ctx));
        if (p)
        {
            *p = i;
        }
    }
    for (a_u32_t i = 0; i != 10; ++i)
    {
        a_vector_pop(ctx);
    }

    {
        a_byte_t *end = a_cast(a_byte_t *, a_vector_end(ctx));
        a_byte_t *top = a_cast(a_byte_t *, a_vector_top(ctx));
        TEST_BUG(a_vector_size(ctx) == a_cast(a_size_t, end - top));
    }

    a_vector_forenum(i, ctx)
    {
        a_u32_t *it = a_cast(a_u32_t *, a_vector_at(ctx, i));
        assert(a_vector_size(ctx) == sizeof(*it));
        if (it)
        {
            printf("%" PRIu32 " ", *it);
        }
    }
    putchar('\n');
    a_vector_forenum_reverse(i, ctx)
    {
        a_u32_t *it = a_cast(a_u32_t *, a_vector_at(ctx, i));
        assert(a_vector_size(ctx) == sizeof(*it));
        if (it)
        {
            printf("%" PRIu32 " ", *it);
        }
    }
    putchar('\n');

    a_vector_foreach(a_u32_t, it, ctx)
    {
        assert(a_vector_size(ctx) == sizeof(*it));
        static_assert(sizeof(a_u32_t) == sizeof(*it), "bug in a_vector_foreach");
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_vector_foreach_reverse(a_u32_t, it, ctx)
    {
        assert(a_vector_size(ctx) == sizeof(*it));
        static_assert(sizeof(a_u32_t) == sizeof(*it), "bug in a_vector_foreach_reverse");
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    a_vector_die(ctx, dtor);
    putchar('\n');
}

VECTOR_S(int_s, int);
VECTOR_MEM(int_s, int_mem)
VECTOR_NUM(int_s, int_num)
VECTOR_PTR(int_s, int_ptr, int)
VECTOR_AT(int_s, int_at, int)
VECTOR_TOP(int_s, int_top, int)
VECTOR_F(static, int, int_s, int)
VECTOR_CTOR(int_s, int_ctor)
VECTOR_DTOR(int_s, int_dtor, VECTOR_DTOR_NIL)
VECTOR_NEW(int_s, int_new, int_ctor)
VECTOR_DIE(int_s, int_die, int_dtor)
VECTOR_PUSH(int_s, int_push, int)
VECTOR_POP(int_s, int_pop, int)

static a_noret_t test_intern(a_noarg_t)
{
    int_s *ctx = int_new();
    vector_foreach(int, it, ctx);
    vector_foreach_reverse(int, it, ctx);
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
    vector_forenum(i, ctx)
    {
        *int_at(ctx, i) = 0;
    }
    vector_forenum_reverse(i, ctx)
    {
        *int_at(ctx, i) = 0;
    }
    vector_foreach(int, it, ctx)
    {
        *it = 0;
    }
    vector_foreach_reverse(int, it, ctx)
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

    int_die(ctx);
}

a_int_t main(a_noarg_t)
{
    test();
    test_intern();
    return A_SUCCESS;
}
