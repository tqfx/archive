/*!
 @file a_zyx.h
 @brief yaw (Z), pitch (Y), roll (X)
 @details where the X-axis points forward, Y-axis to the right and Z-axis downward
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_ZYX_H__
#define __A_ZYX_H__

#include "liba.h"

#undef A_ZYX_YAW
#undef A_ZYX_PITCH
#undef A_ZYX_ROLL
#define A_ZYX_YAW   0 //!< Z (yaw)
#define A_ZYX_PITCH 1 //!< Y (pitch)
#define A_ZYX_ROLL  2 //!< X (roll)

__BEGIN_DECLS

/*!
 @brief euler angles to quaternion conversion by ZYX
 @param[in] e: 0 (yaw), 1 (pitch), 2 (roll), unit /rad
 @param[out] q: 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
*/
extern void a_zyx_euler2quat(const double e[3], double q[4]) __NONNULL_ALL;
extern void a_zyxf_euler2quat(const float e[3], float q[4]) __NONNULL_ALL;

/*!
 @brief quaternion to euler angles conversion by ZYX
 @param[in] q: 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
 @param[out] e: 0 (yaw), 1 (pitch), 2 (roll), unit /rad
*/
extern void a_zyx_quat2euler(const double q[4], double e[3]) __NONNULL_ALL;
extern void a_zyxf_quat2euler(const float q[4], float e[3]) __NONNULL_ALL;

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_ZYX_H__ */

/* END OF FILE */
