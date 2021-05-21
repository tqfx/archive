/*!
 @file           ca_lpf.h
 @brief          Low Pass Filter
 @details        https://en.wikipedia.org/wiki/Low-pass_filter
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-05-21
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
#ifndef __CA_LPF_H__
#define __CA_LPF_H__

#include "ca.h"

/*!
 @addtogroup     CA
 @{
 @addtogroup     CA_LPF Low Pass Filter
 @{
*/

/*!
 @struct         ca_lpf_f32_t
 @brief          Instance structure for the Low Pass Filter
*/
typedef struct
{
    float out; /*!< Output */
    float k;   /*!< Parameter of filtering              */
    float t;   /*!< Time interval of filtering, unit /s */
} ca_lpf_f32_t;

__STATIC_INLINE
/*!
 @brief          Initialization function for Low Pass Filter
 @param[in,out]  lpf: An instance of the Low Pass Filter structure
 @param[in]      k: Parameter of filtering
 @param[in]      t: Time interval of filtering, unit /s
*/
void ca_lpf_f32_init(ca_lpf_f32_t *lpf,
                     float         k,
                     float         t)
{
    lpf->t = t;
    lpf->k = k;
}

__STATIC_INLINE
/*!
 @brief          Reset function for Low Pass Filter
 @param[in,out]  lpf: An instance of the Low Pass Filter structure
*/
void ca_lpf_reset(ca_lpf_f32_t *lpf)
{
    lpf->out = 0;
}

__STATIC_INLINE
/*!
 @brief          Process function for Low Pass Filter
 @param[in,out]  lpf: An instance of the Low Pass Filter structure
 @param[in]      x: Input
 @return         Output
*/
float ca_lpf_f32(ca_lpf_f32_t *lpf,
                 float         x)
{
    float inv_kt = lpf->t / (lpf->k + lpf->t);

    /* y[n] = y[n-1] * k / (k + t) + x * t / (k + t) */
    lpf->out *= 1 - inv_kt;
    lpf->out += x * inv_kt;

    return lpf->out;
}

/*!< @} */
/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __CA_LPF_H__ */

/* END OF FILE */
