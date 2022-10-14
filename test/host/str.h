#ifndef TEST_HOST_STR_H
#define TEST_HOST_STR_H

#include "a/host/str.h"
#include "../test.h"
#include <stdio.h>

A_STATIC a_void_t tests(void)
{
    a_str_s ctx[1] = {A_STR_NIL};
    a_str_t str = a_str_exit(ctx);
    printf("0x%zX ", a_cast_r(a_uptr_t, str));
    a_str_getc(ctx);
    a_str_getc_(ctx);
    a_str_putc_(ctx, 0);
    a_str_putn_(ctx, A_NULL, 0);
    a_str_putc(ctx, 0);
    a_str_puts(ctx, "");
    a_str_putn(ctx, A_NULL, 0);
    str = a_str_val(ctx);
    printf("0x%zX ", a_cast_r(a_uptr_t, str));
    a_str_dtor(ctx);
}

A_STATIC a_void_t testt(void)
{
    a_str_t str = A_NULL;
    a_str_s *ctx = a_str_new();
    a_str_init(ctx, "4321+-/\\", 0);
    a_str_getc(ctx);
    a_str_getc_(ctx);
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

A_STATIC a_void_t testc(void)
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
a_int_t vector_c(void);
a_int_t vector_cpp(void);
#if defined(__cplusplus)
} /* extern "C" */
#define func vector_cpp
#else /* !__cplusplus */
#define func vector_c
#endif /* __cplusplus */
a_int_t func(void)
{
    printf("%s\n", __func__);
    tests();
    testt();
    testc();
    return A_SUCCESS;
}

#endif /* TEST_HOST_STR_H */
