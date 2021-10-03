/*!
 @file           a_ahrs.c
 @brief          AHRS(Automatic Heading Reference System) algorithm library
 @details        IMU(Inertial Measurement Unit)
                 Mehony AHRS
                 Madgwick AHRS
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

/* Includes */
#include "a_ahrs.h"

/* Private includes */
#include "a_math.h"

#include <math.h>
#include <stdint.h>

/* gain */
#undef KI
#undef KP
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

/* Normalise */
#undef NORM3
/* Normalise 3 measurement */
#define NORM3(_x, _y, _z)                                     \
    do                                                        \
    {                                                         \
        /* Fast inverse square-root */                        \
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
        /* Fast inverse square-root */              \
        float norm = a_inv_sqrt(_w * _w + _x * _x + \
                                _y * _y + _z * _z); \
        _w *= norm;                                 \
        _x *= norm;                                 \
        _y *= norm;                                 \
        _z *= norm;                                 \
    } while (0);

/* ahrs type */

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

/* error integral */
static float eix; /* error integral of x axis */
static float eiy; /* error integral of x axis */
static float eiz; /* error integral of x axis */

/* inv_sqrt */
#ifndef __A_MATH_H__
/*!
 @brief          fast inverse square-root, to calculate 1 / sqrtf(x)
                 http://en.wikipedia.org/wiki/Fast_inverse_square_root
 @param[in]      x: the number need to be calculated
 @return         1 / sqrtf(x)
*/
static float a_inv_sqrt(float x);

static float a_inv_sqrt(float x)
{
    b32->f32 = x;

    if (b32->u32 & 0x80000000)
    {
        x = (0.0F / 0.0F);
    }
    else if (b32->u32 & 0x7FFFFFFF)
    {
        float xh = 0.5F * x;

        b32->u32 = 0x5F3759DF - (b32->u32 >> 1);
        x = b32->f32;

        x = x * (1.5F - (xh * x * x));
        x = x * (1.5F - (xh * x * x));
    }
    else
    {
        x = (1.0F / 0.0F);
    }

    return x;
}
#endif /* __A_MATH_H__ */

/* Private macro */
#undef x /* Remove x */
#undef y /* Remove y */
#undef z /* Remove z */

#define x 0 /*!< x axis */
#define y 1 /*!< y axis */
#define z 2 /*!< z axis */

