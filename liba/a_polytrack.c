/*!
 @file           a_polytrack.c
 @brief          polynomial trajectory
 @details        Trajectory Planning for Automatic Machines and Robots.
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_polytrack.h"

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
        type dist = ctx->q[1] - ctx->q[0];                              \
        type t1 = ctx->t[1] - ctx->t[0];                                \
        type inv_t1 = 1 / t1;                                           \
        type inv_t2 = inv_t1 * inv_t1;                                  \
        type inv_t3 = inv_t1 * inv_t2;                                  \
        type vt = (ctx->v[0] + ctx->v[1]) * t1;                         \
                                                                        \
        ctx->k[0] = ctx->q[0];                                          \
        ctx->k[1] = ctx->v[0];                                          \
        ctx->k[2] = inv_t2 * (3 * dist - ctx->v[0] * t1 - vt);          \
        ctx->k[3] = inv_t3 * (vt - 2 * dist);                           \
    }
__A_POLYTRACK3_INIT(a_polytrack3, double, a_polytrack3_init)
__A_POLYTRACK3_INIT(a_polytrack3f, float, a_polytrack3f_init)
#undef __A_POLYTRACK3_INIT

#undef __A_POLYTRACK3_POS
#define __A_POLYTRACK3_POS(def, type, func) \
    type func(const def##_t *ctx, type t)   \
    {                                       \
        type t1 = t - ctx->t[0];            \
        type t2 = t1 * t1;                  \
        type t3 = t1 * t2;                  \
        return (ctx->k[0] +                 \
                ctx->k[1] * t1 +            \
                ctx->k[2] * t2 +            \
                ctx->k[3] * t3);            \
    }
__A_POLYTRACK3_POS(a_polytrack3, double, a_polytrack3_pos)
__A_POLYTRACK3_POS(a_polytrack3f, float, a_polytrack3f_pos)
#undef __A_POLYTRACK3_POS

#undef __A_POLYTRACK3_VEC
#define __A_POLYTRACK3_VEC(def, type, func) \
    type func(const def##_t *ctx, type t)   \
    {                                       \
        type t1 = t - ctx->t[0];            \
        type t2 = t1 * t1;                  \
        return (ctx->k[1] +                 \
                ctx->k[2] * t1 * 2 +        \
                ctx->k[3] * t2 * 3);        \
    }
__A_POLYTRACK3_VEC(a_polytrack3, double, a_polytrack3_vec)
__A_POLYTRACK3_VEC(a_polytrack3f, float, a_polytrack3f_vec)
#undef __A_POLYTRACK3_VEC

#undef __A_POLYTRACK3_ACC
#define __A_POLYTRACK3_ACC(def, type, func) \
    type func(const def##_t *ctx, type t)   \
    {                                       \
        type t1 = t - ctx->t[0];            \
        return (ctx->k[2] * 2 +             \
                ctx->k[3] * t1 * 6);        \
    }
__A_POLYTRACK3_ACC(a_polytrack3, double, a_polytrack3_acc)
__A_POLYTRACK3_ACC(a_polytrack3f, float, a_polytrack3f_acc)
#undef __A_POLYTRACK3_ACC

#undef __A_POLYTRACK3_ALL
#define __A_POLYTRACK3_ALL(def, type, func)          \
    void func(const def##_t *ctx, type t, type o[3]) \
    {                                                \
        type t1 = t - ctx->t[0];                     \
        type t2 = t1 * t1;                           \
        type t3 = t1 * t2;                           \
        o[0] = ctx->k[0] +                           \
               ctx->k[1] * t1 +                      \
               ctx->k[2] * t2 +                      \
               ctx->k[3] * t3;                       \
        o[1] = ctx->k[1] +                           \
               ctx->k[2] * t1 * 2 +                  \
               ctx->k[3] * t2 * 3;                   \
        o[2] = ctx->k[2] * 2 +                       \
               ctx->k[3] * t1 * 6;                   \
    }
__A_POLYTRACK3_ALL(a_polytrack3, double, a_polytrack3_all)
__A_POLYTRACK3_ALL(a_polytrack3f, float, a_polytrack3f_all)
#undef __A_POLYTRACK3_ALL

/* function for quintic polynomial trajectory */

