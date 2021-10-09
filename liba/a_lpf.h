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
#define __A_LPF_T(bit)                                              \
    typedef struct a_lpf_f##bit##_t                                 \
    {                                                               \
        float##bit##_t o; /* Output */                              \
        float##bit##_t k; /* Parameter of filtering              */ \
        float##bit##_t t; /* Time interval of filtering, unit /s */ \
    } a_lpf_f##bit##_t
__A_LPF_T(32);
__A_LPF_T(64);
#undef __A_LPF_T

#undef __A_LPF_INIT
#define __A_LPF_INIT(bit, ctx, k, t)                 \
    __STATIC_INLINE                                  \
    void a_lpf_f##bit##_init(a_lpf_f##bit##_t *ctx,  \
                             const float##bit##_t k, \
                             const float##bit##_t t) \
    {                                                \
        ctx->t = t;                                  \
        ctx->k = k;                                  \
    }
__A_LPF_INIT(32, ctx, k, t)
__A_LPF_INIT(64, ctx, k, t)
#undef __A_LPF_INIT

#undef __A_LPF
#define __A_LPF(bit, ctx, x)                                \
    __STATIC_INLINE                                         \
    float##bit##_t a_lpf_f##bit(a_lpf_f##bit##_t *ctx,      \
                                const float##bit##_t x)     \
    {                                                       \
        float##bit##_t inv_kt = ctx->t / (ctx->k + ctx->t); \
                                                            \
        /* y[n] = y[n-1] * k / (k + t) + x * t / (k + t) */ \
        ctx->o *= 1 - inv_kt;                               \
        ctx->o += x * inv_kt;                               \
                                                            \
        return ctx->o;                                      \
    }
__A_LPF(32, ctx, x)
__A_LPF(64, ctx, x)
#undef __A_LPF

#undef __A_LPF_RESET
#define __A_LPF_RESET(bit, ctx)                      \
    __STATIC_INLINE                                  \
    void a_lpf_f##bit##_reset(a_lpf_f##bit##_t *ctx) \
    {                                                \
        ctx->o = 0;                                  \
    }
__A_LPF_RESET(32, ctx)
__A_LPF_RESET(64, ctx)
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
 @param[in]      bit: bits for the floating-point data
*/
#define a_lpf_t(bit) a_lpf_f##bit##_t
#endif /* a_lpf_t */

#ifndef a_lpf_init
/*!
 @brief          Initialize function for Low Pass Filter
 @param[in]      bit: bits for the floating-point data
 @param[in,out]  ctx: points to an instance of Low Pass Filter structure
 @param[in]      k: Parameter of filtering
 @param[in]      t: Time interval of filtering, unit /s
*/
#define a_lpf_init(bit, ctx, k, t) a_lpf_f##bit##_init(ctx, k, t)
#endif /* a_lpf_init */

#ifndef a_lpf
/*!
 @brief          Process function for Low Pass Filter
 \f{aligned}{
     y_n &= \cfrac {k} {k + t} y_{n-1} + \cfrac {t} {t + k} x \\
         &= (1 - \alpha) y_{n-1} + \alpha x, \alpha = \cfrac {t} {t + k}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in,out]  ctx: points to an instance of Low Pass Filter structure
 @param[in]      x: Input
 @return         Output
*/
#define a_lpf(bit, ctx, x) a_lpf_f##bit(ctx, x)
#endif /* a_lpf */

#ifndef a_lpf_reset
/*!
 @brief          Reset function for Low Pass Filter
 @param[in]      bit: bits for the floating-point data
 @param[in,out]  ctx: points to an instance of Low Pass Filter structure
*/
#define a_lpf_reset(bit, ctx) a_lpf_f##bit##_reset(ctx)
#endif /* a_lpf_reset */

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_LPF_H__ */

/* END OF FILE */
