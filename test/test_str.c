/*!
 @file test_str.c
 @brief test string library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_str.h"

#include <stdio.h>

static void tests(void)
{
    a_str_s ctx[1] = {a_str_inits()};
    printf("0x%zX ", (size_t)a_str_done(ctx));
    a_str_putc_(ctx, 0);
    a_str_putn_(ctx, 0, 0);
    a_str_putc(ctx, 0);
    a_str_puts(ctx, "");
    a_str_putn(ctx, 0, 0);
    printf("0x%zX\n", (size_t)a_str_val(ctx));
    a_str_sfree(*ctx);
}

static void testt(void)
{
    char *s = 0;
    a_str_s *ctx = a_str_init(0, 0);
    a_str_free(ctx);
    ctx = a_str_init("4321+-/\\", 8);
    a_str_putc(ctx, '-');
    a_str_putc_(ctx, '+');
    a_str_putn(ctx, "12", 1);
    a_str_putn_(ctx, "23", 1);
    a_str_puts(ctx, "3");
    a_str_printf(ctx, "%u", 4);
    s = a_str_done(ctx);
    printf("%s\n", s);
    afree(s);
    a_str_free(ctx);
}

static void testm(void)
{
    int *p = 0;
    const char *pat = "def";
    const char *s = "abcdefghijklmnopqrst";
    printf("%s %s %s %s\n", s, pat, a_strstr(s, pat, &p), a_strstr(s, pat, &p));
    afree(p);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    tests();
    testt();
    testm();

    return 0;
}

/* END OF FILE */
