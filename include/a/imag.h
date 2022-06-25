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
    a_real_t re; //!< real part
    a_real_t im; //!< imaginary part
} a_imag_s;

#define a_imag_real(ctx) (ctx).re
#define a_imag_imag(ctx) (ctx).im

typedef a_imag_s a_imag_t;

/*!
 @brief create imaginary number
 @param re real part
 @param im imaginary part
 @return a_imag_t
*/
A_INLINE a_imag_t a_imag_c(a_real_t re, a_real_t im) { return (a_imag_t){re, im}; }
/*!
 @brief z = @f[ (a+b i)+(c+d i)=(a+c)+(b+d)i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_imag_t
*/
A_INLINE a_imag_t a_imag_add(a_imag_t l, a_imag_t r)
{
    return (a_imag_t){l.re + r.re, l.re + r.im};
}
/*!
 @brief z = @f[ (a+b i)-(c+d i)=(a-c)+(b-d)i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_imag_t
*/
A_INLINE a_imag_t a_imag_sub(a_imag_t l, a_imag_t r)
{
    return (a_imag_t){l.re - r.re, l.re - r.im};
}
/*!
 @brief z = @f[ (a+b i)(c+d i)=a c+b c i+a d i+b d i^{2}=(a c-b d)+(b c+a d) i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_imag_t
*/
A_INLINE a_imag_t a_imag_mul(a_imag_t l, a_imag_t r)
{
    return (a_imag_t){
        l.re * r.re - l.im * r.im,
        l.im * r.re + l.re * r.im,
    };
}
/*!
 @brief z = @f[ \frac{(a+b i)}{(c+d i)}=\frac{(a+b i)(c-d i)}{(c+d i)(c-d i)}=\frac{a c+b c i-a d i-b d i^{2}}{c^{2}-(d i)^{2}}=\frac{(a c+b d)+(b c-a d) i}{c^{2}+d^{2}}=\left(\frac{a c+b d}{c^{2}+d^{2}}\right)+\left(\frac{b c-a d}{c^{2}+d^{2}}\right) i @f]
 @param l the left-hand operand
 @param r the right-hand operand
 @return a_imag_t
*/
A_INLINE a_imag_t a_imag_div(a_imag_t l, a_imag_t r)
{
    a_real_t den_inv = 1 / (r.re * r.re + r.im * r.im);
    return (a_imag_t){
        (l.re * r.re + l.im * r.im) * den_inv,
        (l.im * r.re - l.re * r.im) * den_inv,
    };
}

#if A_DEF_FLOAT == 0
#define A_IMAG_P
#define A_IMAG_C(R, I) \
    {                  \
        R##F, I##F     \
    }
#elif A_DEF_FLOAT == 1
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
 @brief = @f$ \boldsymbol{a} + \boldsymbol{b} @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_imag_nadd(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r);
/*!
 @brief = @f$ \boldsymbol{a} - \boldsymbol{b} @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_imag_nsub(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r);
/*!
 @brief = @f$ \boldsymbol{a} \times \boldsymbol{b} @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_imag_nmul(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r);
/*!
 @brief = @f$ \boldsymbol{a} \div \boldsymbol{b} @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_imag_ndiv(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_IMAG_H__ */
