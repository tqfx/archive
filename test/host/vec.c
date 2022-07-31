/*!
 @file vec.c
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

    a_vec_swap(ctx, 0, 0);
    a_vec_swap(ctx, 0, ~0U);
    a_vec_swap(ctx, ~0U, 0);
    a_vec_swap(ctx, 4, 6);
    a_vec_swap(ctx, 6, 4);

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

a_int_t main(a_noarg_t)
{
    test();
    return A_SUCCESS;
}
