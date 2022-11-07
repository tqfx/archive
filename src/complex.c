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
#if defined(_MSC_VER)
#pragma warning(disable : 4204)
#endif /* _MSC_VER */
#include "complex.h"
#undef A_INTERN

a_complex_s a_complex_polar(a_real_t r, a_real_t theta)
{
    return a_complex_c(r * a_real_cos(theta), r * a_real_sin(theta));
}

a_real_t a_complex_logabs(a_complex_s z)
{
    a_real_t xabs = a_real_abs(z.real);
    a_real_t yabs = a_real_abs(z.imag);
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
    return a_real_log(max) + a_real_log1p(u * u) * A_REAL_C(0.5);
}

a_real_t a_complex_abs2(a_complex_s z)
{
    return z.real * z.real + z.imag * z.imag;
}

a_real_t a_complex_abs(a_complex_s z)
{
    return a_real_hypot(z.real, z.imag);
}

a_real_t a_complex_arg(a_complex_s z)
{
    return a_real_atan2(z.imag, z.real);
}

a_complex_s a_complex_add(a_complex_s x, a_complex_s y)
{
    return a_complex_c(x.real + y.real, x.imag + y.imag);
}

a_complex_s a_complex_add_real(a_complex_s x, a_real_t y)
{
    return a_complex_c(x.real + y, x.imag);
}

a_complex_s a_complex_add_imag(a_complex_s x, a_real_t y)
{
    return a_complex_c(x.real, x.imag + y);
}

a_complex_s a_complex_sub(a_complex_s x, a_complex_s y)
{
    return a_complex_c(x.real - y.real, x.imag - y.imag);
}

a_complex_s a_complex_sub_real(a_complex_s x, a_real_t y)
{
    return a_complex_c(x.real - y, x.imag);
}

a_complex_s a_complex_sub_imag(a_complex_s x, a_real_t y)
{
    return a_complex_c(x.real, x.imag - y);
}

a_complex_s a_complex_mul(a_complex_s x, a_complex_s y)
{
    return a_complex_c(x.real * y.real - x.imag * y.imag,
                       x.real * y.imag + x.imag * y.real);
}

a_complex_s a_complex_mul_real(a_complex_s x, a_real_t y)
{
    return a_complex_c(x.real * y, x.imag * y);
}

a_complex_s a_complex_mul_imag(a_complex_s x, a_real_t y)
{
    return a_complex_c(-x.imag * y, x.real * y);
}

a_complex_s a_complex_div(a_complex_s x, a_complex_s y)
{
    a_real_t inv = 1 / (y.real * y.real + y.imag * y.imag);
    return a_complex_c((x.real * y.real + x.imag * y.imag) * inv,
                       (x.imag * y.real - x.real * y.imag) * inv);
}

a_complex_s a_complex_div_real(a_complex_s x, a_real_t y)
{
    return a_complex_c(x.real / y, x.imag / y);
}

a_complex_s a_complex_div_imag(a_complex_s x, a_real_t y)
{
    return a_complex_c(x.imag / y, -x.real / y);
}

a_complex_s a_complex_inv(a_complex_s z)
{
    a_real_t inv = 1 / (z.real * z.real + z.imag * z.imag);
    return a_complex_c(z.real * inv, -z.imag * inv);
}

#if __has_warning("-Wincompatible-library-redeclaration")
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"
#endif /* clang 4.0+ */
#if a_prereq_gnuc(2, 95) || __has_warning("-Wimplicit-function-declaration")
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#endif /* gcc 2.95+ */
#if a_prereq_gnuc(10, 1)
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#endif /* gcc 10.1+ */

#if defined(A_HAVE_CSQRT) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(csqrt, a_complex_s);
#endif /* A_HAVE_CSQRT */

a_complex_s a_complex_sqrt(a_complex_s z)
{
#if defined(A_HAVE_CSQRT) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(csqrt, u.z);
    return u.s;
#elif defined(A_HAVE_CSQRT)
    return A_REAL_F1(csqrt, z);
#else /* !A_HAVE_CSQRT */
    if (z.real == 0 && z.imag == 0)
    {
        return A_COMPLEX_C(0.0, 0.0);
    }
    a_real_t x = a_real_abs(z.real);
    a_real_t y = a_real_abs(z.imag);
    a_real_t w;
    if (x >= y)
    {
        a_real_t t = y / x;
        w = a_real_sqrt(x) * a_real_sqrt((a_real_sqrt(A_SQ(t) + 1) + 1) * A_REAL_C(0.5));
    }
    else
    {
        a_real_t t = x / y;
        w = a_real_sqrt(y) * a_real_sqrt((a_real_sqrt(A_SQ(t) + 1) + t) * A_REAL_C(0.5));
    }
    if (z.real >= 0)
    {
        return a_complex_c(w, z.imag / (w * 2));
    }
    if (z.imag < 0)
    {
        w = -w;
    }
    return a_complex_c(z.imag / (w * 2), w);
#endif /* A_HAVE_CSQRT */
}