#undef __A_POLYTRACK5_INIT
#define __A_POLYTRACK5_INIT(def, type, func)                                    \
    void func(def##_t *ctx, const type source[4], const type target[4])         \
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
        type dist = ctx->q[1] - ctx->q[0];                                      \
        type t1 = ctx->t[1] - ctx->t[0];                                        \
        type t2 = t1 * t1;                                                      \
        type inv_t1 = 1 / t1;                                                   \
        type inv_t2 = inv_t1 * inv_t1;                                          \
        type inv_t3 = inv_t1 * inv_t2;                                          \
        type inv_t4 = inv_t2 * inv_t2;                                          \
        type inv_t5 = inv_t2 * inv_t3;                                          \
        type v0t1 = ctx->v[0] * t1;                                             \
        type v1t1 = ctx->v[1] * t1;                                             \
        type a0t2 = ctx->a[0] * t2;                                             \
        type a1t2 = ctx->a[1] * t2;                                             \
                                                                                \
        ctx->k[0] = ctx->q[0];                                                  \
        ctx->k[1] = ctx->v[0];                                                  \
        ctx->k[2] = ctx->a[0] * (type)(1 / 2.0);                                \
        ctx->k[3] = (type)(1 / 2.0) * inv_t3 *                                  \
                    (20 * dist - 8 * v1t1 - 12 * v0t1 + a1t2 - 3 * a0t2);       \
        ctx->k[4] = (type)(1 / 2.0) * inv_t4 *                                  \
                    (-30 * dist + 14 * v1t1 + 16 * v0t1 + 3 * a0t2 - 2 * a1t2); \
        ctx->k[5] = (type)(1 / 2.0) * inv_t5 *                                  \
                    (12 * dist - 6 * (v1t1 + v0t1) + a1t2 - a0t2);              \
    }
__A_POLYTRACK5_INIT(a_polytrack5, double, a_polytrack5_init)
__A_POLYTRACK5_INIT(a_polytrack5f, float, a_polytrack5f_init)
#undef __A_POLYTRACK5_INIT

