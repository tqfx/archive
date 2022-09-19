/*!
 @file operator.c
 @brief Test algorithm library operator
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/a.h"
#include "a/operator.h"
#include "../src/operator.h"
#include <stdio.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++-compat"
#endif /* diagnostic */

A_STATIC a_void_t test_intern(void)
{
    {
        a_int_t x = 1;
        printf("inc %i ", x);
        printf("= %i\n", inc x);
    }
    {
        a_int_t x = 1;
        printf("dec %i ", x);
        printf("= %i\n", dec x);
    }
    {
        a_int_t x = pos 1;
        printf("pos 1 = %+i\n", x);
    }
    {
        a_int_t x = neg 1;
        printf("neg 1 = %+i\n", x);
    }
    {
        a_int_t x = not 1;
        printf("not 1 = %i\n", x);
    }
    {
        a_int_t x = compl 1;
        printf("compl 1 = %i\n", x);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("%i mul %i = %i\n", a, b, a mul b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("%i div %i = %i\n", a, b, a div b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("%i mod %i = %i\n", a, b, a mod b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("%i add %i = %i\n", a, b, a add b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("%i sub %i = %i\n", a, b, a sub b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("%i lshift %i = %i\n", a, b, a lshift b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("%i rshift %i = %i\n", a, b, a rshift b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("%i eq %i = %i\n", a, b, a eq b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("%i ne %i = %i\n", a, b, a ne b);
    }
    {
        a_int_t a = 1;
        a_int_t b = 2;
        printf("%i lt %i = %i\n", a, b, a lt b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("%i gt %i = %i\n", a, b, a gt b);
    }
    {
        a_int_t a = 1;
        a_int_t b = 2;
        printf("%i le %i = %i\n", a, b, a le b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("%i ge %i = %i\n", a, b, a ge b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        printf("%i bitand %i = %i\n", a, b, a bitand b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        printf("%i bitxor %i = %i\n", a, b, a bitxor b);
    }
    {
        a_int_t a = 9;
        a_int_t b = 2;
        printf("%i bitor %i = %i\n", a, b, a bitor b);
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        printf("%i and %i = %i\n", a, b, a and b);
    }
    {
        a_int_t a = 0;
        a_int_t b = 2;
        printf("%i or %i = %i\n", a, b, a or b);
    }
    {
        a_int_t a = 1;
        a_int_t b = 1;
        a_int_t c = a;
        c add_eq b;
        printf("%i add_eq %i = %i\n", a, b, c);
    }
    {
        a_int_t a = 1;
        a_int_t b = 1;
        a_int_t c = a;
        c sub_eq b;
        printf("%i sub_eq %i = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        a_int_t c = a;
        c mul_eq b;
        printf("%i mul_eq %i = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        a_int_t c = a;
        c div_eq b;
        printf("%i div_eq %i = %i\n", a, b, c);
    }
    {
        a_int_t a = 3;
        a_int_t b = 2;
        a_int_t c = a;
        c mod_eq b;
        printf("%i mod_eq %i = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        a_int_t c = a;
        c shl_eq b;
        printf("%i shl_eq %i = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        a_int_t c = a;
        c shr_eq b;
        printf("%i shr_eq %i = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        a_int_t c = a;
        c and_eq b;
        printf("%i and_eq %i = %i\n", a, b, c);
    }
    {
        a_int_t a = 9;
        a_int_t b = 2;
        a_int_t c = a;
        c xor_eq b;
        printf("%i xor_eq %i = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        a_int_t c = a;
        c or_eq b;
        printf("%i or_eq %i = %i\n", a, b, c);
    }
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */

A_STATIC a_void_t test_extern(void)
{
    {
        a_int_t x = 1;
        printf("inc(%i) ", x);
        printf("= %i\n", a_inc(x));
    }
    {
        a_int_t x = 1;
        printf("dec(%i) ", x);
        printf("= %i\n", a_dec(x));
    }
    {
        a_int_t x = a_pos(1);
        printf("pos(1) = %+i\n", x);
    }
    {
        a_int_t x = a_neg(1);
        printf("neg(1) = %+i\n", x);
    }
    {
        a_int_t x = a_not(1);
        printf("not(1) = %i\n", x);
    }
    {
        a_int_t x = a_compl(1);
        printf("compl(1) = %i\n", x);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("mul(%i, %i) = %i\n", a, b, a_mul(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("div(%i, %i) = %i\n", a, b, a_div(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("mod(%i, %i) = %i\n", a, b, a_mod(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("add(%i, %i) = %i\n", a, b, a_add(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("sub(%i, %i) = %i\n", a, b, a_sub(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("lshift(%i, %i) = %i\n", a, b, a_lshift(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("rshift(%i, %i) = %i\n", a, b, a_rshift(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("eq(%i, %i) = %i\n", a, b, a_eq(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        printf("ne(%i, %i) = %i\n", a, b, a_ne(a, b));
    }
    {
        a_int_t a = 1;
        a_int_t b = 2;
        printf("lt(%i, %i) = %i\n", a, b, a_lt(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("gt(%i, %i) = %i\n", a, b, a_gt(a, b));
    }
    {
        a_int_t a = 1;
        a_int_t b = 2;
        printf("le(%i, %i) = %i\n", a, b, a_le(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        printf("ge(%i, %i) = %i\n", a, b, a_ge(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        printf("bitand(%i, %i) = %i\n", a, b, a_bitand(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        printf("bitxor(%i, %i) = %i\n", a, b, a_bitxor(a, b));
    }
    {
        a_int_t a = 9;
        a_int_t b = 2;
        printf("bitor(%i, %i) = %i\n", a, b, a_bitor(a, b));
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        printf("and(%i, %i) = %i\n", a, b, a_and(a, b));
    }
    {
        a_int_t a = 0;
        a_int_t b = 2;
        printf("or(%i, %i) = %i\n", a, b, a_or(a, b));
    }
    {
        a_int_t a = 1;
        a_int_t b = 1;
        a_int_t c = a;
        a_add_eq(c, b);
        printf("add_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 1;
        a_int_t b = 1;
        a_int_t c = a;
        a_sub_eq(c, b);
        printf("sub_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        a_int_t c = a;
        a_mul_eq(c, b);
        printf("mul_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        a_int_t c = a;
        a_div_eq(c, b);
        printf("div_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 3;
        a_int_t b = 2;
        a_int_t c = a;
        a_mod_eq(c, b);
        printf("mod_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        a_int_t c = a;
        a_shl_eq(c, b);
        printf("shl_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 1;
        a_int_t c = a;
        a_shr_eq(c, b);
        printf("shr_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 2;
        a_int_t c = a;
        a_and_eq(c, b);
        printf("and_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 9;
        a_int_t b = 2;
        a_int_t c = a;
        a_xor_eq(c, b);
        printf("xor_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        a_int_t a = 2;
        a_int_t b = 0;
        a_int_t c = a;
        a_or_eq(c, b);
        printf("or_eq(%i, %i) = %i\n", a, b, c);
    }
}

int main(void)
{
    test_intern();
    test_extern();

    return A_SUCCESS;
}
