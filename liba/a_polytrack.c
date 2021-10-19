/*!
 @file           a_polytrack.c
 @brief          polynomial trajectory
 @details        Trajectory Planning for Automatic Machines and Robots.
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_polytrack.h"
#include "a_poly.h"

/* function for cubic polynomial trajectory */

#undef __A_POLYTRACK3_INIT
#define __A_POLYTRACK3_INIT(def, type, func)                            \
    void func(def##_t *ctx, const type source[3], const type target[3]) \
    {                                                                   \
        ctx->t[0] = source[0];                                          \
        ctx->q[0] = source[1];                                          \
        ctx->v[0] = source[2];                                          \
        ctx->t[1] = target[0];                                          \
        ctx->q[1] = target[1];                                          \
        ctx->v[1] = target[2];                                          \
                                                                        \
        type q = ctx->q[1] - ctx->q[0];                                 \
        type t = ctx->t[1] - ctx->t[0];                                 \
        type inv_t1 = 1 / t;                                            \
        type inv_t2 = inv_t1 * inv_t1;                                  \
        type inv_t3 = inv_t1 * inv_t2;                                  \
                                                                        \
        ctx->k[0] = ctx->q[0];                                          \
        ctx->k[1] = ctx->v[0];                                          \
        ctx->k[2] = inv_t1 * (-2 * ctx->v[0] - ctx->v[1]) +             \
                    inv_t2 * q * 3;                                     \
        ctx->k[3] = inv_t2 * (ctx->v[0] + ctx->v[1]) -                  \
                    inv_t3 * q * 2;                                     \
    }
__A_POLYTRACK3_INIT(a_polytrack3, double, a_polytrack3_init)
__A_POLYTRACK3_INIT(a_polytrack3f, float, a_polytrack3f_init)
#undef __A_POLYTRACK3_INIT

#undef __A_POLYTRACK3_POS
#define __A_POLYTRACK3_POS(def, type, func, poly) \
    type func(const def##_t *ctx, type t)         \
    {                                             \
        type a[4] = {                             \
            ctx->k[3],                            \
            ctx->k[2],                            \
            ctx->k[1],                            \
            ctx->k[0],                            \
        };                                        \
        return poly(a, 4, t - ctx->t[0]);         \
    }
__A_POLYTRACK3_POS(a_polytrack3, double, a_polytrack3_pos, a_horner)
__A_POLYTRACK3_POS(a_polytrack3f, float, a_polytrack3f_pos, a_hornerf)
#undef __A_POLYTRACK3_POS

#undef __A_POLYTRACK3_VEC
#define __A_POLYTRACK3_VEC(def, type, func, poly) \
    type func(const def##_t *ctx, type t)         \
    {                                             \
        type a[3] = {                             \
            ctx->k[3] * 3,                        \
            ctx->k[2] * 2,                        \
            ctx->k[1],                            \
        };                                        \
        return poly(a, 3, t - ctx->t[0]);         \
    }
__A_POLYTRACK3_VEC(a_polytrack3, double, a_polytrack3_vec, a_horner)
__A_POLYTRACK3_VEC(a_polytrack3f, float, a_polytrack3f_vec, a_hornerf)
#undef __A_POLYTRACK3_VEC

#undef __A_POLYTRACK3_ACC
#define __A_POLYTRACK3_ACC(def, type, func, poly) \
    type func(const def##_t *ctx, type t)         \
    {                                             \
        type a[2] = {                             \
            ctx->k[3] * 3 * 2,                    \
            ctx->k[2] * 2,                        \
        };                                        \
        return poly(a, 2, t - ctx->t[0]);         \
    }
__A_POLYTRACK3_ACC(a_polytrack3, double, a_polytrack3_acc, a_horner)
__A_POLYTRACK3_ACC(a_polytrack3f, float, a_polytrack3f_acc, a_hornerf)
#undef __A_POLYTRACK3_ACC

#undef __A_POLYTRACK3_ALL
#define __A_POLYTRACK3_ALL(def, type, func, poly)    \
    void func(const def##_t *ctx, type t, type o[3]) \
    {                                                \
        type a[4] = {                                \
            ctx->k[3],                               \
            ctx->k[2],                               \
            ctx->k[1],                               \
            ctx->k[0],                               \
        };                                           \
        t = t - ctx->t[0];                           \
        o[0] = poly(a, 4, t);                        \
        a[0] *= 3;                                   \
        a[1] *= 2;                                   \
        o[1] = poly(a, 3, t);                        \
        a[0] *= 2;                                   \
        o[2] = poly(a, 2, t);                        \
    }
__A_POLYTRACK3_ALL(a_polytrack3, double, a_polytrack3_all, a_horner)
__A_POLYTRACK3_ALL(a_polytrack3f, float, a_polytrack3f_all, a_hornerf)
#undef __A_POLYTRACK3_ALL

/* function for quintic polynomial trajectory */

#undef __A_POLYTRACK5_INIT
#define __A_POLYTRACK5_INIT(def, type, func)                            \
    void func(def##_t *ctx, const type source[4], const type target[4]) \
    {                                                                   \
        ctx->t[0] = source[0];                                          \
        ctx->q[0] = source[1];                                          \
        ctx->v[0] = source[2];                                          \
        ctx->a[0] = source[3];                                          \
        ctx->t[1] = target[0];                                          \
        ctx->q[1] = target[1];                                          \
        ctx->v[1] = target[2];                                          \
        ctx->a[1] = target[3];                                          \
                                                                        \
        type q = ctx->q[1] - ctx->q[0];                                 \
        type t = ctx->t[1] - ctx->t[0];                                 \
        type inv_t1 = 1 / t;                                            \
        type inv_t2 = inv_t1 * inv_t1;                                  \
        type inv_t3 = inv_t1 * inv_t2;                                  \
        type inv_t4 = inv_t2 * inv_t2;                                  \
        type inv_t5 = inv_t2 * inv_t3;                                  \
                                                                        \
        ctx->k[0] = ctx->q[0];                                          \
        ctx->k[1] = ctx->v[0];                                          \
        ctx->k[2] = ctx->a[0] * (type)(1 / 2.0);                        \
        ctx->k[3] = (inv_t1 * (ctx->a[1] - 3 * ctx->a[0]) -             \
                     inv_t2 * (12 * ctx->v[0] + 8 * ctx->v[1]) +        \
                     inv_t3 * q * 20) *                                 \
                    (type)(1 / 2.0);                                    \
        ctx->k[4] = (inv_t2 * (3 * ctx->a[0] - 2 * ctx->a[1]) +         \
                     inv_t3 * (16 * ctx->v[0] + 14 * ctx->v[1]) -       \
                     inv_t4 * q * 30) *                                 \
                    (type)(1 / 2.0);                                    \
        ctx->k[5] = (inv_t3 * (ctx->a[1] - ctx->a[0]) -                 \
                     inv_t4 * (ctx->v[0] + ctx->v[1]) * 6 +             \
                     inv_t5 * q * 12) *                                 \
                    (type)(1 / 2.0);                                    \
    }
__A_POLYTRACK5_INIT(a_polytrack5, double, a_polytrack5_init)
__A_POLYTRACK5_INIT(a_polytrack5f, float, a_polytrack5f_init)
#undef __A_POLYTRACK5_INIT

#undef __A_POLYTRACK5_POS
#define __A_POLYTRACK5_POS(def, type, func, poly) \
    type func(const def##_t *ctx, type t)         \
    {                                             \
        type a[6] = {                             \
            ctx->k[5],                            \
            ctx->k[4],                            \
            ctx->k[3],                            \
            ctx->k[2],                            \
            ctx->k[1],                            \
            ctx->k[0],                            \
        };                                        \
        return poly(a, 6, t - ctx->t[0]);         \
    }
__A_POLYTRACK5_POS(a_polytrack5, double, a_polytrack5_pos, a_horner)
__A_POLYTRACK5_POS(a_polytrack5f, float, a_polytrack5f_pos, a_hornerf)
#undef __A_POLYTRACK5_POS

#undef __A_POLYTRACK5_VEC
#define __A_POLYTRACK5_VEC(def, type, func, poly) \
    type func(const def##_t *ctx, type t)         \
    {                                             \
        type a[5] = {                             \
            ctx->k[5] * 5,                        \
            ctx->k[4] * 4,                        \
            ctx->k[3] * 3,                        \
            ctx->k[2] * 2,                        \
            ctx->k[1],                            \
        };                                        \
        return poly(a, 5, t - ctx->t[0]);         \
    }
__A_POLYTRACK5_VEC(a_polytrack5, double, a_polytrack5_vec, a_horner)
__A_POLYTRACK5_VEC(a_polytrack5f, float, a_polytrack5f_vec, a_hornerf)
#undef __A_POLYTRACK5_VEC

#undef __A_POLYTRACK5_ACC
#define __A_POLYTRACK5_ACC(def, type, func, poly) \
    type func(const def##_t *ctx, type t)         \
    {                                             \
        type a[4] = {                             \
            ctx->k[5] * 5 * 4,                    \
            ctx->k[4] * 4 * 3,                    \
            ctx->k[3] * 3 * 2,                    \
            ctx->k[2] * 2,                        \
        };                                        \
        return poly(a, 4, t - ctx->t[0]);         \
    }
__A_POLYTRACK5_ACC(a_polytrack5, double, a_polytrack5_acc, a_horner)
__A_POLYTRACK5_ACC(a_polytrack5f, float, a_polytrack5f_acc, a_hornerf)
#undef __A_POLYTRACK5_ACC

#undef __A_POLYTRACK5_ALL
#define __A_POLYTRACK5_ALL(def, type, func, poly)    \
    void func(const def##_t *ctx, type t, type o[3]) \
    {                                                \
        type a[6] = {                                \
            ctx->k[5],                               \
            ctx->k[4],                               \
            ctx->k[3],                               \
            ctx->k[2],                               \
            ctx->k[1],                               \
            ctx->k[0],                               \
        };                                           \
        t = t - ctx->t[0];                           \
        o[0] = poly(a, 6, t);                        \
        a[0] *= 5;                                   \
        a[1] *= 4;                                   \
        a[2] *= 3;                                   \
        a[3] *= 2;                                   \
        o[1] = poly(a, 5, t);                        \
        a[0] *= 4;                                   \
        a[1] *= 3;                                   \
        a[2] *= 2;                                   \
        o[2] = poly(a, 4, t);                        \
    }
__A_POLYTRACK5_ALL(a_polytrack5, double, a_polytrack5_all, a_horner)
__A_POLYTRACK5_ALL(a_polytrack5f, float, a_polytrack5f_all, a_hornerf)
#undef __A_POLYTRACK5_ALL

/* function for hepta polynomial trajectory */

#undef __A_POLYTRACK7_INIT
#define __A_POLYTRACK7_INIT(def, type, func)                            \
    void func(def##_t *ctx, const type source[5], const type target[5]) \
    {                                                                   \
        ctx->t[0] = source[0];                                          \
        ctx->q[0] = source[1];                                          \
        ctx->v[0] = source[2];                                          \
        ctx->a[0] = source[3];                                          \
        ctx->j[0] = source[4];                                          \
        ctx->t[1] = target[0];                                          \
        ctx->q[1] = target[1];                                          \
        ctx->v[1] = target[2];                                          \
        ctx->a[1] = target[3];                                          \
        ctx->j[1] = target[4];                                          \
                                                                        \
        type q = ctx->q[1] - ctx->q[0];                                 \
        type t = ctx->t[1] - ctx->t[0];                                 \
        type inv_t1 = 1 / t;                                            \
        type inv_t2 = inv_t1 * inv_t1;                                  \
        type inv_t3 = inv_t1 * inv_t2;                                  \
        type inv_t4 = inv_t2 * inv_t2;                                  \
        type inv_t5 = inv_t2 * inv_t3;                                  \
        type inv_t6 = inv_t3 * inv_t3;                                  \
        type inv_t7 = inv_t3 * inv_t4;                                  \
                                                                        \
        ctx->k[0] = ctx->q[0];                                          \
        ctx->k[1] = ctx->v[0];                                          \
        ctx->k[2] = ctx->a[0] * (type)(1 / 2.0);                        \
        ctx->k[3] = ctx->j[0] * (type)(1 / 6.0);                        \
        ctx->k[4] = (inv_t1 * (-4 * ctx->j[0] - ctx->j[1]) +            \
                     inv_t2 * (15 * ctx->a[1] - 30 * ctx->a[0]) -       \
                     inv_t3 * (120 * ctx->v[0] + 90 * ctx->v[1]) +      \
                     inv_t4 * q * 210) *                                \
                    (type)(1 / 6.0);                                    \
        ctx->k[5] = (inv_t2 * (2 * ctx->j[0] + ctx->j[1]) +             \
                     inv_t3 * (20 * ctx->a[0] - 14 * ctx->a[1]) +       \
                     inv_t4 * (90 * ctx->v[0] + 78 * ctx->v[1]) -       \
                     inv_t5 * q * 168) *                                \
                    (type)(1 / 2.0);                                    \
        ctx->k[6] = (inv_t3 * (-4 * ctx->j[0] - 3 * ctx->j[1]) +        \
                     inv_t4 * (39 * ctx->a[1] - 45 * ctx->a[0]) -       \
                     inv_t5 * (216 * ctx->v[0] + 204 * ctx->v[1]) +     \
                     inv_t6 * q * 420) *                                \
                    (type)(1 / 6.0);                                    \
        ctx->k[7] = (inv_t4 * (ctx->j[0] + ctx->j[1]) +                 \
                     inv_t5 * (ctx->a[0] - ctx->a[1]) * 12 +            \
                     inv_t6 * (ctx->v[0] + ctx->v[1]) * 60 -            \
                     inv_t7 * q * 120) *                                \
                    (type)(1 / 6.0);                                    \
    }
__A_POLYTRACK7_INIT(a_polytrack7, double, a_polytrack7_init)
__A_POLYTRACK7_INIT(a_polytrack7f, float, a_polytrack7f_init)
#undef __A_POLYTRACK7_INIT

#undef __A_POLYTRACK7_POS
#define __A_POLYTRACK7_POS(def, type, func, poly) \
    type func(const def##_t *ctx, type t)         \
    {                                             \
        type a[8] = {                             \
            ctx->k[7],                            \
            ctx->k[6],                            \
            ctx->k[5],                            \
            ctx->k[4],                            \
            ctx->k[3],                            \
            ctx->k[2],                            \
            ctx->k[1],                            \
            ctx->k[0],                            \
        };                                        \
        return poly(a, 8, t - ctx->t[0]);         \
    }
__A_POLYTRACK7_POS(a_polytrack7, double, a_polytrack7_pos, a_horner)
__A_POLYTRACK7_POS(a_polytrack7f, float, a_polytrack7f_pos, a_hornerf)
#undef __A_POLYTRACK7_POS

#undef __A_POLYTRACK7_VEC
#define __A_POLYTRACK7_VEC(def, type, func, poly) \
    type func(const def##_t *ctx, type t)         \
    {                                             \
        type a[7] = {                             \
            ctx->k[7] * 7,                        \
            ctx->k[6] * 6,                        \
            ctx->k[5] * 5,                        \
            ctx->k[4] * 4,                        \
            ctx->k[3] * 3,                        \
            ctx->k[2] * 2,                        \
            ctx->k[1],                            \
        };                                        \
        return poly(a, 7, t - ctx->t[0]);         \
    }
__A_POLYTRACK7_VEC(a_polytrack7, double, a_polytrack7_vec, a_horner)
__A_POLYTRACK7_VEC(a_polytrack7f, float, a_polytrack7f_vec, a_hornerf)
#undef __A_POLYTRACK7_VEC

#undef __A_POLYTRACK7_ACC
#define __A_POLYTRACK7_ACC(def, type, func, poly) \
    type func(const def##_t *ctx, type t)         \
    {                                             \
        type a[6] = {                             \
            ctx->k[7] * 7 * 6,                    \
            ctx->k[6] * 6 * 5,                    \
            ctx->k[5] * 5 * 4,                    \
            ctx->k[4] * 4 * 3,                    \
            ctx->k[3] * 3 * 2,                    \
            ctx->k[2] * 2,                        \
        };                                        \
        return poly(a, 6, t - ctx->t[0]);         \
    }
__A_POLYTRACK7_ACC(a_polytrack7, double, a_polytrack7_acc, a_horner)
__A_POLYTRACK7_ACC(a_polytrack7f, float, a_polytrack7f_acc, a_hornerf)
#undef __A_POLYTRACK7_ACC

#undef __A_POLYTRACK7_JER
#define __A_POLYTRACK7_JER(def, type, func, poly) \
    type func(const def##_t *ctx, type t)         \
    {                                             \
        type a[5] = {                             \
            ctx->k[7] * 7 * 6 * 5,                \
            ctx->k[6] * 6 * 5 * 4,                \
            ctx->k[5] * 5 * 4 * 3,                \
            ctx->k[4] * 4 * 3 * 2,                \
            ctx->k[3] * 3 * 2,                    \
        };                                        \
        return poly(a, 5, t - ctx->t[0]);         \
    }
__A_POLYTRACK7_JER(a_polytrack7, double, a_polytrack7_jer, a_horner)
__A_POLYTRACK7_JER(a_polytrack7f, float, a_polytrack7f_jer, a_hornerf)
#undef __A_POLYTRACK7_JER

#undef __A_POLYTRACK7_ALL
#define __A_POLYTRACK7_ALL(def, type, func, poly)    \
    void func(const def##_t *ctx, type t, type o[4]) \
    {                                                \
        type a[8] = {                                \
            ctx->k[7],                               \
            ctx->k[6],                               \
            ctx->k[5],                               \
            ctx->k[4],                               \
            ctx->k[3],                               \
            ctx->k[2],                               \
            ctx->k[1],                               \
            ctx->k[0],                               \
        };                                           \
        t = t - ctx->t[0];                           \
        o[0] = poly(a, 8, t);                        \
        a[0] *= 7;                                   \
        a[1] *= 6;                                   \
        a[2] *= 5;                                   \
        a[3] *= 4;                                   \
        a[4] *= 3;                                   \
        a[5] *= 2;                                   \
        o[1] = poly(a, 7, t);                        \
        a[0] *= 6;                                   \
        a[1] *= 5;                                   \
        a[2] *= 4;                                   \
        a[3] *= 3;                                   \
        a[4] *= 2;                                   \
        o[2] = poly(a, 6, t);                        \
        a[0] *= 5;                                   \
        a[1] *= 4;                                   \
        a[2] *= 3;                                   \
        a[3] *= 2;                                   \
        o[3] = poly(a, 5, t);                        \
    }
__A_POLYTRACK7_ALL(a_polytrack7, double, a_polytrack7_all, a_horner)
__A_POLYTRACK7_ALL(a_polytrack7f, float, a_polytrack7f_all, a_hornerf)
#undef __A_POLYTRACK7_ALL

/* END OF FILE */
