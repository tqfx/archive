#define A_COMPLEX_I
#include "a/math.h"
#undef A_INTERN
#define A_INTERN A_INLINE
#if a_prereq_gnuc(2, 95) || __has_warning("-Waggregate-return")
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* -Waggregate-return */
#if a_prereq_gnuc(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */
#include "complex.h"
#undef A_INTERN

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
#if defined(A_HAVE_CSQRT) && defined(A_COMPLEX_T)
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
        w = A_REAL_F(sqrt, x) * A_REAL_F(sqrt, (A_REAL_F(sqrt, A_SQ(t) + 1) + 1) * A_REAL_C(0.5));
    }
    else
    {
        a_real_t t = x / y;
        w = A_REAL_F(sqrt, y) * A_REAL_F(sqrt, (A_REAL_F(sqrt, A_SQ(t) + 1) + t) * A_REAL_C(0.5));
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
#if defined(A_HAVE_CPOW) && defined(A_COMPLEX_T)
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
#if defined(A_HAVE_CEXP) && defined(A_COMPLEX_T)
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
#if defined(A_HAVE_CLOG) && defined(A_COMPLEX_T)
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
#if defined(A_HAVE_CSIN) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(csin, u.z);
    return u.s;
#else /* !A_HAVE_CSIN */
    if (z.imag == 0)
    {
        return (a_complex_s){A_REAL_F(sin, z.real), 0};
    }
    return (a_complex_s){
        A_REAL_F(sin, z.real) * A_REAL_F(cosh, z.imag),
        A_REAL_F(cos, z.real) * A_REAL_F(sinh, z.imag),
    };
#endif /* A_HAVE_CSIN */
}

a_complex_s a_complex_cos(a_complex_s z)
{
#if defined(A_HAVE_CCOS) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(ccos, u.z);
    return u.s;
#else /* !A_HAVE_CCOS */
    if (z.imag == 0)
    {
        return (a_complex_s){A_REAL_F(cos, z.real), 0};
    }
    return (a_complex_s){
        A_REAL_F(cos, z.real) * A_REAL_F(cosh, z.imag),
        A_REAL_F(sin, z.real) * A_REAL_F(sinh, -z.imag),
    };
#endif /* A_HAVE_CCOS */
}

a_complex_s a_complex_tan(a_complex_s z)
{
#if defined(A_HAVE_CTAN) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(ctan, u.z);
    return u.s;
#else /* !A_HAVE_CTAN */
    a_real_t cr = A_REAL_F(cos, z.real);
    a_real_t si = A_REAL_F(sinh, z.imag);
    a_real_t inv = A_REAL_C(0.5) / (cr * cr + si * si);
    a_real_t real = A_REAL_F(sin, z.real * 2) * inv;
    if (A_REAL_F(fabs, z.imag) < 1)
    {
        return (a_complex_s){real, A_REAL_F(sinh, z.imag * 2) * inv};
    }
    a_real_t den = A_REAL_F(pow, cr / si, 2) + 1;
    return (a_complex_s){real, 1 / (A_REAL_F(tanh, z.imag) * den)};
#endif /* A_HAVE_CTAN */
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
#if defined(A_HAVE_CASIN) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(casin, u.z);
    return u.s;
#else /* !A_HAVE_CASIN */
    if (z.imag == 0)
    {
        return a_complex_asin_real(z.real);
    }
    const a_real_t a_crossover = A_REAL_C(1.5);
    const a_real_t b_crossover = A_REAL_C(0.6417);
    a_real_t x = A_REAL_F(fabs, z.real);
    a_real_t y = A_REAL_F(fabs, z.imag);
    a_real_t r = A_REAL_F(hypot, x + 1, y);
    a_real_t s = A_REAL_F(hypot, x - 1, y);
    a_real_t a = A_REAL_C(0.5) * (r + s);
    a_real_t b = x / a;
    a_real_t y2 = y * y;
    a_real_t real, imag;
    if (b <= b_crossover)
    {
        real = A_REAL_F(asin, b);
    }
    else if (x <= 1)
    {
        a_real_t den = A_REAL_C(0.5) * (a + x) * (y2 / (r + x + 1) + (s + 1 - x));
        real = A_REAL_F(atan, x / A_REAL_F(sqrt, den));
    }
    else
    {
        a_real_t ax = a + x;
        a_real_t den = A_REAL_C(0.5) * (ax / (r + x + 1) + ax / (s + x - 1));
        real = A_REAL_F(atan, x / (A_REAL_F(sqrt, den) * y));
    }
    if (a <= a_crossover)
    {
        a_real_t a1;
        if (x < 1)
        {
            a1 = A_REAL_C(0.5) * (y2 / (r + x + 1) + y2 / (s + 1 - x));
        }
        else
        {
            a1 = A_REAL_C(0.5) * (y2 / (r + x + 1) + (s + x - 1));
        }
        imag = A_REAL_F(log1p, a1 + A_REAL_F(sqrt, (a + 1) * a1));
    }
    else
    {
        imag = A_REAL_F(log, a + A_REAL_F(sqrt, a * a - 1));
    }
    return (a_complex_s){
        real >= 0 ? real : -real,
        imag >= 0 ? imag : -imag,
    };
#endif /* A_HAVE_CASIN */
}

