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

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* __GNUC__ || __clang__ */

static void test(void)
{
    {
        a_imag_t a = A_IMAG_C(1.0, 1.0);
        a_imag_t b = a_imag_c(1, 1);
        a_imag_t c;

        c = a_imag_add(a, b);
        printf("+:%" A_IMAG_P "g+%" A_IMAG_P "gi\n", a_imag_real(c), a_imag_imag(c));

        c = a_imag_sub(a, b);
        printf("-:%" A_IMAG_P "g+%" A_IMAG_P "gi\n", a_imag_real(c), a_imag_imag(c));

        c = a_imag_mul(a, b);
        printf("*:%" A_IMAG_P "g+%" A_IMAG_P "gi\n", a_imag_real(c), a_imag_imag(c));

        c = a_imag_div(a, b);
        printf("/:%" A_IMAG_P "g+%" A_IMAG_P "gi\n", a_imag_real(c), a_imag_imag(c));
    }
    {
        a_complex_t a = A_COMPLEX_C(1.0, 1.0);
        a_complex_t b = A_COMPLEX_C(1.0, 1.0);
        a_complex_t c;

        c = a_complex_add(a, b);
        printf("+:%" A_REAL_P "g+%" A_REAL_P "gi\n", A_REAL_F(creal, c), A_REAL_F(cimag, c));

        c = a_complex_sub(a, b);
        printf("-:%" A_REAL_P "g+%" A_REAL_P "gi\n", A_REAL_F(creal, c), A_REAL_F(cimag, c));

        c = a_complex_mul(a, b);
        printf("*:%" A_REAL_P "g+%" A_REAL_P "gi\n", A_REAL_F(creal, c), A_REAL_F(cimag, c));

        c = a_complex_div(a, b);
        printf("/:%" A_REAL_P "g+%" A_REAL_P "gi\n", A_REAL_F(creal, c), A_REAL_F(cimag, c));
    }
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

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
