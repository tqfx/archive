/*!
 @file math.h
 @brief mathematical algorithm library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef A_MATH_H
#define A_MATH_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_MATH mathematical algorithm library
 @{
*/

/*! \f$ e \f$ */
#define A_E 2.71828182845904523536
/*! \f$ \log_{2}{e}=\frac{1}{\ln{2}} \f$ */
#define A_LOG2E 1.44269504088896340736
/*! \f$ \lg{e}=\frac{1}{\ln{2}+\ln{5}} \f$ */
#define A_LOG10E 0.434294481903251827651
/*! \f$ \ln{2} \f$ */
#define A_LN2 0.693147180559945309417
/*! \f$ \ln{10} \f$ */
#define A_LN10 2.30258509299404568402
/*! \f$ \pi \f$ */
#define A_PI 3.14159265358979323846
/*! \f$ \frac{\pi}{2} \f$ */
#define A_PI_2 1.57079632679489661923
/*! \f$ \frac{\pi}{4} \f$ */
#define A_PI_4 0.785398163397448309616
/*! \f$ \frac{1}{\pi} \f$ */
#define A_1_PI 0.318309886183790671538
/*! \f$ \frac{2}{\pi} \f$ */
#define A_2_PI 0.636619772367581343076
/*! \f$ \frac{2}{\sqrt{\pi}} \f$ */
#define A_2_SQRTPI 1.12837916709551257390
/*! \f$ \sqrt{2} \f$ */
#define A_SQRT2 1.41421356237309504880
/*! \f$ \frac{1}{\sqrt{2}}=\frac{\sqrt{2}}{2} \f$ */
#define A_SQRT1_2 0.707106781186547524401

/*!
 @brief square of x, \f$ x^2 \f$
*/
#define A_SQ(x) ((x) * (x))

/*!
 @brief absolute value of x, \f$ |x| \f$
*/
#define A_ABS(x) ((x) < 0 ? -(x) : (x))

/*!
 @brief signum function, \f$ \texttt{sgn}{x}=\begin{cases}+1&x>0\\0&0\\-1&x<0\end{cases} \f$
*/
#define A_SGN(x) ((0 < (x)) - ((x) < 0))

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief fast inverse square-root, \f$ \frac{1}{\sqrt{x}} \f$
 @details http://en.wikipedia.org/wiki/Fast_inverse_square_root
 @param[in] x independent variable
 @return calculated result
*/
A_PUBLIC a_f32_t a_sqrt_inv(a_f32_t x);
A_PUBLIC a_u32_t a_u32_sqrt(a_u32_t x);
A_PUBLIC a_u64_t a_u64_sqrt(a_u64_t x);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_MATH */

#endif /* A_MATH_H */