a_complex_s a_complex_asin_real(a_real_t x)
{
    if (A_REAL_F(fabs, x) <= 1)
    {
        return (a_complex_s){A_REAL_F(asin, 0), 0};
    }
    if (x < 0)
    {
        return (a_complex_s){-a_real_c(A_PI_2), A_REAL_F(acosh, -x)};
    }
    return (a_complex_s){a_real_c(A_PI_2), -A_REAL_F(acosh, x)};
}

a_complex_s a_complex_acos(a_complex_s z)
{
#if defined(A_HAVE_CACOS) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(cacos, u.z);
    return u.s;
#else /* !A_HAVE_CACOS */
    if (z.imag == 0)
    {
        return a_complex_acos_real(z.real);
    }
    const a_real_t a_crossover = A_REAL_C(1.5);
    const a_real_t b_crossover = A_REAL_C(0.6417);
    a_real_t x = A_REAL_F(fabs, z.real);
    a_real_t y = A_REAL_F(fabs, z.imag);
    a_real_t r = A_REAL_F(hypot, x + 1, y);
    a_real_t s = A_REAL_F(hypot, x - 1, y);
    a_real_t a = A_REAL_C(0.5) * (r + s);
    a_real_t b = x / a;
    a_real_t y2 = y * y;
    a_real_t real, imag;
    if (b <= b_crossover)
    {
        real = A_REAL_F(acos, b);
    }
    else if (x <= 1)
    {
        a_real_t den = A_REAL_C(0.5) * (a + x) * (y2 / (r + x + 1) + (s + 1 - x));
        real = A_REAL_F(atan, A_REAL_F(sqrt, den) / x);
    }
    else
    {
        a_real_t ax = a + x;
        a_real_t den = A_REAL_C(0.5) * (ax / (r + x + 1) + ax / (s + x - 1));
        real = A_REAL_F(atan, A_REAL_F(sqrt, den) * y / x);
    }
    if (a <= a_crossover)
    {
        a_real_t a1;
        if (x < 1)
        {
            a1 = A_REAL_C(0.5) * (y2 / (r + x + 1) + y2 / (s + 1 - x));
        }
        else
        {
            a1 = A_REAL_C(0.5) * (y2 / (r + x + 1) + (s + x - 1));
        }
        imag = A_REAL_F(log1p, a1 + A_REAL_F(sqrt, (a + 1) * a1));
    }
    else
    {
        imag = A_REAL_F(log, a + A_REAL_F(sqrt, a * a - 1));
    }
    return (a_complex_s){
        real >= 0 ? real : a_real_c(A_PI) - real,
        imag >= 0 ? -imag : imag,
    };
#endif /* A_HAVE_CACOS */
}

a_complex_s a_complex_acos_real(a_real_t x)
{
    if (A_REAL_F(fabs, x) <= 1)
    {
        return (a_complex_s){A_REAL_F(acos, 0), 0};
    }
    if (x < 0)
    {
        return (a_complex_s){a_real_c(A_PI), -A_REAL_F(acosh, -x)};
    }
    return (a_complex_s){0, A_REAL_F(acosh, x)};
}

a_complex_s a_complex_atan(a_complex_s z)
{
#if defined(A_HAVE_CATAN) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(catan, u.z);
    return u.s;
#else /* !A_HAVE_CATAN */
    if (z.imag == 0)
    {
        return (a_complex_s){A_REAL_F(atan, z.real), 0};
    }
    a_real_t r = A_REAL_F(hypot, z.real, z.imag);
    a_real_t u = 2 * z.imag / (r * r + 1);
    a_real_t imag;
    if (A_REAL_F(fabs, u) < 0.1)
    {
        imag = A_REAL_C(0.25) * (A_REAL_F(log1p, u) - A_REAL_F(log1p, -u));
    }
    else
    {
        a_real_t a = A_REAL_F(hypot, z.real, z.imag + 1);
        a_real_t b = A_REAL_F(hypot, z.real, z.imag - 1);
        imag = A_REAL_C(0.5) * A_REAL_F(log, a / b);
    }
    if (z.real == 0)
    {
        if (z.imag > 1)
        {
            return (a_complex_s){a_real_c(A_PI), imag};
        }
        if (z.imag < -1)
        {
            return (a_complex_s){-a_real_c(A_PI), imag};
        }
        return (a_complex_s){0, imag};
    }
    return (a_complex_s){A_REAL_C(0.5) * A_REAL_F(atan2, z.real * 2, (1 + r) * (1 - r)), imag};
#endif /* A_HAVE_CATAN */
}

a_complex_s a_complex_asec(a_complex_s z)
{
    return a_complex_acos(a_complex_inv(z));
}

