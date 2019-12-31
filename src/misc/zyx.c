/*!
 @file zyx.c
 @brief yaw (Z), pitch (Y), roll (X)
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/misc/zyx.h"
#include "a/misc/math.h"

#include <assert.h>
#include <math.h>

void a_zyx_euler2quat(const a_real_t e[3], a_real_t q[4])
{
    assert(e);
    assert(q);

    /* Abbreviations for the various angular functions */
    a_real_t cy = A_REAL_F(cos, e[A_ZYX_YAW] * (a_real_t)0.5);
    a_real_t sy = A_REAL_F(sin, e[A_ZYX_YAW] * (a_real_t)0.5);
    a_real_t cp = A_REAL_F(cos, e[A_ZYX_PITCH] * (a_real_t)0.5);
    a_real_t sp = A_REAL_F(sin, e[A_ZYX_PITCH] * (a_real_t)0.5);
    a_real_t cr = A_REAL_F(cos, e[A_ZYX_ROLL] * (a_real_t)0.5);
    a_real_t sr = A_REAL_F(sin, e[A_ZYX_ROLL] * (a_real_t)0.5);

    q[0] = cr * cp * cy + sr * sp * sy;
    q[1] = sr * cp * cy - cr * sp * sy;
    q[2] = cr * sp * cy + sr * cp * sy;
    q[3] = cr * cp * sy - sr * sp * cy;
}

void a_zyx_quat2euler(const a_real_t q[4], a_real_t e[3])
{
    assert(q);
    assert(e);

    /* roll (x-axis rotation) */
    a_real_t sinr_cosp = 2 * (q[0] * q[1] + q[2] * q[3]);
    a_real_t cosr_cosp = 1 - 2 * (q[1] * q[1] + q[2] * q[2]);

    e[A_ZYX_ROLL] = A_REAL_F(atan2, sinr_cosp, cosr_cosp);

    /* pitch (y-axis rotation) */
    a_real_t sinp = 2 * (q[0] * q[2] - q[3] * q[1]);
    if (A_REAL_F(fabs, sinp) >= 1)
    {
        /* use 90 degrees if out of range */
        e[A_ZYX_PITCH] = A_REAL_F(copysign, (a_real_t)A_PI_2, sinp);
    }
    else
    {
        e[A_ZYX_PITCH] = A_REAL_F(asin, sinp);
    }

    /* yaw (z-axis rotation) */
    a_real_t siny_cosp = 2 * (q[0] * q[3] + q[1] * q[2]);
    a_real_t cosy_cosp = 1 - 2 * (q[2] * q[2] + q[3] * q[3]);

    e[A_ZYX_YAW] = A_REAL_F(atan2, siny_cosp, cosy_cosp);
}
