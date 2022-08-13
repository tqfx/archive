/*!
 @file vectors.cc
 @brief Test basic vector library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "vectors.h"

#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

static a_noret_t dtor(a_vptr_t ptr)
{
    a_u32_t *p = static_cast<a_u32_t *>(ptr);
    printf("%" PRIu32 " ", *p);
}

static a_int_t u32dup(a_vptr_t dst, a_cptr_t src)
{
    *static_cast<a_u32_t *>(dst) = *static_cast<const a_u32_t *>(src);
    printf("%" PRIu32 " ", *static_cast<const a_u32_t *>(src));
    return 0;
}

static a_noret_t test(a_noarg_t)
{
    a_vectors_s *ctx = a_vectors_new(sizeof(a_u64_t));
    for (a_u64_t i = 0; i != 10; ++i)
    {
        a_u64_t *p = static_cast<a_u64_t *>(a_vectors_push(ctx));
        if (p)
        {
            *p = i;
        }
    }
    a_vectors_set(ctx, sizeof(a_u32_t), a_null);
    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *p = static_cast<a_u32_t *>(a_vectors_push(ctx));
        if (p)
        {
            *p = i;
        }
    }
    for (a_u32_t i = 0; i != 10; ++i)
    {
        a_vectors_pull(ctx);
    }

    {
        a_byte_t *end = static_cast<a_byte_t *>(a_vectors_end(ctx));
        a_byte_t *top = static_cast<a_byte_t *>(a_vectors_top(ctx));
        TEST_BUG(a_vectors_get(ctx) == static_cast<a_size_t>(end - top));
    }

    a_vectors_swap(ctx, 0, 0);
    a_vectors_swap(ctx, 0, ~0U);
    a_vectors_swap(ctx, ~0U, 0);
    a_vectors_swap(ctx, 4, 6);
    a_vectors_swap(ctx, 6, 4);

    a_vectors_forenum(i, ctx)
    {
        a_u32_t *it = static_cast<a_u32_t *>(a_vectors_at(ctx, i));
        assert(a_vectors_get(ctx) == sizeof(*it));
        if (it)
        {
            printf("%" PRIu32 " ", *it);
        }
    }
    putchar('\n');
    a_vectors_forenum_reverse(i, ctx)
    {
        a_u32_t *it = static_cast<a_u32_t *>(a_vectors_at(ctx, i));
        assert(a_vectors_get(ctx) == sizeof(*it));
        if (it)
        {
            printf("%" PRIu32 " ", *it);
        }
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
        a_vectors_dtor(ctx, a_null);
        a_vectors_move(ctx, obj);
    }

    a_vectors_die(ctx, dtor);
    putchar('\n');

    {
        ctx = a_vectors_new(sizeof(a_u32_t));
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *p = static_cast<a_u32_t *>(a_vectors_insert(ctx, i));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = static_cast<a_u32_t *>(a_vectors_insert(ctx, i));
            if (p)
            {
                *p = i;
            }
        }
        a_vectors_foreach(a_u32_t, it, ctx)
        {
            printf("%" PRIu32 " ", *it);
        }
        putchar('\n');
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = static_cast<a_u32_t *>(a_vectors_remove(ctx, i));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = static_cast<a_u32_t *>(a_vectors_remove(ctx, 0));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        putchar('\n');
        a_vectors_die(ctx, a_null);
    }
    {
        ctx = a_vectors_new(sizeof(a_u32_t));
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *p = static_cast<a_u32_t *>(a_vectors_push_back(ctx));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *p = static_cast<a_u32_t *>(a_vectors_pull_back(ctx));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = static_cast<a_u32_t *>(a_vectors_push_fore(ctx));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = static_cast<a_u32_t *>(a_vectors_pull_fore(ctx));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        putchar('\n');
        a_vectors_die(ctx, a_null);
    }
}

a_int_t main(a_noarg_t)
{
    test();
    return A_SUCCESS;
}
