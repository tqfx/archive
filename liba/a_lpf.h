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

/*!
 @ingroup        LIBA
 @defgroup       LIBA_LPF Low Pass Filter
 @details        A low-pass filter is a filter that passes signals with a
                 frequency lower than a selected cutoff frequency and attenuates
                 signals with frequencies higher than the cutoff frequency.
 \f{aligned}{
     y_n &= \cfrac {k} {k + t} y_{n-1} + \cfrac {t} {t + k} x \\
         &= (1 - \alpha) y_{n-1} + \alpha x, \alpha = \cfrac {t} {t + k}
 \f}
                 https://en.wikipedia.org/wiki/Low-pass_filter
 @{
*/

#undef __A_LPF_T
/*!
 @brief          Instance structure for Low Pass Filter
*/
#define __A_LPF_T(def, type)                              \
    typedef struct def##_t                                \
    {                                                     \
        type o; /* Output */                              \
        type k; /* Parameter of filtering              */ \
        type t; /* Time interval of filtering, unit /s */ \
    } def##_t
__A_LPF_T(a_lpf, double);
__A_LPF_T(a_lpff, float);
#undef __A_LPF_T

#undef __A_LPF_INIT
/*!
 @brief          Initialize function for Low Pass Filter
*/
#define __A_LPF_INIT(def, type, func)       \
    __STATIC_INLINE                         \
    void func(def##_t *ctx, type k, type t) \
    {                                       \
        ctx->t = t;                         \
        ctx->k = k;                         \
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
#define __A_LPF_PROCESS(def, type, func)                    \
    __STATIC_INLINE                                         \
    type func(def##_t *ctx, type x)                         \
    {                                                       \
        type inv_kt = ctx->t / (ctx->k + ctx->t);           \
                                                            \
        /* y[n] = y[n-1] * k / (k + t) + x * t / (k + t) */ \
        ctx->o *= 1 - inv_kt;                               \
        ctx->o += x * inv_kt;                               \
                                                            \
        return ctx->o;                                      \
    }
__A_LPF_PROCESS(a_lpf, double, a_lpf_process)
__A_LPF_PROCESS(a_lpff, float, a_lpff_process)
#undef __A_LPF_PROCESS

#undef __A_LPF_RESET
/*!
 @brief          Reset function for Low Pass Filter
*/
#define __A_LPF_RESET(def, func) \
    __STATIC_INLINE              \
    void func(def##_t *ctx)      \
    {                            \
        ctx->o = 0;              \
    }
__A_LPF_RESET(a_lpf, a_lpf_reset)
__A_LPF_RESET(a_lpff, a_lpff_reset)
#undef __A_LPF_RESET

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_LPF_H__ */

/* END OF FILE */
