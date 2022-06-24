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

typedef struct a_imag_s
{
    a_real_t r;
    a_real_t i;
} a_imag_s;

typedef a_imag_s a_imag_t;
#define a_imag_real(ctx) (ctx).r
#define a_imag_imag(ctx) (ctx).i

#if A_DEF_FLOAT == 0
#define A_IMAG_P
#define A_IMAG_C(R, I) \
    {                  \
        R##F, I##F     \
    }
#elif A_DEF_FLOAT == 1
typedef double a_real_t;
#define A_IMAG_P
#define A_IMAG_C(R, I) \
    {                  \
        R, I           \
    }
#elif A_DEF_FLOAT == 2
#define A_IMAG_P "L"
#define A_IMAG_C(R, I) \
    {                  \
        R##L, I##L     \
    }
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
A_PUBLIC void a_imag_add(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r);
/*!
 @brief = @f[ (a+b i)-(c+d i)=(a-c)+(b-d)i @f]
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_imag_sub(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r);
/*!
 @brief = @f[ (a+b i)(c+d i)=a c+b c i+a d i+b d i^{2}=(a c-b d)+(b c+a d) i @f]
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_imag_mul(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r);
/*!
 @brief = @f[ \frac{(a+b i)}{(c+d i)}=\frac{(a+b i)(c-d i)}{(c+d i)(c-d i)}=\frac{a c+b c i-a d i-b d i^{2}}{c^{2}-(d i)^{2}}=\frac{(a c+b d)+(b c-a d) i}{c^{2}+d^{2}}=\left(\frac{a c+b d}{c^{2}+d^{2}}\right)+\left(\frac{b c-a d}{c^{2}+d^{2}}\right) i @f]
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_imag_div(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_IMAG_H__ */
