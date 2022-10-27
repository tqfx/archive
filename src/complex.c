#define A_COMPLEX_I
#include "a/math.h"
#undef A_INTERN
#define A_INTERN A_INLINE
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Waggregate-return"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* __GNUC__ || __clang__ */
#include "a/complex.h"
#undef A_INTERN
#include <math.h>

a_complex_s a_complex_polar(a_real_t r, a_real_t theta)
{
    return (a_complex_s){r * A_REAL_F(cos, theta), r * A_REAL_F(sin, theta)};
}

a_real_t a_complex_logabs(a_complex_s z)
{
    a_real_t xabs = A_REAL_F(fabs, z.real);
    a_real_t yabs = A_REAL_F(fabs, z.imag);
    a_real_t max, u;
    if (xabs >= yabs)
    {
        max = xabs;
        u = yabs / xabs;
    }
    else
    {
        max = yabs;
        u = xabs / yabs;
    }
    return A_REAL_F(log, max) + A_REAL_C(0.5) * A_REAL_F(log1p, u * u);
}

a_real_t a_complex_abs2(a_complex_s z)
{
    return z.real * z.real + z.imag * z.imag;
}

a_real_t a_complex_abs(a_complex_s z)
{
#if defined(A_HAVE_HYPOT)
    return A_REAL_F(hypot, z.real, z.imag);
#else /* !A_HAVE_HYPOT */
    return A_REAL_F(sqrt, z.real * z.real + z.imag * z.imag);
#endif /* A_HAVE_HYPOT */
}

a_real_t a_complex_arg(a_complex_s z)
{
#if defined(A_HAVE_ATAN2)
    return A_REAL_F(atan2, z.imag, z.real);
#else /* !A_HAVE_ATAN2 */
    if (z.real > 0)
    {
        return A_REAL_F(atan, z.imag / z.real);
    }
    if (z.real < 0)
    {
        if (z.imag >= 0)
        {
            return A_REAL_F(atan, z.imag / z.real) + a_real_c(A_PI);
        }
        return A_REAL_F(atan, z.imag / z.real) - a_real_c(A_PI);
    }
    if (z.imag > 0)
    {
        return +a_real_c(A_PI);
    }
    if (z.imag < 0)
    {
        return -a_real_c(A_PI);
    }
    return 0;
#endif /* A_HAVE_ATAN2 */
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

a_complex_s a_complex_inv(a_complex_s z)
{
    a_real_t inv = 1 / (z.real * z.real + z.imag * z.imag);
    return (a_complex_s){z.real * inv, -z.imag * inv};
}

a_complex_s a_complex_sqrt(a_complex_s z)
{
#if defined(A_HAVE_CSQRT)
    a_complex_u u = {z};
    u.z = A_REAL_F(csqrt, u.z);
    return u.s;
#else /* !A_HAVE_CSQRT */
    if (z.real == 0 && z.imag == 0)
    {
        return A_COMPLEX_C(0.0, 0.0);
    }
    a_real_t x = A_REAL_F(fabs, z.real);
    a_real_t y = A_REAL_F(fabs, z.imag);
    a_real_t w;
    if (x >= y)
    {
        a_real_t t = y / x;
        w = A_REAL_F(sqrt, x) * A_REAL_F(sqrt, (A_REAL_F(sqrt, t * t + 1) + 1) * A_REAL_C(0.5));
    }
    else
    {
        a_real_t t = x / y;
        w = A_REAL_F(sqrt, y) * A_REAL_F(sqrt, (A_REAL_F(sqrt, t * t + 1) + t) * A_REAL_C(0.5));
    }
    if (z.real >= 0)
    {
        return (a_complex_s){w, z.imag / (w * 2)};
    }
    if (z.imag < 0)
    {
        w = -w;
    }
    return (a_complex_s){z.imag / (w * 2), w};
#endif /* A_HAVE_CSQRT */
}

a_complex_s a_complex_sqrt_real(a_real_t x)
{
    if (x >= 0)
    {
        return (a_complex_s){A_REAL_F(sqrt, x), 0};
    }
    return (a_complex_s){0, A_REAL_F(sqrt, -x)};
}

a_complex_s a_complex_pow(a_complex_s z, a_complex_s a)
{
#if defined(A_HAVE_CPOW)
    a_complex_u u = {z};
    u.z = A_REAL_F(cpow, u.z, ((a_complex_u){a}).z);
    return u.s;
#else /* !A_HAVE_CPOW */
    if (z.real == 0 && z.imag == 0)
    {
        if (a.real == 0 && a.imag == 0)
        {
            return A_COMPLEX_C(1.0, 0.0);
        }
        return A_COMPLEX_C(0.0, 0.0);
    }
    a_real_t logr = a_complex_logabs(z);
    a_real_t theta = a_complex_arg(z);
    a_real_t rho = A_REAL_F(exp, logr * a.real - theta * a.imag);
    a_real_t beta = theta * a.real + logr * a.imag;
    return a_complex_polar(rho, beta);
#endif /* A_HAVE_CPOW */
}

a_complex_s a_complex_pow_real(a_complex_s z, a_real_t a)
{
    if (z.real == 0 && z.imag == 0)
    {
        return a == 0 ? A_COMPLEX_C(1.0, 0.0) : A_COMPLEX_C(0.0, 0.0);
    }
    a_real_t logr = a_complex_logabs(z);
    a_real_t theta = a_complex_arg(z);
    a_real_t rho = A_REAL_F(exp, logr * a);
    a_real_t beta = theta * a;
    return a_complex_polar(rho, beta);
}

a_complex_s a_complex_exp(a_complex_s z)
{
#if defined(A_HAVE_CEXP)
    a_complex_u u = {z};
    u.z = A_REAL_F(cexp, u.z);
    return u.s;
#else /* !A_HAVE_CEXP */
    a_real_t rho = A_REAL_F(exp, z.real);
    return a_complex_polar(rho, z.imag);
#endif /* A_HAVE_CEXP */
}

a_complex_s a_complex_log(a_complex_s z)
{
#if defined(A_HAVE_CLOG)
    a_complex_u u = {z};
    u.z = A_REAL_F(clog, u.z);
    return u.s;
#else /* !A_HAVE_CLOG */
    a_real_t logr = a_complex_logabs(z);
    a_real_t theta = a_complex_arg(z);
    return (a_complex_s){logr, theta};
#endif /* A_HAVE_CLOG */
}

a_complex_s a_complex_log2(a_complex_s z)
{
    return a_complex_mul_real(a_complex_log(z), a_real_c(1 / A_LN2));
}

a_complex_s a_complex_log10(a_complex_s z)
{
    return a_complex_mul_real(a_complex_log(z), a_real_c(1 / A_LN10));
}

a_complex_s a_complex_logb(a_complex_s z, a_complex_s b)
{
    return a_complex_div(a_complex_log(z), a_complex_log(b));
}

a_complex_s a_complex_sin(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CSIN)
    u.z = A_REAL_F(csin, u.z);
#endif /* A_HAVE_CSIN */
    return u.s;
}

