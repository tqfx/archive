/*!
 @file complex.h
 @brief complex number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_COMPLEX_H__
#define __A_COMPLEX_H__

#include "def.h"
#include "real.h"

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
#define A_COMPLEX_P
#if defined(_MSC_VER)
#define A_COMPLEX_C(R, I) _FCbuild(R, I)
#else /* !_MSC_VER */
#define A_COMPLEX_C(R, I) (R##F + (__extension__ 1.0IF) * I##F)
#endif /* _MSC_VER */
#define A_COMPLEX_F(F, ...) c##F##f(__VA_ARGS__)

#elif A_DEF_FLOAT == 1

typedef a_complex_d a_complex_t;
#define A_COMPLEX_P
#if defined(_MSC_VER)
#define A_COMPLEX_C(R, I) _Cbuild(R, I)
#else /* !_MSC_VER */
#define A_COMPLEX_C(R, I) (R + (__extension__ 1.0I) * I)
#endif /* _MSC_VER */
#define A_COMPLEX_F(F, ...) c##F(__VA_ARGS__)

#elif A_DEF_FLOAT == 2

typedef a_complex_l a_complex_t;
#define A_COMPLEX_P "L"
#if defined(_MSC_VER)
#define A_COMPLEX_C(R, I) _LCbuild(R, I)
#else /* !_MSC_VER */
#define A_COMPLEX_C(R, I) (R##L + (__extension__ 1.0IL) * I##L)
#endif /* _MSC_VER */
#define A_COMPLEX_F(F, ...) c##F##l(__VA_ARGS__)

#endif /* A_DEF_FLOAT */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief = @f[ (a+b i)+(c+d i)=(a+c)+(b+d)i @f]
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_complex_add(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r);
/*!
 @brief = @f[ (a+b i)-(c+d i)=(a-c)+(b-d)i @f]
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_complex_sub(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r);
/*!
 @brief = @f[ (a+b i)(c+d i)=a c+b c i+a d i+b d i^{2}=(a c-b d)+(b c+a d) i @f]
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_complex_mul(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r);
/*!
 @brief = @f[ \frac{(a+b i)}{(c+d i)}=\frac{(a+b i)(c-d i)}{(c+d i)(c-d i)}=\frac{a c+b c i-a d i-b d i^{2}}{c^{2}-(d i)^{2}}=\frac{(a c+b d)+(b c-a d) i}{c^{2}+d^{2}}=\left(\frac{a c+b d}{c^{2}+d^{2}}\right)+\left(\frac{b c-a d}{c^{2}+d^{2}}\right) i @f]
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_complex_div(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_COMPLEX_H__ */
