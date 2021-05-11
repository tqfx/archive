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

/* Includes ------------------------------------------------------------------*/
#include "zyx.h"

/* Private includes ----------------------------------------------------------*/
#include <math.h>

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

void zyx_euler_quat(const double e[3], double q[4])
{
    /* Abbreviations for the various angular functions */
    double cy = cos(e[0] * 0.5);
    double sy = sin(e[0] * 0.5);
    double cp = cos(e[1] * 0.5);
    double sp = sin(e[1] * 0.5);
    double cr = cos(e[2] * 0.5);
    double sr = sin(e[2] * 0.5);

    q[0] = cr * cp * cy + sr * sp * sy;
    q[1] = sr * cp * cy - cr * sp * sy;
    q[2] = cr * sp * cy + sr * cp * sy;
    q[3] = cr * cp * sy - sr * sp * cy;
}

void zyx_f32_euler_quat(const float e[3], float q[4])
{
    /* Abbreviations for the various angular functions */
    float cy = cos(e[0] * 0.5F);
    float sy = sin(e[0] * 0.5F);
    float cp = cos(e[1] * 0.5F);
    float sp = sin(e[1] * 0.5F);
    float cr = cos(e[2] * 0.5F);
    float sr = sin(e[2] * 0.5F);

    q[0] = cr * cp * cy + sr * sp * sy;
    q[1] = sr * cp * cy - cr * sp * sy;
    q[2] = cr * sp * cy + sr * cp * sy;
    q[3] = cr * cp * sy - sr * sp * cy;
}

void zyx_quat_euler(const double q[4], double e[3])
{
    /* roll (x-axis rotation) */
    double sinr_cosp = 2 * (q[0] * q[1] + q[2] * q[3]);
    double cosr_cosp = 1 - 2 * (q[1] * q[1] + q[2] * q[2]);

    e[2] = atan2(sinr_cosp, cosr_cosp);

    /* pitch (y-axis rotation) */
    double sinp = 2 * (q[0] * q[2] - q[3] * q[1]);
    if (fabs(sinp) >= 1)
    {
        /* use 90 degrees if out of range */
        e[1] = copysign(M_PI / 2, sinp);
    }
    else
    {
        e[1] = asin(sinp);
    }

    /* yaw (z-axis rotation) */
    double siny_cosp = 2 * (q[0] * q[3] + q[1] * q[2]);
    double cosy_cosp = 1 - 2 * (q[2] * q[2] + q[3] * q[3]);

    e[0] = atan2(siny_cosp, cosy_cosp);
}

void zyx_f32_quat_euler(const float q[4], float e[3])
{
    /* roll (x-axis rotation) */
    float sinr_cosp = 2 * (q[0] * q[1] + q[2] * q[3]);
    float cosr_cosp = 1 - 2 * (q[1] * q[1] + q[2] * q[2]);

    e[2] = atan2f(sinr_cosp, cosr_cosp);

    /* pitch (y-axis rotation) */
    float sinp = 2 * (q[0] * q[2] - q[3] * q[1]);
    if (fabs(sinp) >= 1)
    {
        /* use 90 degrees if out of range */
        e[1] = copysignf(M_PI / 2, sinp);
    }
    else
    {
        e[1] = asinf(sinp);
    }

    /* yaw (z-axis rotation) */
    double siny_cosp = 2 * (q[0] * q[3] + q[1] * q[2]);
    double cosy_cosp = 1 - 2 * (q[2] * q[2] + q[3] * q[3]);

    e[0] = atan2f(siny_cosp, cosy_cosp);
}

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
