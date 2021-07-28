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
 @ingroup        CA
 @defgroup       CA_LPF Low Pass Filter
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

/*!
 @struct         ca_lpf_f32_t
 @brief          Instance structure for float Low Pass Filter
*/
typedef struct
{
    float out; /*!< Output */
    float k;   /*!< Parameter of filtering              */
    float t;   /*!< Time interval of filtering, unit /s */
} ca_lpf_f32_t;

/*!
 @struct         ca_lpf_f64_t
 @brief          Instance structure for double Low Pass Filter
*/
typedef struct
{
    double out; /*!< Output */
    double k;   /*!< Parameter of filtering              */
    double t;   /*!< Time interval of filtering, unit /s */
} ca_lpf_f64_t;

__STATIC_INLINE
/*!
 @brief          Initialization function for float Low Pass Filter
 @param[in,out]  lpf: An instance of float Low Pass Filter structure
 @param[in]      k: Parameter of filtering
 @param[in]      t: Time interval of filtering, unit /s
*/
void ca_lpf_f32_init(ca_lpf_f32_t *lpf,
                     float k,
                     float t)
{
    lpf->t = t;
    lpf->k = k;
}

__STATIC_INLINE
/*!
 @brief          Initialization function for double Low Pass Filter
 @param[in,out]  lpf: An instance of double Low Pass Filter structure
 @param[in]      k: Parameter of filtering
 @param[in]      t: Time interval of filtering, unit /s
*/
void ca_lpf_f64_init(ca_lpf_f64_t *lpf,
                     double k,
                     double t)
{
    lpf->t = t;
    lpf->k = k;
}

__STATIC_INLINE
/*!
 @brief          Reset function for float Low Pass Filter
 @param[in,out]  lpf: An instance of float Low Pass Filter structure
*/
void ca_lpf_f32_reset(ca_lpf_f32_t *lpf)
{
    lpf->out = 0;
}

__STATIC_INLINE
/*!
 @brief          Reset function for double Low Pass Filter
 @param[in,out]  lpf: An instance of double Low Pass Filter structure
*/
void ca_lpf_f64_reset(ca_lpf_f64_t *lpf)
{
    lpf->out = 0;
}

__STATIC_INLINE
/*!
 @brief          Process function for float Low Pass Filter
 \f{aligned}{
     y_n &= \cfrac {k} {k + t} y_{n-1} + \cfrac {t} {t + k} x \\
         &= (1 - \alpha) y_{n-1} + \alpha x, \alpha = \cfrac {t} {t + k}
 \f}
 @param[in,out]  lpf: An instance of float Low Pass Filter structure
 @param[in]      x: Input
 @return         Output
*/
float ca_lpf_f32(ca_lpf_f32_t *lpf,
                 float x)
{
    float inv_kt = lpf->t / (lpf->k + lpf->t);

    /* y[n] = y[n-1] * k / (k + t) + x * t / (k + t) */
    lpf->out *= 1 - inv_kt;
    lpf->out += x * inv_kt;

    return lpf->out;
}

__STATIC_INLINE
/*!
 @brief          Process function for double Low Pass Filter
 \f{aligned}{
     y_n &= \cfrac {k} {k + t} y_{n-1} + \cfrac {t} {t + k} x \\
         &= (1 - \alpha) y_{n-1} + \alpha x, \alpha = \cfrac {t} {t + k}
 \f}
 @param[in,out]  lpf: An instance of double Low Pass Filter structure
 @param[in]      x: Input
 @return         Output
*/
double ca_lpf_f64(ca_lpf_f64_t *lpf,
                  double x)
{
    double inv_kt = lpf->t / (lpf->k + lpf->t);

    /* y[n] = y[n-1] * k / (k + t) + x * t / (k + t) */
    lpf->out *= 1 - inv_kt;
    lpf->out += x * inv_kt;

    return lpf->out;
}

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_LPF_H__ */

/* END OF FILE */
