/*!
 @file lpf.h
 @brief Low Pass Filter
 @details
 A low-pass filter is a filter that passes signals with a
 frequency lower than a selected cutoff frequency and attenuates
 signals with frequencies higher than the cutoff frequency.
 @f{aligned}{
  y_n &=\cfrac{k}{k+t}y_{n-1}+\cfrac{t}{t+k}x \\
      &=(1-\alpha)y_{n-1}+\alpha x,\alpha=\cfrac{t}{t+k}
 @f}
 https://en.wikipedia.org/wiki/Low-pass_filter
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_LPF_H__
#define __A_LPF_H__

#include "../def.h"

/*!
 @brief Instance structure for Low Pass Filter
*/
typedef struct a_lpf_s
{
    a_real_t o; /*!< Output */
    a_real_t k; /*!< Factor */
    a_real_t t; /*!< Time unit(s) */
} a_lpf_s;

/*!
 @brief Initialize function for Low Pass Filter
 @param[in,out] ctx points to an instance of Low Pass Filter structure
 @param[in] k Factor
 @param[in] t Time
*/
A_INLINE void a_lpf_init(a_lpf_s *ctx, a_real_t k, a_real_t t)
{
    ctx->t = t;
    ctx->k = k;
    ctx->o = 0;
}

/*!
 @brief Process function for Low Pass Filter
 @f{aligned}{
  y_n &= \cfrac {k} {k + t} y_{n-1} + \cfrac {t} {t + k} x \\
      &= (1 - \alpha) y_{n-1} + \alpha x, \alpha = \cfrac {t} {t + k}
 @f}
 @param[in,out] ctx points to an instance of Low Pass Filter structure
 @param[in] x Input
 @return Output
*/
A_INLINE a_real_t a_lpf_proc(a_lpf_s *ctx, a_real_t x)
{
    a_real_t inv_kt = ctx->t / (ctx->k + ctx->t);
    /* y[n] = y[n-1] * k / (k + t) + x * t / (k + t) */
    ctx->o *= 1 - inv_kt;
    ctx->o += x * inv_kt;
    return ctx->o;
}

/*!
 @brief Terminate function for Low Pass Filter
 @param[in,out] ctx points to an instance of Low Pass Filter structure
*/
A_INLINE void a_lpf_done(a_lpf_s *ctx) { ctx->o = 0; }

#endif /* __A_LPF_H__ */
