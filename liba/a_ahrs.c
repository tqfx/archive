/*!
 @file           a_ahrs.c
 @brief          AHRS(Automatic Heading Reference System) algorithm library
 @details        IMU(Inertial Measurement Unit)
                 Mehony AHRS
                 Madgwick AHRS
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_ahrs.h"

#include "a_math.h"

#include <math.h>

#undef KP
#undef KI
#undef KP2

/*!
 Proportional gain governs rate of convergence to accelerometer/magnetometer
*/
#define KP 2.0F
/*!
 Integral gain governs rate of convergence of gyroscope biases
*/
#define KI 0.01F
/*!
 2 * proportional gain (Kp)
*/
#define KP2 0.1F

#undef NORM3
/* Normalise 3 measurement */
#define NORM3(_x, _y, _z)                                     \
    do                                                        \
    {                                                         \
        float norm = a_inv_sqrt(_x * _x + _y * _y + _z * _z); \
        _x *= norm;                                           \
        _y *= norm;                                           \
        _z *= norm;                                           \
    } while (0);

#undef NORM4
/* Normalise 4 measurement */
#define NORM4(_w, _x, _y, _z)                       \
    do                                              \
    {                                               \
        float norm = a_inv_sqrt(_w * _w + _x * _x + \
                                _y * _y + _z * _z); \
        _w *= norm;                                 \
        _x *= norm;                                 \
        _y *= norm;                                 \
        _z *= norm;                                 \
    } while (0);

typedef enum
{
    A_AHRS_AXIS9,  //!< 9 axis
    A_AHRS_AXIS6,  //!< 6 axis
} a_ahrs_type_t;

/* convert between long and float */
static union
{
    float f32;
    unsigned long u32;
} b32[3];

static float eix; /* error integral of x axis */
static float eiy; /* error integral of y axis */
static float eiz; /* error integral of z axis */

/* inv_sqrt */
#ifndef __A_MATH_H__
/*!
 @brief          fast inverse square-root, to calculate 1 / sqrtf(x)
 @details        http://en.wikipedia.org/wiki/Fast_inverse_square_root
 @param[in]      x: the number need to be calculated
 @return         1 / sqrtf(x)
*/
static float a_inv_sqrt(float x);

static float a_inv_sqrt(float _x)
{
    b32->f32 = _x;

    if (b32->u32 & 0x80000000)
    {
        b32->u32 = 0xFFC00000;
        _x = b32->f32;
    }
    else if (b32->u32 & 0x7FFFFFFF)
    {
        float xh = 0.5F * _x;

        b32->u32 = 0x5F3759DF - (b32->u32 >> 1);
        _x = b32->f32;

        _x = _x * (1.5F - (xh * _x * _x));
        _x = _x * (1.5F - (xh * _x * _x));
    }
    else
    {
        b32->u32 = 0x7F800000;
        _x = b32->f32;
    }

    return _x;
}
#endif /* __A_MATH_H__ */

#undef x
#undef y
#undef z
#define x 0 /*!< x axis */
#define y 1 /*!< y axis */
#define z 2 /*!< z axis */

