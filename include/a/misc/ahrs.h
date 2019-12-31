/*!
 @file ahrs.h
 @brief AHRS(Automatic Heading Reference System) algorithm library
 @details IMU(Inertial Measurement Unit)
 - Mehony AHRS
 - Madgwick AHRS
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_AHRS_H__
#define __A_AHRS_H__

#include "../def.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief Mehony AHRS attitude calculation with magnetometer
 @param[out] q quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 @param[in] g x,y,z axis of gyroscope
 @param[in] a x,y,z axis of accelerometer
 @param[in] m x,y,z axis of magnetometer
 @param[in] ht half of sampling period, unit /s
*/
A_PUBLIC void a_ahrs_mahony(float q[4], float g[3], float a[3], float m[3], float ht);

/*!
 @brief Mehony AHRS attitude calculation without magnetometer
 @param[out] q quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 @param[in] g x,y,z axis of gyroscope
 @param[in] a x,y,z axis of accelerometer
 @param[in] ht half of sampling period, unit /s
*/
A_PUBLIC void a_ahrs_mahony_imu(float q[4], float g[3], float a[3], float ht);

/*!
 @brief Madgwick AHRS attitude calculation with magnetometer
 @param[out] q quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 @param[in] g x,y,z axis of gyroscope
 @param[in] a x,y,z axis of accelerometer
 @param[in] m x,y,z axis of magnetometer
 @param[in] t sampling period, unit /s
*/
A_PUBLIC void a_ahrs_madgwick(float q[4], float g[3], float a[3], float m[3], float t);

/*!
 @brief Madgwick AHRS attitude calculation without magnetometer
 @param[out] q quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 @param[in] g x,y,z axis of gyroscope
 @param[in] a x,y,z axis of accelerometer
 @param[in] t sampling period, unit /s
*/
A_PUBLIC void a_ahrs_madgwick_imu(float q[4], float g[3], float a[3], float t);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_AHRS_H__ */
