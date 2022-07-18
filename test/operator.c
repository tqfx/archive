/*!
 @file operator.c
 @brief Testing algorithm library operator
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/operator.h"

#include "../src/operator.h"

#include <stdio.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++-compat"
#endif /* __GNUC__ || __clang__ */

static void test_intern(void)
{
    {
        int x = 1;
        printf("inc %i ", x);
        printf("= %i\n", inc x);
    }
    {
        int x = 1;
        printf("dec %i ", x);
        printf("= %i\n", dec x);
    }
    {
        int x = pos 1;
        printf("pos 1 = %+i\n", x);
    }
    {
        int x = neg 1;
        printf("neg 1 = %+i\n", x);
    }
    {
        int x = not 1;
        printf("not 1 = %i\n", x);
    }
    {
        int x = compl 1;
        printf("compl 1 = %i\n", x);
    }
    {
        int a = 2;
        int b = 2;
        printf("%i mul %i = %i\n", a, b, a mul b);
    }
    {
        int a = 2;
        int b = 2;
        printf("%i div %i = %i\n", a, b, a div b);
    }
    {
        int a = 2;
        int b = 2;
        printf("%i mod %i = %i\n", a, b, a mod b);
    }
    {
        int a = 2;
        int b = 2;
        printf("%i add %i = %i\n", a, b, a add b);
    }
    {
        int a = 2;
        int b = 2;
        printf("%i sub %i = %i\n", a, b, a sub b);
    }
    {
        int a = 2;
        int b = 1;
        printf("%i lshift %i = %i\n", a, b, a lshift b);
    }
    {
        int a = 2;
        int b = 1;
        printf("%i rshift %i = %i\n", a, b, a rshift b);
    }
    {
        int a = 1;
        int b = 2;
        printf("%i lt %i = %i\n", a, b, a lt b);
    }
    {
        int a = 2;
        int b = 1;
        printf("%i gt %i = %i\n", a, b, a gt b);
    }
    {
        int a = 1;
        int b = 2;
        printf("%i le %i = %i\n", a, b, a le b);
    }
    {
        int a = 2;
        int b = 1;
        printf("%i ge %i = %i\n", a, b, a ge b);
    }
    {
        int a = 2;
        int b = 2;
        printf("%i eq %i = %i\n", a, b, a eq b);
    }
    {
        int a = 2;
        int b = 2;
        printf("%i ne %i = %i\n", a, b, a ne b);
    }
    {
        int a = 2;
        int b = 0;
        printf("%i bitand %i = %i\n", a, b, a bitand b);
    }
    {
        int a = 2;
        int b = 0;
        printf("%i bitxor %i = %i\n", a, b, a bitxor b);
    }
    {
        int a = 9;
        int b = 2;
        printf("%i bitor %i = %i\n", a, b, a bitor b);
    }
    {
        int a = 2;
        int b = 0;
        printf("%i and %i = %i\n", a, b, a and b);
    }
    {
        int a = 0;
        int b = 2;
        printf("%i or %i = %i\n", a, b, a or b);
    }
    {
        int a = 1;
        int b = 1;
        int c = a;
        c add_eq b;
        printf("%i add_eq %i = %i\n", a, b, c);
    }
    {
        int a = 1;
        int b = 1;
        int c = a;
        c sub_eq b;
        printf("%i sub_eq %i = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 2;
        int c = a;
        c mul_eq b;
        printf("%i mul_eq %i = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 2;
        int c = a;
        c div_eq b;
        printf("%i div_eq %i = %i\n", a, b, c);
    }
    {
        int a = 3;
        int b = 2;
        int c = a;
        c mod_eq b;
        printf("%i mod_eq %i = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 1;
        int c = a;
        c shl_eq b;
        printf("%i shl_eq %i = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 1;
        int c = a;
        c shr_eq b;
        printf("%i shr_eq %i = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 2;
        int c = a;
        c and_eq b;
        printf("%i and_eq %i = %i\n", a, b, c);
    }
    {
        int a = 9;
        int b = 2;
        int c = a;
        c xor_eq b;
        printf("%i xor_eq %i = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 0;
        int c = a;
        c or_eq b;
        printf("%i or_eq %i = %i\n", a, b, c);
    }
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

static void test_extern(void)
{
    {
        int x = 1;
        printf("inc(%i) ", x);
        printf("= %i\n", a_inc(x));
    }
    {
        int x = 1;
        printf("dec(%i) ", x);
        printf("= %i\n", a_dec(x));
    }
    {
        int x = a_pos(1);
        printf("pos(1) = %+i\n", x);
    }
    {
        int x = a_neg(1);
        printf("neg(1) = %+i\n", x);
    }
    {
        int x = a_not(1);
        printf("not(1) = %i\n", x);
    }
    {
        int x = a_compl(1);
        printf("compl(1) = %i\n", x);
    }
    {
        int a = 2;
        int b = 2;
        printf("mul(%i, %i) = %i\n", a, b, a_mul(a, b));
    }
    {
        int a = 2;
        int b = 2;
        printf("div(%i, %i) = %i\n", a, b, a_div(a, b));
    }
    {
        int a = 2;
        int b = 2;
        printf("mod(%i, %i) = %i\n", a, b, a_mod(a, b));
    }
    {
        int a = 2;
        int b = 2;
        printf("add(%i, %i) = %i\n", a, b, a_add(a, b));
    }
    {
        int a = 2;
        int b = 2;
        printf("sub(%i, %i) = %i\n", a, b, a_sub(a, b));
    }
    {
        int a = 2;
        int b = 1;
        printf("lshift(%i, %i) = %i\n", a, b, a_lshift(a, b));
    }
    {
        int a = 2;
        int b = 1;
        printf("rshift(%i, %i) = %i\n", a, b, a_rshift(a, b));
    }
    {
        int a = 1;
        int b = 2;
        printf("lt(%i, %i) = %i\n", a, b, a_lt(a, b));
    }
    {
        int a = 2;
        int b = 1;
        printf("gt(%i, %i) = %i\n", a, b, a_gt(a, b));
    }
    {
        int a = 1;
        int b = 2;
        printf("le(%i, %i) = %i\n", a, b, a_le(a, b));
    }
    {
        int a = 2;
        int b = 1;
        printf("ge(%i, %i) = %i\n", a, b, a_ge(a, b));
    }
    {
        int a = 2;
        int b = 2;
        printf("eq(%i, %i) = %i\n", a, b, a_eq(a, b));
    }
    {
        int a = 2;
        int b = 2;
        printf("ne(%i, %i) = %i\n", a, b, a_ne(a, b));
    }
    {
        int a = 2;
        int b = 0;
        printf("bitand(%i, %i) = %i\n", a, b, a_bitand(a, b));
    }
    {
        int a = 2;
        int b = 0;
        printf("bitxor(%i, %i) = %i\n", a, b, a_bitxor(a, b));
    }
    {
        int a = 9;
        int b = 2;
        printf("bitor(%i, %i) = %i\n", a, b, a_bitor(a, b));
    }
    {
        int a = 2;
        int b = 0;
        printf("and(%i, %i) = %i\n", a, b, a_and(a, b));
    }
    {
        int a = 0;
        int b = 2;
        printf("or(%i, %i) = %i\n", a, b, a_or(a, b));
    }
    {
        int a = 1;
        int b = 1;
        int c = a;
        a_add_eq(c, b);
        printf("add_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 1;
        int b = 1;
        int c = a;
        a_sub_eq(c, b);
        printf("sub_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 2;
        int c = a;
        a_mul_eq(c, b);
        printf("mul_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 2;
        int c = a;
        a_div_eq(c, b);
        printf("div_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 3;
        int b = 2;
        int c = a;
        a_mod_eq(c, b);
        printf("mod_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 1;
        int c = a;
        a_shl_eq(c, b);
        printf("shl_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 1;
        int c = a;
        a_shr_eq(c, b);
        printf("shr_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 2;
        int c = a;
        a_and_eq(c, b);
        printf("and_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 9;
        int b = 2;
        int c = a;
        a_xor_eq(c, b);
        printf("xor_eq(%i, %i) = %i\n", a, b, c);
    }
    {
        int a = 2;
        int b = 0;
        int c = a;
        a_or_eq(c, b);
        printf("or_eq(%i, %i) = %i\n", a, b, c);
    }
}

int main(void)
{
    test_intern();
    test_extern();
    return 0;
}
