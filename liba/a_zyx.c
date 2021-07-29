/*!
 @file           a_zyx.c
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

#include "a_zyx.h"

#include <math.h>

void a_zyx_euler_quat(const double e[3], double q[4])
{
    /* Abbreviations for the various angular functions */
    double cy = cos(e[A_ZYX_YAW] * 0.5);
    double sy = sin(e[A_ZYX_YAW] * 0.5);
    double cp = cos(e[A_ZYX_PITCH] * 0.5);
    double sp = sin(e[A_ZYX_PITCH] * 0.5);
    double cr = cos(e[A_ZYX_ROLL] * 0.5);
    double sr = sin(e[A_ZYX_ROLL] * 0.5);

    q[0] = cr * cp * cy + sr * sp * sy;
    q[1] = sr * cp * cy - cr * sp * sy;
    q[2] = cr * sp * cy + sr * cp * sy;
    q[3] = cr * cp * sy - sr * sp * cy;
}

void a_zyx_f32_euler_quat(const float e[3], float q[4])
{
    /* Abbreviations for the various angular functions */
    float cy = cosf(e[A_ZYX_YAW] * 0.5F);
    float sy = sinf(e[A_ZYX_YAW] * 0.5F);
    float cp = cosf(e[A_ZYX_PITCH] * 0.5F);
    float sp = sinf(e[A_ZYX_PITCH] * 0.5F);
    float cr = cosf(e[A_ZYX_ROLL] * 0.5F);
    float sr = sinf(e[A_ZYX_ROLL] * 0.5F);

    q[0] = cr * cp * cy + sr * sp * sy;
    q[1] = sr * cp * cy - cr * sp * sy;
    q[2] = cr * sp * cy + sr * cp * sy;
    q[3] = cr * cp * sy - sr * sp * cy;
}

void a_zyx_quat_euler(const double q[4], double e[3])
{
    /* roll (x-axis rotation) */
    double sinr_cosp = 2 * (q[0] * q[1] + q[2] * q[3]);
    double cosr_cosp = 1 - 2 * (q[1] * q[1] + q[2] * q[2]);

    e[A_ZYX_ROLL] = atan2(sinr_cosp, cosr_cosp);

    /* pitch (y-axis rotation) */
    double sinp = 2 * (q[0] * q[2] - q[3] * q[1]);
    if (fabs(sinp) >= 1)
    {
        /* use 90 degrees if out of range */
        e[A_ZYX_PITCH] = copysign(A_PI / 2, sinp);
    }
    else
    {
        e[A_ZYX_PITCH] = asin(sinp);
    }

    /* yaw (z-axis rotation) */
    double siny_cosp = 2 * (q[0] * q[3] + q[1] * q[2]);
    double cosy_cosp = 1 - 2 * (q[2] * q[2] + q[3] * q[3]);

    e[A_ZYX_YAW] = atan2(siny_cosp, cosy_cosp);
}

void a_zyx_f32_quat_euler(const float q[4], float e[3])
{
    /* roll (x-axis rotation) */
    float sinr_cosp = 2 * (q[0] * q[1] + q[2] * q[3]);
    float cosr_cosp = 1 - 2 * (q[1] * q[1] + q[2] * q[2]);

    e[A_ZYX_ROLL] = atan2f(sinr_cosp, cosr_cosp);

    /* pitch (y-axis rotation) */
    float sinp = 2 * (q[0] * q[2] - q[3] * q[1]);
    if (fabsf(sinp) >= 1)
    {
        /* use 90 degrees if out of range */
        e[A_ZYX_PITCH] = copysignf((float)(A_PI / 2), sinp);
    }
    else
    {
        e[A_ZYX_PITCH] = asinf(sinp);
    }

    /* yaw (z-axis rotation) */
    float siny_cosp = 2 * (q[0] * q[3] + q[1] * q[2]);
    float cosy_cosp = 1 - 2 * (q[2] * q[2] + q[3] * q[3]);

    e[A_ZYX_YAW] = atan2f(siny_cosp, cosy_cosp);
}

/* END OF FILE */
