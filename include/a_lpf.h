/*!
 @file a_lpf.h
 @brief Low Pass Filter
 @details
 A low-pass filter is a filter that passes signals with a
 frequency lower than a selected cutoff frequency and attenuates
 signals with frequencies higher than the cutoff frequency.
 \f{aligned}{
  y_n &= \cfrac {k} {k + t} y_{n-1} + \cfrac {t} {t + k} x \\
  &= (1 - \alpha) y_{n-1} + \alpha x, \alpha = \cfrac {t} {t + k}
 \f}
 https://en.wikipedia.org/wiki/Low-pass_filter
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_LPF_H__
#define __A_LPF_H__

#include "liba.h"

#undef A_LPF_S
/*!
 @brief Instance structure for Low Pass Filter
*/
#define A_LPF_S(def, type)                                \
    typedef struct def##_s                                \
    {                                                     \
        type o; /* Output */                              \
        type k; /* Parameter of filtering              */ \
        type t; /* Time interval of filtering, unit /s */ \
    } def##_s
A_LPF_S(a_lpf, double);
A_LPF_S(a_lpff, float);
#undef A_LPF_S

#undef A_LPF_INIT
#define A_LPF_INIT(def, type, func)         \
    __NONNULL((1))                          \
    __STATIC_INLINE                         \
    void func(def##_s *ctx, type k, type t) \
    {                                       \
        AASSERT(ctx);                       \
        ctx->t = t;                         \
        ctx->k = k;                         \
    }
A_LPF_INIT(a_lpf, double, a_lpf_init)
A_LPF_INIT(a_lpff, float, a_lpff_init)
#undef A_LPF_INIT

#undef A_LPF_PROCESS
#define A_LPF_PROCESS(def, type, func)                      \
    __NONNULL((1))                                          \
    __STATIC_INLINE                                         \
    type func(def##_s *ctx, type x)                         \
    {                                                       \
        AASSERT(ctx);                                       \
        type inv_kt = ctx->t / (ctx->k + ctx->t);           \
        /* y[n] = y[n-1] * k / (k + t) + x * t / (k + t) */ \
        ctx->o *= 1 - inv_kt;                               \
        ctx->o += x * inv_kt;                               \
        return ctx->o;                                      \
    }
A_LPF_PROCESS(a_lpf, double, a_lpf_process)
A_LPF_PROCESS(a_lpff, float, a_lpff_process)
#undef A_LPF_PROCESS

#undef A_LPF_RESET
#define A_LPF_RESET(def, func) \
    __NONNULL_ALL              \
    __STATIC_INLINE            \
    void func(def##_s *ctx)    \
    {                          \
        AASSERT(ctx);          \
        ctx->o = 0;            \
    }
A_LPF_RESET(a_lpf, a_lpf_reset)
A_LPF_RESET(a_lpff, a_lpff_reset)
#undef A_LPF_RESET

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
/*!
 @brief Initialize function for Low Pass Filter
*/
#define a_lpf_init(ctx, k, t) \
    _Generic((ctx),           \
             default          \
             : a_lpf_init,    \
               a_lpff_s *     \
             : a_lpff_init)(ctx, k, t)
/*!
 @brief Process function for Low Pass Filter
 \f{aligned}{
     y_n &= \cfrac {k} {k + t} y_{n-1} + \cfrac {t} {t + k} x \\
         &= (1 - \alpha) y_{n-1} + \alpha x, \alpha = \cfrac {t} {t + k}
 \f}
*/
#define a_lpf_process(ctx, x) \
    _Generic((ctx),           \
             default          \
             : a_lpf_process, \
               a_lpff_s *     \
             : a_lpff_process)(ctx, x)
/*!
 @brief Reset function for Low Pass Filter
*/
#define a_lpf_reset(ctx)    \
    _Generic((ctx),         \
             default        \
             : a_lpf_reset, \
               a_lpff_s *   \
             : a_lpff_reset)(ctx)
#endif /* __STDC_VERSION__ */

/* Enddef to prevent recursive inclusion */
#endif /* __A_LPF_H__ */
