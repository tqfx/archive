/*!
 @file zyx.h
 @brief yaw (Z), pitch (Y), roll (X)
 @details where the X-axis points forward, Y-axis to the right and Z-axis downward
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_ZYX_H__
#define __A_ZYX_H__

#include "../real.h"

#define A_ZYX_YAW   0 //!< Z (yaw)
#define A_ZYX_PITCH 1 //!< Y (pitch)
#define A_ZYX_ROLL  2 //!< X (roll)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief euler angles to quaternion conversion by ZYX
 @param[in] e 0 (yaw), 1 (pitch), 2 (roll), unit /rad
 @param[out] q 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
*/
A_PUBLIC void a_zyx_euler2quat(const a_real_t e[3], a_real_t q[4]);

/*!
 @brief quaternion to euler angles conversion by ZYX
 @param[in] q 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
 @param[out] e 0 (yaw), 1 (pitch), 2 (roll), unit /rad
*/
A_PUBLIC void a_zyx_quat2euler(const a_real_t q[4], a_real_t e[3]);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_ZYX_H__ */
