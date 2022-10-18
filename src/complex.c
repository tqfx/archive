#include "a/complex.h"
#include <math.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* __GNUC__ || __clang__ */

a_complex_s a_complex_polar(a_real_t r, a_real_t theta)
{
    return (a_complex_s){r * A_REAL_F(cos, theta), r * A_REAL_F(sin, theta)};
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

a_real_t a_complex_arg(a_complex_s z)
{
    return A_REAL_F(atan2, z.imag, z.real);
}

a_complex_s a_complex_inv(a_complex_s z)
{
    a_real_t inv = 1 / (z.real * z.real + z.imag * z.imag);
    return (a_complex_s){z.real * inv, -z.imag * inv};
}

a_complex_s a_complex_add(a_complex_s x, a_complex_s y)
{
    return (a_complex_s){x.real + y.real, x.imag + y.imag};
}

a_complex_s a_complex_add_real(a_complex_s x, a_real_t y)
{
    return (a_complex_s){x.real + y, x.imag};
}

a_complex_s a_complex_add_imag(a_complex_s x, a_real_t y)
{
    return (a_complex_s){x.real, x.imag + y};
}

a_complex_s a_complex_sub(a_complex_s x, a_complex_s y)
{
    return (a_complex_s){x.real - y.real, x.imag - y.imag};
}

a_complex_s a_complex_sub_real(a_complex_s x, a_real_t y)
{
    return (a_complex_s){x.real - y, x.imag};
}

a_complex_s a_complex_sub_imag(a_complex_s x, a_real_t y)
{
    return (a_complex_s){x.real, x.imag - y};
}

a_complex_s a_complex_mul(a_complex_s x, a_complex_s y)
{
    return (a_complex_s){
        x.real * y.real - x.imag * y.imag,
        x.real * y.imag + x.imag * y.real,
    };
}

a_complex_s a_complex_mul_real(a_complex_s x, a_real_t y)
{
    return (a_complex_s){x.real * y, x.imag * y};
}

a_complex_s a_complex_mul_imag(a_complex_s x, a_real_t y)
{
    return (a_complex_s){-x.imag * y, x.real * y};
}

a_complex_s a_complex_div(a_complex_s x, a_complex_s y)
{
    a_real_t inv = 1 / (y.real * y.real + y.imag * y.imag);
    return (a_complex_s){
        (x.real * y.real + x.imag * y.imag) * inv,
        (x.imag * y.real - x.real * y.imag) * inv,
    };
}

a_complex_s a_complex_div_real(a_complex_s x, a_real_t y)
{
    return (a_complex_s){x.real / y, x.imag / y};
}

a_complex_s a_complex_div_imag(a_complex_s x, a_real_t y)
{
    return (a_complex_s){x.imag / y, -x.real / y};
}
