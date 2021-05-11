/**
 * *****************************************************************************
 * @file         ca_lpf.h
 * @brief        Low Pass Filter
 * @author       tqfx
 * @date         20210430
 * @version      1
 * @copyright    Copyright (c) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CA_LPF_H__
#define __CA_LPF_H__

/* Includes ------------------------------------------------------------------*/
#include "ca.h"

/* Exported types ------------------------------------------------------------*/

/**
 * @ingroup        CA
 * @defgroup       CA_LPF Low Pass Filter Group
 * @addtogroup     CA_LPF
 * @{
*/

/**
 * @struct         ca_lpf_f32_t
 * @brief          Instance structure for the Low Pass Filter
*/
typedef struct
{
    float out; /* Output */

    float k; /* Parameter of filtering              */
    float t; /* Time interval of filtering, unit /s */

} ca_lpf_f32_t;

/* Private defines -----------------------------------------------------------*/

/**
 * @brief          Initialization function for Low Pass Filter
 * @param[in,out]  lpf: An instance of the Low Pass Filter structure
 * @param[in]      k: Parameter of filtering
 * @param[in]      t: Time interval of filtering, unit /s
*/
static inline void ca_lpf_f32_init(ca_lpf_f32_t *lpf,
                                   float         k,
                                   float         t)
{
    lpf->t = t;
    lpf->k = k;
}

/**
 * @brief          Reset function for Low Pass Filter
 * @param[in,out]  lpf: An instance of the Low Pass Filter structure
*/
static inline void ca_lpf_reset(ca_lpf_f32_t *lpf)
{
    lpf->out = 0;
}

/**
 * @brief          Process function for Low Pass Filter
 * @param[in,out]  lpf: An instance of the Low Pass Filter structure
 * @param[in]      x: Input
 * @return         float Output
*/
static inline float ca_lpf_f32(ca_lpf_f32_t *lpf,
                               float         x)
{
    float inv_kt = 1 / (lpf->k + lpf->t);

    /* y[n] = y[n-1] * k / (k + t) + x * t / (k + t) */
    lpf->out *= inv_kt * lpf->k;
    lpf->out += inv_kt * lpf->t * x;

    return lpf->out;
}

/**
 * @}              End of CA_LPF group
*/

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __CA_LPF_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
