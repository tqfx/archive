/*!
 @file           polynomial.c
 @brief          polynomial trajectory
 @details        Trajectory Planning for Automatic Machines and Robots.
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-07-23
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

#include "polynomial.h"

void polynomial3_init(polynomial3_t *p,
                      float source[3],
                      float target[3])
{
    p->t[0] = source[0];
    p->q[0] = source[1];
    p->v[0] = source[2];
    p->t[1] = target[0];
    p->q[1] = target[1];
    p->v[1] = target[2];

    float dist = p->q[1] - p->q[0];
    float t1 = p->t[1] - p->t[0];
    float inv_t1 = 1 / t1;
    float inv_t2 = inv_t1 * inv_t1;
    float inv_t3 = inv_t1 * inv_t2;
    float vt = (p->v[0] + p->v[1]) * t1;

    p->k[0] = p->q[0];
    p->k[1] = p->v[0];
    p->k[2] = inv_t2 * (3 * dist - p->v[0] * t1 - vt);
    p->k[3] = inv_t3 * (vt - 2 * dist);
}

float polynomial3_pos(const polynomial3_t *p,
                      float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    return (p->k[0] +
            p->k[1] * t1 +
            p->k[2] * t2 +
            p->k[3] * t3);
}

float polynomial3_vec(const polynomial3_t *p,
                      float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    return (p->k[1] +
            p->k[2] * t1 * 2 +
            p->k[3] * t2 * 3);
}

float polynomial3_acc(const polynomial3_t *p,
                      float t)
{
    float t1 = t - p->t[0];
    return (p->k[2] * 2 +
            p->k[3] * t1 * 6);
}

void polynomial3_all(const polynomial3_t *p,
                     float out[3],
                     float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    out[0] = p->k[0] + p->k[1] * t1 + p->k[2] * t2 + p->k[3] * t3;
    out[1] = p->k[1] + p->k[2] * t1 * 2 + p->k[3] * t2 * 3;
    out[2] = p->k[2] * 2 + p->k[3] * t1 * 6;
}

void polynomial5_init(polynomial5_t *p,
                      float source[4],
                      float target[4])
{
    p->t[0] = source[0];
    p->q[0] = source[1];
    p->v[0] = source[2];
    p->a[0] = source[3];
    p->t[1] = target[0];
    p->q[1] = target[1];
    p->v[1] = target[2];
    p->a[1] = target[3];

    float dist = p->q[1] - p->q[0];
    float t1 = p->t[1] - p->t[0];
    float t2 = t1 * t1;
    float inv_t1 = 1 / t1;
    float inv_t2 = inv_t1 * inv_t1;
    float inv_t3 = inv_t1 * inv_t2;
    float inv_t4 = inv_t2 * inv_t2;
    float inv_t5 = inv_t2 * inv_t3;
    float v0t1 = p->v[0] * t1;
    float v1t1 = p->v[1] * t1;
    float a0t2 = p->a[0] * t2;
    float a1t2 = p->a[1] * t2;

    p->k[0] = p->q[0];
    p->k[1] = p->v[0];
    p->k[2] = p->a[0] * (1.0F / 2);
    p->k[3] = (1.0F / 2) * inv_t3 * (20 * dist - 8 * v1t1 - 12 * v0t1 + a1t2 - 3 * a0t2);
    p->k[4] = (1.0F / 2) * inv_t4 * (-30 * dist + 14 * v1t1 + 16 * v0t1 + 3 * a0t2 - 2 * a1t2);
    p->k[5] = (1.0F / 2) * inv_t5 * (12 * dist - 6 * (v1t1 + v0t1) + a1t2 - a0t2);
}

float polynomial5_pos(const polynomial5_t *p,
                      float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    float t4 = t2 * t2;
    float t5 = t2 * t3;
    return (p->k[0] +
            p->k[1] * t1 +
            p->k[2] * t2 +
            p->k[3] * t3 +
            p->k[4] * t4 +
            p->k[5] * t5);
}

float polynomial5_vec(const polynomial5_t *p,
                      float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    float t4 = t2 * t2;
    return (p->k[1] +
            p->k[2] * t1 * 2 +
            p->k[3] * t2 * 3 +
            p->k[4] * t3 * 4 +
            p->k[5] * t4 * 5);
}

float polynomial5_acc(const polynomial5_t *p,
                      float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    return (p->k[2] * 2 +
            p->k[3] * t1 * 6 +
            p->k[4] * t2 * 12 +
            p->k[5] * t3 * 20);
}

void polynomial5_all(const polynomial5_t *p,
                     float out[3],
                     float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    float t4 = t2 * t2;
    float t5 = t2 * t3;
    out[0] = p->k[0] +
             p->k[1] * t1 +
             p->k[2] * t2 +
             p->k[3] * t3 +
             p->k[4] * t4 +
             p->k[5] * t5;
    out[1] = p->k[1] +
             p->k[2] * t1 * 2 +
             p->k[3] * t2 * 3 +
             p->k[4] * t3 * 4 +
             p->k[5] * t4 * 5;
    out[2] = p->k[2] * 2 +
             p->k[3] * t1 * 6 +
             p->k[4] * t2 * 12 +
             p->k[5] * t3 * 20;
}

void polynomial7_init(polynomial7_t *p,
                      float source[5],
                      float target[5])
{
    p->t[0] = source[0];
    p->q[0] = source[1];
    p->v[0] = source[2];
    p->a[0] = source[3];
    p->j[0] = source[4];
    p->t[1] = target[0];
    p->q[1] = target[1];
    p->v[1] = target[2];
    p->a[1] = target[3];
    p->j[1] = target[4];

    float dist = p->q[1] - p->q[0];
    float t1 = p->t[1] - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    float inv_t1 = 1 / t1;
    float inv_t2 = inv_t1 * inv_t1;
    float inv_t3 = inv_t1 * inv_t2;
    float inv_t4 = inv_t2 * inv_t2;
    float inv_t5 = inv_t2 * inv_t3;
    float inv_t6 = inv_t3 * inv_t3;
    float inv_t7 = inv_t3 * inv_t4;
    float v0t1 = p->v[0] * t1;
    float v1t1 = p->v[1] * t1;
    float a0t2 = p->a[0] * t2;
    float a1t2 = p->a[1] * t2;
    float j0t3 = p->j[0] * t3;
    float j1t3 = p->j[1] * t3;

    p->k[0] = p->q[0];
    p->k[1] = p->v[0];
    p->k[2] = p->a[0] * (1.0F / 2);
    p->k[3] = p->j[0] * (1.0F / 6);
    p->k[4] = (1.0F / 6) * inv_t4 * (210 * dist - 120 * v0t1 - 90 * v0t1 - 30 * a0t2 + 15 * a1t2 - 4 * j0t3 - j1t3);
    p->k[5] = (1.0F / 2) * inv_t5 * (-168 * dist + 90 * v0t1 + 78 * v1t1 + 20 * a0t2 - 14 * a1t2 + 2 * j0t3 + j1t3);
    p->k[6] = (1.0F / 6) * inv_t6 * (420 * dist - 216 * v0t1 - 204 * v1t1 - 45 * a0t2 + 39 * a1t2 - 4 * j0t3 - 3 * j1t3);
    p->k[7] = (1.0F / 6) * inv_t7 * (-120 * dist + 60 * (v0t1 + v1t1) + 12 * (a0t2 - a1t2) + j0t3 + j1t3);
}

float polynomial7_pos(const polynomial7_t *p,
                      float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    float t4 = t2 * t2;
    float t5 = t2 * t3;
    float t6 = t3 * t3;
    float t7 = t3 * t4;
    return (p->k[0] +
            p->k[1] * t1 +
            p->k[2] * t2 +
            p->k[3] * t3 +
            p->k[4] * t4 +
            p->k[5] * t5 +
            p->k[6] * t6 +
            p->k[7] * t7);
}

float polynomial7_vec(const polynomial7_t *p,
                      float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    float t4 = t2 * t2;
    float t5 = t2 * t3;
    float t6 = t3 * t3;
    return (p->k[1] +
            p->k[2] * t1 * 2 +
            p->k[3] * t2 * 3 +
            p->k[4] * t3 * 4 +
            p->k[5] * t4 * 5 +
            p->k[6] * t5 * 6 +
            p->k[7] * t6 * 7);
}

float polynomial7_acc(const polynomial7_t *p,
                      float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    float t4 = t2 * t2;
    float t5 = t2 * t3;
    return (p->k[2] * 2 +
            p->k[3] * t1 * 6 +
            p->k[4] * t2 * 12 +
            p->k[5] * t3 * 20 +
            p->k[6] * t4 * 30 +
            p->k[7] * t5 * 42);
}

float polynomial7_jer(const polynomial7_t *p,
                      float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    float t4 = t2 * t2;
    return (p->k[3] * 6 +
            p->k[4] * t1 * 24 +
            p->k[5] * t2 * 60 +
            p->k[6] * t3 * 120 +
            p->k[7] * t4 * 210);
}

void polynomial7_all(const polynomial7_t *p,
                     float out[4],
                     float t)
{
    float t1 = t - p->t[0];
    float t2 = t1 * t1;
    float t3 = t1 * t2;
    float t4 = t2 * t2;
    float t5 = t2 * t3;
    float t6 = t3 * t3;
    float t7 = t3 * t4;
    out[0] = p->k[0] +
             p->k[1] * t1 +
             p->k[2] * t2 +
             p->k[3] * t3 +
             p->k[4] * t4 +
             p->k[5] * t5 +
             p->k[6] * t6 +
             p->k[7] * t7;
    out[1] = p->k[1] +
             p->k[2] * t1 * 2 +
             p->k[3] * t2 * 3 +
             p->k[4] * t3 * 4 +
             p->k[5] * t4 * 5 +
             p->k[6] * t5 * 6 +
             p->k[7] * t6 * 7;
    out[2] = p->k[2] * 2 +
             p->k[3] * t1 * 6 +
             p->k[4] * t2 * 12 +
             p->k[5] * t3 * 20 +
             p->k[6] * t4 * 30 +
             p->k[7] * t5 * 42;
    out[3] = p->k[3] * 6 +
             p->k[4] * t1 * 24 +
             p->k[5] * t2 * 60 +
             p->k[6] * t3 * 120 +
             p->k[7] * t4 * 210;
}

/* END OF FILE */