void a_ahrs_mahony(float q[4],
                   float g[3],
                   float a[3],
                   float m[3],
                   float ht)
{
    a_ahrs_type_t type = A_AHRS_AXIS9;

    b32[x].f32 = m[x];
    b32[y].f32 = m[y];
    b32[z].f32 = m[z];
    /* Avoids NaN in magnetometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* mx != 0 && my != 0 && mz != 0 */
    {
        /* Normalise magnetometer measurement */
        NORM3(m[x], m[y], m[z]);
    }
    else /* mx == 0, my = 0, mz = 0 */
    {
        type = A_AHRS_AXIS6;
    }

    /* Auxiliary variables to avoid repeated arithmetic */
    float q0q0 = q[0] * q[0];
    float q0q1 = q[0] * q[1];
    float q0q2 = q[0] * q[2];
    float q0q3 = q[0] * q[3];
    float q1q1 = q[1] * q[1];
    float q1q2 = q[1] * q[2];
    float q1q3 = q[1] * q[3];
    float q2q2 = q[2] * q[2];
    float q2q3 = q[2] * q[3];
    float q3q3 = q[3] * q[3];

    b32[x].f32 = a[x];
    b32[y].f32 = a[y];
    b32[z].f32 = a[z];
    /* Avoids NaN in accelerometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* ax != 0 && ay != 0 && az != 0 */
    {
        /* Normalise accelerometer measurement */
        NORM3(a[x], a[y], a[z]);

        /* Reference direction of Earth's magnetic field */
        float hx = 0;
        float hy = 0;
        float bx = 0;
        float bz = 0;
        if (type == A_AHRS_AXIS9)
        {
            hx = 2.0F * (m[x] * (0.5F - q2q2 - q3q3) +
                         m[y] * (q1q2 - q0q3) +
                         m[z] * (q1q3 + q0q2) /**/);
            hy = 2.0F * (m[x] * (q1q2 + q0q3) +
                         m[y] * (0.5F - q1q1 - q3q3) +
                         m[z] * (q2q3 - q0q1) /**/);
            bx = sqrtf(hx * hx + hy * hy);
            bz = 2.0F * (m[x] * (q1q3 - q0q2) +
                         m[y] * (q2q3 + q0q1) +
                         m[z] * (0.5F - q1q1 - q2q2) /**/);
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
        e[x] = a[y] * vz - a[z] * vy;
        e[y] = a[z] * vx - a[x] * vz;
        e[z] = a[x] * vy - a[y] * vx;
        if (type == A_AHRS_AXIS9)
        {
            e[x] += m[y] * wz - m[z] * wy;
            e[y] += m[z] * wx - m[x] * wz;
            e[z] += m[x] * wy - m[y] * wx;
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
            eix += e[x] * KI * ht;
            eiy += e[y] * KI * ht;
            eiz += e[z] * KI * ht;

            g[x] += KP * e[x] + eix;
            g[y] += KP * e[y] + eiy;
            g[z] += KP * e[z] + eiz;
        }
    }

    float q_0 = q[0];
    float q_1 = q[1];
    float q_2 = q[2];
    /* Integrate quaternion rate */
    q[0] += ht * (-q_1 * g[x] - q_2 * g[y] - q[3] * g[z]);
    q[1] += ht * (+q_0 * g[x] + q_2 * g[z] - q[3] * g[y]);
    q[2] += ht * (+q_0 * g[y] - q_1 * g[z] + q[3] * g[x]);
    q[3] += ht * (+q_0 * g[z] + q_1 * g[y] - q_2 * g[x]);

    /* Normalise quaternion */
    NORM4(q[0], q[1], q[2], q[3]);
}

void a_ahrs_mahony_imu(float q[4],
                       float g[3],
                       float a[3],
                       float ht)
{
    /* Auxiliary variables to avoid repeated arithmetic */
    float q0q0 = q[0] * q[0];
    float q0q1 = q[0] * q[1];
    float q0q2 = q[0] * q[2];
    float q1q1 = q[1] * q[1];
    float q1q3 = q[1] * q[3];
    float q2q2 = q[2] * q[2];
    float q2q3 = q[2] * q[3];
    float q3q3 = q[3] * q[3];

    b32[x].f32 = a[x];
    b32[y].f32 = a[y];
    b32[z].f32 = a[z];
    /* Avoids NaN in accelerometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* ax != 0 && ay != 0 && az != 0 */
    {
        /* Normalise accelerometer measurement */
        NORM3(a[x], a[y], a[z]);

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
        e[x] = a[y] * vz - a[z] * vy;
        e[y] = a[z] * vx - a[x] * vz;
        e[z] = a[x] * vy - a[y] * vx;

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

            g[x] += KP * e[x] + eix;
            g[y] += KP * e[y] + eiy;
            g[z] += KP * e[z] + eiz;
        }
    }

    float q_0 = q[0];
    float q_1 = q[1];
    float q_2 = q[2];
    /* Integrate quaternion rate */
    q[0] += ht * (-q_1 * g[x] - q_2 * g[y] - q[3] * g[z]);
    q[1] += ht * (+q_0 * g[x] + q_2 * g[z] - q[3] * g[y]);
    q[2] += ht * (+q_0 * g[y] - q_1 * g[z] + q[3] * g[x]);
    q[3] += ht * (+q_0 * g[z] + q_1 * g[y] - q_2 * g[x]);

    /* Normalise quaternion */
    NORM4(q[0], q[1], q[2], q[3]);
}

