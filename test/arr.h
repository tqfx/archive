/*!
 @file arr.h
 @brief Test basic array library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_ARR_H__
#define __TEST_ARR_H__

#include "a/arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

A_STATIC a_noret_t dtor(a_vptr_t ptr)
{
    a_u32_t *obj = a_cast_s(a_u32_t *, ptr);
    printf("%" PRIu32 " ", *obj);
}

A_STATIC a_noret_t back(a_noarg_t)
{
    a_arr_s ctx[1];
    a_u32_t buf[10];
    a_arr_ctor(ctx, buf, sizeof(a_u32_t), 10);

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_arr_push_back(a_u32_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }

    a_arr_foreach(a_u32_t, it, ctx)
    {
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_arr_pull_back(a_u32_t, ctx);
        if (obj)
        {
            printf("%" PRIu32 " ", *obj);
        }
    }
    putchar('\n');

    a_arr_dtor(ctx, dtor);
}

A_STATIC a_noret_t fore(a_noarg_t)
{
    a_arr_s ctx[1];
    a_u32_t buf[10];
    a_arr_ctor(ctx, buf, sizeof(a_u32_t), 10);

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_arr_push_fore(a_u32_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }

    a_arr_foreach_reverse(a_u32_t, it, ctx)
    {
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');

    for (a_u32_t i = 0; i != 20; ++i)
    {
        a_u32_t *obj = a_arr_pull_fore(a_u32_t, ctx);
        if (obj)
        {
            printf("%" PRIu32 " ", *obj);
        }
    }
    putchar('\n');

    a_arr_dtor(ctx, dtor);
}

#include "a/host/str.h"
#include <time.h>

A_STATIC a_int_t cmp(a_cptr_t lhs, a_cptr_t rhs)
{
    return *a_cast_s(const a_int_t *, lhs) - *a_cast_s(const a_int_t *, rhs);
}

A_STATIC a_int_t cmpr(a_cptr_t lhs, a_cptr_t rhs)
{
    return *a_cast_s(const a_int_t *, rhs) - *a_cast_s(const a_int_t *, lhs);
}

A_STATIC a_int_t rand10(a_noarg_t)
{
    return a_cast_s(a_int_t, rand() / a_cast_s(double, RAND_MAX) * 10);
}

A_STATIC a_noret_t test_sort(a_noarg_t)
{
    a_arr_s ctx[1];
    a_int_t buf[10];
    a_uint_t t = a_cast_s(a_uint_t, time(a_null));
    a_arr_ctor(ctx, buf, sizeof(a_int_t), 10);

    srand(t);
    a_arr_drop(ctx, a_null);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_int_t *obj = a_arr_push_fore(a_int_t, ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_arr_sort_fore(ctx, cmp);
        }
    }
    printf("-> ");
    a_arr_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_arr_drop(ctx, a_null);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_int_t *obj = a_arr_push_back(a_int_t, ctx);
        if (obj)
        {
            *obj = rand10();
            printf("%i ", *obj);
            a_arr_sort_back(ctx, cmp);
        }
    }
    printf("-> ");
    a_arr_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_arr_foreach(a_int_t, it, ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_arr_sort(ctx, cmp);
    a_arr_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_arr_foreach(a_int_t, it, ctx)
    {
        *it = rand10();
        printf("%i ", *it);
    }
    printf("-> ");
    a_arr_sort(ctx, cmpr);
    a_arr_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    {
        a_str_s *ok = a_str_new();
        a_str_s *no = a_str_new();
        a_str_puts(ok, "finding ");
        a_str_puts(no, "missing ");
        for (a_int_t i = 0; i != 10; ++i)
        {
            a_int_t *obj = a_arr_search(a_int_t, ctx, &i, cmp);
            if (obj)
            {
                a_str_printf(ok, "%i ", *obj);
            }
            else
            {
                a_str_printf(no, "%i ", i);
            }
        }
        printf("%s\n%s\n", a_str_val(ok), a_str_val(no));
        a_str_die(ok);
        a_str_die(no);
    }

    a_arr_dtor(ctx, a_null);
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t main_c(a_noarg_t);
a_int_t main_cpp(a_noarg_t);
#if defined(__cplusplus)
} /* extern "C" */
#define test_main main_cpp
#else /* !__cplusplus */
#define test_main main_c
#endif /* __cplusplus */
a_int_t test_main(a_noarg_t)
{
    printf("%s\n", __func__);

    back();
    fore();
    test_sort();

    return A_SUCCESS;
}

#endif /* __TEST_ARR_H__ */
