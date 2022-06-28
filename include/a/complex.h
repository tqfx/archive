/*!
 @file complex.h
 @brief complex number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_COMPLEX_H__
#define __A_COMPLEX_H__

#include "real.h"

#if defined(__STDC_VERSION__)

#include <complex.h>

#if defined(_MSC_VER)

typedef _Fcomplex a_complex_f;
typedef _Dcomplex a_complex_d;
typedef _Lcomplex a_complex_l;

#else /* !_MSC_VER */

typedef float _Complex a_complex_f;
typedef double _Complex a_complex_d;
typedef long double _Complex a_complex_l;

#endif /* _MSC_VER */

#if A_DEF_FLOAT == 0

typedef a_complex_f a_complex_t;

#if defined(_MSC_VER)
#define A_COMPLEX_C(R, I) _FCbuild(R, I)
#else /* !_MSC_VER */
#define A_COMPLEX_C(R, I) (R##F + (__extension__ 1.0IF) * I##F)
#endif /* _MSC_VER */
#define A_COMPLEX_F(F, ...) c##F##f(__VA_ARGS__)

#define A_COMPLEX_PRI(RF, RC, IF, IC) "(%" RF RC ",%" IF IC ")"

#elif A_DEF_FLOAT == 1

typedef a_complex_d a_complex_t;

#if defined(_MSC_VER)
#define A_COMPLEX_C(R, I) _Cbuild(R, I)
#else /* !_MSC_VER */
#define A_COMPLEX_C(R, I) (R + (__extension__ 1.0I) * I)
#endif /* _MSC_VER */
#define A_COMPLEX_F(F, ...) c##F(__VA_ARGS__)

#define A_COMPLEX_PRI(RF, RC, IF, IC) "(%" RF RC ",%" IF IC ")"

#elif A_DEF_FLOAT == 2

typedef a_complex_l a_complex_t;

#if defined(_MSC_VER)
#define A_COMPLEX_C(R, I) _LCbuild(R, I)
#else /* !_MSC_VER */
#define A_COMPLEX_C(R, I) (R##L + (__extension__ 1.0IL) * I##L)
#endif /* _MSC_VER */
#define A_COMPLEX_F(F, ...) c##F##l(__VA_ARGS__)

#define A_COMPLEX_PRI(RF, RC, IF, IC) "(%" RF "L" RC ",%" IF "L" IC ")"

#endif /* A_DEF_FLOAT */

A_INLINE a_real_t a_complex_real(a_complex_t z)
{
    return A_COMPLEX_F(real, z);
}
A_INLINE a_real_t a_complex_imag(a_complex_t z)
{
    return A_COMPLEX_F(imag, z);
}
A_INLINE a_real_t a_complex_abs(a_complex_t z)
{
    return A_COMPLEX_F(abs, z);
}
A_INLINE a_real_t a_complex_arg(a_complex_t z)
{
    return A_COMPLEX_F(arg, z);
}
A_INLINE a_complex_t a_complex_conj(a_complex_t z)
{
    return A_COMPLEX_F(onj, z);
}
A_INLINE a_complex_t a_complex_proj(a_complex_t z)
{
    return A_COMPLEX_F(proj, z);
}

/*!
 @brief = @f[ (a+b i)+(c+d i)=(a+c)+(b+d)i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_complex_t
*/
A_INLINE a_complex_t a_complex_add(a_complex_t l, a_complex_t r)
{
#if defined(_MSC_VER)

    return (a_complex_t){l._Val[0] + r._Val[0], l._Val[1] + r._Val[1]};

#else /* !_MSC_VER */

    return l + r;

#endif /* _MSC_VER */
}
/*!
 @brief = @f[ (a+b i)-(c+d i)=(a-c)+(b-d)i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_complex_t
*/
A_INLINE a_complex_t a_complex_sub(a_complex_t l, a_complex_t r)
{
#if defined(_MSC_VER)

    return (a_complex_t){l._Val[0] - r._Val[0], l._Val[1] - r._Val[1]};

#else /* !_MSC_VER */

    return l - r;

#endif /* _MSC_VER */
}
/*!
 @brief = @f[ (a+b i)(c+d i)=a c+b c i+a d i+b d i^{2}=(a c-b d)+(b c+a d) i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_complex_t
*/
A_INLINE a_complex_t a_complex_mul(a_complex_t l, a_complex_t r)
{
#if defined(_MSC_VER)

#if A_DEF_FLOAT == 0
    return _FCmulcc(l, r);
#elif A_DEF_FLOAT == 1
    return _Cmulcc(l, r);
#elif A_DEF_FLOAT == 2
    return _LCmulcc(l, r);
#endif /* A_DEF_FLOAT */

#else /* !_MSC_VER */

    return l * r;

#endif /* _MSC_VER */
}
/*!
 @brief = @f[ \frac{(a+b i)}{(c+d i)}=\frac{(a+b i)(c-d i)}{(c+d i)(c-d i)}=\frac{a c+b c i-a d i-b d i^{2}}{c^{2}-(d i)^{2}}=\frac{(a c+b d)+(b c-a d) i}{c^{2}+d^{2}}=\left(\frac{a c+b d}{c^{2}+d^{2}}\right)+\left(\frac{b c-a d}{c^{2}+d^{2}}\right) i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_complex_t
*/
A_INLINE a_complex_t a_complex_div(a_complex_t l, a_complex_t r)
{
#if defined(_MSC_VER)

    a_real_t inv = 1 / (r._Val[0] * r._Val[0] + r._Val[1] * r._Val[1]);
    return (a_complex_t){
        (l._Val[0] * r._Val[0] + l._Val[1] * r._Val[1]) * inv,
        (l._Val[1] * r._Val[0] - l._Val[0] * r._Val[1]) * inv,
    };

#else /* !_MSC_VER */

    return l / r;

#endif /* _MSC_VER */
}

#endif /* __STDC_VERSION__ */

#endif /* __A_COMPLEX_H__ */