void a_ahrs_madgwick(float q[4],
                     float g[3],
                     float a[3],
                     float m[3],
                     float t)
{
    a_ahrs_type_t type = A_AHRS_AXIS9;

    b32[x].f32 = m[x];
    b32[y].f32 = m[y];
    b32[z].f32 = m[z];
    /* Avoids NaN in magnetometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* mx != 0 && my != 0 && mz != 0 */
    {
        /* Normalise magnetometer measurement */
        NORM3(m[x], m[y], m[z]);
    }
    else /* mx == 0, my = 0, mz = 0 */
    {
        type = A_AHRS_AXIS6;
    }

    /* Rate of change of quaternion from gyroscope */
    float q_dot1 = 0.5F * (-q[1] * g[x] - q[2] * g[y] - q[3] * g[z]);
    float q_dot2 = 0.5F * (q[0] * g[x] + q[2] * g[z] - q[3] * g[y]);
    float q_dot3 = 0.5F * (q[0] * g[y] - q[1] * g[z] + q[3] * g[x]);
    float q_dot4 = 0.5F * (q[0] * g[z] + q[1] * g[y] - q[2] * g[x]);

    b32[x].f32 = a[x];
    b32[y].f32 = a[y];
    b32[z].f32 = a[z];
    /* Avoids NaN in accelerometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* ax != 0 && ay != 0 && az != 0 */
    {
        /* Normalise accelerometer measurement */
        NORM3(a[x], a[y], a[z]);

        /* Auxiliary variables to avoid repeated arithmetic */
        float _2q0 = 2.0F * q[0];
        float _2q1 = 2.0F * q[1];
        float _2q2 = 2.0F * q[2];
        float _2q3 = 2.0F * q[3];
        float q0q0 = q[0] * q[0];
        float q0q1 = q[0] * q[1];
        float q0q2 = q[0] * q[2];
        float q0q3 = q[0] * q[3];
        float q1q1 = q[1] * q[1];
        float q1q2 = q[1] * q[2];
        float q1q3 = q[1] * q[3];
        float q2q2 = q[2] * q[2];
        float q2q3 = q[2] * q[3];
        float q3q3 = q[3] * q[3];

        float s0 = 0;
        float s1 = 0;
        float s2 = 0;
        float s3 = 0;
        if (type == A_AHRS_AXIS9)
        {
            float _2q0q2 = 2.0F * q[0] * q[2];
            float _2q2q3 = 2.0F * q[2] * q[3];
            float _2q0mx = 2.0F * q[0] * m[x];
            float _2q0my = 2.0F * q[0] * m[y];
            float _2q0mz = 2.0F * q[0] * m[z];
            float _2q1mx = 2.0F * q[1] * m[x];

            /* Reference direction of Earth's magnetic field */
            float hx = m[x] * q0q0 -
                       _2q0my * q[3] +
                       _2q0mz * q[2] +
                       m[x] * q1q1 +
                       _2q1 * m[y] * q[2] +
                       _2q1 * m[z] * q[3] -
                       m[x] * q2q2 -
                       m[x] * q3q3;
            float hy = _2q0mx * q[3] +
                       m[y] * q0q0 -
                       _2q0mz * q[1] +
                       _2q1mx * q[2] -
                       m[y] * q1q1 +
                       m[y] * q2q2 +
                       _2q2 * m[z] * q[3] -
                       m[y] * q3q3;
            float _2bx = sqrtf(hx * hx + hy * hy);
            float _2bz = -_2q0mx * q[2] +
                         _2q0my * q[1] +
                         m[z] * q0q0 +
                         _2q1mx * q[3] -
                         m[z] * q1q1 +
                         _2q2 * m[y] * q[3] -
                         m[z] * q2q2 +
                         m[z] * q3q3;
            float _4bx = 2.0F * _2bx;
            float _4bz = 2.0F * _2bz;

            /* Gradient decent algorithm corrective step */
            s0 = -_2q2 * (2.0F * q1q3 - _2q0q2 - a[x]) +
                 _2q1 * (2.0F * q0q1 + _2q2q3 - a[y]) -
                 _2bz * q[2] * (_2bx * (0.5F - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - m[x]) +
                 (-_2bx * q[3] + _2bz * q[1]) *
                     (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - m[y]) +
                 _2bx * q[2] * (_2bx * (q0q2 + q1q3) + _2bz * (0.5F - q1q1 - q2q2) - m[z]);
            s1 = _2q3 * (2.0F * q1q3 - _2q0q2 - a[x]) +
                 _2q0 * (2.0F * q0q1 + _2q2q3 - a[y]) -
                 4.0F * q[1] * (1 - 2.0F * q1q1 - 2.0F * q2q2 - a[z]) +
                 _2bz * q[3] * (_2bx * (0.5F - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - m[x]) +
                 (_2bx * q[2] + _2bz * q[0]) *
                     (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - m[y]) +
                 (_2bx * q[3] - _4bz * q[1]) *
                     (_2bx * (q0q2 + q1q3) + _2bz * (0.5F - q1q1 - q2q2) - m[z]);
            s2 = -_2q0 * (2.0F * q1q3 - _2q0q2 - a[x]) +
                 _2q3 * (2.0F * q0q1 + _2q2q3 - a[y]) -
                 4.0F * q[2] * (1 - 2.0F * q1q1 - 2.0F * q2q2 - a[z]) +
                 (-_4bx * q[2] - _2bz * q[0]) *
                     (_2bx * (0.5F - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - m[x]) +
                 (_2bx * q[1] + _2bz * q[3]) *
                     (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - m[y]) +
                 (_2bx * q[0] - _4bz * q[2]) *
                     (_2bx * (q0q2 + q1q3) + _2bz * (0.5F - q1q1 - q2q2) - m[z]);
            s3 = _2q1 * (2.0F * q1q3 - _2q0q2 - a[x]) +
                 _2q2 * (2.0F * q0q1 + _2q2q3 - a[y]) +
                 (-_4bx * q[3] + _2bz * q[1]) *
                     (_2bx * (0.5F - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - m[x]) +
                 (-_2bx * q[0] + _2bz * q[2]) *
                     (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - m[y]) +
                 _2bx * q[1] * (_2bx * (q0q2 + q1q3) + _2bz * (0.5F - q1q1 - q2q2) - m[z]);
        }
        else
        {
            float _4q0 = 4.0F * q[0];
            float _4q1 = 4.0F * q[1];
            float _4q2 = 4.0F * q[2];
            float _8q1 = 8.0F * q[1];
            float _8q2 = 8.0F * q[2];

            /* Gradient decent algorithm corrective step */
            s0 = _4q0 * q2q2 +
                 _2q2 * a[x] +
                 _4q0 * q1q1 -
                 _2q1 * a[y];
            s1 = _4q1 * q3q3 -
                 _2q3 * a[x] +
                 4.0F * q0q0 * q[1] -
                 _2q0 * a[y] -
                 _4q1 +
                 _8q1 * q1q1 +
                 _8q1 * q2q2 +
                 _4q1 * a[z];
            s2 = 4.0F * q0q0 * q[2] +
                 _2q0 * a[x] +
                 _4q2 * q3q3 -
                 _2q3 * a[y] -
                 _4q2 +
                 _8q2 * q1q1 +
                 _8q2 * q2q2 +
                 _4q2 * a[z];
            s3 = 4.0F * q1q1 * q[3] -
                 _2q1 * a[x] +
                 4.0F * q2q2 * q[3] -
                 _2q2 * a[y];
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
    q[0] += q_dot1 * t;
    q[1] += q_dot2 * t;
    q[2] += q_dot3 * t;
    q[3] += q_dot4 * t;

    /* Normalise quaternion */
    NORM4(q[0], q[1], q[2], q[3]);
}

void a_ahrs_madgwick_imu(float q[4],
                         float g[3],
                         float a[3],
                         float t)
{
    /* Rate of change of quaternion from gyroscope */
    float q_dot1 = 0.5F * (-q[1] * g[x] - q[2] * g[y] - q[3] * g[z]);
    float q_dot2 = 0.5F * (q[0] * g[x] + q[2] * g[z] - q[3] * g[y]);
    float q_dot3 = 0.5F * (q[0] * g[y] - q[1] * g[z] + q[3] * g[x]);
    float q_dot4 = 0.5F * (q[0] * g[z] + q[1] * g[y] - q[2] * g[x]);

    b32[x].f32 = a[x];
    b32[y].f32 = a[y];
    b32[z].f32 = a[z];
    /* Avoids NaN in accelerometer normalisation */
    if ((b32[x].u32 & 0x7FFFFFFF) ||
        (b32[y].u32 & 0x7FFFFFFF) ||
        (b32[z].u32 & 0x7FFFFFFF))
    /* ax != 0 && ay != 0 && az != 0 */
    {
        /* Normalise accelerometer measurement */
        NORM3(a[x], a[y], a[z]);

        /* Auxiliary variables to avoid repeated arithmetic */
        float _2q0 = 2.0F * q[0];
        float _2q1 = 2.0F * q[1];
        float _2q2 = 2.0F * q[2];
        float _2q3 = 2.0F * q[3];
        float _4q0 = 4.0F * q[0];
        float _4q1 = 4.0F * q[1];
        float _4q2 = 4.0F * q[2];
        float _8q1 = 8.0F * q[1];
        float _8q2 = 8.0F * q[2];
        float q0q0 = q[0] * q[0];
        float q1q1 = q[1] * q[1];
        float q2q2 = q[2] * q[2];
        float q3q3 = q[3] * q[3];

        /* Gradient decent algorithm corrective step */
        float s0 = _4q0 * q2q2 +
                   _2q2 * a[x] +
                   _4q0 * q1q1 -
                   _2q1 * a[y];
        float s1 = _4q1 * q3q3 -
                   _2q3 * a[x] +
                   4.0F * q0q0 * q[1] -
                   _2q0 * a[y] -
                   _4q1 +
                   _8q1 * q1q1 +
                   _8q1 * q2q2 +
                   _4q1 * a[z];
        float s2 = 4.0F * q0q0 * q[2] +
                   _2q0 * a[x] +
                   _4q2 * q3q3 -
                   _2q3 * a[y] -
                   _4q2 +
                   _8q2 * q1q1 +
                   _8q2 * q2q2 +
                   _4q2 * a[z];
        float s3 = 4.0F * q1q1 * q[3] -
                   _2q1 * a[x] +
                   4.0F * q2q2 * q[3] -
                   _2q2 * a[y];

        /* Normalise step magnitude */
        NORM4(s0, s1, s2, s3);

        /* Apply feedback step */
        q_dot1 -= KP2 * s0;
        q_dot2 -= KP2 * s1;
        q_dot3 -= KP2 * s2;
        q_dot4 -= KP2 * s3;
    }

    /* Integrate rate of change of quaternion to yield quaternion */
    q[0] += q_dot1 * t;
    q[1] += q_dot2 * t;
    q[2] += q_dot3 * t;
    q[3] += q_dot4 * t;

    /* Normalise quaternion */
    NORM4(q[0], q[1], q[2], q[3]);
}

/* Remove macro */
#undef x /* Remove x */
#undef y /* Remove y */
#undef z /* Remove z */

/* END OF FILE */
