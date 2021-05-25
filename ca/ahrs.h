/*!
 @file           zyx.h
 @brief          AHRS(Automatic Heading Reference System) algorithm library
 @details        IMU(Inertial Measurement Unit)
                 Mehony AHRS
                 Madgwick AHRS
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-05-25
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
#ifndef __AHRS_H__
#define __AHRS_H__

/* Includes */
#include "ca.h"

/* Exported functions prototypes */

__BEGIN_DECLS

/**
 @brief        Mehony AHRS attitude calculation with magnetometer
 @param[out]   q: quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 @param[in]    g: x,y,z axis of gyroscope
 @param[in]    a: x,y,z axis of accelerometer
 @param[in]    m: x,y,z axis of magnetometer
 @param[in]    ht: half of sampling period, unit /s
*/
extern void ahrs_mahony(volatile float q[4],
                        volatile float g[3],
                        volatile float a[3],
                        volatile float m[3],
                        volatile float ht);

/**
 @brief        Mehony AHRS attitude calculation without magnetometer
 @param[out]   q: quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 @param[in]    g: x,y,z axis of gyroscope
 @param[in]    a: x,y,z axis of accelerometer
 @param[in]    ht: half of sampling period, unit /s
*/
extern void ahrs_mahony_imu(volatile float q[4],
                            volatile float g[3],
                            volatile float a[3],
                            volatile float ht);

/**
 @brief        Madgwick AHRS attitude calculation with magnetometer
 @param[out]   q: quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 @param[in]    g: x,y,z axis of gyroscope
 @param[in]    a: x,y,z axis of accelerometer
 @param[in]    m: x,y,z axis of magnetometer
 @param[in]    t: sampling period, unit /s
*/
extern void ahrs_madgwick(volatile float q[4],
                          volatile float g[3],
                          volatile float a[3],
                          volatile float m[3],
                          volatile float t);

/**
 @brief        Madgwick AHRS attitude calculation without magnetometer
 @param[out]   q: quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 @param[in]    g: x,y,z axis of gyroscope
 @param[in]    a: x,y,z axis of accelerometer
 @param[in]    t: sampling period, unit /s
*/
extern void ahrs_madgwick_imu(volatile float q[4],
                              volatile float g[3],
                              volatile float a[3],
                              volatile float t);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __AHRS_H__ */

/* END OF FILE */
