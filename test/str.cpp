/*!
 @file str.cpp
 @brief test string library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_str.h"

#include <stdio.h>

static void tests(void)
{
    a_str_s ctx[1] = {A_STR_INITS()};
    const char *str = a_str_done(ctx);
    printf("0x%zX ", (size_t)str);
    a_str_putc_(ctx, 0);
    a_str_putn_(ctx, 0, 0);
    a_str_putc(ctx, 0);
    a_str_puts(ctx, "");
    a_str_putn(ctx, 0, 0);
    str = a_str_val(ctx);
    printf("0x%zX\n", (size_t)str);
    a_str_dtor(ctx);
}

static void testt(void)
{
    char *s = 0;
    a_str_s *ctx = a_str_new();
    a_str_init(ctx, "4321+-/\\", 0);
    a_str_putc(ctx, '-');
    a_str_putc_(ctx, '+');
    a_str_putn(ctx, "12", 1);
    a_str_putn_(ctx, "23", 1);
    a_str_puts(ctx, "3");
    a_str_printf(ctx, "%u", 4);
    s = a_str_done(ctx);
    printf("%s\n", s);
    free(s);
    a_str_delete(ctx);
}

int main(int argc, char *argv[])
{
    (void)argc, (void)argv;

    tests();
    testt();

    return 0;
}
