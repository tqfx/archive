/**
 * *****************************************************************************
 * @file         zyx.c/h
 * @brief        yaw (Z), pitch (Y), roll (X)
 * @details      where the X-axis points forward,
 *               Y-axis to the right and Z-axis downward
 * @author       tqfx
 * @date         20210430
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ZYX_H__
#define __ZYX_H__

/* Includes ------------------------------------------------------------------*/
#include "ca.h"

/* Exported constants --------------------------------------------------------*/

#undef ZYX_YAW
#undef ZYX_PITCH
#undef ZYX_ROLL
#define ZYX_YAW   0U /* Z (yaw) */
#define ZYX_PITCH 1U /* Y (pitch) */
#define ZYX_ROLL  2U /* X (roll) */

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

/**
 * @brief        euler angles to quaternion conversion by ZYX
 * @param[in]    e[3]: 0 (yaw), 1 (pitch), 2 (roll), unit /rad
 * @param[out]   q[4]: 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
*/
extern void zyx_euler_quat(const double e[3], double q[4]);

/**
 * @brief        euler angles to quaternion conversion by ZYX
 * @param[in]    e[3]: 0 (yaw), 1 (pitch), 2 (roll), unit /rad
 * @param[out]   q[4]: 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
*/
extern void zyx_f32_euler_quat(const float e[3], float q[4]);

/**
 * @brief        quaternion to euler angles conversion by ZYX
 * @param[in]    q[4]: 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
 * @param[out]   e[3]: 0 (yaw), 1 (pitch), 2 (roll), unit /rad
*/
extern void zyx_quat_euler(const double q[4], double e[3]);

/**
 * @brief        quaternion to euler angles conversion by ZYX
 * @param[in]    q[4]: 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
 * @param[out]   e[3]: 0 (yaw), 1 (pitch), 2 (roll), unit /rad
*/
extern void zyx_f32_quat_euler(const float q[4], float e[3]);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __ZYX_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