a_complex_s a_complex_sqrt_real(a_real_t x)
{
    if (x >= 0)
    {
        return a_complex_c(a_real_sqrt(x), 0);
    }
    return a_complex_c(0, a_real_sqrt(-x));
}

#if defined(A_HAVE_CPOW) && !defined A_COMPLEX_T
a_complex_s A_REAL_F2(cpow, a_complex_s, a_complex_s);
#endif /* A_HAVE_CPOW */

a_complex_s a_complex_pow(a_complex_s z, a_complex_s a)
{
#if defined(A_HAVE_CPOW) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    a_complex_u v = {a};
    u.z = A_REAL_F2(cpow, u.z, v.z);
    return u.s;
#elif defined(A_HAVE_CPOW)
    return A_REAL_F2(cpow, z, a);
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
    a_real_t rho = a_real_exp(logr * a.real - theta * a.imag);
    a_real_t beta = theta * a.real + logr * a.imag;
    return a_complex_polar(rho, beta);
#endif /* A_HAVE_CPOW */
}

a_complex_s a_complex_pow_real(a_complex_s z, a_real_t a)
{
    if (z.real == 0 && z.imag == 0)
    {
        if (a == 0)
        {
            return A_COMPLEX_C(1.0, 0.0);
        }
        return A_COMPLEX_C(0.0, 0.0);
    }
    a_real_t logr = a_complex_logabs(z);
    a_real_t theta = a_complex_arg(z);
    a_real_t rho = a_real_exp(logr * a);
    a_real_t beta = theta * a;
    return a_complex_polar(rho, beta);
}

#if defined(A_HAVE_CEXP) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(cexp, a_complex_s);
#endif /* A_HAVE_CEXP */

a_complex_s a_complex_exp(a_complex_s z)
{
#if defined(A_HAVE_CEXP) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(cexp, u.z);
    return u.s;
#elif defined(A_HAVE_CEXP)
    return A_REAL_F1(cexp, z);
#else /* !A_HAVE_CEXP */
    a_real_t rho = a_real_exp(z.real);
    return a_complex_polar(rho, z.imag);
#endif /* A_HAVE_CEXP */
}

#if defined(A_HAVE_CLOG) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(clog, a_complex_s);
#endif /* A_HAVE_CLOG */

a_complex_s a_complex_log(a_complex_s z)
{
#if defined(A_HAVE_CLOG) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(clog, u.z);
    return u.s;
#elif defined(A_HAVE_CLOG)
    return A_REAL_F1(clog, z);
#else /* !A_HAVE_CLOG */
    a_real_t logr = a_complex_logabs(z);
    a_real_t theta = a_complex_arg(z);
    return a_complex_c(logr, theta);
#endif /* A_HAVE_CLOG */
}

a_complex_s a_complex_log2(a_complex_s z)
{
    return a_complex_mul_real(a_complex_log(z), 1 / A_REAL_LN2);
}

a_complex_s a_complex_log10(a_complex_s z)
{
    return a_complex_mul_real(a_complex_log(z), 1 / A_REAL_LN10);
}

a_complex_s a_complex_logb(a_complex_s z, a_complex_s b)
{
    return a_complex_div(a_complex_log(z), a_complex_log(b));
}

#if defined(A_HAVE_CSIN) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(csin, a_complex_s);
#endif /* A_HAVE_CSIN */

a_complex_s a_complex_sin(a_complex_s z)
{
#if defined(A_HAVE_CSIN) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(csin, u.z);
    return u.s;
#elif defined(A_HAVE_CSIN)
    return A_REAL_F1(csin, z);
#else /* !A_HAVE_CSIN */
    if (z.imag == 0)
    {
        return a_complex_c(a_real_sin(z.real), 0);
    }
    return a_complex_c(a_real_sin(z.real) * a_real_cosh(z.imag),
                       a_real_cos(z.real) * a_real_sinh(z.imag));
#endif /* A_HAVE_CSIN */
}

