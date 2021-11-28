/*!
 @file a_zyx.c
 @brief yaw (Z), pitch (Y), roll (X)
 @details where the X-axis points forward, Y-axis to the right and Z-axis downward
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_zyx.h"

#include "a_math.h"

#include <math.h>

#undef a_zyx_euler2quat
void a_zyx_euler2quat(const double _e[3], double _q[4])
{
    aassert(_e);
    aassert(_q);

    /* Abbreviations for the various angular functions */
    double cy = cos(_e[A_ZYX_YAW] * 0.5);
    double sy = sin(_e[A_ZYX_YAW] * 0.5);
    double cp = cos(_e[A_ZYX_PITCH] * 0.5);
    double sp = sin(_e[A_ZYX_PITCH] * 0.5);
    double cr = cos(_e[A_ZYX_ROLL] * 0.5);
    double sr = sin(_e[A_ZYX_ROLL] * 0.5);

    _q[0] = cr * cp * cy + sr * sp * sy;
    _q[1] = sr * cp * cy - cr * sp * sy;
    _q[2] = cr * sp * cy + sr * cp * sy;
    _q[3] = cr * cp * sy - sr * sp * cy;
}

void a_zyxf_euler2quat(const float _e[3], float _q[4])
{
    aassert(_e);
    aassert(_q);

    /* Abbreviations for the various angular functions */
    float cy = cosf(_e[A_ZYX_YAW] * 0.5F);
    float sy = sinf(_e[A_ZYX_YAW] * 0.5F);
    float cp = cosf(_e[A_ZYX_PITCH] * 0.5F);
    float sp = sinf(_e[A_ZYX_PITCH] * 0.5F);
    float cr = cosf(_e[A_ZYX_ROLL] * 0.5F);
    float sr = sinf(_e[A_ZYX_ROLL] * 0.5F);

    _q[0] = cr * cp * cy + sr * sp * sy;
    _q[1] = sr * cp * cy - cr * sp * sy;
    _q[2] = cr * sp * cy + sr * cp * sy;
    _q[3] = cr * cp * sy - sr * sp * cy;
}

#undef a_zyx_quat2euler
void a_zyx_quat2euler(const double _q[4], double _e[3])
{
    aassert(_q);
    aassert(_e);

    /* roll (x-axis rotation) */
    double sinr_cosp = 2 * (_q[0] * _q[1] + _q[2] * _q[3]);
    double cosr_cosp = 1 - 2 * (_q[1] * _q[1] + _q[2] * _q[2]);

    _e[A_ZYX_ROLL] = atan2(sinr_cosp, cosr_cosp);

    /* pitch (y-axis rotation) */
    double sinp = 2 * (_q[0] * _q[2] - _q[3] * _q[1]);
    if (fabs(sinp) >= 1)
    {
        /* use 90 degrees if out of range */
        _e[A_ZYX_PITCH] = copysign(A_PI / 2, sinp);
    }
    else
    {
        _e[A_ZYX_PITCH] = asin(sinp);
    }

    /* yaw (z-axis rotation) */
    double siny_cosp = 2 * (_q[0] * _q[3] + _q[1] * _q[2]);
    double cosy_cosp = 1 - 2 * (_q[2] * _q[2] + _q[3] * _q[3]);

    _e[A_ZYX_YAW] = atan2(siny_cosp, cosy_cosp);
}

void a_zyxf_quat2euler(const float _q[4], float _e[3])
{
    aassert(_q);
    aassert(_e);

    /* roll (x-axis rotation) */
    float sinr_cosp = 2 * (_q[0] * _q[1] + _q[2] * _q[3]);
    float cosr_cosp = 1 - 2 * (_q[1] * _q[1] + _q[2] * _q[2]);

    _e[A_ZYX_ROLL] = atan2f(sinr_cosp, cosr_cosp);

    /* pitch (y-axis rotation) */
    float sinp = 2 * (_q[0] * _q[2] - _q[3] * _q[1]);
    if (fabsf(sinp) >= 1)
    {
        /* use 90 degrees if out of range */
        _e[A_ZYX_PITCH] = copysignf((float)(A_PI / 2), sinp);
    }
    else
    {
        _e[A_ZYX_PITCH] = asinf(sinp);
    }

    /* yaw (z-axis rotation) */
    float siny_cosp = 2 * (_q[0] * _q[3] + _q[1] * _q[2]);
    float cosy_cosp = 1 - 2 * (_q[2] * _q[2] + _q[3] * _q[3]);

    _e[A_ZYX_YAW] = atan2f(siny_cosp, cosy_cosp);
}

/* END OF FILE */
