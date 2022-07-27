/*!
 @file str.cc
 @brief Test basic string library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "str.h"

#include <stdio.h>

static a_noret_t tests(a_noarg_t)
{
    a_str_s ctx[1] = {A_STR_NIL};
    a_str_t str = a_str_exit(ctx);
    printf("0x%zX ", reinterpret_cast<size_t>(str));
    a_str_putc_(ctx, 0);
    a_str_putn_(ctx, a_null, a_zero);
    a_str_putc(ctx, 0);
    a_str_puts(ctx, "");
    a_str_putn(ctx, a_null, a_zero);
    str = a_str_val(ctx);
    printf("0x%zX ", reinterpret_cast<size_t>(str));
    a_str_dtor(ctx);
}

static a_noret_t testt(a_noarg_t)
{
    a_str_t str = a_null;
    a_str_s *ctx = a_str_new();
    a_str_init(ctx, "4321+-/\\", a_zero);
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

a_int_t main(a_noarg_t)
{
    tests();
    testt();

    return A_SUCCESS;
}
