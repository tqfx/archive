/*!
 @file           a_polytrack.c
 @brief          polynomial trajectory
 @details        Trajectory Planning for Automatic Machines and Robots.
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

#include "a_polytrack.h"

#undef __A_POLYTRACK3_INIT
#define __A_POLYTRACK3_INIT(bit)                               \
    void a_polytrack3_f##bit##_init(                           \
        a_polytrack3_f##bit##_t *ctx,                          \
        const float##bit##_t source[3],                        \
        const float##bit##_t target[3])                        \
    {                                                          \
        ctx->t[0] = source[0];                                 \
        ctx->q[0] = source[1];                                 \
        ctx->v[0] = source[2];                                 \
        ctx->t[1] = target[0];                                 \
        ctx->q[1] = target[1];                                 \
        ctx->v[1] = target[2];                                 \
                                                               \
        float##bit##_t dist = ctx->q[1] - ctx->q[0];           \
        float##bit##_t t1 = ctx->t[1] - ctx->t[0];             \
        float##bit##_t inv_t1 = 1 / t1;                        \
        float##bit##_t inv_t2 = inv_t1 * inv_t1;               \
        float##bit##_t inv_t3 = inv_t1 * inv_t2;               \
        float##bit##_t vt = (ctx->v[0] + ctx->v[1]) * t1;      \
                                                               \
        ctx->k[0] = ctx->q[0];                                 \
        ctx->k[1] = ctx->v[0];                                 \
        ctx->k[2] = inv_t2 * (3 * dist - ctx->v[0] * t1 - vt); \
        ctx->k[3] = inv_t3 * (vt - 2 * dist);                  \
    }
__A_POLYTRACK3_INIT(32)
__A_POLYTRACK3_INIT(64)

#undef __A_POLYTRACK3_POS
#define __A_POLYTRACK3_POS(bit)               \
    float##bit##_t a_polytrack3_f##bit##_pos( \
        const a_polytrack3_f##bit##_t *ctx,   \
        const float##bit##_t t)               \
    {                                         \
        float##bit##_t t1 = t - ctx->t[0];    \
        float##bit##_t t2 = t1 * t1;          \
        float##bit##_t t3 = t1 * t2;          \
        return (ctx->k[0] +                   \
                ctx->k[1] * t1 +              \
                ctx->k[2] * t2 +              \
                ctx->k[3] * t3);              \
    }
__A_POLYTRACK3_POS(32)
__A_POLYTRACK3_POS(64)

#undef __A_POLYTRACK3_VEC
#define __A_POLYTRACK3_VEC(bit)               \
    float##bit##_t a_polytrack3_f##bit##_vec( \
        const a_polytrack3_f##bit##_t *ctx,   \
        const float##bit##_t t)               \
    {                                         \
        float##bit##_t t1 = t - ctx->t[0];    \
        float##bit##_t t2 = t1 * t1;          \
        return (ctx->k[1] +                   \
                ctx->k[2] * t1 * 2 +          \
                ctx->k[3] * t2 * 3);          \
    }
__A_POLYTRACK3_VEC(32)
__A_POLYTRACK3_VEC(64)

#undef __A_POLYTRACK3_ACC
#define __A_POLYTRACK3_ACC(bit)               \
    float##bit##_t a_polytrack3_f##bit##_acc( \
        const a_polytrack3_f##bit##_t *ctx,   \
        const float##bit##_t t)               \
    {                                         \
        float##bit##_t t1 = t - ctx->t[0];    \
        return (ctx->k[2] * 2 +               \
                ctx->k[3] * t1 * 6);          \
    }
__A_POLYTRACK3_ACC(32)
__A_POLYTRACK3_ACC(64)

#undef __A_POLYTRACK3_ALL
#define __A_POLYTRACK3_ALL(bit)             \
    void a_polytrack3_f##bit##_all(         \
        const a_polytrack3_f##bit##_t *ctx, \
        const float##bit##_t t,             \
        float##bit##_t o[3])                \
    {                                       \
        float##bit##_t t1 = t - ctx->t[0];  \
        float##bit##_t t2 = t1 * t1;        \
        float##bit##_t t3 = t1 * t2;        \
        o[0] = ctx->k[0] +                  \
               ctx->k[1] * t1 +             \
               ctx->k[2] * t2 +             \
               ctx->k[3] * t3;              \
        o[1] = ctx->k[1] +                  \
               ctx->k[2] * t1 * 2 +         \
               ctx->k[3] * t2 * 3;          \
        o[2] = ctx->k[2] * 2 +              \
               ctx->k[3] * t1 * 6;          \
    }
__A_POLYTRACK3_ALL(32)
__A_POLYTRACK3_ALL(64)

#undef __A_POLYTRACK5_INIT
#define __A_POLYTRACK5_INIT(bit)                                                \
    void a_polytrack5_f##bit##_init(                                            \
        a_polytrack5_f##bit##_t *ctx,                                           \
        const float##bit##_t source[4],                                         \
        const float##bit##_t target[4])                                         \
    {                                                                           \
        ctx->t[0] = source[0];                                                  \
        ctx->q[0] = source[1];                                                  \
        ctx->v[0] = source[2];                                                  \
        ctx->a[0] = source[3];                                                  \
        ctx->t[1] = target[0];                                                  \
        ctx->q[1] = target[1];                                                  \
        ctx->v[1] = target[2];                                                  \
        ctx->a[1] = target[3];                                                  \
                                                                                \
        float##bit##_t dist = ctx->q[1] - ctx->q[0];                            \
        float##bit##_t t1 = ctx->t[1] - ctx->t[0];                              \
        float##bit##_t t2 = t1 * t1;                                            \
        float##bit##_t inv_t1 = 1 / t1;                                         \
        float##bit##_t inv_t2 = inv_t1 * inv_t1;                                \
        float##bit##_t inv_t3 = inv_t1 * inv_t2;                                \
        float##bit##_t inv_t4 = inv_t2 * inv_t2;                                \
        float##bit##_t inv_t5 = inv_t2 * inv_t3;                                \
        float##bit##_t v0t1 = ctx->v[0] * t1;                                   \
        float##bit##_t v1t1 = ctx->v[1] * t1;                                   \
        float##bit##_t a0t2 = ctx->a[0] * t2;                                   \
        float##bit##_t a1t2 = ctx->a[1] * t2;                                   \
                                                                                \
        ctx->k[0] = ctx->q[0];                                                  \
        ctx->k[1] = ctx->v[0];                                                  \
        ctx->k[2] = ctx->a[0] * (float##bit##_t)(1 / 2.0);                      \
        ctx->k[3] = (float##bit##_t)(1 / 2.0) * inv_t3 *                        \
                    (20 * dist - 8 * v1t1 - 12 * v0t1 + a1t2 - 3 * a0t2);       \
        ctx->k[4] = (float##bit##_t)(1 / 2.0) * inv_t4 *                        \
                    (-30 * dist + 14 * v1t1 + 16 * v0t1 + 3 * a0t2 - 2 * a1t2); \
        ctx->k[5] = (float##bit##_t)(1 / 2.0) * inv_t5 *                        \
                    (12 * dist - 6 * (v1t1 + v0t1) + a1t2 - a0t2);              \
    }
__A_POLYTRACK5_INIT(32)
__A_POLYTRACK5_INIT(64)

#undef __A_POLYTRACK5_POS
#define __A_POLYTRACK5_POS(bit)               \
    float##bit##_t a_polytrack5_f##bit##_pos( \
        const a_polytrack5_f##bit##_t *ctx,   \
        const float##bit##_t t)               \
    {                                         \
        float##bit##_t t1 = t - ctx->t[0];    \
        float##bit##_t t2 = t1 * t1;          \
        float##bit##_t t3 = t1 * t2;          \
        float##bit##_t t4 = t2 * t2;          \
        float##bit##_t t5 = t2 * t3;          \
        return (ctx->k[0] +                   \
                ctx->k[1] * t1 +              \
                ctx->k[2] * t2 +              \
                ctx->k[3] * t3 +              \
                ctx->k[4] * t4 +              \
                ctx->k[5] * t5);              \
    }
__A_POLYTRACK5_POS(32)
__A_POLYTRACK5_POS(64)

#undef __A_POLYTRACK5_VEC
#define __A_POLYTRACK5_VEC(bit)               \
    float##bit##_t a_polytrack5_f##bit##_vec( \
        const a_polytrack5_f##bit##_t *ctx,   \
        const float##bit##_t t)               \
    {                                         \
        float##bit##_t t1 = t - ctx->t[0];    \
        float##bit##_t t2 = t1 * t1;          \
        float##bit##_t t3 = t1 * t2;          \
        float##bit##_t t4 = t2 * t2;          \
        return (ctx->k[1] +                   \
                ctx->k[2] * t1 * 2 +          \
                ctx->k[3] * t2 * 3 +          \
                ctx->k[4] * t3 * 4 +          \
                ctx->k[5] * t4 * 5);          \
    }
__A_POLYTRACK5_VEC(32)
__A_POLYTRACK5_VEC(64)

#undef __A_POLYTRACK5_ACC
#define __A_POLYTRACK5_ACC(bit)               \
    float##bit##_t a_polytrack5_f##bit##_acc( \
        const a_polytrack5_f##bit##_t *ctx,   \
        const float##bit##_t t)               \
    {                                         \
        float##bit##_t t1 = t - ctx->t[0];    \
        float##bit##_t t2 = t1 * t1;          \
        float##bit##_t t3 = t1 * t2;          \
        return (ctx->k[2] * 2 +               \
                ctx->k[3] * t1 * 6 +          \
                ctx->k[4] * t2 * 12 +         \
                ctx->k[5] * t3 * 20);         \
    }
__A_POLYTRACK5_ACC(32)
__A_POLYTRACK5_ACC(64)

#undef __A_POLYTRACK5_ALL
#define __A_POLYTRACK5_ALL(bit)             \
    void a_polytrack5_f##bit##_all(         \
        const a_polytrack5_f##bit##_t *ctx, \
        const float##bit##_t t,             \
        float##bit##_t o[3])                \
    {                                       \
        float##bit##_t t1 = t - ctx->t[0];  \
        float##bit##_t t2 = t1 * t1;        \
        float##bit##_t t3 = t1 * t2;        \
        float##bit##_t t4 = t2 * t2;        \
        float##bit##_t t5 = t2 * t3;        \
        o[0] = ctx->k[0] +                  \
               ctx->k[1] * t1 +             \
               ctx->k[2] * t2 +             \
               ctx->k[3] * t3 +             \
               ctx->k[4] * t4 +             \
               ctx->k[5] * t5;              \
        o[1] = ctx->k[1] +                  \
               ctx->k[2] * t1 * 2 +         \
               ctx->k[3] * t2 * 3 +         \
               ctx->k[4] * t3 * 4 +         \
               ctx->k[5] * t4 * 5;          \
        o[2] = ctx->k[2] * 2 +              \
               ctx->k[3] * t1 * 6 +         \
               ctx->k[4] * t2 * 12 +        \
               ctx->k[5] * t3 * 20;         \
    }
__A_POLYTRACK5_ALL(32)
__A_POLYTRACK5_ALL(64)

#undef __A_POLYTRACK7_INIT
#define __A_POLYTRACK7_INIT(bit)                                   \
    void a_polytrack7_f##bit##_init(                               \
        a_polytrack7_f##bit##_t *ctx,                              \
        const float##bit##_t source[5],                            \
        const float##bit##_t target[5])                            \
    {                                                              \
        ctx->t[0] = source[0];                                     \
        ctx->q[0] = source[1];                                     \
        ctx->v[0] = source[2];                                     \
        ctx->a[0] = source[3];                                     \
        ctx->j[0] = source[4];                                     \
        ctx->t[1] = target[0];                                     \
        ctx->q[1] = target[1];                                     \
        ctx->v[1] = target[2];                                     \
        ctx->a[1] = target[3];                                     \
        ctx->j[1] = target[4];                                     \
                                                                   \
        float##bit##_t dist = ctx->q[1] - ctx->q[0];               \
        float##bit##_t t1 = ctx->t[1] - ctx->t[0];                 \
        float##bit##_t t2 = t1 * t1;                               \
        float##bit##_t t3 = t1 * t2;                               \
        float##bit##_t inv_t1 = 1 / t1;                            \
        float##bit##_t inv_t2 = inv_t1 * inv_t1;                   \
        float##bit##_t inv_t3 = inv_t1 * inv_t2;                   \
        float##bit##_t inv_t4 = inv_t2 * inv_t2;                   \
        float##bit##_t inv_t5 = inv_t2 * inv_t3;                   \
        float##bit##_t inv_t6 = inv_t3 * inv_t3;                   \
        float##bit##_t inv_t7 = inv_t3 * inv_t4;                   \
        float##bit##_t v0t1 = ctx->v[0] * t1;                      \
        float##bit##_t v1t1 = ctx->v[1] * t1;                      \
        float##bit##_t a0t2 = ctx->a[0] * t2;                      \
        float##bit##_t a1t2 = ctx->a[1] * t2;                      \
        float##bit##_t j0t3 = ctx->j[0] * t3;                      \
        float##bit##_t j1t3 = ctx->j[1] * t3;                      \
                                                                   \
        ctx->k[0] = ctx->q[0];                                     \
        ctx->k[1] = ctx->v[0];                                     \
        ctx->k[2] = ctx->a[0] * (float##bit##_t)(1 / 2.0);         \
        ctx->k[3] = ctx->j[0] * (float##bit##_t)(1 / 6.0);         \
        ctx->k[4] = (float##bit##_t)(1 / 6.0) * inv_t4 *           \
                    (210 * dist - 120 * v0t1 - 90 * v0t1 -         \
                     30 * a0t2 + 15 * a1t2 - 4 * j0t3 - j1t3);     \
        ctx->k[5] = (float##bit##_t)(1 / 2.0) * inv_t5 *           \
                    (-168 * dist + 90 * v0t1 + 78 * v1t1 +         \
                     20 * a0t2 - 14 * a1t2 + 2 * j0t3 + j1t3);     \
        ctx->k[6] = (float##bit##_t)(1 / 6.0) * inv_t6 *           \
                    (420 * dist - 216 * v0t1 - 204 * v1t1 -        \
                     45 * a0t2 + 39 * a1t2 - 4 * j0t3 - 3 * j1t3); \
        ctx->k[7] = (float##bit##_t)(1 / 6.0) * inv_t7 *           \
                    (-120 * dist + 60 * (v0t1 + v1t1) +            \
                     12 * (a0t2 - a1t2) + j0t3 + j1t3);            \
    }
__A_POLYTRACK7_INIT(32)
__A_POLYTRACK7_INIT(64)

#undef __A_POLYTRACK7_POS
#define __A_POLYTRACK7_POS(bit)               \
    float##bit##_t a_polytrack7_f##bit##_pos( \
        const a_polytrack7_f##bit##_t *ctx,   \
        const float##bit##_t t)               \
    {                                         \
        float##bit##_t t1 = t - ctx->t[0];    \
        float##bit##_t t2 = t1 * t1;          \
        float##bit##_t t3 = t1 * t2;          \
        float##bit##_t t4 = t2 * t2;          \
        float##bit##_t t5 = t2 * t3;          \
        float##bit##_t t6 = t3 * t3;          \
        float##bit##_t t7 = t3 * t4;          \
        return (ctx->k[0] +                   \
                ctx->k[1] * t1 +              \
                ctx->k[2] * t2 +              \
                ctx->k[3] * t3 +              \
                ctx->k[4] * t4 +              \
                ctx->k[5] * t5 +              \
                ctx->k[6] * t6 +              \
                ctx->k[7] * t7);              \
    }
__A_POLYTRACK7_POS(32)
__A_POLYTRACK7_POS(64)

#undef __A_POLYTRACK7_VEC
#define __A_POLYTRACK7_VEC(bit)               \
    float##bit##_t a_polytrack7_f##bit##_vec( \
        const a_polytrack7_f##bit##_t *ctx,   \
        const float##bit##_t t)               \
    {                                         \
        float##bit##_t t1 = t - ctx->t[0];    \
        float##bit##_t t2 = t1 * t1;          \
        float##bit##_t t3 = t1 * t2;          \
        float##bit##_t t4 = t2 * t2;          \
        float##bit##_t t5 = t2 * t3;          \
        float##bit##_t t6 = t3 * t3;          \
        return (ctx->k[1] +                   \
                ctx->k[2] * t1 * 2 +          \
                ctx->k[3] * t2 * 3 +          \
                ctx->k[4] * t3 * 4 +          \
                ctx->k[5] * t4 * 5 +          \
                ctx->k[6] * t5 * 6 +          \
                ctx->k[7] * t6 * 7);          \
    }
__A_POLYTRACK7_VEC(32)
__A_POLYTRACK7_VEC(64)

#undef __A_POLYTRACK7_ACC
#define __A_POLYTRACK7_ACC(bit)               \
    float##bit##_t a_polytrack7_f##bit##_acc( \
        const a_polytrack7_f##bit##_t *ctx,   \
        const float##bit##_t t)               \
    {                                         \
        float##bit##_t t1 = t - ctx->t[0];    \
        float##bit##_t t2 = t1 * t1;          \
        float##bit##_t t3 = t1 * t2;          \
        float##bit##_t t4 = t2 * t2;          \
        float##bit##_t t5 = t2 * t3;          \
        return (ctx->k[2] * 2 +               \
                ctx->k[3] * t1 * 6 +          \
                ctx->k[4] * t2 * 12 +         \
                ctx->k[5] * t3 * 20 +         \
                ctx->k[6] * t4 * 30 +         \
                ctx->k[7] * t5 * 42);         \
    }
__A_POLYTRACK7_ACC(32)
__A_POLYTRACK7_ACC(64)

#undef __A_POLYTRACK7_JER
#define __A_POLYTRACK7_JER(bit)               \
    float##bit##_t a_polytrack7_f##bit##_jer( \
        const a_polytrack7_f##bit##_t *ctx,   \
        const float##bit##_t t)               \
    {                                         \
        float##bit##_t t1 = t - ctx->t[0];    \
        float##bit##_t t2 = t1 * t1;          \
        float##bit##_t t3 = t1 * t2;          \
        float##bit##_t t4 = t2 * t2;          \
        return (ctx->k[3] * 6 +               \
                ctx->k[4] * t1 * 24 +         \
                ctx->k[5] * t2 * 60 +         \
                ctx->k[6] * t3 * 120 +        \
                ctx->k[7] * t4 * 210);        \
    }
__A_POLYTRACK7_JER(32)
__A_POLYTRACK7_JER(64)

#undef __A_POLYTRACK7_ALL
#define __A_POLYTRACK7_ALL(bit)             \
    void a_polytrack7_f##bit##_all(         \
        const a_polytrack7_f##bit##_t *ctx, \
        const float##bit##_t t,             \
        float##bit##_t o[4])                \
    {                                       \
        float##bit##_t t1 = t - ctx->t[0];  \
        float##bit##_t t2 = t1 * t1;        \
        float##bit##_t t3 = t1 * t2;        \
        float##bit##_t t4 = t2 * t2;        \
        float##bit##_t t5 = t2 * t3;        \
        float##bit##_t t6 = t3 * t3;        \
        float##bit##_t t7 = t3 * t4;        \
        o[0] = ctx->k[0] +                  \
               ctx->k[1] * t1 +             \
               ctx->k[2] * t2 +             \
               ctx->k[3] * t3 +             \
               ctx->k[4] * t4 +             \
               ctx->k[5] * t5 +             \
               ctx->k[6] * t6 +             \
               ctx->k[7] * t7;              \
        o[1] = ctx->k[1] +                  \
               ctx->k[2] * t1 * 2 +         \
               ctx->k[3] * t2 * 3 +         \
               ctx->k[4] * t3 * 4 +         \
               ctx->k[5] * t4 * 5 +         \
               ctx->k[6] * t5 * 6 +         \
               ctx->k[7] * t6 * 7;          \
        o[2] = ctx->k[2] * 2 +              \
               ctx->k[3] * t1 * 6 +         \
               ctx->k[4] * t2 * 12 +        \
               ctx->k[5] * t3 * 20 +        \
               ctx->k[6] * t4 * 30 +        \
               ctx->k[7] * t5 * 42;         \
        o[3] = ctx->k[3] * 6 +              \
               ctx->k[4] * t1 * 24 +        \
               ctx->k[5] * t2 * 60 +        \
               ctx->k[6] * t3 * 120 +       \
               ctx->k[7] * t4 * 210;        \
    }
__A_POLYTRACK7_ALL(32)
__A_POLYTRACK7_ALL(64)

/* END OF FILE */
