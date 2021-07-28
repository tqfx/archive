/*!
 @file           a_zyx.h
 @brief          yaw (Z), pitch (Y), roll (X)
 @details        where the X-axis points forward,
                 Y-axis to the right and Z-axis downward
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2021 tqfx
 \n \n
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 \n \n
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 \n \n
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_ZYX_H__
#define __A_ZYX_H__

#include "liba.h"

/*!
 @ingroup        LIBA
 @defgroup       LIBA_ZYX zyx axis
 @{
*/

#undef ZYX_YAW
#undef ZYX_PITCH
#undef ZYX_ROLL
#define ZYX_YAW   0U  //!< Z (yaw)
#define ZYX_PITCH 1U  //!< Y (pitch)
#define ZYX_ROLL  2U  //!< X (roll)

__BEGIN_DECLS

/*!
 @brief        euler angles to quaternion conversion by ZYX
 @param[in]    e: 0 (yaw), 1 (pitch), 2 (roll), unit /rad
 @param[out]   q: 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
*/
extern void zyx_euler_quat(const double e[3],
                           double q[4]);

/*!
 @brief        euler angles to quaternion conversion by ZYX
 @param[in]    e: 0 (yaw), 1 (pitch), 2 (roll), unit /rad
 @param[out]   q: 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
*/
extern void zyx_f32_euler_quat(const float e[3],
                               float q[4]);

/*!
 @brief        quaternion to euler angles conversion by ZYX
 @param[in]    q: 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
 @param[out]   e: 0 (yaw), 1 (pitch), 2 (roll), unit /rad
*/
extern void zyx_quat_euler(const double q[4],
                           double e[3]);

/*!
 @brief        quaternion to euler angles conversion by ZYX
 @param[in]    q: 0 (w q0), 1 (x q1), 2 (y q2), 3 (z q3)
 @param[out]   e: 0 (yaw), 1 (pitch), 2 (roll), unit /rad
*/
extern void zyx_f32_quat_euler(const float q[4],
                               float e[3]);

__END_DECLS

/*! @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_ZYX_H__ */

/* END OF FILE */
