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

#define a_lpf_t(bit)                                                \
    typedef struct a_lpf_f##bit##_t                                 \
    {                                                               \
        float##bit##_t o; /* Output */                              \
        float##bit##_t k; /* Parameter of filtering              */ \
        float##bit##_t t; /* Time interval of filtering, unit /s */ \
    } a_lpf_f##bit##_t
a_lpf_t(32);
a_lpf_t(64);
#undef a_lpf_t

#define A_LPF_INIT(bit)                             \
    __STATIC_INLINE                                 \
    void a_lpf_f##bit##_init(a_lpf_f##bit##_t *ctx, \
                             float##bit##_t k,      \
                             float##bit##_t t)      \
    {                                               \
        ctx->t = t;                                 \
        ctx->k = k;                                 \
    }
A_LPF_INIT(32)
A_LPF_INIT(64)
#undef A_LPF_INIT

#define A_LPF(bit)                                          \
    __STATIC_INLINE                                         \
    float##bit##_t a_lpf_f##bit(a_lpf_f##bit##_t *ctx,      \
                                float##bit##_t x)           \
    {                                                       \
        float##bit##_t inv_kt = ctx->t / (ctx->k + ctx->t); \
                                                            \
        /* y[n] = y[n-1] * k / (k + t) + x * t / (k + t) */ \
        ctx->o *= 1 - inv_kt;                               \
        ctx->o += x * inv_kt;                               \
                                                            \
        return ctx->o;                                      \
    }
A_LPF(32)
A_LPF(64)
#undef A_LPF

#define A_LPF_RESET(bit)                             \
    __STATIC_INLINE                                  \
    void a_lpf_f##bit##_reset(a_lpf_f##bit##_t *ctx) \
    {                                                \
        ctx->o = 0;                                  \
    }
A_LPF_RESET(32)
A_LPF_RESET(64)
#undef A_LPF_RESET

/*!
 @brief          Instance structure for Low Pass Filter
*/
#define a_lpf_t(bit) a_lpf_f##bit##_t

/*!
 @brief          Initialization function for Low Pass Filter
 @param[in]      bit: bits for the floating point data
 @param[in,out]  ctx: points to an instance of Low Pass Filter structure
 @param[in]      k: Parameter of filtering
 @param[in]      t: Time interval of filtering, unit /s
*/
#define a_lpf_init(bit, ctx, k, t) a_lpf_f##bit##_init(ctx, k, t)

/*!
 @brief          Process function for Low Pass Filter
 \f{aligned}{
     y_n &= \cfrac {k} {k + t} y_{n-1} + \cfrac {t} {t + k} x \\
         &= (1 - \alpha) y_{n-1} + \alpha x, \alpha = \cfrac {t} {t + k}
 \f}
 @param[in]      bit: bits for the floating point data
 @param[in,out]  ctx: points to an instance of Low Pass Filter structure
 @param[in]      x: Input
 @return         Output
*/
#define a_lpf(bit, ctx, x) a_lpf_f##bit(ctx, x)

/*!
 @brief          Reset function for Low Pass Filter
 @param[in]      bit: bits for the floating point data
 @param[in,out]  ctx: points to an instance of Low Pass Filter structure
*/
#define a_lpf_reset(bit, ctx) a_lpf_f##bit##_reset(ctx)

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_LPF_H__ */

/* END OF FILE */
