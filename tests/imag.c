/*!
 @file imag.c
 @brief Testing imaginary number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/imag.h"
#include "a/complex.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void test(void)
{
    {
        a_imag_t a = A_IMAG_C(1, 1);
        a_imag_t b = A_IMAG_C(1, 1);
        a_imag_t c;

        a_imag_add(1, &c, &a, &b);
        printf("+:" A_IMAG_P(g) "+" A_IMAG_P(g) "i\n", a_imag_real(c), a_imag_imag(c));

        a_imag_sub(1, &c, &a, &b);
        printf("-:" A_IMAG_P(g) "+" A_IMAG_P(g) "i\n", a_imag_real(c), a_imag_imag(c));

        a_imag_mul(1, &c, &a, &b);
        printf("*:" A_IMAG_P(g) "+" A_IMAG_P(g) "i\n", a_imag_real(c), a_imag_imag(c));

        a_imag_div(1, &c, &a, &b);
        printf("/:" A_IMAG_P(g) "+" A_IMAG_P(g) "i\n", a_imag_real(c), a_imag_imag(c));
    }
    {
        a_complex_t a = A_COMPLEX_C(1, 1);
        a_complex_t b = A_COMPLEX_C(1, 1);
        a_complex_t c;

        a_complex_add(1, &c, &a, &b);
        printf("+:" A_REAL_P(g) "+" A_REAL_P(g) "i\n", A_REAL_F(creal, c), A_REAL_F(cimag, c));

        a_complex_sub(1, &c, &a, &b);
        printf("-:" A_REAL_P(g) "+" A_REAL_P(g) "i\n", A_REAL_F(creal, c), A_REAL_F(cimag, c));

        a_complex_mul(1, &c, &a, &b);
        printf("*:" A_REAL_P(g) "+" A_REAL_P(g) "i\n", A_REAL_F(creal, c), A_REAL_F(cimag, c));

        a_complex_div(1, &c, &a, &b);
        printf("/:" A_REAL_P(g) "+" A_REAL_P(g) "i\n", A_REAL_F(creal, c), A_REAL_F(cimag, c));
    }
}

int main(int argc, char *argv[])
{
    test();

    if (argc > 1)
    {
        char *endptr;
        strtoull(argv[argc - 1], &endptr, 0);
    }

    return 0;
}
