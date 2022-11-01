/*!
 @file real.h
 @brief real number
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef A_REAL_H
#define A_REAL_H

#include "a.h"
#include "math.h"

/*!
 @ingroup A
 @addtogroup A_REAL real number
 @{
*/

/*! \f$ e \f$ */
#define A_REAL_E A_REAL_C(2.71828182845904523536)
/*! \f$ \log_{2}{e}=\frac{1}{\ln{2}} \f$ */
#define A_REAL_LOG2E A_REAL_C(1.44269504088896340736)
/*! \f$ \lg{e}=\frac{1}{\ln{2}+\ln{5}} \f$ */
#define A_REAL_LOG10E A_REAL_C(0.434294481903251827651)
/*! \f$ \ln{2} \f$ */
#define A_REAL_LN2 A_REAL_C(0.693147180559945309417)
/*! \f$ \ln{10} \f$ */
#define A_REAL_LN10 A_REAL_C(2.30258509299404568402)
/*! \f$ \pi \f$ */
#define A_REAL_PI A_REAL_C(3.14159265358979323846)
/*! \f$ \frac{\pi}{2} \f$ */
#define A_REAL_PI_2 A_REAL_C(1.57079632679489661923)
/*! \f$ \frac{\pi}{4} \f$ */
#define A_REAL_PI_4 A_REAL_C(0.785398163397448309616)
/*! \f$ \frac{1}{\pi} \f$ */
#define A_REAL_1_PI A_REAL_C(0.318309886183790671538)
/*! \f$ \frac{2}{\pi} \f$ */
#define A_REAL_2_PI A_REAL_C(0.636619772367581343076)
/*! \f$ \frac{2}{\sqrt{\pi}} \f$ */
#define A_REAL_2_SQRTPI A_REAL_C(1.12837916709551257390)
/*! \f$ \sqrt{2} \f$ */
#define A_REAL_SQRT2 A_REAL_C(1.41421356237309504880)
/*! \f$ \frac{1}{\sqrt{2}}=\frac{\sqrt{2}}{2} \f$ */
#define A_REAL_SQRT1_2 A_REAL_C(0.707106781186547524401)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC a_real_t a_real_log1p(a_real_t x);
A_PUBLIC a_real_t a_real_hypot(a_real_t x, a_real_t y);
A_PUBLIC a_real_t a_real_atan2(a_real_t x, a_real_t y);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define a_real_abs(x) A_REAL_F(fabs, x)
#define a_real_exp(x) A_REAL_F(exp, x)
#define a_real_log(x) A_REAL_F(log, x)
#define a_real_pow(x, y) A_REAL_F(pow, x, y)
#define a_real_sqrt(x) A_REAL_F(sqrt, x)

#if defined(A_HAVE_LOG1P)
#define a_real_log1p(x) A_REAL_F(log1p, x)
#endif /* A_HAVE_LOG1P */
#if defined(A_HAVE_HYPOT)
#define a_real_hypot(x, y) A_REAL_F(hypot, x, y)
#endif /* A_HAVE_HYPOT */
#if defined(A_HAVE_ATAN2)
#define a_real_atan2(x, y) A_REAL_F(atan2, x, y)
#endif /* A_HAVE_ATAN2 */

#define a_real_sin(x) A_REAL_F(sin, x)
#define a_real_cos(x) A_REAL_F(cos, x)
#define a_real_tan(x) A_REAL_F(tan, x)
#define a_real_sinh(x) A_REAL_F(sin, x)
#define a_real_cosh(x) A_REAL_F(cos, x)
#define a_real_tanh(x) A_REAL_F(tan, x)
#define a_real_asin(x) A_REAL_F(sin, x)
#define a_real_acos(x) A_REAL_F(cos, x)
#define a_real_atan(x) A_REAL_F(tan, x)
#define a_real_asinh(x) A_REAL_F(sin, x)
#define a_real_acosh(x) A_REAL_F(cos, x)
#define a_real_atanh(x) A_REAL_F(tan, x)

/*! @} A_REAL */

#endif /* A_REAL_H */
