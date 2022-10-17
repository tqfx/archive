#ifndef TEST_COMPLEX_H
#define TEST_COMPLEX_H

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* __GNUC__ || __clang__ */

#include "a/complex.h"
#include "a/math.h"
#include <stdio.h>

A_STATIC a_void_t test(a_void_t)
{
    a_complex_s a = A_COMPLEX_C(1.0, 2.0);
    a_complex_s b = a_complex_c(2.0, 1.0);
    a_complex_s c = a_complex_polar(A_REAL_C(1.0), a_real_c(A_PI_2));
    a_real_t x = 0;

    x = a_complex_abs(a);
#if defined(__cplusplus)
    printf("abs" A_COMPLEX_PRI(, "g", , "g") "=" A_REAL_PRI(, "g\n"), a_complex_real(a), a_complex_imag(a), x);
#endif /* __cplusplus */

    x = a_complex_arg(a);
#if defined(__cplusplus)
    printf("arg" A_COMPLEX_PRI(, "g", , "g") "=" A_REAL_PRI(, "g\n"), a_complex_real(a), a_complex_imag(a), x);
#endif /* __cplusplus */

    x = a_complex_abs2(a);
#if defined(__cplusplus)
    printf("abs2" A_COMPLEX_PRI(, "g", , "g") "=" A_REAL_PRI(, "g\n"), a_complex_real(a), a_complex_imag(a), x);
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("-" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */
    c = a_complex_neg(c);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("1/" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(a), a_complex_imag(a));
#endif /* __cplusplus */
    c = a_complex_inv(a);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

#if defined(__cplusplus)
    printf("conj" A_COMPLEX_PRI(, "g", , "g"), a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */
    c = a_complex_conj(c);
#if defined(__cplusplus)
    printf("=" A_COMPLEX_PRI(, "g", , "g") "\n", a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_add(a, b);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "+" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a),
           a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_sub(a, b);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "-" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a),
           a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_mul(a, b);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "*" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a),
           a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_div(a, b);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "/" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a),
           a_complex_real(b), a_complex_imag(b),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_add_real(a, x);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "+" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), x, A_REAL_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_sub_real(a, x);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "-" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), x, A_REAL_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_mul_real(a, x);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "*" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), x, A_REAL_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_div_real(a, x);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "/" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), x, A_REAL_C(0.0),
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_add_imag(a, x);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "+" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_REAL_C(0.0), x,
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_sub_imag(a, x);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "-" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_REAL_C(0.0), x,
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_mul_imag(a, x);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "*" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_REAL_C(0.0), x,
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */

    c = a_complex_div_imag(a, x);
#if defined(__cplusplus)
    printf(A_COMPLEX_PRI(, "g", , "g") "/" A_COMPLEX_PRI(, "g", , "g") "=" A_COMPLEX_PRI(, "g", , "g") "\n",
           a_complex_real(a), a_complex_imag(a), A_REAL_C(0.0), x,
           a_complex_real(c), a_complex_imag(c));
#endif /* __cplusplus */
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t complex_c(void);
a_int_t complex_cpp(void);
#if defined(__cplusplus)
} /* extern "C" */
#define func complex_cpp
#else /* !__cplusplus */
#define func complex_c
#endif /* __cplusplus */
a_int_t func(void)
{
    printf("%s\n", __func__);

    test();

    return A_SUCCESS;
}

#endif /* TEST_COMPLEX_H */