void a_ahrs_mahony(float _q[4], float _g[3], float _a[3], float _m[3], float _ht)
{
    a_assert(_q);
    a_assert(_g);
    a_assert(_a);
    a_assert(_m);

    a_ahrs_type_t type = A_AHRS_AXIS9;

    b32[x].f32 = _m[x];
    b32[y].f32 = _m[y];
    b32[z].f32 = _m[z];
    /* Avoids NaN in magnetometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* mx != 0 && my != 0 && mz != 0 */
    {
        /* Normalise magnetometer measurement */
        NORM3(_m[x], _m[y], _m[z]);
    }
    else /* mx == 0, my = 0, mz = 0 */
    {
        type = A_AHRS_AXIS6;
    }

    /* Auxiliary variables to avoid repeated arithmetic */
    float q0q0 = _q[0] * _q[0];
    float q0q1 = _q[0] * _q[1];
    float q0q2 = _q[0] * _q[2];
    float q0q3 = _q[0] * _q[3];
    float q1q1 = _q[1] * _q[1];
    float q1q2 = _q[1] * _q[2];
    float q1q3 = _q[1] * _q[3];
    float q2q2 = _q[2] * _q[2];
    float q2q3 = _q[2] * _q[3];
    float q3q3 = _q[3] * _q[3];

    b32[x].f32 = _a[x];
    b32[y].f32 = _a[y];
    b32[z].f32 = _a[z];
    /* Avoids NaN in accelerometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* ax != 0 && ay != 0 && az != 0 */
    {
        /* Normalise accelerometer measurement */
        NORM3(_a[x], _a[y], _a[z]);

        /* Reference direction of Earth's magnetic field */
        float hx = 0;
        float hy = 0;
        float bx = 0;
        float bz = 0;
        if (type == A_AHRS_AXIS9)
        {
            hx = 2.0F * (_m[x] * (0.5F - q2q2 - q3q3) +
                         _m[y] * (q1q2 - q0q3) +
                         _m[z] * (q1q3 + q0q2) /**/);
            hy = 2.0F * (_m[x] * (q1q2 + q0q3) +
                         _m[y] * (0.5F - q1q1 - q3q3) +
                         _m[z] * (q2q3 - q0q1) /**/);
            bx = sqrtf(hx * hx + hy * hy);
            bz = 2.0F * (_m[x] * (q1q3 - q0q2) +
                         _m[y] * (q2q3 + q0q1) +
                         _m[z] * (0.5F - q1q1 - q2q2) /**/);
        }

        /*!
         \f{aligned}{
            \left[\begin{array}{ccc}
            1 - 2(q_{2}^{2} + q_{3}^{2}) &
            2\left(q_{1} q_{2}-q_{0} q_{3}\right) &
            2\left(q_{1} q_{3}+q_{0} q_{2}\right) \\
            2\left(q_{1} q_{2}+q_{0} q_{3}\right) &
            1 - 2(q_{1}^{2} + q_{3}^{2}) &
            2\left(q_{2} q_{3}-q_{0} q_{1}\right) \\
            2\left(q_{1} q_{3}-q_{0} q_{2}\right) &
            2\left(q_{2} q_{3}+q_{0} q_{1}\right) &
            1 - 2(q_{1}^{2} + q_{2}^{2})
            \end{array}\right]
         \f}
        */

        /* Estimated direction of gravity and magnetic field (v and w) */
        float vx = 2.0F * (q1q3 - q0q2);
        float vy = 2.0F * (q0q1 + q2q3);
#if 0
        float vz = 2.0F * (q0q0 - 0.5F + q3q3);
#else
        float vz = q0q0 - q1q1 - q2q2 + q3q3;
#endif
        float wx = 0;
        float wy = 0;
        float wz = 0;
        if (type == A_AHRS_AXIS9)
        {
            wx = 2.0F * (bx * (0.5F - q2q2 - q3q3) + (q1q3 - q0q2) * bz);
            wy = 2.0F * (bx * (q1q2 - q0q3) + (q0q1 + q2q3) * bz);
            wz = 2.0F * (bx * (q0q2 + q1q3) + (0.5F - q1q1 - q2q2) * bz);
        }

        /*
         Error is sum of cross product between reference
         direction of fields and direction measured by sensors
        */
        static float e[3];
        e[x] = _a[y] * vz - _a[z] * vy;
        e[y] = _a[z] * vx - _a[x] * vz;
        e[z] = _a[x] * vy - _a[y] * vx;
        if (type == A_AHRS_AXIS9)
        {
            e[x] += _m[y] * wz - _m[z] * wy;
            e[y] += _m[z] * wx - _m[x] * wz;
            e[z] += _m[x] * wy - _m[y] * wx;
        }

        b32[x].f32 = e[x];
        b32[y].f32 = e[y];
        b32[z].f32 = e[z];
        /* PI */
        if ((b32[x].u32 & 0x7FFFFFFF) ||
            (b32[y].u32 & 0x7FFFFFFF) ||
            (b32[z].u32 & 0x7FFFFFFF))
        /* ex != 0 && ey != 0 && ez != 0 */
        {
            eix += e[x] * KI * _ht;
            eiy += e[y] * KI * _ht;
            eiz += e[z] * KI * _ht;

            _g[x] += KP * e[x] + eix;
            _g[y] += KP * e[y] + eiy;
            _g[z] += KP * e[z] + eiz;
        }
    }

    float q_0 = _q[0];
    float q_1 = _q[1];
    float q_2 = _q[2];
    /* Integrate quaternion rate */
    _q[0] += _ht * (-q_1 * _g[x] - q_2 * _g[y] - _q[3] * _g[z]);
    _q[1] += _ht * (+q_0 * _g[x] + q_2 * _g[z] - _q[3] * _g[y]);
    _q[2] += _ht * (+q_0 * _g[y] - q_1 * _g[z] + _q[3] * _g[x]);
    _q[3] += _ht * (+q_0 * _g[z] + q_1 * _g[y] - q_2 * _g[x]);

    /* Normalise quaternion */
    NORM4(_q[0], _q[1], _q[2], _q[3]);
}

