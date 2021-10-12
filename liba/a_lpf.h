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
#define __A_LPF_T(id, type)                               \
    typedef struct a_lpf_##id##_t                         \
    {                                                     \
        type o; /* Output */                              \
        type k; /* Parameter of filtering              */ \
        type t; /* Time interval of filtering, unit /s */ \
    } a_lpf_##id##_t
__A_LPF_T(f32, float32_t);
__A_LPF_T(f64, float64_t);
#undef __A_LPF_T

#undef __A_LPF_INIT
#define __A_LPF_INIT(id, type, func)                           \
    __STATIC_INLINE                                            \
    void func(a_lpf_##id##_t *ctx, const type k, const type t) \
    {                                                          \
        ctx->t = t;                                            \
        ctx->k = k;                                            \
    }
__A_LPF_INIT(f32, float32_t, a_lpf_f32_init)
__A_LPF_INIT(f64, float64_t, a_lpf_f64_init)
#undef __A_LPF_INIT

#undef __A_LPF
#define __A_LPF(id, type, func)                             \
    __STATIC_INLINE                                         \
    type func(a_lpf_##id##_t *ctx, const type x)            \
    {                                                       \
        type inv_kt = ctx->t / (ctx->k + ctx->t);           \
                                                            \
        /* y[n] = y[n-1] * k / (k + t) + x * t / (k + t) */ \
        ctx->o *= 1 - inv_kt;                               \
        ctx->o += x * inv_kt;                               \
                                                            \
        return ctx->o;                                      \
    }
__A_LPF(f32, float32_t, a_lpf_f32)
__A_LPF(f64, float64_t, a_lpf_f64)
#undef __A_LPF

#undef __A_LPF_RESET
#define __A_LPF_RESET(id, func)    \
    __STATIC_INLINE                \
    void func(a_lpf_##id##_t *ctx) \
    {                              \
        ctx->o = 0;                \
    }
__A_LPF_RESET(f32, a_lpf_f32_reset)
__A_LPF_RESET(f64, a_lpf_f64_reset)
#undef __A_LPF_RESET

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

#ifndef a_lpf_t
/*!
 @brief          Instance structure for Low Pass Filter
 @param[in]      id: id for the type of the data
*/
#define a_lpf_t(id) a_lpf_##id##_t
#endif /* a_lpf_t */

#ifndef a_lpf_init
/*!
 @brief          Initialize function for Low Pass Filter
 @param[in]      id: id for the type of the data
 @param[in,out]  ctx: points to an instance of Low Pass Filter structure
 @param[in]      k: Parameter of filtering
 @param[in]      t: Time interval of filtering, unit /s
*/
#define a_lpf_init(id, ctx, k, t) a_lpf_##id##_init(ctx, k, t)
#endif /* a_lpf_init */

#ifndef a_lpf
/*!
 @brief          Process function for Low Pass Filter
 \f{aligned}{
     y_n &= \cfrac {k} {k + t} y_{n-1} + \cfrac {t} {t + k} x \\
         &= (1 - \alpha) y_{n-1} + \alpha x, \alpha = \cfrac {t} {t + k}
 \f}
 @param[in]      id: id for the type of the data
 @param[in,out]  ctx: points to an instance of Low Pass Filter structure
 @param[in]      x: Input
 @return         Output
*/
#define a_lpf(id, ctx, x) a_lpf_##id(ctx, x)
#endif /* a_lpf */

#ifndef a_lpf_reset
/*!
 @brief          Reset function for Low Pass Filter
 @param[in]      id: id for the type of the data
 @param[in,out]  ctx: points to an instance of Low Pass Filter structure
*/
#define a_lpf_reset(id, ctx) a_lpf_##id##_reset(ctx)
#endif /* a_lpf_reset */

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_LPF_H__ */

/* END OF FILE */
