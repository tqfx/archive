/*!
 @file vector.h
 @brief Test basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_HOST_VECTOR_H__
#define __TEST_HOST_VECTOR_H__

#include "a/host/vector.h"
#include "../test.h"

#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

static a_noret_t dtor(a_vptr_t ptr)
{
    a_u32_t *p = a_cast_s(a_u32_t *, ptr);
    printf("%" PRIu32 " ", *p);
}

static a_int_t u32dup(a_vptr_t dst, a_cptr_t src)
{
    *a_cast_s(a_u32_t *, dst) = *a_cast_s(const a_u32_t *, src);
    printf("%" PRIu32 " ", *a_cast_s(const a_u32_t *, src));
    return 0;
}

static a_noret_t test(a_noarg_t)
{
    a_vector_s *ctx = a_vector_new(sizeof(a_u64_t));
    for (a_u64_t i = 0; i != 10; ++i)
    {
        a_u64_t *p = a_cast_s(a_u64_t *, a_vector_push(ctx));
        if (p)
        {
            *p = i;
        }
    }
    a_vector_set(ctx, sizeof(a_u32_t), a_null);
    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *p = a_cast_s(a_u32_t *, a_vector_push(ctx));
        if (p)
        {
            *p = i;
        }
    }
    for (a_u32_t i = 0; i != 10; ++i)
    {
        a_vector_pull(ctx);
    }

    {
        a_byte_t *end = a_cast_s(a_byte_t *, a_vector_end(ctx));
        a_byte_t *top = a_cast_s(a_byte_t *, a_vector_top(ctx));
        TEST_BUG(a_vector_get(ctx) == a_cast_s(a_size_t, end - top));
    }

    a_vector_swap(ctx, 0, 0);
    a_vector_swap(ctx, 0, ~0U);
    a_vector_swap(ctx, ~0U, 0);
    a_vector_swap(ctx, 4, 6);
    a_vector_swap(ctx, 6, 4);

    a_vector_forenum(i, ctx)
    {
        a_u32_t *it = a_cast_s(a_u32_t *, a_vector_at(ctx, i));
        assert(a_vector_get(ctx) == sizeof(*it));
        if (it)
        {
            printf("%" PRIu32 " ", *it);
        }
    }
    putchar('\n');
    a_vector_forenum_reverse(i, ctx)
    {
        a_u32_t *it = a_cast_s(a_u32_t *, a_vector_at(ctx, i));
        assert(a_vector_get(ctx) == sizeof(*it));
        if (it)
        {
            printf("%" PRIu32 " ", *it);
        }
    }
    putchar('\n');

    a_vector_foreach(a_u32_t, it, ctx)
    {
        assert(a_vector_get(ctx) == sizeof(*it));
        static_assert(sizeof(a_u32_t) == sizeof(*it), "bug in a_vector_foreach");
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_vector_foreach_reverse(a_u32_t, it, ctx)
    {
        assert(a_vector_get(ctx) == sizeof(*it));
        static_assert(sizeof(a_u32_t) == sizeof(*it), "bug in a_vector_foreach_reverse");
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    {
        a_vector_s obj[1];
        a_vector_copy(obj, ctx, u32dup);
        putchar('\n');
        a_vector_dtor(ctx, a_null);
        a_vector_move(ctx, obj);
    }

    a_vector_die(ctx, dtor);
    putchar('\n');

    {
        ctx = a_vector_new(sizeof(a_u32_t));
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *p = a_cast_s(a_u32_t *, a_vector_insert(ctx, i));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast_s(a_u32_t *, a_vector_insert(ctx, i));
            if (p)
            {
                *p = i;
            }
        }
        a_vector_foreach(a_u32_t, it, ctx)
        {
            printf("%" PRIu32 " ", *it);
        }
        putchar('\n');
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast_s(a_u32_t *, a_vector_remove(ctx, i));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast_s(a_u32_t *, a_vector_remove(ctx, 0));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        putchar('\n');
        a_vector_die(ctx, a_null);
    }
    {
        ctx = a_vector_new(sizeof(a_u32_t));
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *p = a_cast_s(a_u32_t *, a_vector_push_back(ctx));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *p = a_cast_s(a_u32_t *, a_vector_pull_back(ctx));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast_s(a_u32_t *, a_vector_push_fore(ctx));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast_s(a_u32_t *, a_vector_pull_fore(ctx));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        putchar('\n');
        a_vector_die(ctx, a_null);
    }
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t main_c(a_noarg_t);
a_int_t main_cc(a_noarg_t);
#if defined(__cplusplus)
} /* extern "C" */
#define test_main main_cc
#else /* #__cplusplus */
#define test_main main_c
#endif /* __cplusplus */
a_int_t test_main(a_noarg_t)
{
    printf("%s\n", __func__);
    test();
    return A_SUCCESS;
}

#endif /* __TEST_HOST_VECTOR_H__ */
