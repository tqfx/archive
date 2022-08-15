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
    a_u32_t *p = a_cast_s(a_u32_t *, ptr);
    printf("%" PRIu32 " ", *p);
}

static a_noret_t test(a_noarg_t)
{
    a_que_s *ctx = a_que_new(sizeof(a_u64_t));
    for (a_u64_t i = 0; i != 10; ++i)
    {
        a_u64_t *p = a_que_push_back(a_u64_t, ctx);
        if (p)
        {
            *p = i;
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
        a_u32_t *p = a_que_push_fore(a_u32_t, ctx);
        if (p)
        {
            *p = i;
        }
    }
    for (a_u32_t i = 5; i != 10; ++i)
    {
        a_u32_t *p = a_que_push_back(a_u32_t, ctx);
        if (p)
        {
            *p = i;
        }
    }
    {
        a_u32_t *p = a_que_insert(a_u32_t, ctx, 0);
        if (p)
        {
            *p = A_U32_MAX;
        }
    }
    {
        a_u32_t *p = a_que_insert(a_u32_t, ctx, A_SIZE_MAX);
        if (p)
        {
            *p = A_U32_MAX;
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

#include "a/host/str.h"

static a_noret_t tests(a_noarg_t)
{
    a_que_s *ctx = a_que_new(sizeof(a_str_s));
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_str_s *p = a_que_push_back(a_str_s, ctx);
        if (p)
        {
            a_str_ctor(p);
            a_str_printf(p, "%i", i);
        }
    }
    a_que_foreach(a_str_s, it, ctx)
    {
        printf("%s ", a_str_val(it));
    }
    putchar('\n');
    a_que_die(ctx, a_str_dtor_);
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
    tests();
    return A_SUCCESS;
}

#endif /* __TEST_HOST_QUE_H__ */
