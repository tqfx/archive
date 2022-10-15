/*!
 @file complex.c
 @brief complex number
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/complex.h"
#include <math.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* __GNUC__ || __clang__ */

a_complex_s a_complex_polar(a_real_t r, a_real_t theta)
{
    a_complex_s z = {r * A_REAL_F(cos, theta), r * A_REAL_F(sin, theta)};
    return z;
}

a_complex_s a_complex_neg(a_complex_s z)
{
    z.real = -z.real;
    z.imag = -z.imag;
    return z;
}

a_complex_s a_complex_conj(a_complex_s z)
{
    z.imag = -z.imag;
    return z;
}

a_real_t a_complex_abs2(a_complex_s z)
{
    return z.real * z.real + z.imag * z.imag;
}

a_real_t a_complex_abs(a_complex_s z)
{
#if 1
    return A_REAL_F(hypot, z.real, z.imag);
#else
    return A_REAL_F(sqrt, z.real * z.real + z.imag * z.imag);
#endif
}

a_complex_s a_complex_inv(a_complex_s z)
{
    a_real_t inv = 1 / (z.real * z.real + z.imag * z.imag);
    z.imag *= -inv;
    z.real *= inv;
    return z;
}

a_real_t a_complex_arg(a_complex_s z)
{
    return A_REAL_F(atan2, z.imag, z.real);
}

a_complex_s a_complex_add(a_complex_s x, a_complex_s y)
{
    a_complex_s z = {x.real + y.real, x.imag + y.imag};
    return z;
}

a_complex_s a_complex_add_real(a_complex_s x, a_real_t y)
{
    a_complex_s z = {x.real + y, x.imag};
    return z;
}

a_complex_s a_complex_add_imag(a_complex_s x, a_real_t y)
{
    a_complex_s z = {x.real, x.imag + y};
    return z;
}

a_complex_s a_complex_sub(a_complex_s x, a_complex_s y)
{
    a_complex_s z = {x.real - y.real, x.imag - y.imag};
    return z;
}

a_complex_s a_complex_sub_real(a_complex_s x, a_real_t y)
{
    a_complex_s z = {x.real - y, x.imag};
    return z;
}

a_complex_s a_complex_sub_imag(a_complex_s x, a_real_t y)
{
    a_complex_s z = {x.real, x.imag - y};
    return z;
}

a_complex_s a_complex_mul(a_complex_s x, a_complex_s y)
{
    a_complex_s z = {
        x.real * y.real - x.imag * y.imag,
        x.real * y.imag + x.imag * y.real,
    };
    return z;
}

a_complex_s a_complex_mul_real(a_complex_s x, a_real_t y)
{
    a_complex_s z = {x.real * y, x.imag * y};
    return z;
}

a_complex_s a_complex_mul_imag(a_complex_s x, a_real_t y)
{
    a_complex_s z = {-x.imag * y, x.real * y};
    return z;
}

a_complex_s a_complex_div(a_complex_s x, a_complex_s y)
{
    a_real_t inv = 1 / (y.real * y.real + y.imag * y.imag);
    a_complex_s z = {
        (x.real * y.real + x.imag * y.imag) * inv,
        (x.imag * y.real - x.real * y.imag) * inv,
    };
    return z;
}

a_complex_s a_complex_div_real(a_complex_s x, a_real_t y)
{
    a_complex_s z = {x.real / y, x.imag / y};
    return z;
}

a_complex_s a_complex_div_imag(a_complex_s x, a_real_t y)
{
    a_complex_s z = {x.imag / y, -x.real / y};
    return z;
}