a_complex_s a_complex_asec_real(a_real_t x)
{
    if (x <= -1 || x >= 1)
    {
        return (a_complex_s){A_REAL_F(acos, 1 / x), 0};
    }
    if (x >= 0)
    {
        return (a_complex_s){0, A_REAL_F(acosh, 1 / x)};
    }
    return (a_complex_s){a_real_c(A_PI), -A_REAL_F(acosh, -1 / x)};
}

a_complex_s a_complex_acsc(a_complex_s z)
{
    return a_complex_asin(a_complex_inv(z));
}

a_complex_s a_complex_acsc_real(a_real_t x)
{
    if (x <= -1 || x >= 1)
    {
        return (a_complex_s){A_REAL_F(asin, 1 / x), 0};
    }
    if (x >= 0)
    {
        return (a_complex_s){a_real_c(A_PI_2), -A_REAL_F(acosh, 1 / x)};
    }
    return (a_complex_s){-a_real_c(A_PI_2), A_REAL_F(acosh, -1 / x)};
}

a_complex_s a_complex_acot(a_complex_s z)
{
    return a_complex_atan(a_complex_inv(z));
}

a_complex_s a_complex_sinh(a_complex_s z)
{
#if defined(A_HAVE_CSINH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(csinh, u.z);
    return u.s;
#else /* !A_HAVE_CSINH */
    return (a_complex_s){
        A_REAL_F(sinh, z.real) * A_REAL_F(cos, z.imag),
        A_REAL_F(cosh, z.real) * A_REAL_F(sin, z.imag),
    };
#endif /* A_HAVE_CSINH */
}

a_complex_s a_complex_cosh(a_complex_s z)
{
#if defined(A_HAVE_CCOSH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(ccosh, u.z);
    return u.s;
#else /* !A_HAVE_CCOSH */
    return (a_complex_s){
        A_REAL_F(cosh, z.real) * A_REAL_F(cos, z.imag),
        A_REAL_F(sinh, z.real) * A_REAL_F(sin, z.imag),
    };
#endif /* A_HAVE_CCOSH */
}

a_complex_s a_complex_tanh(a_complex_s z)
{
#if defined(A_HAVE_CTANH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(ctanh, u.z);
    return u.s;
#else /* !A_HAVE_CTANH */
    a_real_t ci = A_REAL_F(cos, z.imag);
    a_real_t sr = A_REAL_F(sinh, z.real);
    a_real_t inv = 1 / (ci * ci + sr * sr);
    a_real_t imag = A_REAL_F(sin, z.imag * 2) * inv * A_REAL_C(0.5);
    if (A_REAL_F(fabs, z.real) < 1)
    {
        return (a_complex_s){A_REAL_F(sinh, z.real) * A_REAL_F(cosh, z.real) * inv, imag};
    }
    a_real_t den = A_REAL_F(pow, ci / sr, 2) + 1;
    return (a_complex_s){1 / (A_REAL_F(tanh, z.real) * den), imag};
#endif /* A_HAVE_CTANH */
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
#if defined(A_HAVE_CASINH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(casinh, u.z);
    return u.s;
#else /* !A_HAVE_CASINH */
    z = a_complex_mul_imag(z, 1);
    z = a_complex_asin(z);
    return a_complex_mul_imag(z, -1);
#endif /* A_HAVE_CASINH */
}

a_complex_s a_complex_acosh(a_complex_s z)
{
#if defined(A_HAVE_CACOSH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(cacosh, u.z);
    return u.s;
#else /* !A_HAVE_CACOSH */
    z = a_complex_acsc(z);
    return a_complex_mul_imag(z, z.imag > 0 ? -1 : 1);
#endif /* A_HAVE_CACOSH */
}

a_complex_s a_complex_acosh_real(a_real_t x)
{
    if (x >= 1)
    {
        return (a_complex_s){A_REAL_F(acosh, x), 0};
    }
    if (x >= -1)
    {
        return (a_complex_s){0, A_REAL_F(acos, x)};
    }
    return (a_complex_s){A_REAL_F(acos, -x), a_real_c(A_PI)};
}

a_complex_s a_complex_atanh(a_complex_s z)
{
#if defined(A_HAVE_CATANH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F(catanh, u.z);
    return u.s;
#else /* !A_HAVE_CATANH */
    if (z.imag == 0)
    {
        return a_complex_atanh_real(z.real);
    }
    z = a_complex_mul_imag(z, 1);
    z = a_complex_atan(z);
    return a_complex_mul_imag(z, -1);
#endif /* A_HAVE_CATANH */
}

a_complex_s a_complex_atanh_real(a_real_t x)
{
    if (x > -1 && x < 1)
    {
        return (a_complex_s){A_REAL_F(atanh, x), 0};
    }
    return (a_complex_s){
        A_REAL_F(atanh, 1 / x),
        x < 0 ? a_real_c(A_PI_2) : -a_real_c(A_PI_2),
    };
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
