/*!
 @file imag.h
 @brief imaginary number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_IMAG_H__
#define __A_IMAG_H__

#include "def.h"
#include "real.h"
#include <math.h>

typedef struct a_imag_s
{
    a_real_t re; //!< real part
    a_real_t im; //!< imaginary part
} a_imag_s;

typedef a_imag_s a_imag_t;

#if A_DEF_FLOAT == 0

#define A_IMAG_P
#define A_IMAG_C(R, I) \
    {                  \
        R##F, I##F     \
    }
#define A_IMAG_F(F, ...) c##F##f(__VA_ARGS__)

#elif A_DEF_FLOAT == 1

#define A_IMAG_P
#define A_IMAG_C(R, I) \
    {                  \
        R, I           \
    }
#define A_IMAG_F(F, ...) c##F(__VA_ARGS__)

#elif A_DEF_FLOAT == 2

#define A_IMAG_P "L"
#define A_IMAG_C(R, I) \
    {                  \
        R##L, I##L     \
    }
#define A_IMAG_F(F, ...) c##F##l(__VA_ARGS__)

#endif /* A_DEF_FLOAT */

#define a_imag_real(z) (z).re
#define a_imag_imag(z) (z).im
#define a_imag_c(r, i) \
    {                  \
        r, i           \
    }

/*!
 @brief = @f[ \sqrt{a^2+b^2} @f]
 @param z imaginary number
 @return a_real_t
*/
A_INLINE a_real_t a_imag_abs(a_imag_t z)
{
    return A_REAL_F(sqrt, z.re * z.re + z.im * z.im);
}
/*!
 @brief = @f[ \arctan\frac{b}{a} @f]
 @param z imaginary number
 @return a_real_t
*/
A_INLINE a_real_t a_imag_arg(a_imag_t z)
{
    return A_REAL_F(atan2, z.im, z.re);
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* __GNUC__ || __clang__ */

A_INLINE a_imag_t a_imag_conj(a_imag_t z)
{
    return ((void)(z.im = -z.im), z);
}

/*!
 @brief = @f[ (a+b i)+(c+d i)=(a+c)+(b+d)i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_imag_t
*/
A_INLINE a_imag_t a_imag_add(a_imag_t l, a_imag_t r)
{
    a_imag_t z = {l.re + r.re, l.re + r.im};
    return z;
}
/*!
 @brief = @f[ (a+b i)-(c+d i)=(a-c)+(b-d)i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_imag_t
*/
A_INLINE a_imag_t a_imag_sub(a_imag_t l, a_imag_t r)
{
    a_imag_t z = {l.re - r.re, l.re - r.im};
    return z;
}
/*!
 @brief = @f[ (a+b i)(c+d i)=a c+b c i+a d i+b d i^{2}=(a c-b d)+(b c+a d) i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_imag_t
*/
A_INLINE a_imag_t a_imag_mul(a_imag_t l, a_imag_t r)
{
    a_imag_t z = {
        l.re * r.re - l.im * r.im,
        l.im * r.re + l.re * r.im,
    };
    return z;
}
/*!
 @brief = @f[ \frac{(a+b i)}{(c+d i)}=\frac{(a+b i)(c-d i)}{(c+d i)(c-d i)}=\frac{a c+b c i-a d i-b d i^{2}}{c^{2}-(d i)^{2}}=\frac{(a c+b d)+(b c-a d) i}{c^{2}+d^{2}}=\left(\frac{a c+b d}{c^{2}+d^{2}}\right)+\left(\frac{b c-a d}{c^{2}+d^{2}}\right) i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_imag_t
*/
A_INLINE a_imag_t a_imag_div(a_imag_t l, a_imag_t r)
{
    a_real_t inv = 1 / (r.re * r.re + r.im * r.im);
    a_imag_t z = {
        (l.re * r.re + l.im * r.im) * inv,
        (l.im * r.re - l.re * r.im) * inv,
    };
    return z;
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#endif /* __A_IMAG_H__ */