#if defined(A_HAVE_CCOS) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(ccos, a_complex_s);
#endif /* A_HAVE_CCOS */

a_complex_s a_complex_cos(a_complex_s z)
{
#if defined(A_HAVE_CCOS) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(ccos, u.z);
    return u.s;
#elif defined(A_HAVE_CCOS)
    return A_REAL_F1(ccos, z);
#else /* !A_HAVE_CCOS */
    if (z.imag == 0)
    {
        return a_complex_c(a_real_cos(z.real), 0);
    }
    return a_complex_c(a_real_cos(z.real) * a_real_cosh(z.imag),
                       a_real_sin(z.real) * a_real_sinh(-z.imag));
#endif /* A_HAVE_CCOS */
}

#if defined(A_HAVE_CTAN) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(ctan, a_complex_s);
#endif /* A_HAVE_CTAN */

a_complex_s a_complex_tan(a_complex_s z)
{
#if defined(A_HAVE_CTAN) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(ctan, u.z);
    return u.s;
#elif defined(A_HAVE_CTAN)
    return A_REAL_F1(ctan, z);
#else /* !A_HAVE_CTAN */
    a_real_t cr = a_real_cos(z.real);
    a_real_t si = a_real_sinh(z.imag);
    a_real_t inv = A_REAL_C(0.5) / (cr * cr + si * si);
    a_real_t real = a_real_sin(z.real * 2) * inv;
    if (a_real_abs(z.imag) < 1)
    {
        return a_complex_c(real, a_real_sinh(z.imag * 2) * inv);
    }
    a_real_t den = a_real_pow(cr / si, 2) + 1;
    return a_complex_c(real, 1 / (a_real_tanh(z.imag) * den));
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

#if defined(A_HAVE_CASIN) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(casin, a_complex_s);
#endif /* A_HAVE_CASIN */

a_complex_s a_complex_asin(a_complex_s z)
{
#if defined(A_HAVE_CASIN) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(casin, u.z);
    return u.s;
#elif defined(A_HAVE_CASIN)
    return A_REAL_F1(casin, z);
#else /* !A_HAVE_CASIN */
    if (z.imag == 0)
    {
        return a_complex_asin_real(z.real);
    }
    const a_real_t a_crossover = A_REAL_C(1.5);
    const a_real_t b_crossover = A_REAL_C(0.6417);
    a_real_t x = a_real_abs(z.real);
    a_real_t y = a_real_abs(z.imag);
    a_real_t r = a_real_hypot(x + 1, y);
    a_real_t s = a_real_hypot(x - 1, y);
    a_real_t a = A_REAL_C(0.5) * (r + s);
    a_real_t b = x / a;
    a_real_t y2 = y * y;
    a_real_t real, imag;
    if (b <= b_crossover)
    {
        real = a_real_asin(b);
    }
    else if (x <= 1)
    {
        a_real_t den = A_REAL_C(0.5) * (a + x) * (y2 / (r + x + 1) + (s + 1 - x));
        real = a_real_atan(x / a_real_sqrt(den));
    }
    else
    {
        a_real_t ax = a + x;
        a_real_t den = A_REAL_C(0.5) * (ax / (r + x + 1) + ax / (s + x - 1));
        real = a_real_atan(x / (a_real_sqrt(den) * y));
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
        imag = a_real_log1p(a1 + a_real_sqrt((a + 1) * a1));
    }
    else
    {
        imag = a_real_log(a + a_real_sqrt(a * a - 1));
    }
    return a_complex_c(real >= 0 ? real : -real,
                       imag >= 0 ? imag : -imag);
#endif /* A_HAVE_CASIN */
}

a_complex_s a_complex_asin_real(a_real_t x)
{
    if (a_real_abs(x) <= 1)
    {
        return a_complex_c(a_real_asin(0), 0);
    }
    if (x < 0)
    {
        return a_complex_c(-A_REAL_PI_2, a_real_acosh(-x));
    }
    return a_complex_c(A_REAL_PI_2, -a_real_acosh(x));
}

#if defined(A_HAVE_CACOS) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(cacos, a_complex_s);
#endif /* A_HAVE_CACOS */

a_complex_s a_complex_acos(a_complex_s z)
{
#if defined(A_HAVE_CACOS) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(cacos, u.z);
    return u.s;
#elif defined(A_HAVE_CACOS)
    return A_REAL_F1(cacos, z);
#else /* !A_HAVE_CACOS */
    if (z.imag == 0)
    {
        return a_complex_acos_real(z.real);
    }
    const a_real_t a_crossover = A_REAL_C(1.5);
    const a_real_t b_crossover = A_REAL_C(0.6417);
    a_real_t x = a_real_abs(z.real);
    a_real_t y = a_real_abs(z.imag);
    a_real_t r = a_real_hypot(x + 1, y);
    a_real_t s = a_real_hypot(x - 1, y);
    a_real_t a = A_REAL_C(0.5) * (r + s);
    a_real_t b = x / a;
    a_real_t y2 = y * y;
    a_real_t real, imag;
    if (b <= b_crossover)
    {
        real = a_real_acos(b);
    }
    else if (x <= 1)
    {
        a_real_t den = A_REAL_C(0.5) * (a + x) * (y2 / (r + x + 1) + (s + 1 - x));
        real = a_real_atan(a_real_sqrt(den) / x);
    }
    else
    {
        a_real_t ax = a + x;
        a_real_t den = A_REAL_C(0.5) * (ax / (r + x + 1) + ax / (s + x - 1));
        real = a_real_atan(a_real_sqrt(den) * y / x);
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
        imag = a_real_log1p(a1 + a_real_sqrt((a + 1) * a1));
    }
    else
    {
        imag = a_real_log(a + a_real_sqrt(a * a - 1));
    }
    return a_complex_c(real >= 0 ? real : A_REAL_PI - real,
                       imag >= 0 ? -imag : imag);
#endif /* A_HAVE_CACOS */
}

a_complex_s a_complex_acos_real(a_real_t x)
{
    if (a_real_abs(x) <= 1)
    {
        return a_complex_c(a_real_acos(0), 0);
    }
    if (x < 0)
    {
        return a_complex_c(A_REAL_PI, -a_real_acosh(-x));
    }
    return a_complex_c(0, a_real_acosh(x));
}

#if defined(A_HAVE_CATAN) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(catan, a_complex_s);
#endif /* A_HAVE_CATAN */

a_complex_s a_complex_atan(a_complex_s z)
{
#if defined(A_HAVE_CATAN) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(catan, u.z);
    return u.s;
#elif defined(A_HAVE_CATAN)
    return A_REAL_F1(catan, z);
#else /* !A_HAVE_CATAN */
    if (z.imag == 0)
    {
        return a_complex_c(a_real_atan(z.real), 0);
    }
    a_real_t r = a_real_hypot(z.real, z.imag);
    a_real_t u = 2 * z.imag / (r * r + 1);
    a_real_t imag;
    if (a_real_abs(u) < 0.1)
    {
        imag = A_REAL_C(0.25) * (a_real_log1p(u) - a_real_log1p(-u));
    }
    else
    {
        a_real_t a = a_real_hypot(z.real, z.imag + 1);
        a_real_t b = a_real_hypot(z.real, z.imag - 1);
        imag = A_REAL_C(0.5) * a_real_log(a / b);
    }
    if (z.real == 0)
    {
        if (z.imag > 1)
        {
            return a_complex_c(A_REAL_PI, imag);
        }
        if (z.imag < -1)
        {
            return a_complex_c(-A_REAL_PI, imag);
        }
        return a_complex_c(0, imag);
    }
    return a_complex_c(A_REAL_C(0.5) * a_real_atan2(z.real * 2, (1 + r) * (1 - r)), imag);
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
        return a_complex_c(a_real_acos(1 / x), 0);
    }
    if (x >= 0)
    {
        return a_complex_c(0, a_real_acosh(1 / x));
    }
    return a_complex_c(A_REAL_PI, -a_real_acosh(-1 / x));
}

