/*!
 @file str.h
 @brief Test basic string library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_HOST_STR_H__
#define __TEST_HOST_STR_H__

#include "a/host/str.h"
#include "../test.h"
#include <stdio.h>

A_STATIC a_noret_t tests(a_noarg_t)
{
    a_str_s ctx[1] = {A_STR_NIL};
    a_str_t str = a_str_exit(ctx);
    printf("0x%zX ", a_cast_r(a_uptr_t, str));
    a_str_putc_(ctx, 0);
    a_str_putn_(ctx, a_null, 0);
    a_str_putc(ctx, 0);
    a_str_puts(ctx, "");
    a_str_putn(ctx, a_null, 0);
    str = a_str_val(ctx);
    printf("0x%zX ", a_cast_r(a_uptr_t, str));
    a_str_dtor(ctx);
}

A_STATIC a_noret_t testt(a_noarg_t)
{
    a_str_t str = a_null;
    a_str_s *ctx = a_str_new();
    a_str_init(ctx, "4321+-/\\", 0);
    a_str_putc(ctx, '-');
    a_str_putc_(ctx, '+');
    a_str_putn(ctx, "12", 1);
    a_str_putn_(ctx, "23", 1);
    a_str_puts(ctx, "3");
    a_str_printf(ctx, "%u", 4);
    str = a_str_exit(ctx);
    printf("%s\n", str);
    free(str);
    a_str_die(ctx);
}

A_STATIC a_noret_t testc(a_noarg_t)
{
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();

        TEST_BUG(a_str_cmp(lhs, rhs) == 0);

        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(lhs, "");

        TEST_BUG(a_str_cmp(lhs, rhs) == 0);

        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(rhs, "");

        TEST_BUG(a_str_cmp(lhs, rhs) == 0);

        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(lhs, "0");

        TEST_BUG(a_str_cmp(lhs, rhs) > 0);

        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(rhs, "0");

        TEST_BUG(a_str_cmp(lhs, rhs) < 0);

        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(lhs, "0");
        a_str_puts(rhs, "00");

        TEST_BUG(a_str_cmp(lhs, rhs) < 0);

        a_str_die(lhs);
        a_str_die(rhs);
    }
    {
        a_str_s *lhs = a_str_new();
        a_str_s *rhs = a_str_new();
        a_str_puts(rhs, "0");
        a_str_puts(lhs, "00");

        TEST_BUG(a_str_cmp(lhs, rhs) > 0);

        a_str_die(lhs);
        a_str_die(rhs);
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
#else /* !__cplusplus */
#define test_main main_c
#endif /* __cplusplus */
a_int_t test_main(a_noarg_t)
{
    printf("%s\n", __func__);
    tests();
    testt();
    testc();
    return A_SUCCESS;
}

#endif /* __TEST_HOST_STR_H__ */
