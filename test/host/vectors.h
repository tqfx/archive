/*!
 @file vectors.h
 @brief Test basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_HOST_VECTORS_H__
#define __TEST_HOST_VECTORS_H__

#include "a/host/vectors.h"
#include "../test.h"

#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

static a_noret_t dtor(a_vptr_t ptr)
{
    a_u32_t *obj = a_cast_s(a_u32_t *, ptr);
    printf("%" PRIu32 " ", *obj);
}

static a_int_t u32dup(a_vptr_t dst, a_cptr_t src)
{
    *a_cast_s(a_u32_t *, dst) = *a_cast_s(const a_u32_t *, src);
    printf("%" PRIu32 " ", *a_cast_s(const a_u32_t *, src));
    return 0;
}

static a_noret_t test(a_noarg_t)
{
    a_vectors_s *ctx = a_vectors_new(sizeof(a_u64_t), a_null, a_null);
    a_vectors_foreach(a_u64_t, it, ctx);
    a_vectors_foreach_reverse(a_u64_t, it, ctx);
    for (a_u64_t i = 0; i != 10; ++i)
    {
        a_u64_t *obj = a_vectors_push(a_u64_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }
    a_vectors_set(ctx, sizeof(a_u32_t), a_null, dtor);
    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_vectors_push(a_u32_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }
    for (a_u32_t i = 0; i != 10; ++i)
    {
        a_vectors_pull(a_u32_t, ctx);
    }

    {
        a_byte_t *end = a_vectors_end(a_byte_t, ctx);
        a_byte_t *top = a_vectors_top(a_byte_t, ctx);
        TEST_BUG(a_vectors_get(ctx) == a_cast_s(a_size_t, end - top));
    }

    a_vectors_swap(ctx, 0, 0);
    a_vectors_swap(ctx, 0, ~0U);
    a_vectors_swap(ctx, ~0U, 0);
    a_vectors_swap(ctx, 4, 6);
    a_vectors_swap(ctx, 6, 4);

    a_vectors_forenum(i, ctx)
    {
        a_u32_t *it = a_vectors_at(a_u32_t, ctx, i);
        assert(a_vectors_get(ctx) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_vectors_forenum_reverse(i, ctx)
    {
        a_u32_t *it = a_vectors_at(a_u32_t, ctx, i);
        assert(a_vectors_get(ctx) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    a_vectors_foreach(a_u32_t, it, ctx)
    {
        assert(a_vectors_get(ctx) == sizeof(*it));
        static_assert(sizeof(a_u32_t) == sizeof(*it), "bug in a_vectors_foreach");
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_vectors_foreach_reverse(a_u32_t, it, ctx)
    {
        assert(a_vectors_get(ctx) == sizeof(*it));
        static_assert(sizeof(a_u32_t) == sizeof(*it), "bug in a_vectors_foreach_reverse");
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    {
        a_vectors_s obj[1];
        a_vectors_copy(obj, ctx, u32dup);
        putchar('\n');
        a_vectors_dtor(ctx);
        putchar('\n');
        a_vectors_move(ctx, obj);
    }

    a_vectors_die(ctx);
    putchar('\n');

    {
        ctx = a_vectors_new(sizeof(a_u32_t), a_null, a_null);
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *obj = a_vectors_insert(a_u32_t, ctx, i);
            if (obj)
            {
                *obj = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *obj = a_vectors_insert(a_u32_t, ctx, i);
            if (obj)
            {
                *obj = i;
            }
        }
        a_vectors_foreach(a_u32_t, it, ctx)
        {
            printf("%" PRIu32 " ", *it);
        }
        putchar('\n');
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *obj = a_vectors_remove(a_u32_t, ctx, i);
            if (obj)
            {
                printf("%" PRIu32 " ", *obj);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *obj = a_vectors_remove(a_u32_t, ctx, 0);
            if (obj)
            {
                printf("%" PRIu32 " ", *obj);
            }
        }
        putchar('\n');
        a_vectors_die(ctx);
    }
    {
        ctx = a_vectors_new(sizeof(a_u32_t), a_null, a_null);
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *obj = a_vectors_push_back(a_u32_t, ctx);
            if (obj)
            {
                *obj = i;
            }
        }
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *obj = a_vectors_pull_back(a_u32_t, ctx);
            if (obj)
            {
                printf("%" PRIu32 " ", *obj);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *obj = a_vectors_push_fore(a_u32_t, ctx);
            if (obj)
            {
                *obj = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *obj = a_vectors_pull_fore(a_u32_t, ctx);
            if (obj)
            {
                printf("%" PRIu32 " ", *obj);
            }
        }
        putchar('\n');
        a_vectors_die(ctx);
    }
}

#include <time.h>

static a_int_t cmp(a_cptr_t lhs, a_cptr_t rhs)
{
    return *a_cast_s(const a_int_t *, lhs) - *a_cast_s(const a_int_t *, rhs);
}

static a_int_t cmpr(a_cptr_t lhs, a_cptr_t rhs)
{
    return *a_cast_s(const a_int_t *, rhs) - *a_cast_s(const a_int_t *, lhs);
}

static a_noret_t test_sort(a_noarg_t)
{
    a_uint_t t = a_cast_s(a_uint_t, time(a_null));
    a_vectors_s *ctx = a_vectors_new(sizeof(a_int_t), a_null, a_null);

    a_vectors_set_num(ctx, 10);

    srand(t);
    a_vectors_foreach(a_int_t, it, ctx)
    {
        *it = rand() % 10;
        printf("%i ", *it);
    }
    printf("-> ");
    a_vectors_sort(ctx, cmpr);
    a_vectors_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_vectors_foreach(a_int_t, it, ctx)
    {
        *it = rand() % 10;
        printf("%i ", *it);
    }
    printf("-> ");
    a_vectors_sort(ctx, cmp);
    a_vectors_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_vectors_drop(ctx);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_int_t *obj = a_vectors_push_fore(a_int_t, ctx);
        if (obj)
        {
            *obj = rand() % 10;
            printf("%i ", *obj);
            a_vectors_sort_fore(ctx, cmp);
        }
    }
    printf("-> ");
    a_vectors_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_vectors_drop(ctx);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_int_t *obj = a_vectors_push_back(a_int_t, ctx);
        if (obj)
        {
            *obj = rand() % 10;
            printf("%i ", *obj);
            a_vectors_sort_back(ctx, cmp);
        }
    }
    printf("-> ");
    a_vectors_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    a_vectors_die(ctx);
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
    test_sort();
    return A_SUCCESS;
}

#endif /* __TEST_HOST_VECTORS_H__ */
