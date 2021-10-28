/*!
 @file           a_lpf.h
 @brief          Low Pass Filter
 @details        A low-pass filter is a filter that passes signals with a
                 frequency lower than a selected cutoff frequency and attenuates
                 signals with frequencies higher than the cutoff frequency.
 \f{aligned}{
     y_n &= \cfrac {k} {k + t} y_{n-1} + \cfrac {t} {t + k} x \\
         &= (1 - \alpha) y_{n-1} + \alpha x, \alpha = \cfrac {t} {t + k}
 \f}
                 https://en.wikipedia.org/wiki/Low-pass_filter
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_LPF_H__
#define __A_LPF_H__

#include "liba.h"

#undef __A_LPF_T
/*!
 @brief          Instance structure for Low Pass Filter
*/
#define __A_LPF_T(_def, _type)                             \
    typedef struct _def##_t                                \
    {                                                      \
        _type o; /* Output */                              \
        _type k; /* Parameter of filtering              */ \
        _type t; /* Time interval of filtering, unit /s */ \
    } _def##_t
__A_LPF_T(a_lpf, double);
__A_LPF_T(a_lpff, float);
#undef __A_LPF_T

#undef __A_LPF_INIT
/*!
 @brief          Initialize function for Low Pass Filter
*/
#define __A_LPF_INIT(_def, _type, _func)           \
    __NONNULL((1))                                 \
    __STATIC_INLINE                                \
    void _func(_def##_t *_ctx, _type _k, _type _t) \
    {                                              \
        a_assert(_ctx);                            \
        _ctx->t = _t;                              \
        _ctx->k = _k;                              \
    }
__A_LPF_INIT(a_lpf, double, a_lpf_init)
__A_LPF_INIT(a_lpff, float, a_lpff_init)
#undef __A_LPF_INIT

#undef __A_LPF_PROCESS
/*!
 @brief          Process function for Low Pass Filter
 \f{aligned}{
     y_n &= \cfrac {k} {k + t} y_{n-1} + \cfrac {t} {t + k} x \\
         &= (1 - \alpha) y_{n-1} + \alpha x, \alpha = \cfrac {t} {t + k}
 \f}
*/
#define __A_LPF_PROCESS(_def, _type, _func)                 \
    __NONNULL((1))                                          \
    __STATIC_INLINE                                         \
    _type _func(_def##_t *_ctx, _type _x)                   \
    {                                                       \
        a_assert(_ctx);                                     \
        _type inv_kt = _ctx->t / (_ctx->k + _ctx->t);       \
        /* y[n] = y[n-1] * k / (k + t) + x * t / (k + t) */ \
        _ctx->o *= 1 - inv_kt;                              \
        _ctx->o += _x * inv_kt;                             \
        return _ctx->o;                                     \
    }
__A_LPF_PROCESS(a_lpf, double, a_lpf_process)
__A_LPF_PROCESS(a_lpff, float, a_lpff_process)
#undef __A_LPF_PROCESS

#undef __A_LPF_RESET
/*!
 @brief          Reset function for Low Pass Filter
*/
#define __A_LPF_RESET(_def, _func) \
    __NONNULL_ALL                  \
    __STATIC_INLINE                \
    void _func(_def##_t *_ctx)     \
    {                              \
        a_assert(_ctx);            \
        _ctx->o = 0;               \
    }
__A_LPF_RESET(a_lpf, a_lpf_reset)
__A_LPF_RESET(a_lpff, a_lpff_reset)
#undef __A_LPF_RESET

/* Enddef to prevent recursive inclusion */
#endif /* __A_LPF_H__ */

/* END OF FILE */
