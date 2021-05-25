/**
 * *****************************************************************************
 * @file         ahrs.c/h
 * @brief        AHRS(Automatic Heading Reference System) algorithm library
 * @details      IMU(Inertial Measurement Unit)
 *               Mehony AHRS
 *               Madgwick AHRS
 * @author       tqfx
 * @date         20210430
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AHRS_H__
#define __AHRS_H__

/* Includes ------------------------------------------------------------------*/
#include "ca.h"

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

/**
 * @brief        Mehony AHRS attitude calculation with magnetometer
 * @param[out]   q[4]: quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 * @param[in]    g[3]: x,y,z axis of gyroscope
 * @param[in]    a[3]: x,y,z axis of accelerometer
 * @param[in]    m[3]: x,y,z axis of magnetometer
 * @param[in]    ht: half of sampling period, unit /s
*/
extern void ahrs_mahony(volatile float q[4],
                        volatile float g[3],
                        volatile float a[3],
                        volatile float m[3],
                        volatile float ht);

/**
 * @brief        Mehony AHRS attitude calculation without magnetometer
 * @param[out]   q[4]: quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 * @param[in]    g[3]: x,y,z axis of gyroscope
 * @param[in]    a[3]: x,y,z axis of accelerometer
 * @param[in]    ht: half of sampling period, unit /s
*/
extern void ahrs_mahony_imu(volatile float q[4],
                            volatile float g[3],
                            volatile float a[3],
                            volatile float ht);

/**
 * @brief        Madgwick AHRS attitude calculation with magnetometer
 * @param[out]   q[4]: quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 * @param[in]    g[3]: x,y,z axis of gyroscope
 * @param[in]    a[3]: x,y,z axis of accelerometer
 * @param[in]    m[3]: x,y,z axis of magnetometer
 * @param[in]    t: sampling period, unit /s
*/
extern void ahrs_madgwick(volatile float q[4],
                          volatile float g[3],
                          volatile float a[3],
                          volatile float m[3],
                          volatile float t);

/**
 * @brief        Madgwick AHRS attitude calculation without magnetometer
 * @param[out]   q[4]: quaternion q[0] + q[1] * i + q[2] * j + q[3] * k
 * @param[in]    g[3]: x,y,z axis of gyroscope
 * @param[in]    a[3]: x,y,z axis of accelerometer
 * @param[in]    t: sampling period, unit /s
*/
extern void ahrs_madgwick_imu(volatile float q[4],
                              volatile float g[3],
                              volatile float a[3],
                              volatile float t);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __AHRS_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
