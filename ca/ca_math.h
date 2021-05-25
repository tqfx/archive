/**
 * *****************************************************************************
 * @file         ca_math.c/h
 * @brief        Calculate math library
 * @author       tqfx
 * @date         20210430
 * @version      1
 * @copyright    Copyright (c) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CA_MATH_H__
#define __CA_MATH_H__

/* Includes ------------------------------------------------------------------*/
#include "ca.h"

/* Private includes ----------------------------------------------------------*/
#include <float.h>

/* Exported constants --------------------------------------------------------*/

#ifndef M_E
#define M_E 2.7182818284590452354
#endif /* M_E */
#ifndef M_LOG2E
#define M_LOG2E 1.4426950408889634074
#endif /* M_LOG2E */
#ifndef M_LOG10E
#define M_LOG10E 0.43429448190325182765
#endif /* M_LOG10E */
#ifndef M_LN2
#define M_LN2 0.69314718055994530942
#endif /* M_LN2 */
#ifndef M_LN10
#define M_LN10 2.30258509299404568402
#endif /* M_LN10 */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif /* M_PI */
#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif /* M_PI_2 */
#ifndef M_PI_4
#define M_PI_4 0.78539816339744830962
#endif /* M_PI_4 */
#ifndef M_1_PI
#define M_1_PI 0.31830988618379067154
#endif /* M_1_PI */
#ifndef M_2_PI
#define M_2_PI 0.63661977236758134308
#endif /* M_2_PI */
#ifndef M_2_SQRTPI
#define M_2_SQRTPI 1.12837916709551257390
#endif /* M_2_SQRTPI */
#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif /* M_SQRT2 */
#ifndef M_SQRT1_2
#define M_SQRT1_2 0.70710678118654752440
#endif /* M_SQRT1_2 */

/* Exported macro ------------------------------------------------------------*/

#undef ABS
/* The absolute value of x */
#define ABS(x) ((x) < 0 ? -(x) : (x))

#undef SQ
/* The square of the x */
#define SQ(x) ((x) * (x))

#undef LIMIT
/* Limiting macro */
#define LIMIT(x, min, max) ((x) < (min)        \
                                ? (min)        \
                                : ((x) > (max) \
                                       ? (max) \
                                       : (x)))

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @ingroup        CA
 * @defgroup       CA_MATH Calculate math library
*/

__BEGIN_DECLS

/**
 * @brief          Fast inverse square-root, to calculate 1 / sqrtf(x)
 *                 http://en.wikipedia.org/wiki/Fast_inverse_square_root
 * @param[in]      x: Number need to be calculated
 * @return         float 1 / sqrtf(x)
*/
extern float inv_sqrt(float x);

/**
 * @brief          Fast sqrt for unsigned int32
 * @param[in]      x: Number need to be calculated
 * @return         unsigned int sqrt(x)
*/
extern unsigned int ca_sqrt_u32(unsigned int x);

/**
 * @brief          Normalize function
 * @param[in]      n: Number of variables
 * @param[in,out]  ...: Pointer of variables
*/
extern void ca_normalize(unsigned int n, ...);

/**
 * @brief          Normalize function for the floating-point
 * @param[in]      n: Number of variables
 * @param[in,out]  ...: Pointer of variables
*/
extern void ca_normalize_f32(unsigned int n, ...);

/**
 * @brief          Restricted periodic function
 * @param[in]      x: Input
 * @param[in]      min: Minimum
 * @param[in]      max: Minimum
 * @return         double Output
*/
extern double restrict_loop(double x,
                            double min,
                            double max);

/**
 * @brief          Restricted periodic function for the floating-point
 * @param[in]      x: Input
 * @param[in]      min: Minimum
 * @param[in]      max: Minimum
 * @return         float
*/
extern float restrict_loop_f32(float x,
                               float min,
                               float max);

__END_DECLS

/* Private defines -----------------------------------------------------------*/

#define restrict_angle(x)     restrict_loop((x), -180, 180)
#define restrict_angle_f32(x) restrict_loop_f32((x), -180, 180)
#define restrict_rad(x)       restrict_loop((x), -M_PI, M_PI)
#define restrict_rad_f32(x)   restrict_loop_f32((x), -M_PI, M_PI)

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __CA_MATH_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
