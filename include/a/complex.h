/*!
 @file complex.h
 @brief complex number
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef A_COMPLEX_H
#define A_COMPLEX_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_COMPLEX complex number
 @{
*/

#define A_COMPLEX_PRI(RF, RC, IF, IC) \
    "(" A_REAL_PRI(RF, RC) "," A_REAL_PRI(IF, IC) ")"

#if defined(__cplusplus)
#define a_complex_c(r, i)                            \
    {                                                \
        a_cast_s(a_real_t, r), a_cast_s(a_real_t, i) \
    }
#else /* !__cplusplus */
#define a_complex_c(r, i)            \
    (a_complex_s)                    \
    {                                \
        (a_real_t)(r), (a_real_t)(i) \
    }
#endif /* __cplusplus */

#if defined(__cplusplus)
#define A_COMPLEX_C(R, I)        \
    {                            \
        A_REAL_C(R), A_REAL_C(I) \
    }
#else /* !__cplusplus */
#define A_COMPLEX_C(R, I)        \
    (a_complex_s)                \
    {                            \
        A_REAL_C(R), A_REAL_C(I) \
    }
#endif /* __cplusplus */

#define a_complex_real(z) (z).real
#define a_complex_imag(z) (z).imag

/*!
 @brief instance structure for complex number
*/
typedef struct a_complex_s
{
    a_real_t real;
    a_real_t imag;
} a_complex_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief = \f[ (r\cos\theta,ir\sin\theta) \f] from polar form
 @param r a distance from a reference point
 @param theta an angle from a reference direction
 @return complex number
*/
A_PUBLIC a_complex_s a_complex_polar(a_real_t r, a_real_t theta);

/*!
 @brief = \f[ (-a-b i) \f]
 @param z complex number
 @return negative value
*/
A_PUBLIC a_complex_s a_complex_neg(a_complex_s z);

/*!
 @brief = \f[ (a-b i) \f]
 @param z complex number
 @return conjugate value
*/
A_PUBLIC a_complex_s a_complex_conj(a_complex_s z);

/*!
 @brief = \f[ a^2+b^2 \f]
 @param z complex number
 @return squared magnitude
*/
A_PUBLIC a_real_t a_complex_abs2(a_complex_s z);

/*!
 @brief = \f[ \sqrt{a^2+b^2} \f]
 @param z complex number
 @return absolute value
*/
A_PUBLIC a_real_t a_complex_abs(a_complex_s z);

/*!
 @brief = \f[ \arctan\frac{b}{a} \f]
 @param z complex number
 @return argument value
*/
A_PUBLIC a_real_t a_complex_arg(a_complex_s z);

/*!
 @brief = \f[ \frac{a-bi}{a^2+b^2}=\left(\frac{a}{a^2+b^2}\right)-\left(\frac{b}{a^2+b^2}\right)i \f]
 @param z complex number
 @return inverse or reciprocal
*/
A_PUBLIC a_complex_s a_complex_inv(a_complex_s z);

/*!
 @brief = \f[ (a+b i)+(c+d i)=(a+c)+(b+d)i \f]
 @param x complex number on the left
 @param y complex number on the right
 @return result after calculation
*/
A_PUBLIC a_complex_s a_complex_add(a_complex_s x, a_complex_s y);
A_PUBLIC a_complex_s a_complex_add_real(a_complex_s x, a_real_t y);
A_PUBLIC a_complex_s a_complex_add_imag(a_complex_s x, a_real_t y);

/*!
 @brief = \f[ (a+b i)-(c+d i)=(a-c)+(b-d)i \f]
 @param x complex number on the left
 @param y complex number on the right
 @return result after calculation
*/
A_PUBLIC a_complex_s a_complex_sub(a_complex_s x, a_complex_s y);
A_PUBLIC a_complex_s a_complex_sub_real(a_complex_s x, a_real_t y);
A_PUBLIC a_complex_s a_complex_sub_imag(a_complex_s x, a_real_t y);

/*!
 @brief = \f[ (a+b i)(c+d i)=a c+b c i+a d i+b d i^{2}=(a c-b d)+(b c+a d) i \f]
 @param x complex number on the left
 @param y complex number on the right
 @return result after calculation
*/
A_PUBLIC a_complex_s a_complex_mul(a_complex_s x, a_complex_s y);
A_PUBLIC a_complex_s a_complex_mul_real(a_complex_s x, a_real_t y);
A_PUBLIC a_complex_s a_complex_mul_imag(a_complex_s x, a_real_t y);

/*!
 @brief = \f[ \frac{(a+b i)}{(c+d i)}=\frac{(a+b i)(c-d i)}{(c+d i)(c-d i)}=\frac{a c+b c i-a d i-b d i^{2}}{c^{2}-(d i)^{2}}=\frac{(a c+b d)+(b c-a d) i}{c^{2}+d^{2}}=\left(\frac{a c+b d}{c^{2}+d^{2}}\right)+\left(\frac{b c-a d}{c^{2}+d^{2}}\right) i \f]
 @param x complex number on the left
 @param y complex number on the right
 @return result after calculation
*/
A_PUBLIC a_complex_s a_complex_div(a_complex_s x, a_complex_s y);
A_PUBLIC a_complex_s a_complex_div_real(a_complex_s x, a_real_t y);
A_PUBLIC a_complex_s a_complex_div_imag(a_complex_s x, a_real_t y);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_COMPLEX */

#endif /* A_COMPLEX_H */