a_complex_s a_complex_cos(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CCOS)
    u.z = A_REAL_F(ccos, u.z);
#endif /* A_HAVE_CCOS */
    return u.s;
}

a_complex_s a_complex_tan(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CTAN)
    u.z = A_REAL_F(ctan, u.z);
#endif /* A_HAVE_CTAN */
    return u.s;
}

a_complex_s a_complex_sec(a_complex_s z)
{
    return a_complex_inv(a_complex_cos(z));
}

a_complex_s a_complex_csc(a_complex_s z)
{
    return a_complex_inv(a_complex_sin(z));
}

a_complex_s a_complex_cot(a_complex_s z)
{
    return a_complex_inv(a_complex_tan(z));
}

a_complex_s a_complex_asin(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CASIN)
    u.z = A_REAL_F(casin, u.z);
#endif /* A_HAVE_CASIN */
    return u.s;
}

a_complex_s a_complex_acos(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CACOS)
    u.z = A_REAL_F(cacos, u.z);
#endif /* A_HAVE_CACOS */
    return u.s;
}

a_complex_s a_complex_atan(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CATAN)
    u.z = A_REAL_F(catan, u.z);
#endif /* A_HAVE_CATAN */
    return u.s;
}

a_complex_s a_complex_asec(a_complex_s z)
{
    return a_complex_acos(a_complex_inv(z));
}

a_complex_s a_complex_acsc(a_complex_s z)
{
    return a_complex_asin(a_complex_inv(z));
}

a_complex_s a_complex_acot(a_complex_s z)
{
    return a_complex_atan(a_complex_inv(z));
}

a_complex_s a_complex_sinh(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CSINH)
    u.z = A_REAL_F(csinh, u.z);
#endif /* A_HAVE_CSINH */
    return u.s;
}

a_complex_s a_complex_cosh(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CCOSH)
    u.z = A_REAL_F(ccosh, u.z);
#endif /* A_HAVE_CCOSH */
    return u.s;
}

a_complex_s a_complex_tanh(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CTANH)
    u.z = A_REAL_F(ctanh, u.z);
#endif /* A_HAVE_CTANH */
    return u.s;
}

a_complex_s a_complex_sech(a_complex_s z)
{
    return a_complex_inv(a_complex_cosh(z));
}

a_complex_s a_complex_csch(a_complex_s z)
{
    return a_complex_inv(a_complex_sinh(z));
}

a_complex_s a_complex_coth(a_complex_s z)
{
    return a_complex_inv(a_complex_tanh(z));
}

a_complex_s a_complex_asinh(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CASINH)
    u.z = A_REAL_F(casinh, u.z);
#endif /* A_HAVE_CASINH */
    return u.s;
}

a_complex_s a_complex_acosh(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CACOSH)
    u.z = A_REAL_F(cacosh, u.z);
#endif /* A_HAVE_CACOSH */
    return u.s;
}

a_complex_s a_complex_atanh(a_complex_s z)
{
    a_complex_u u = {z};
#if defined(A_HAVE_CATANH)
    u.z = A_REAL_F(catanh, u.z);
#endif /* A_HAVE_CATANH */
    return u.s;
}

a_complex_s a_complex_asech(a_complex_s z)
{
    return a_complex_acosh(a_complex_inv(z));
}

a_complex_s a_complex_acsch(a_complex_s z)
{
    return a_complex_asinh(a_complex_inv(z));
}

a_complex_s a_complex_acoth(a_complex_s z)
{
    return a_complex_atanh(a_complex_inv(z));
}
