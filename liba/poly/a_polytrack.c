/*!
 @file a_polytrack.c
 @brief polynomial trajectory
 @details Trajectory Planning for Automatic Machines and Robots.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_polytrack.h"

#include "a_poly.h"
#undef a_horner

/* function for cubic polynomial trajectory */

#undef a_polytrack3_init
#undef __A_POLYTRACK3_INIT
#define __A_POLYTRACK3_INIT(_def, _type, _func)                                \
    void _func(_def##_s *_ctx, const _type _source[3], const _type _target[3]) \
    {                                                                          \
        aassert(_ctx);                                                         \
        aassert(_source);                                                      \
        aassert(_target);                                                      \
                                                                               \
        _ctx->t[0] = _source[0];                                               \
        _ctx->q[0] = _source[1];                                               \
        _ctx->v[0] = _source[2];                                               \
        _ctx->t[1] = _target[0];                                               \
        _ctx->q[1] = _target[1];                                               \
        _ctx->v[1] = _target[2];                                               \
                                                                               \
        _type q = _ctx->q[1] - _ctx->q[0];                                     \
        _type t = _ctx->t[1] - _ctx->t[0];                                     \
        _type inv_t1 = 1 / t;                                                  \
        _type inv_t2 = inv_t1 * inv_t1;                                        \
        _type inv_t3 = inv_t1 * inv_t2;                                        \
                                                                               \
        _ctx->k[0] = _ctx->q[0];                                               \
        _ctx->k[1] = _ctx->v[0];                                               \
        _ctx->k[2] = inv_t1 * (-2 * _ctx->v[0] - _ctx->v[1]) +                 \
                     inv_t2 * q * 3;                                           \
        _ctx->k[3] = inv_t2 * (_ctx->v[0] + _ctx->v[1]) -                      \
                     inv_t3 * q * 2;                                           \
    }
__A_POLYTRACK3_INIT(a_polytrack3, double, a_polytrack3_init)
__A_POLYTRACK3_INIT(a_polytrack3f, float, a_polytrack3f_init)
#undef __A_POLYTRACK3_INIT

#undef a_polytrack3_pos
#undef __A_POLYTRACK3_POS
#define __A_POLYTRACK3_POS(_def, _type, _func, _poly) \
    _type _func(const _def##_s *_ctx, _type _t)       \
    {                                                 \
        aassert(_ctx);                                \
        _type a[4] = {                                \
            _ctx->k[3],                               \
            _ctx->k[2],                               \
            _ctx->k[1],                               \
            _ctx->k[0],                               \
        };                                            \
        return _poly(a, 4, _t - _ctx->t[0]);          \
    }
__A_POLYTRACK3_POS(a_polytrack3, double, a_polytrack3_pos, a_horner)
__A_POLYTRACK3_POS(a_polytrack3f, float, a_polytrack3f_pos, a_hornerf)
#undef __A_POLYTRACK3_POS

#undef a_polytrack3_vec
#undef __A_POLYTRACK3_VEC
#define __A_POLYTRACK3_VEC(_def, _type, _func, _poly) \
    _type _func(const _def##_s *_ctx, _type _t)       \
    {                                                 \
        aassert(_ctx);                                \
        _type a[3] = {                                \
            _ctx->k[3] * 3,                           \
            _ctx->k[2] * 2,                           \
            _ctx->k[1],                               \
        };                                            \
        return _poly(a, 3, _t - _ctx->t[0]);          \
    }
__A_POLYTRACK3_VEC(a_polytrack3, double, a_polytrack3_vec, a_horner)
__A_POLYTRACK3_VEC(a_polytrack3f, float, a_polytrack3f_vec, a_hornerf)
#undef __A_POLYTRACK3_VEC

#undef a_polytrack3_acc
#undef __A_POLYTRACK3_ACC
#define __A_POLYTRACK3_ACC(_def, _type, _func, _poly) \
    _type _func(const _def##_s *_ctx, _type _t)       \
    {                                                 \
        aassert(_ctx);                                \
        _type a[2] = {                                \
            _ctx->k[3] * 3 * 2,                       \
            _ctx->k[2] * 2,                           \
        };                                            \
        return _poly(a, 2, _t - _ctx->t[0]);          \
    }
__A_POLYTRACK3_ACC(a_polytrack3, double, a_polytrack3_acc, a_horner)
__A_POLYTRACK3_ACC(a_polytrack3f, float, a_polytrack3f_acc, a_hornerf)
#undef __A_POLYTRACK3_ACC

#undef a_polytrack3_all
#undef __A_POLYTRACK3_ALL
#define __A_POLYTRACK3_ALL(_def, _type, _func, _poly)       \
    void _func(const _def##_s *_ctx, _type _t, _type _o[3]) \
    {                                                       \
        aassert(_o);                                        \
        aassert(_ctx);                                      \
        _type a[4] = {                                      \
            _ctx->k[3],                                     \
            _ctx->k[2],                                     \
            _ctx->k[1],                                     \
            _ctx->k[0],                                     \
        };                                                  \
        _t -= _ctx->t[0];                                   \
        _o[0] = _poly(a, 4, _t);                            \
        a[0] *= 3;                                          \
        a[1] *= 2;                                          \
        _o[1] = _poly(a, 3, _t);                            \
        a[0] *= 2;                                          \
        _o[2] = _poly(a, 2, _t);                            \
    }
__A_POLYTRACK3_ALL(a_polytrack3, double, a_polytrack3_all, a_horner)
__A_POLYTRACK3_ALL(a_polytrack3f, float, a_polytrack3f_all, a_hornerf)
#undef __A_POLYTRACK3_ALL

/* function for quintic polynomial trajectory */

#undef a_polytrack5_init
#undef __A_POLYTRACK5_INIT
#define __A_POLYTRACK5_INIT(_def, _type, _func)                                \
    void _func(_def##_s *_ctx, const _type _source[4], const _type _target[4]) \
    {                                                                          \
        aassert(_ctx);                                                         \
        aassert(_source);                                                      \
        aassert(_target);                                                      \
                                                                               \
        _ctx->t[0] = _source[0];                                               \
        _ctx->q[0] = _source[1];                                               \
        _ctx->v[0] = _source[2];                                               \
        _ctx->a[0] = _source[3];                                               \
        _ctx->t[1] = _target[0];                                               \
        _ctx->q[1] = _target[1];                                               \
        _ctx->v[1] = _target[2];                                               \
        _ctx->a[1] = _target[3];                                               \
                                                                               \
        _type q = _ctx->q[1] - _ctx->q[0];                                     \
        _type t = _ctx->t[1] - _ctx->t[0];                                     \
        _type inv_t1 = 1 / t;                                                  \
        _type inv_t2 = inv_t1 * inv_t1;                                        \
        _type inv_t3 = inv_t1 * inv_t2;                                        \
        _type inv_t4 = inv_t2 * inv_t2;                                        \
        _type inv_t5 = inv_t2 * inv_t3;                                        \
                                                                               \
        _ctx->k[0] = _ctx->q[0];                                               \
        _ctx->k[1] = _ctx->v[0];                                               \
        _ctx->k[2] = _ctx->a[0] * (_type)(1 / 2.0);                            \
        _ctx->k[3] = (inv_t1 * (_ctx->a[1] - 3 * _ctx->a[0]) -                 \
                      inv_t2 * (12 * _ctx->v[0] + 8 * _ctx->v[1]) +            \
                      inv_t3 * q * 20) *                                       \
                     (_type)(1 / 2.0);                                         \
        _ctx->k[4] = (inv_t2 * (3 * _ctx->a[0] - 2 * _ctx->a[1]) +             \
                      inv_t3 * (16 * _ctx->v[0] + 14 * _ctx->v[1]) -           \
                      inv_t4 * q * 30) *                                       \
                     (_type)(1 / 2.0);                                         \
        _ctx->k[5] = (inv_t3 * (_ctx->a[1] - _ctx->a[0]) -                     \
                      inv_t4 * (_ctx->v[0] + _ctx->v[1]) * 6 +                 \
                      inv_t5 * q * 12) *                                       \
                     (_type)(1 / 2.0);                                         \
    }
__A_POLYTRACK5_INIT(a_polytrack5, double, a_polytrack5_init)
__A_POLYTRACK5_INIT(a_polytrack5f, float, a_polytrack5f_init)
#undef __A_POLYTRACK5_INIT

#undef a_polytrack5_pos
#undef __A_POLYTRACK5_POS
#define __A_POLYTRACK5_POS(_def, _type, _func, _poly) \
    _type _func(const _def##_s *_ctx, _type _t)       \
    {                                                 \
        aassert(_ctx);                                \
        _type a[6] = {                                \
            _ctx->k[5],                               \
            _ctx->k[4],                               \
            _ctx->k[3],                               \
            _ctx->k[2],                               \
            _ctx->k[1],                               \
            _ctx->k[0],                               \
        };                                            \
        return _poly(a, 6, _t - _ctx->t[0]);          \
    }
__A_POLYTRACK5_POS(a_polytrack5, double, a_polytrack5_pos, a_horner)
__A_POLYTRACK5_POS(a_polytrack5f, float, a_polytrack5f_pos, a_hornerf)
#undef __A_POLYTRACK5_POS

#undef a_polytrack5_vec
#undef __A_POLYTRACK5_VEC
#define __A_POLYTRACK5_VEC(_def, _type, _func, _poly) \
    _type _func(const _def##_s *_ctx, _type _t)       \
    {                                                 \
        aassert(_ctx);                                \
        _type a[5] = {                                \
            _ctx->k[5] * 5,                           \
            _ctx->k[4] * 4,                           \
            _ctx->k[3] * 3,                           \
            _ctx->k[2] * 2,                           \
            _ctx->k[1],                               \
        };                                            \
        return _poly(a, 5, _t - _ctx->t[0]);          \
    }
__A_POLYTRACK5_VEC(a_polytrack5, double, a_polytrack5_vec, a_horner)
__A_POLYTRACK5_VEC(a_polytrack5f, float, a_polytrack5f_vec, a_hornerf)
#undef __A_POLYTRACK5_VEC

#undef a_polytrack5_acc
#undef __A_POLYTRACK5_ACC
#define __A_POLYTRACK5_ACC(_def, _type, _func, _poly) \
    _type _func(const _def##_s *_ctx, _type _t)       \
    {                                                 \
        aassert(_ctx);                                \
        _type a[4] = {                                \
            _ctx->k[5] * 5 * 4,                       \
            _ctx->k[4] * 4 * 3,                       \
            _ctx->k[3] * 3 * 2,                       \
            _ctx->k[2] * 2,                           \
        };                                            \
        return _poly(a, 4, _t - _ctx->t[0]);          \
    }
__A_POLYTRACK5_ACC(a_polytrack5, double, a_polytrack5_acc, a_horner)
__A_POLYTRACK5_ACC(a_polytrack5f, float, a_polytrack5f_acc, a_hornerf)
#undef __A_POLYTRACK5_ACC

#undef a_polytrack5_all
#undef __A_POLYTRACK5_ALL
#define __A_POLYTRACK5_ALL(_def, _type, _func, _poly)       \
    void _func(const _def##_s *_ctx, _type _t, _type _o[3]) \
    {                                                       \
        aassert(_o);                                        \
        aassert(_ctx);                                      \
        _type a[6] = {                                      \
            _ctx->k[5],                                     \
            _ctx->k[4],                                     \
            _ctx->k[3],                                     \
            _ctx->k[2],                                     \
            _ctx->k[1],                                     \
            _ctx->k[0],                                     \
        };                                                  \
        _t -= _ctx->t[0];                                   \
        _o[0] = _poly(a, 6, _t);                            \
        a[0] *= 5;                                          \
        a[1] *= 4;                                          \
        a[2] *= 3;                                          \
        a[3] *= 2;                                          \
        _o[1] = _poly(a, 5, _t);                            \
        a[0] *= 4;                                          \
        a[1] *= 3;                                          \
        a[2] *= 2;                                          \
        _o[2] = _poly(a, 4, _t);                            \
    }
__A_POLYTRACK5_ALL(a_polytrack5, double, a_polytrack5_all, a_horner)
__A_POLYTRACK5_ALL(a_polytrack5f, float, a_polytrack5f_all, a_hornerf)
#undef __A_POLYTRACK5_ALL

/* function for hepta polynomial trajectory */

#undef a_polytrack7_init
#undef __A_POLYTRACK7_INIT
#define __A_POLYTRACK7_INIT(_def, _type, _func)                                \
    void _func(_def##_s *_ctx, const _type _source[5], const _type _target[5]) \
    {                                                                          \
        aassert(_ctx);                                                         \
        aassert(_source);                                                      \
        aassert(_target);                                                      \
                                                                               \
        _ctx->t[0] = _source[0];                                               \
        _ctx->q[0] = _source[1];                                               \
        _ctx->v[0] = _source[2];                                               \
        _ctx->a[0] = _source[3];                                               \
        _ctx->j[0] = _source[4];                                               \
        _ctx->t[1] = _target[0];                                               \
        _ctx->q[1] = _target[1];                                               \
        _ctx->v[1] = _target[2];                                               \
        _ctx->a[1] = _target[3];                                               \
        _ctx->j[1] = _target[4];                                               \
                                                                               \
        _type q = _ctx->q[1] - _ctx->q[0];                                     \
        _type t = _ctx->t[1] - _ctx->t[0];                                     \
        _type inv_t1 = 1 / t;                                                  \
        _type inv_t2 = inv_t1 * inv_t1;                                        \
        _type inv_t3 = inv_t1 * inv_t2;                                        \
        _type inv_t4 = inv_t2 * inv_t2;                                        \
        _type inv_t5 = inv_t2 * inv_t3;                                        \
        _type inv_t6 = inv_t3 * inv_t3;                                        \
        _type inv_t7 = inv_t3 * inv_t4;                                        \
                                                                               \
        _ctx->k[0] = _ctx->q[0];                                               \
        _ctx->k[1] = _ctx->v[0];                                               \
        _ctx->k[2] = _ctx->a[0] * (_type)(1 / 2.0);                            \
        _ctx->k[3] = _ctx->j[0] * (_type)(1 / 6.0);                            \
        _ctx->k[4] = (inv_t1 * (-4 * _ctx->j[0] - _ctx->j[1]) +                \
                      inv_t2 * (15 * _ctx->a[1] - 30 * _ctx->a[0]) -           \
                      inv_t3 * (120 * _ctx->v[0] + 90 * _ctx->v[1]) +          \
                      inv_t4 * q * 210) *                                      \
                     (_type)(1 / 6.0);                                         \
        _ctx->k[5] = (inv_t2 * (2 * _ctx->j[0] + _ctx->j[1]) +                 \
                      inv_t3 * (20 * _ctx->a[0] - 14 * _ctx->a[1]) +           \
                      inv_t4 * (90 * _ctx->v[0] + 78 * _ctx->v[1]) -           \
                      inv_t5 * q * 168) *                                      \
                     (_type)(1 / 2.0);                                         \
        _ctx->k[6] = (inv_t3 * (-4 * _ctx->j[0] - 3 * _ctx->j[1]) +            \
                      inv_t4 * (39 * _ctx->a[1] - 45 * _ctx->a[0]) -           \
                      inv_t5 * (216 * _ctx->v[0] + 204 * _ctx->v[1]) +         \
                      inv_t6 * q * 420) *                                      \
                     (_type)(1 / 6.0);                                         \
        _ctx->k[7] = (inv_t4 * (_ctx->j[0] + _ctx->j[1]) +                     \
                      inv_t5 * (_ctx->a[0] - _ctx->a[1]) * 12 +                \
                      inv_t6 * (_ctx->v[0] + _ctx->v[1]) * 60 -                \
                      inv_t7 * q * 120) *                                      \
                     (_type)(1 / 6.0);                                         \
    }
__A_POLYTRACK7_INIT(a_polytrack7, double, a_polytrack7_init)
__A_POLYTRACK7_INIT(a_polytrack7f, float, a_polytrack7f_init)
#undef __A_POLYTRACK7_INIT

#undef a_polytrack7_pos
#undef __A_POLYTRACK7_POS
#define __A_POLYTRACK7_POS(_def, _type, _func, _poly) \
    _type _func(const _def##_s *_ctx, _type _t)       \
    {                                                 \
        aassert(_ctx);                                \
        _type a[8] = {                                \
            _ctx->k[7],                               \
            _ctx->k[6],                               \
            _ctx->k[5],                               \
            _ctx->k[4],                               \
            _ctx->k[3],                               \
            _ctx->k[2],                               \
            _ctx->k[1],                               \
            _ctx->k[0],                               \
        };                                            \
        return _poly(a, 8, _t - _ctx->t[0]);          \
    }
__A_POLYTRACK7_POS(a_polytrack7, double, a_polytrack7_pos, a_horner)
__A_POLYTRACK7_POS(a_polytrack7f, float, a_polytrack7f_pos, a_hornerf)
#undef __A_POLYTRACK7_POS

#undef a_polytrack7_vec
#undef __A_POLYTRACK7_VEC
#define __A_POLYTRACK7_VEC(_def, _type, _func, _poly) \
    _type _func(const _def##_s *_ctx, _type _t)       \
    {                                                 \
        aassert(_ctx);                                \
        _type a[7] = {                                \
            _ctx->k[7] * 7,                           \
            _ctx->k[6] * 6,                           \
            _ctx->k[5] * 5,                           \
            _ctx->k[4] * 4,                           \
            _ctx->k[3] * 3,                           \
            _ctx->k[2] * 2,                           \
            _ctx->k[1],                               \
        };                                            \
        return _poly(a, 7, _t - _ctx->t[0]);          \
    }
__A_POLYTRACK7_VEC(a_polytrack7, double, a_polytrack7_vec, a_horner)
__A_POLYTRACK7_VEC(a_polytrack7f, float, a_polytrack7f_vec, a_hornerf)
#undef __A_POLYTRACK7_VEC

#undef a_polytrack7_acc
#undef __A_POLYTRACK7_ACC
#define __A_POLYTRACK7_ACC(_def, _type, _func, _poly) \
    _type _func(const _def##_s *_ctx, _type _t)       \
    {                                                 \
        aassert(_ctx);                                \
        _type a[6] = {                                \
            _ctx->k[7] * 7 * 6,                       \
            _ctx->k[6] * 6 * 5,                       \
            _ctx->k[5] * 5 * 4,                       \
            _ctx->k[4] * 4 * 3,                       \
            _ctx->k[3] * 3 * 2,                       \
            _ctx->k[2] * 2,                           \
        };                                            \
        return _poly(a, 6, _t - _ctx->t[0]);          \
    }
__A_POLYTRACK7_ACC(a_polytrack7, double, a_polytrack7_acc, a_horner)
__A_POLYTRACK7_ACC(a_polytrack7f, float, a_polytrack7f_acc, a_hornerf)
#undef __A_POLYTRACK7_ACC

#undef a_polytrack7_jer
#undef __A_POLYTRACK7_JER
#define __A_POLYTRACK7_JER(_def, _type, _func, _poly) \
    _type _func(const _def##_s *_ctx, _type _t)       \
    {                                                 \
        aassert(_ctx);                                \
        _type a[5] = {                                \
            _ctx->k[7] * 7 * 6 * 5,                   \
            _ctx->k[6] * 6 * 5 * 4,                   \
            _ctx->k[5] * 5 * 4 * 3,                   \
            _ctx->k[4] * 4 * 3 * 2,                   \
            _ctx->k[3] * 3 * 2,                       \
        };                                            \
        return _poly(a, 5, _t - _ctx->t[0]);          \
    }
__A_POLYTRACK7_JER(a_polytrack7, double, a_polytrack7_jer, a_horner)
__A_POLYTRACK7_JER(a_polytrack7f, float, a_polytrack7f_jer, a_hornerf)
#undef __A_POLYTRACK7_JER

#undef a_polytrack7_all
#undef __A_POLYTRACK7_ALL
#define __A_POLYTRACK7_ALL(_def, _type, _func, _poly)       \
    void _func(const _def##_s *_ctx, _type _t, _type _o[4]) \
    {                                                       \
        aassert(_o);                                        \
        aassert(_ctx);                                      \
        _type a[8] = {                                      \
            _ctx->k[7],                                     \
            _ctx->k[6],                                     \
            _ctx->k[5],                                     \
            _ctx->k[4],                                     \
            _ctx->k[3],                                     \
            _ctx->k[2],                                     \
            _ctx->k[1],                                     \
            _ctx->k[0],                                     \
        };                                                  \
        _t -= _ctx->t[0];                                   \
        _o[0] = _poly(a, 8, _t);                            \
        a[0] *= 7;                                          \
        a[1] *= 6;                                          \
        a[2] *= 5;                                          \
        a[3] *= 4;                                          \
        a[4] *= 3;                                          \
        a[5] *= 2;                                          \
        _o[1] = _poly(a, 7, _t);                            \
        a[0] *= 6;                                          \
        a[1] *= 5;                                          \
        a[2] *= 4;                                          \
        a[3] *= 3;                                          \
        a[4] *= 2;                                          \
        _o[2] = _poly(a, 6, _t);                            \
        a[0] *= 5;                                          \
        a[1] *= 4;                                          \
        a[2] *= 3;                                          \
        a[3] *= 2;                                          \
        _o[3] = _poly(a, 5, _t);                            \
    }
__A_POLYTRACK7_ALL(a_polytrack7, double, a_polytrack7_all, a_horner)
__A_POLYTRACK7_ALL(a_polytrack7f, float, a_polytrack7f_all, a_hornerf)
#undef __A_POLYTRACK7_ALL

/* END OF FILE */
