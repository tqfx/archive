#ifndef TEST_COMPLEX_H
#define TEST_COMPLEX_H

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* __GNUC__ || __clang__ */

#include "a/complex.h"
#include "a/math.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

A_STATIC a_void_t test(a_complex_s a, a_complex_s b)
{
    a_complex_s c = a_complex_polar(A_REAL_C(1.0), a_real_c(A_PI_2));
    a_real_t x = 0;

    x = a_complex_logabs(a);
#if defined(__cplusplus)
    printf("logabs" A_COMPLEX_PRI(, "g", , "g") "=" A_REAL_PRI(, "g\n"), a_complex_real(a), a_complex_imag(a), x);
#endif /* __cplusplus */

    x = a_complex_abs2(a);
#if defined(__cplusplus)
    printf("abs2" A_COMPLEX_PRI(, "g", , "g") "=" A_REAL_PRI(, "g\n"), a_complex_real(a), a_complex_imag(a), x);
#endif /* __cplusplus */

    x = a_complex_abs(a);
#if defined(__cplusplus)
    printf("abs" A_COMPLEX_PRI(, "g", , "g") "=" A_REAL_PRI(, "g\n"), a_complex_real(a), a_complex_imag(a), x);
#endif /* __cplusplus */

    x = a_complex_arg(a);
#if defined(__cplusplus)
    printf("arg" A_COMPLEX_PRI(, "g", , "g") "=" A_REAL_PRI(, "g\n"), a_complex_real(a), a_complex_imag(a), x);
#endif /* __cplusplus */

    c = a_complex_conj(a);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "*=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_neg(a);
#if defined(__cplusplus)
    printf("-" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_add(a, b);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "+" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_sub(a, b);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "-" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_mul(a, b);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "*" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_div(a, b);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "/" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_add_real(a, a_complex_real(b));
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "+" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_REAL_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_sub_real(a, a_complex_real(b));
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "-" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_REAL_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_mul_real(a, a_complex_real(b));
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "*" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_REAL_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_div_real(a, a_complex_real(b));
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "/" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), A_REAL_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_add_imag(a, a_complex_real(b));
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "+" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_REAL_C(0.0), a_complex_real(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_sub_imag(a, a_complex_real(b));
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "-" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_REAL_C(0.0), a_complex_real(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_mul_imag(a, a_complex_real(b));
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "*" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_REAL_C(0.0), a_complex_real(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_div_imag(a, a_complex_real(b));
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "/" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_REAL_C(0.0), a_complex_real(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_inv(a);
#if defined(__cplusplus)
    printf("1/" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_sqrt(a);
#if defined(__cplusplus)
    printf("sqrt" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_sqrt_real(a_complex_real(a));
#if defined(__cplusplus)
    printf("sqrt(" A_REAL_PRI(, "g") ")=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_pow(a, b);
#if defined(__cplusplus)
    printf("pow(" A_COMPLEX_PRI(, "g", , "g") "," A_COMPLEX_PRI(, "g", , "g") ")=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_pow_real(a, a_complex_real(b));
#if defined(__cplusplus)
    printf("pow(" A_COMPLEX_PRI(, "g", , "g") "," A_REAL_PRI(, "g") ")=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_exp(a);
#if defined(__cplusplus)
    printf("exp" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_log(a);
#if defined(__cplusplus)
    printf("log" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_log2(a);
#if defined(__cplusplus)
    printf("log2" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_log10(a);
#if defined(__cplusplus)
    printf("log10" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_logb(a, b);
#if defined(__cplusplus)
    printf("logb(" A_COMPLEX_PRI(, "g", , "g") "," A_COMPLEX_PRI(, "g", , "g") ")=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    a_void_c(c);
    a_void_c(x);
}

A_STATIC a_void_t test_tri(a_complex_s x)
{
    a_complex_s z;

#if defined(__cplusplus)
    printf("sin" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_sin(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("cos" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_cos(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("tan" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_tan(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("sec" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_sec(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("csc" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_csc(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("cot" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_cot(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

    a_void_c(z);
}

A_STATIC a_void_t test_atri(a_complex_s x)
{
    a_complex_s z;

#if defined(__cplusplus)
    printf("sinh" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_sinh(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("cosh" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_cosh(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("tanh" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_tanh(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("sech" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_sech(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("csch" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_csch(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("coth" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_coth(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

    a_void_c(z);
}

A_STATIC a_void_t test_trih(a_complex_s x)
{
    a_complex_s z;

#if defined(__cplusplus)
    printf("asin" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_asin(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("acos" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_acos(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("atan" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_atan(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("asec" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_asec(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("acsc" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_acsc(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("acot" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_acot(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

    a_void_c(z);
}

A_STATIC a_void_t test_atrih(a_complex_s x)
{
    a_complex_s z;

#if defined(__cplusplus)
    printf("asinh" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_asinh(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("acosh" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_acosh(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("atanh" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_atanh(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("asech" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_asech(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("acsch" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_acsch(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("acoth" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(x), a_complex_imag(x));
#endif /* __cplusplus */
    z = a_complex_acoth(x);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(z), a_complex_imag(z));
#endif /* __cplusplus */

    a_void_c(z);
}

#if A_REAL_BITS > 64
#define strtoreal(str, endptr) strtold(str, endptr)
#elif A_REAL_BITS == 64
#define strtoreal(str, endptr) strtod(str, endptr)
#elif A_REAL_BITS == 32
#define strtoreal(str, endptr) strtof(str, endptr)
#endif /* A_REAL_BITS */

A_STATIC a_complex_s strtocomplex(const char *a_restrict str, char **a_restrict endptr)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    a_complex_real(z) = strtoreal(str, endptr);
    if (endptr && *endptr)
    {
        for (str = *endptr; *str; ++str)
        {
            if (*str == '+' || *str == '-' || ('0' <= *str && *str <= '9') || *str == '.')
            {
                a_complex_imag(z) = strtoreal(str, endptr);
                break;
            }
        }
    }
    return z;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t complex_c(a_int_t argc, a_str_t argv[]);
a_int_t complex_cpp(a_int_t argc, a_str_t argv[]);
#if defined(__cplusplus)
} /* extern "C" */
#define func complex_cpp
#else /* !__cplusplus */
#define func complex_c
#endif /* __cplusplus */
a_int_t func(a_int_t argc, a_str_t argv[])
{
    a_complex_s x = A_COMPLEX_C(0.0, 0.0);
    a_complex_s y = A_COMPLEX_C(0.0, 0.0);
    a_str_t endptr = A_NULL;

    if (argc > 1)
    {
        x = strtocomplex(argv[1], &endptr);
    }
    if (argc > 2)
    {
        y = strtocomplex(argv[2], &endptr);
    }

    test(x, y);
    test_tri(x);
    test_atri(x);
    test_trih(x);
    test_atrih(x);

#if defined(__cplusplus)
    if (argc > 1)
    {
        printf("x=" A_COMPLEX_PRI(, "g", , "g") " ", a_complex_real(x), a_complex_imag(x));
    }
    if (argc > 2)
    {
        printf("y=" A_COMPLEX_PRI(, "g", , "g") " ", a_complex_real(y), a_complex_imag(y));
    }
    putchar('\n');
#endif /* __cplusplus */

    return A_SUCCESS;
}

#endif /* TEST_COMPLEX_H */