a_complex_s a_complex_acsc(a_complex_s z)
{
    return a_complex_asin(a_complex_inv(z));
}

a_complex_s a_complex_acsc_real(a_real_t x)
{
    if (x <= -1 || x >= 1)
    {
        return a_complex_c(a_real_asin(1 / x), 0);
    }
    if (x >= 0)
    {
        return a_complex_c(A_REAL_PI_2, -a_real_acosh(1 / x));
    }
    return a_complex_c(-A_REAL_PI_2, a_real_acosh(-1 / x));
}

a_complex_s a_complex_acot(a_complex_s z)
{
    return a_complex_atan(a_complex_inv(z));
}

#if defined(A_HAVE_CSINH) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(csinh, a_complex_s);
#endif /* A_HAVE_CSINH */

a_complex_s a_complex_sinh(a_complex_s z)
{
#if defined(A_HAVE_CSINH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(csinh, u.z);
    return u.s;
#elif defined(A_HAVE_CSINH)
    return A_REAL_F1(csinh, z);
#else /* !A_HAVE_CSINH */
    return a_complex_c(a_real_sinh(z.real) * a_real_cos(z.imag),
                       a_real_cosh(z.real) * a_real_sin(z.imag));
#endif /* A_HAVE_CSINH */
}

#if defined(A_HAVE_CCOSH) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(ccosh, a_complex_s);
#endif /* A_HAVE_CCOSH */

