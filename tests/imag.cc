/*!
 @file imag.cc
 @brief Testing imaginary number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/imag.h"
#include "a/complex.h"

#include <cstring>
#include <cstdlib>
#include <cstdio>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waggregate-return"
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* __GNUC__ || __clang__ */

static void test(void)
{
    a_imag_t a = A_IMAG_C(1.0, 1.0);
    a_imag_t b = A_IMAG_C(1.0, 1.0);
    a_imag_t c = a_imag_c(0, -1);

    c = a_imag_conj(a_imag_c(0, -1));

    printf(A_IMAG_PRI(, "g", , "g") "=" A_IMAG_PRI(, "g", , "g") "\n",
           a_imag_real(c), a_imag_imag(c),
           a_imag_abs(c), a_imag_arg(c));

    c = a_imag_add(a, b);
    printf(A_IMAG_PRI(, "g", , "g") "+" A_IMAG_PRI(, "g", , "g") "=" A_IMAG_PRI(, "g", , "g") "\n",
           a_imag_real(a), a_imag_imag(a),
           a_imag_real(b), a_imag_imag(b),
           a_imag_real(c), a_imag_imag(c));

    c = a_imag_sub(a, b);
    printf(A_IMAG_PRI(, "g", , "g") "-" A_IMAG_PRI(, "g", , "g") "=" A_IMAG_PRI(, "g", , "g") "\n",
           a_imag_real(a), a_imag_imag(a),
           a_imag_real(b), a_imag_imag(b),
           a_imag_real(c), a_imag_imag(c));

    c = a_imag_mul(a, b);
    printf(A_IMAG_PRI(, "g", , "g") "*" A_IMAG_PRI(, "g", , "g") "=" A_IMAG_PRI(, "g", , "g") "\n",
           a_imag_real(a), a_imag_imag(a),
           a_imag_real(b), a_imag_imag(b),
           a_imag_real(c), a_imag_imag(c));

    c = a_imag_div(a, b);
    printf(A_IMAG_PRI(, "g", , "g") "/" A_IMAG_PRI(, "g", , "g") "=" A_IMAG_PRI(, "g", , "g") "\n",
           a_imag_real(a), a_imag_imag(a),
           a_imag_real(b), a_imag_imag(b),
           a_imag_real(c), a_imag_imag(c));
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