#undef __A_POLYTRACK5_POS
#define __A_POLYTRACK5_POS(def, type, func) \
    type func(const def##_t *ctx, type t)   \
    {                                       \
        type t1 = t - ctx->t[0];            \
        type t2 = t1 * t1;                  \
        type t3 = t1 * t2;                  \
        type t4 = t2 * t2;                  \
        type t5 = t2 * t3;                  \
        return (ctx->k[0] +                 \
                ctx->k[1] * t1 +            \
                ctx->k[2] * t2 +            \
                ctx->k[3] * t3 +            \
                ctx->k[4] * t4 +            \
                ctx->k[5] * t5);            \
    }
__A_POLYTRACK5_POS(a_polytrack5, double, a_polytrack5_pos)
__A_POLYTRACK5_POS(a_polytrack5f, float, a_polytrack5f_pos)
#undef __A_POLYTRACK5_POS

#undef __A_POLYTRACK5_VEC
#define __A_POLYTRACK5_VEC(def, type, func) \
    type func(const def##_t *ctx, type t)   \
    {                                       \
        type t1 = t - ctx->t[0];            \
        type t2 = t1 * t1;                  \
        type t3 = t1 * t2;                  \
        type t4 = t2 * t2;                  \
        return (ctx->k[1] +                 \
                ctx->k[2] * t1 * 2 +        \
                ctx->k[3] * t2 * 3 +        \
                ctx->k[4] * t3 * 4 +        \
                ctx->k[5] * t4 * 5);        \
    }
__A_POLYTRACK5_VEC(a_polytrack5, double, a_polytrack5_vec)
__A_POLYTRACK5_VEC(a_polytrack5f, float, a_polytrack5f_vec)
#undef __A_POLYTRACK5_VEC

#undef __A_POLYTRACK5_ACC
#define __A_POLYTRACK5_ACC(def, type, func) \
    type func(const def##_t *ctx, type t)   \
    {                                       \
        type t1 = t - ctx->t[0];            \
        type t2 = t1 * t1;                  \
        type t3 = t1 * t2;                  \
        return (ctx->k[2] * 2 +             \
                ctx->k[3] * t1 * 6 +        \
                ctx->k[4] * t2 * 12 +       \
                ctx->k[5] * t3 * 20);       \
    }
__A_POLYTRACK5_ACC(a_polytrack5, double, a_polytrack5_acc)
__A_POLYTRACK5_ACC(a_polytrack5f, float, a_polytrack5f_acc)
#undef __A_POLYTRACK5_ACC

#undef __A_POLYTRACK5_ALL
#define __A_POLYTRACK5_ALL(def, type, func)          \
    void func(const def##_t *ctx, type t, type o[3]) \
    {                                                \
        type t1 = t - ctx->t[0];                     \
        type t2 = t1 * t1;                           \
        type t3 = t1 * t2;                           \
        type t4 = t2 * t2;                           \
        type t5 = t2 * t3;                           \
        o[0] = ctx->k[0] +                           \
               ctx->k[1] * t1 +                      \
               ctx->k[2] * t2 +                      \
               ctx->k[3] * t3 +                      \
               ctx->k[4] * t4 +                      \
               ctx->k[5] * t5;                       \
        o[1] = ctx->k[1] +                           \
               ctx->k[2] * t1 * 2 +                  \
               ctx->k[3] * t2 * 3 +                  \
               ctx->k[4] * t3 * 4 +                  \
               ctx->k[5] * t4 * 5;                   \
        o[2] = ctx->k[2] * 2 +                       \
               ctx->k[3] * t1 * 6 +                  \
               ctx->k[4] * t2 * 12 +                 \
               ctx->k[5] * t3 * 20;                  \
    }
__A_POLYTRACK5_ALL(a_polytrack5, double, a_polytrack5_all)
__A_POLYTRACK5_ALL(a_polytrack5f, float, a_polytrack5f_all)
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
        type dist = ctx->q[1] - ctx->q[0];                              \
        type t1 = ctx->t[1] - ctx->t[0];                                \
        type t2 = t1 * t1;                                              \
        type t3 = t1 * t2;                                              \
        type inv_t1 = 1 / t1;                                           \
        type inv_t2 = inv_t1 * inv_t1;                                  \
        type inv_t3 = inv_t1 * inv_t2;                                  \
        type inv_t4 = inv_t2 * inv_t2;                                  \
        type inv_t5 = inv_t2 * inv_t3;                                  \
        type inv_t6 = inv_t3 * inv_t3;                                  \
        type inv_t7 = inv_t3 * inv_t4;                                  \
        type v0t1 = ctx->v[0] * t1;                                     \
        type v1t1 = ctx->v[1] * t1;                                     \
        type a0t2 = ctx->a[0] * t2;                                     \
        type a1t2 = ctx->a[1] * t2;                                     \
        type j0t3 = ctx->j[0] * t3;                                     \
        type j1t3 = ctx->j[1] * t3;                                     \
                                                                        \
        ctx->k[0] = ctx->q[0];                                          \
        ctx->k[1] = ctx->v[0];                                          \
        ctx->k[2] = ctx->a[0] * (type)(1 / 2.0);                        \
        ctx->k[3] = ctx->j[0] * (type)(1 / 6.0);                        \
        ctx->k[4] = (type)(1 / 6.0) * inv_t4 *                          \
                    (210 * dist - 120 * v0t1 - 90 * v0t1 -              \
                     30 * a0t2 + 15 * a1t2 - 4 * j0t3 - j1t3);          \
        ctx->k[5] = (type)(1 / 2.0) * inv_t5 *                          \
                    (-168 * dist + 90 * v0t1 + 78 * v1t1 +              \
                     20 * a0t2 - 14 * a1t2 + 2 * j0t3 + j1t3);          \
        ctx->k[6] = (type)(1 / 6.0) * inv_t6 *                          \
                    (420 * dist - 216 * v0t1 - 204 * v1t1 -             \
                     45 * a0t2 + 39 * a1t2 - 4 * j0t3 - 3 * j1t3);      \
        ctx->k[7] = (type)(1 / 6.0) * inv_t7 *                          \
                    (-120 * dist + 60 * (v0t1 + v1t1) +                 \
                     12 * (a0t2 - a1t2) + j0t3 + j1t3);                 \
    }
__A_POLYTRACK7_INIT(a_polytrack7, double, a_polytrack7_init)
__A_POLYTRACK7_INIT(a_polytrack7f, float, a_polytrack7f_init)
#undef __A_POLYTRACK7_INIT

#undef __A_POLYTRACK7_POS
#define __A_POLYTRACK7_POS(def, type, func) \
    type func(const def##_t *ctx, type t)   \
    {                                       \
        type t1 = t - ctx->t[0];            \
        type t2 = t1 * t1;                  \
        type t3 = t1 * t2;                  \
        type t4 = t2 * t2;                  \
        type t5 = t2 * t3;                  \
        type t6 = t3 * t3;                  \
        type t7 = t3 * t4;                  \
        return (ctx->k[0] +                 \
                ctx->k[1] * t1 +            \
                ctx->k[2] * t2 +            \
                ctx->k[3] * t3 +            \
                ctx->k[4] * t4 +            \
                ctx->k[5] * t5 +            \
                ctx->k[6] * t6 +            \
                ctx->k[7] * t7);            \
    }
__A_POLYTRACK7_POS(a_polytrack7, double, a_polytrack7_pos)
__A_POLYTRACK7_POS(a_polytrack7f, float, a_polytrack7f_pos)
#undef __A_POLYTRACK7_POS

#undef __A_POLYTRACK7_VEC
#define __A_POLYTRACK7_VEC(def, type, func) \
    type func(const def##_t *ctx, type t)   \
    {                                       \
        type t1 = t - ctx->t[0];            \
        type t2 = t1 * t1;                  \
        type t3 = t1 * t2;                  \
        type t4 = t2 * t2;                  \
        type t5 = t2 * t3;                  \
        type t6 = t3 * t3;                  \
        return (ctx->k[1] +                 \
                ctx->k[2] * t1 * 2 +        \
                ctx->k[3] * t2 * 3 +        \
                ctx->k[4] * t3 * 4 +        \
                ctx->k[5] * t4 * 5 +        \
                ctx->k[6] * t5 * 6 +        \
                ctx->k[7] * t6 * 7);        \
    }
__A_POLYTRACK7_VEC(a_polytrack7, double, a_polytrack7_vec)
__A_POLYTRACK7_VEC(a_polytrack7f, float, a_polytrack7f_vec)
#undef __A_POLYTRACK7_VEC

#undef __A_POLYTRACK7_ACC
#define __A_POLYTRACK7_ACC(def, type, func) \
    type func(const def##_t *ctx, type t)   \
    {                                       \
        type t1 = t - ctx->t[0];            \
        type t2 = t1 * t1;                  \
        type t3 = t1 * t2;                  \
        type t4 = t2 * t2;                  \
        type t5 = t2 * t3;                  \
        return (ctx->k[2] * 2 +             \
                ctx->k[3] * t1 * 6 +        \
                ctx->k[4] * t2 * 12 +       \
                ctx->k[5] * t3 * 20 +       \
                ctx->k[6] * t4 * 30 +       \
                ctx->k[7] * t5 * 42);       \
    }
__A_POLYTRACK7_ACC(a_polytrack7, double, a_polytrack7_acc)
__A_POLYTRACK7_ACC(a_polytrack7f, float, a_polytrack7f_acc)
#undef __A_POLYTRACK7_ACC

#undef __A_POLYTRACK7_JER
#define __A_POLYTRACK7_JER(def, type, func) \
    type func(const def##_t *ctx, type t)   \
    {                                       \
        type t1 = t - ctx->t[0];            \
        type t2 = t1 * t1;                  \
        type t3 = t1 * t2;                  \
        type t4 = t2 * t2;                  \
        return (ctx->k[3] * 6 +             \
                ctx->k[4] * t1 * 24 +       \
                ctx->k[5] * t2 * 60 +       \
                ctx->k[6] * t3 * 120 +      \
                ctx->k[7] * t4 * 210);      \
    }
__A_POLYTRACK7_JER(a_polytrack7, double, a_polytrack7_jer)
__A_POLYTRACK7_JER(a_polytrack7f, float, a_polytrack7f_jer)
#undef __A_POLYTRACK7_JER

#undef __A_POLYTRACK7_ALL
#define __A_POLYTRACK7_ALL(def, type, func)          \
    void func(const def##_t *ctx, type t, type o[4]) \
    {                                                \
        type t1 = t - ctx->t[0];                     \
        type t2 = t1 * t1;                           \
        type t3 = t1 * t2;                           \
        type t4 = t2 * t2;                           \
        type t5 = t2 * t3;                           \
        type t6 = t3 * t3;                           \
        type t7 = t3 * t4;                           \
        o[0] = ctx->k[0] +                           \
               ctx->k[1] * t1 +                      \
               ctx->k[2] * t2 +                      \
               ctx->k[3] * t3 +                      \
               ctx->k[4] * t4 +                      \
               ctx->k[5] * t5 +                      \
               ctx->k[6] * t6 +                      \
               ctx->k[7] * t7;                       \
        o[1] = ctx->k[1] +                           \
               ctx->k[2] * t1 * 2 +                  \
               ctx->k[3] * t2 * 3 +                  \
               ctx->k[4] * t3 * 4 +                  \
               ctx->k[5] * t4 * 5 +                  \
               ctx->k[6] * t5 * 6 +                  \
               ctx->k[7] * t6 * 7;                   \
        o[2] = ctx->k[2] * 2 +                       \
               ctx->k[3] * t1 * 6 +                  \
               ctx->k[4] * t2 * 12 +                 \
               ctx->k[5] * t3 * 20 +                 \
               ctx->k[6] * t4 * 30 +                 \
               ctx->k[7] * t5 * 42;                  \
        o[3] = ctx->k[3] * 6 +                       \
               ctx->k[4] * t1 * 24 +                 \
               ctx->k[5] * t2 * 60 +                 \
               ctx->k[6] * t3 * 120 +                \
               ctx->k[7] * t4 * 210;                 \
    }
__A_POLYTRACK7_ALL(a_polytrack7, double, a_polytrack7_all)
__A_POLYTRACK7_ALL(a_polytrack7f, float, a_polytrack7f_all)
#undef __A_POLYTRACK7_ALL

/* END OF FILE */
