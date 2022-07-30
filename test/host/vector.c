/*!
 @file vector.c
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

static a_int_t u32dup(a_vptr_t dst, a_cptr_t src)
{
    *a_cast(a_u32_t *, dst) = *a_cast(const a_u32_t *, src);
    printf("%" PRIu32 " ", *a_cast(const a_u32_t *, src));
    return 0;
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
            a_u32_t *p = a_cast(a_u32_t *, a_vector_insert(ctx, i));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vector_insert(ctx, i));
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
            a_u32_t *p = a_cast(a_u32_t *, a_vector_remove(ctx, i));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vector_remove(ctx, 0));
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
            a_u32_t *p = a_cast(a_u32_t *, a_vector_push_back(ctx));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 5; i != 10; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vector_pop_back(ctx));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vector_push_front(ctx));
            if (p)
            {
                *p = i;
            }
        }
        for (a_u32_t i = 0; i != 5; ++i)
        {
            a_u32_t *p = a_cast(a_u32_t *, a_vector_pop_front(ctx));
            if (p)
            {
                printf("%" PRIu32 " ", *p);
            }
        }
        putchar('\n');
        a_vector_die(ctx, a_null);
    }
}

a_int_t main(a_noarg_t)
{
    test();
    return A_SUCCESS;
}