void a_ahrs_mahony_imu(float _q[4], float _g[3], float _a[3], float ht)
{
    a_assert(_q);
    a_assert(_g);
    a_assert(_a);

    /* Auxiliary variables to avoid repeated arithmetic */
    float q0q0 = _q[0] * _q[0];
    float q0q1 = _q[0] * _q[1];
    float q0q2 = _q[0] * _q[2];
    float q1q1 = _q[1] * _q[1];
    float q1q3 = _q[1] * _q[3];
    float q2q2 = _q[2] * _q[2];
    float q2q3 = _q[2] * _q[3];
    float q3q3 = _q[3] * _q[3];

    b32[x].f32 = _a[x];
    b32[y].f32 = _a[y];
    b32[z].f32 = _a[z];
    /* Avoids NaN in accelerometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* ax != 0 && ay != 0 && az != 0 */
    {
        /* Normalise accelerometer measurement */
        NORM3(_a[x], _a[y], _a[z]);

        /* Estimated direction of gravity and magnetic field (v and w) */
        float vx = 2.0F * (q1q3 - q0q2);
        float vy = 2.0F * (q0q1 + q2q3);
#if 0
        float vz = 2.0F * (q0q0 - 0.5F + q3q3);
#else
        float vz = q0q0 - q1q1 - q2q2 + q3q3;
#endif

        /*
         Error is sum of cross product between reference
         direction of fields and direction measured by sensors
        */
        static float e[3];
        e[x] = _a[y] * vz - _a[z] * vy;
        e[y] = _a[z] * vx - _a[x] * vz;
        e[z] = _a[x] * vy - _a[y] * vx;

        b32[x].f32 = e[x];
        b32[y].f32 = e[y];
        b32[z].f32 = e[z];
        /* PI */
        if ((b32[x].u32 & 0x7FFFFFFF) ||
            (b32[y].u32 & 0x7FFFFFFF) ||
            (b32[z].u32 & 0x7FFFFFFF))
        /* ex != 0 && ey != 0 && ez != 0 */
        {
            eix += e[x] * KI * ht;
            eiy += e[y] * KI * ht;
            eiz += e[z] * KI * ht;

            _g[x] += KP * e[x] + eix;
            _g[y] += KP * e[y] + eiy;
            _g[z] += KP * e[z] + eiz;
        }
    }

    float q_0 = _q[0];
    float q_1 = _q[1];
    float q_2 = _q[2];
    /* Integrate quaternion rate */
    _q[0] += ht * (-q_1 * _g[x] - q_2 * _g[y] - _q[3] * _g[z]);
    _q[1] += ht * (+q_0 * _g[x] + q_2 * _g[z] - _q[3] * _g[y]);
    _q[2] += ht * (+q_0 * _g[y] - q_1 * _g[z] + _q[3] * _g[x]);
    _q[3] += ht * (+q_0 * _g[z] + q_1 * _g[y] - q_2 * _g[x]);

    /* Normalise quaternion */
    NORM4(_q[0], _q[1], _q[2], _q[3]);
}

