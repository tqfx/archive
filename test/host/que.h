/*!
 @file que.h
 @brief Test basic queue library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_HOST_QUE_H__
#define __TEST_HOST_QUE_H__

#include "a/host/que.h"
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

static a_noret_t test(a_noarg_t)
{
    a_que_s *ctx = a_que_new(sizeof(a_u64_t));
    for (a_u64_t i = 0; i != 10; ++i)
    {
        a_u64_t *obj = a_que_push_back(a_u64_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }
    {
        a_u64_t *fore = a_que_fore_(a_u64_t, ctx);
        a_u64_t *back = a_que_back_(a_u64_t, ctx);
        printf("%" PRIu64 " %" PRIu64 " ", *fore, *back);
    }
    {
        a_u64_t *fore = a_que_fore(a_u64_t, ctx);
        a_u64_t *back = a_que_back(a_u64_t, ctx);
        printf("%" PRIu64 " %" PRIu64 " ", *fore, *back);
    }
    {
        a_u64_t *fore = a_que_at(a_u64_t, ctx, 0);
        a_u64_t *back = a_que_at(a_u64_t, ctx, ~0);
        printf("%" PRIu64 " %" PRIu64 "\n", *fore, *back);
    }
    for (a_u64_t i = 0; i != 5; ++i)
    {
        (void)(a_que_pull_fore(a_u64_t, ctx));
    }
    a_que_set(ctx, sizeof(a_u32_t), a_null);
    for (a_u32_t i = 5; i--;)
    {
        a_u32_t *obj = a_que_push_fore(a_u32_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }
    for (a_u32_t i = 5; i != 10; ++i)
    {
        a_u32_t *obj = a_que_push_back(a_u32_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }
    {
        a_u32_t *obj = a_que_insert(a_u32_t, ctx, 0);
        if (obj)
        {
            *obj = A_U32_MAX;
        }
    }
    {
        a_u32_t *obj = a_que_insert(a_u32_t, ctx, A_SIZE_MAX);
        if (obj)
        {
            *obj = A_U32_MAX;
        }
    }
    (void)(a_que_remove(a_u32_t, ctx, 0));
    (void)(a_que_remove(a_u32_t, ctx, A_SIZE_MAX));
    a_que_swap(ctx, 0, A_SIZE_MAX);
    {
        a_u32_t *lhs = a_que_fore_(a_u32_t, ctx);
        a_u32_t *rhs = a_que_back_(a_u32_t, ctx);
        a_que_swap_(ctx, lhs, rhs);
    }
    a_que_foreach(a_u32_t, it, ctx)
    {
        assert(a_que_get(ctx) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_que_foreach_reverse(a_u32_t, it, ctx)
    {
        assert(a_que_get(ctx) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    for (a_u32_t i = 0; i != 5; ++i)
    {
        (void)(a_que_pull_back(a_u32_t, ctx));
    }
    for (a_u32_t i = 0; i != 5; ++i)
    {
        (void)(a_que_pull_fore(a_u32_t, ctx));
    }
    a_que_die(ctx, dtor);
    putchar('\n');
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
    a_que_s *ctx = a_que_new(sizeof(a_int_t));

    srand(t);
    a_que_drop(ctx, a_null);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_int_t *obj = a_que_push_fore(a_int_t, ctx);
        if (obj)
        {
            *obj = rand() % 10;
            printf("%i ", *obj);
            a_que_sort_fore(ctx, cmp);
        }
    }
    printf("-> ");
    a_que_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_que_drop(ctx, a_null);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_int_t *obj = a_que_push_back(a_int_t, ctx);
        if (obj)
        {
            *obj = rand() % 10;
            printf("%i ", *obj);
            a_que_sort_back(ctx, cmpr);
        }
    }
    printf("-> ");
    a_que_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    a_que_die(ctx, a_null);
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

#endif /* __TEST_HOST_QUE_H__ */
