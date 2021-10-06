/*!
 @file           a_math.h
 @brief          Calculate math library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_MATH_H__
#define __A_MATH_H__

#include "liba.h"

#include <float.h>

/*!
 @ingroup        LIBA
 @defgroup       LIBA_MATH math library
 @{
*/

#ifndef A_E
#define A_E 2.7182818284590452354
#endif /* A_E */
#ifndef A_LOG2E
#define A_LOG2E 1.4426950408889634074
#endif /* A_LOG2E */
#ifndef A_LOG10E
#define A_LOG10E 0.43429448190325182765
#endif /* A_LOG10E */
#ifndef A_LN2
#define A_LN2 0.69314718055994530942
#endif /* A_LN2 */
#ifndef A_LN10
#define A_LN10 2.30258509299404568402
#endif /* A_LN10 */
#ifndef A_PI
#define A_PI 3.14159265358979323846
#endif /* A_PI */
#ifndef A_PI_2
#define A_PI_2 1.57079632679489661923
#endif /* A_PI_2 */
#ifndef A_PI_4
#define A_PI_4 0.78539816339744830962
#endif /* A_PI_4 */
#ifndef A_1_PI
#define A_1_PI 0.31830988618379067154
#endif /* A_1_PI */
#ifndef A_2_PI
#define A_2_PI 0.63661977236758134308
#endif /* A_2_PI */
#ifndef A_2_SQRTPI
#define A_2_SQRTPI 1.12837916709551257390
#endif /* A_2_SQRTPI */
#ifndef A_SQRT2
#define A_SQRT2 1.41421356237309504880
#endif /* A_SQRT2 */
#ifndef A_SQRT1_2
#define A_SQRT1_2 0.70710678118654752440
#endif /* A_SQRT1_2 */

#undef A_ABS
#define A_ABS(x) ((x) < 0 ? -(x) : (x))

#undef A_SQ
#define A_SQ(x) ((x) * (x))

#undef A_LIMIT
#define A_LIMIT(x, min, max) \
    ((min) < (x)             \
         ? ((x) < (max)      \
                ? (x)        \
                : (max))     \
         : (min))

__BEGIN_DECLS

/*!
 @brief          Fast inverse square-root, to calculate 1 / sqrtf(x)
 @details        http://en.wikipedia.org/wiki/Fast_inverse_square_root
 @param[in]      x: Number need to be calculated
 @return         1 / sqrtf(x)
*/
extern float a_inv_sqrt(float x);

/*!
 @brief          Fast sqrt for unsigned uint32
 @param[in]      x: Number need to be calculated
 @return         sqrt(x)
*/
extern unsigned long a_sqrt_u32(unsigned long x);

/*!
 @brief          Fast sqrt for unsigned uint64
 @param[in]      x: Number need to be calculated
 @return         sqrt(x)
*/
extern unsigned long long a_sqrt_u64(unsigned long long x);

/*!
 @brief          Normalize function for the floating-point
 @param[in]      n: Number of variables
 @param[in,out]  ...: Pointer of variables
*/
extern void a_normalize_f32(unsigned int n, ...);

/*!
 @brief          Restricted periodic function
 @param[in]      x: Input
 @param[in]      min: Minimum
 @param[in]      max: Minimum
 @return         Output
*/
extern double a_restrict_loop(double x,
                              double min,
                              double max);

/*!
 @brief          Restricted periodic function for the floating-point
 @param[in]      x: Input
 @param[in]      min: Minimum
 @param[in]      max: Minimum
 @return         Output
*/
extern float a_restrict_loop_f32(float x,
                                 float min,
                                 float max);

__END_DECLS

#define a_restrict_angle(x)     a_restrict_loop((x), -180, 180)
#define a_restrict_angle_f32(x) a_restrict_loop_f32((x), -180, 180)
#define a_restrict_rad(x)       a_restrict_loop((x), -A_PI, A_PI)
#define a_restrict_rad_f32(x)   a_restrict_loop_f32((x), -(float)A_PI, (float)A_PI)

/*!
 @}              End of LIBA_MATH group
*/

/* Enddef to prevent recursive inclusion */
#endif /* __A_MATH_H__ */

/* END OF FILE */