void a_ahrs_madgwick(float _q[4], float _g[3], float _a[3], float _m[3], float _t)
{
    a_assert(_q);
    a_assert(_g);
    a_assert(_a);
    a_assert(_m);

    a_ahrs_type_t type = A_AHRS_AXIS9;

    b32[x].f32 = _m[x];
    b32[y].f32 = _m[y];
    b32[z].f32 = _m[z];
    /* Avoids NaN in magnetometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* mx != 0 && my != 0 && mz != 0 */
    {
        /* Normalise magnetometer measurement */
        NORM3(_m[x], _m[y], _m[z]);
    }
    else /* mx == 0, my = 0, mz = 0 */
    {
        type = A_AHRS_AXIS6;
    }

    /* Rate of change of quaternion from gyroscope */
    float q_dot1 = 0.5F * (-_q[1] * _g[x] - _q[2] * _g[y] - _q[3] * _g[z]);
    float q_dot2 = 0.5F * (_q[0] * _g[x] + _q[2] * _g[z] - _q[3] * _g[y]);
    float q_dot3 = 0.5F * (_q[0] * _g[y] - _q[1] * _g[z] + _q[3] * _g[x]);
    float q_dot4 = 0.5F * (_q[0] * _g[z] + _q[1] * _g[y] - _q[2] * _g[x]);

    b32[x].f32 = _a[x];
    b32[y].f32 = _a[y];
    b32[z].f32 = _a[z];
    /* Avoids NaN in accelerometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* ax != 0 && ay != 0 && az != 0 */
    {
        /* Normalise accelerometer measurement */
        NORM3(_a[x], _a[y], _a[z]);

        /* Auxiliary variables to avoid repeated arithmetic */
        float _2q0 = 2.0F * _q[0];
        float _2q1 = 2.0F * _q[1];
        float _2q2 = 2.0F * _q[2];
        float _2q3 = 2.0F * _q[3];
        float q0q0 = _q[0] * _q[0];
        float q0q1 = _q[0] * _q[1];
        float q0q2 = _q[0] * _q[2];
        float q0q3 = _q[0] * _q[3];
        float q1q1 = _q[1] * _q[1];
        float q1q2 = _q[1] * _q[2];
        float q1q3 = _q[1] * _q[3];
        float q2q2 = _q[2] * _q[2];
        float q2q3 = _q[2] * _q[3];
        float q3q3 = _q[3] * _q[3];

        float s0 = 0;
        float s1 = 0;
        float s2 = 0;
        float s3 = 0;
        if (type == A_AHRS_AXIS9)
        {
            float _2q0q2 = 2.0F * _q[0] * _q[2];
            float _2q2q3 = 2.0F * _q[2] * _q[3];
            float _2q0mx = 2.0F * _q[0] * _m[x];
            float _2q0my = 2.0F * _q[0] * _m[y];
            float _2q0mz = 2.0F * _q[0] * _m[z];
            float _2q1mx = 2.0F * _q[1] * _m[x];

            /* Reference direction of Earth's magnetic field */
            float hx = _m[x] * q0q0 -
                       _2q0my * _q[3] +
                       _2q0mz * _q[2] +
                       _m[x] * q1q1 +
                       _2q1 * _m[y] * _q[2] +
                       _2q1 * _m[z] * _q[3] -
                       _m[x] * q2q2 -
                       _m[x] * q3q3;
            float hy = _2q0mx * _q[3] +
                       _m[y] * q0q0 -
                       _2q0mz * _q[1] +
                       _2q1mx * _q[2] -
                       _m[y] * q1q1 +
                       _m[y] * q2q2 +
                       _2q2 * _m[z] * _q[3] -
                       _m[y] * q3q3;
            float _2bx = sqrtf(hx * hx + hy * hy);
            float _2bz = -_2q0mx * _q[2] +
                         _2q0my * _q[1] +
                         _m[z] * q0q0 +
                         _2q1mx * _q[3] -
                         _m[z] * q1q1 +
                         _2q2 * _m[y] * _q[3] -
                         _m[z] * q2q2 +
                         _m[z] * q3q3;
            float _4bx = 2.0F * _2bx;
            float _4bz = 2.0F * _2bz;

            /* Gradient decent algorithm corrective step */
            s0 = -_2q2 * (2.0F * q1q3 - _2q0q2 - _a[x]) +
                 _2q1 * (2.0F * q0q1 + _2q2q3 - _a[y]) -
                 _2bz * _q[2] * (_2bx * (0.5F - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - _m[x]) +
                 (-_2bx * _q[3] + _2bz * _q[1]) *
                     (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - _m[y]) +
                 _2bx * _q[2] * (_2bx * (q0q2 + q1q3) + _2bz * (0.5F - q1q1 - q2q2) - _m[z]);
            s1 = _2q3 * (2.0F * q1q3 - _2q0q2 - _a[x]) +
                 _2q0 * (2.0F * q0q1 + _2q2q3 - _a[y]) -
                 4.0F * _q[1] * (1 - 2.0F * q1q1 - 2.0F * q2q2 - _a[z]) +
                 _2bz * _q[3] * (_2bx * (0.5F - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - _m[x]) +
                 (_2bx * _q[2] + _2bz * _q[0]) *
                     (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - _m[y]) +
                 (_2bx * _q[3] - _4bz * _q[1]) *
                     (_2bx * (q0q2 + q1q3) + _2bz * (0.5F - q1q1 - q2q2) - _m[z]);
            s2 = -_2q0 * (2.0F * q1q3 - _2q0q2 - _a[x]) +
                 _2q3 * (2.0F * q0q1 + _2q2q3 - _a[y]) -
                 4.0F * _q[2] * (1 - 2.0F * q1q1 - 2.0F * q2q2 - _a[z]) +
                 (-_4bx * _q[2] - _2bz * _q[0]) *
                     (_2bx * (0.5F - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - _m[x]) +
                 (_2bx * _q[1] + _2bz * _q[3]) *
                     (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - _m[y]) +
                 (_2bx * _q[0] - _4bz * _q[2]) *
                     (_2bx * (q0q2 + q1q3) + _2bz * (0.5F - q1q1 - q2q2) - _m[z]);
            s3 = _2q1 * (2.0F * q1q3 - _2q0q2 - _a[x]) +
                 _2q2 * (2.0F * q0q1 + _2q2q3 - _a[y]) +
                 (-_4bx * _q[3] + _2bz * _q[1]) *
                     (_2bx * (0.5F - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - _m[x]) +
                 (-_2bx * _q[0] + _2bz * _q[2]) *
                     (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - _m[y]) +
                 _2bx * _q[1] * (_2bx * (q0q2 + q1q3) + _2bz * (0.5F - q1q1 - q2q2) - _m[z]);
        }
        else
        {
            float _4q0 = 4.0F * _q[0];
            float _4q1 = 4.0F * _q[1];
            float _4q2 = 4.0F * _q[2];
            float _8q1 = 8.0F * _q[1];
            float _8q2 = 8.0F * _q[2];

            /* Gradient decent algorithm corrective step */
            s0 = _4q0 * q2q2 +
                 _2q2 * _a[x] +
                 _4q0 * q1q1 -
                 _2q1 * _a[y];
            s1 = _4q1 * q3q3 -
                 _2q3 * _a[x] +
                 4.0F * q0q0 * _q[1] -
                 _2q0 * _a[y] -
                 _4q1 +
                 _8q1 * q1q1 +
                 _8q1 * q2q2 +
                 _4q1 * _a[z];
            s2 = 4.0F * q0q0 * _q[2] +
                 _2q0 * _a[x] +
                 _4q2 * q3q3 -
                 _2q3 * _a[y] -
                 _4q2 +
                 _8q2 * q1q1 +
                 _8q2 * q2q2 +
                 _4q2 * _a[z];
            s3 = 4.0F * q1q1 * _q[3] -
                 _2q1 * _a[x] +
                 4.0F * q2q2 * _q[3] -
                 _2q2 * _a[y];
        }

        /* Normalise step magnitude */
        NORM4(s0, s1, s2, s3);

        /* Apply feedback step */
        q_dot1 -= KP2 * s0;
        q_dot2 -= KP2 * s1;
        q_dot3 -= KP2 * s2;
        q_dot4 -= KP2 * s3;
    }

    /* Integrate rate of change of quaternion to yield quaternion */
    _q[0] += q_dot1 * _t;
    _q[1] += q_dot2 * _t;
    _q[2] += q_dot3 * _t;
    _q[3] += q_dot4 * _t;

    /* Normalise quaternion */
    NORM4(_q[0], _q[1], _q[2], _q[3]);
}

void a_ahrs_madgwick_imu(float _q[4], float _g[3], float _a[3], float _t)
{
    a_assert(_q);
    a_assert(_g);
    a_assert(_a);

    /* Rate of change of quaternion from gyroscope */
    float q_dot1 = 0.5F * (-_q[1] * _g[x] - _q[2] * _g[y] - _q[3] * _g[z]);
    float q_dot2 = 0.5F * (_q[0] * _g[x] + _q[2] * _g[z] - _q[3] * _g[y]);
    float q_dot3 = 0.5F * (_q[0] * _g[y] - _q[1] * _g[z] + _q[3] * _g[x]);
    float q_dot4 = 0.5F * (_q[0] * _g[z] + _q[1] * _g[y] - _q[2] * _g[x]);

    b32[x].f32 = _a[x];
    b32[y].f32 = _a[y];
    b32[z].f32 = _a[z];
    /* Avoids NaN in accelerometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* ax != 0 && ay != 0 && az != 0 */
    {
        /* Normalise accelerometer measurement */
        NORM3(_a[x], _a[y], _a[z]);

        /* Auxiliary variables to avoid repeated arithmetic */
        float _2q0 = 2.0F * _q[0];
        float _2q1 = 2.0F * _q[1];
        float _2q2 = 2.0F * _q[2];
        float _2q3 = 2.0F * _q[3];
        float _4q0 = 4.0F * _q[0];
        float _4q1 = 4.0F * _q[1];
        float _4q2 = 4.0F * _q[2];
        float _8q1 = 8.0F * _q[1];
        float _8q2 = 8.0F * _q[2];
        float q0q0 = _q[0] * _q[0];
        float q1q1 = _q[1] * _q[1];
        float q2q2 = _q[2] * _q[2];
        float q3q3 = _q[3] * _q[3];

        /* Gradient decent algorithm corrective step */
        float s0 = _4q0 * q2q2 +
                   _2q2 * _a[x] +
                   _4q0 * q1q1 -
                   _2q1 * _a[y];
        float s1 = _4q1 * q3q3 -
                   _2q3 * _a[x] +
                   4.0F * q0q0 * _q[1] -
                   _2q0 * _a[y] -
                   _4q1 +
                   _8q1 * q1q1 +
                   _8q1 * q2q2 +
                   _4q1 * _a[z];
        float s2 = 4.0F * q0q0 * _q[2] +
                   _2q0 * _a[x] +
                   _4q2 * q3q3 -
                   _2q3 * _a[y] -
                   _4q2 +
                   _8q2 * q1q1 +
                   _8q2 * q2q2 +
                   _4q2 * _a[z];
        float s3 = 4.0F * q1q1 * _q[3] -
                   _2q1 * _a[x] +
                   4.0F * q2q2 * _q[3] -
                   _2q2 * _a[y];

        /* Normalise step magnitude */
        NORM4(s0, s1, s2, s3);

        /* Apply feedback step */
        q_dot1 -= KP2 * s0;
        q_dot2 -= KP2 * s1;
        q_dot3 -= KP2 * s2;
        q_dot4 -= KP2 * s3;
    }

    /* Integrate rate of change of quaternion to yield quaternion */
    _q[0] += q_dot1 * _t;
    _q[1] += q_dot2 * _t;
    _q[2] += q_dot3 * _t;
    _q[3] += q_dot4 * _t;

    /* Normalise quaternion */
    NORM4(_q[0], _q[1], _q[2], _q[3]);
}

#undef x
#undef y
#undef z

/* END OF FILE */
