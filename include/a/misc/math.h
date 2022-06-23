/*!
 @file math.h
 @brief Calculate math library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_MATH_H__
#define __A_MATH_H__

#include "../def.h"

#include <float.h>

#define A_DBL_C(x)  (x)
#define A_FLT_C(x)  (x##F)
#define A_LDBL_C(x) (x##L)

#define A_DBL_F(func, ...)  func(__VA_ARGS__)
#define A_FLT_F(func, ...)  func##f(__VA_ARGS__)
#define A_LDBL_F(func, ...) func##l(__VA_ARGS__)

#define A_E        2.71828182845904523536  //!< e
#define A_LOG2E    1.44269504088896340736  //!< log2(e)
#define A_LOG10E   0.434294481903251827651 //!< log10(e)
#define A_LN2      0.693147180559945309417 //!< ln(2)
#define A_LN10     2.30258509299404568402  //!< ln(10)
#define A_PI       3.14159265358979323846  //!< pi
#define A_PI_2     1.57079632679489661923  //!< pi/2
#define A_PI_4     0.785398163397448309616 //!< pi/4
#define A_1_PI     0.318309886183790671538 //!< 1/pi
#define A_2_PI     0.636619772367581343076 //!< 2/pi
#define A_2_SQRTPI 1.12837916709551257390  //!< 2/sqrt(pi)
#define A_SQRT2    1.41421356237309504880  //!< sqrt(2)
#define A_SQRT1_2  0.707106781186547524401 //!< 1/sqrt(2)

#define A_SQ(x) ((x) * (x))

#define A_ABS(x) ((x) < 0 ? -(x) : (x))

#define A_LIMIT(x, min, max) ((min) < (x) ? ((x) < (max) ? (x) : (max)) : (min))

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief fast inverse square-root, to calculate @f$ \frac{1}{\sqrt{x}} @f$
 @details http://en.wikipedia.org/wiki/Fast_inverse_square_root
*/
A_PUBLIC float a_sqrt_inv(float x);

/*!
 @brief fast sqrt for unsigned integer
*/
A_PUBLIC uint32_t a_sqrt_u32(uint32_t x);
A_PUBLIC uint64_t a_sqrt_u64(uint64_t x);

/*!
 @brief Normalize function for the floating-point
 @param[in] num number of variables
 @param[in,out] ... address of variables
*/
A_PUBLIC void a_normalizevf(unsigned int num, ...);
A_PUBLIC void a_normalizef(float *dat, size_t num);

/*!
 @brief restricted periodic function
*/
A_PUBLIC double a_restrict_loop(double x, double min, double max);
A_PUBLIC float a_restrict_loopf(float x, float min, float max);
#define a_restrict_angle(x)  a_restrict_loop(x, -180, 180)
#define a_restrict_anglef(x) a_restrict_loopf(x, -180, 180)
#define a_restrict_rad(x)    a_restrict_loop(x, -A_PI, A_PI)
#define a_restrict_radf(x)   a_restrict_loopf(x, -(float)A_PI, (float)A_PI)

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_MATH_H__ */