a_complex_s a_complex_cosh(a_complex_s z)
{
#if defined(A_HAVE_CCOSH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(ccosh, u.z);
    return u.s;
#elif defined(A_HAVE_CCOSH)
    return A_REAL_F1(ccosh, z);
#else /* !A_HAVE_CCOSH */
    return a_complex_c(a_real_cosh(z.real) * a_real_cos(z.imag),
                       a_real_sinh(z.real) * a_real_sin(z.imag));
#endif /* A_HAVE_CCOSH */
}

#if defined(A_HAVE_CTANH) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(ctanh, a_complex_s);
#endif /* A_HAVE_CTANH */

a_complex_s a_complex_tanh(a_complex_s z)
{
#if defined(A_HAVE_CTANH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(ctanh, u.z);
    return u.s;
#elif defined(A_HAVE_CTANH)
    return A_REAL_F1(ctanh, z);
#else /* !A_HAVE_CTANH */
    a_real_t ci = a_real_cos(z.imag);
    a_real_t sr = a_real_sinh(z.real);
    a_real_t inv = 1 / (ci * ci + sr * sr);
    a_real_t imag = a_real_sin(z.imag * 2) * inv * A_REAL_C(0.5);
    if (a_real_abs(z.real) < 1)
    {
        return a_complex_c(a_real_sinh(z.real) * a_real_cosh(z.real) * inv, imag);
    }
    a_real_t den = a_real_pow(ci / sr, 2) + 1;
    return a_complex_c(1 / (a_real_tanh(z.real) * den), imag);
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

#if defined(A_HAVE_CASINH) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(casinh, a_complex_s);
#endif /* A_HAVE_CASINH */

a_complex_s a_complex_asinh(a_complex_s z)
{
#if defined(A_HAVE_CASINH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(casinh, u.z);
    return u.s;
#elif defined(A_HAVE_CASINH)
    return A_REAL_F1(casinh, z);
#else /* !A_HAVE_CASINH */
    z = a_complex_mul_imag(z, 1);
    z = a_complex_asin(z);
    return a_complex_mul_imag(z, -1);
#endif /* A_HAVE_CASINH */
}

#if defined(A_HAVE_CACOSH) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(cacosh, a_complex_s);
#endif /* A_HAVE_CACOSH */

a_complex_s a_complex_acosh(a_complex_s z)
{
#if defined(A_HAVE_CACOSH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(cacosh, u.z);
    return u.s;
#elif defined(A_HAVE_CACOSH)
    return A_REAL_F1(cacosh, z);
#else /* !A_HAVE_CACOSH */
    z = a_complex_acsc(z);
    return a_complex_mul_imag(z, z.imag > 0 ? -1 : 1);
#endif /* A_HAVE_CACOSH */
}

a_complex_s a_complex_acosh_real(a_real_t x)
{
    if (x >= 1)
    {
        return a_complex_c(a_real_acosh(x), 0);
    }
    if (x >= -1)
    {
        return a_complex_c(0, a_real_acos(x));
    }
    return a_complex_c(a_real_acos(-x), A_REAL_PI);
}

#if defined(A_HAVE_CATANH) && !defined A_COMPLEX_T
a_complex_s A_REAL_F1(catanh, a_complex_s);
#endif /* A_HAVE_CATANH */

a_complex_s a_complex_atanh(a_complex_s z)
{
#if defined(A_HAVE_CATANH) && defined(A_COMPLEX_T)
    a_complex_u u = {z};
    u.z = A_REAL_F1(catanh, u.z);
    return u.s;
#elif defined(A_HAVE_CATANH)
    return A_REAL_F1(catanh, z);
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
        return a_complex_c(a_real_atanh(x), 0);
    }
    return a_complex_c(a_real_atanh(1 / x), x < 0 ? A_REAL_PI_2 : -A_REAL_PI_2);
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
