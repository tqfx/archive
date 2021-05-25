/**
 * *****************************************************************************
 * @file         ca_math.c/h
 * @brief        Calculate math library
 * @author       tqfx
 * @date         20210430
 * @version      1
 * @copyright    Copyright (c) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "ca_math.h"

/* Private includes ----------------------------------------------------------*/
#include <stdarg.h>

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

/**
 * @addtogroup     CA_MATH
 * @{
*/

float inv_sqrt(float x)
{
    float xh = 0.5F * x;
    long  i  = *(long *)&x;

    i = 0x5F3759DF - (i >> 1);
    x = *(float *)&i;
    x = x * (1.5F - (xh * x * x));
    x = x * (1.5F - (xh * x * x));

    return x;
}

unsigned int ca_sqrt_u32(unsigned int x)
{
    unsigned int y = 0U;

    for (unsigned char i = 0U; i != 32U; i += 2U)
    {
        unsigned int k = 0x40000000UL >> i;

        if (k + y <= x)
        {
            x -= k + y;
            y = (y >> 1U) | k;
        }
        else
        {
            y >>= 1U;
        }
    }

    return y;
}

void ca_normalize(unsigned int n, ...)
{
    va_list ap;

    unsigned int i;

    double norm = 0;

    va_start(ap, n);
    i = n;
    while (i--)
    {
        double *p = va_arg(ap, double *);
        norm += SQ(*p);
    }
    va_end(ap);

    norm = inv_sqrt(norm);

    va_start(ap, n);
    i = n;
    while (i--)
    {
        double *p = va_arg(ap, double *);
        *p *= norm;
    }
    va_end(ap);
}

void ca_normalize_f32(unsigned int n, ...)
{
    va_list ap;

    unsigned int i;

    float norm = 0;

    va_start(ap, n);
    i = n;
    while (i--)
    {
        float *p = va_arg(ap, float *);
        norm += SQ(*p);
    }
    va_end(ap);

    norm = inv_sqrt(norm);

    va_start(ap, n);
    i = n;
    while (i--)
    {
        float *p = va_arg(ap, float *);
        *p *= norm;
    }
    va_end(ap);
}

double restrict_loop(double x, double min, double max)
{
    if (x > max)
    {
        double len = max - min;
        do
        {
            x -= len;
        } while (x > max);
    }
    else if (x < min)
    {
        double len = max - min;
        do
        {
            x += len;
        } while (x < min);
    }
    return x;
}

float restrict_loop_f32(float x, float min, float max)
{
    if (x > max)
    {
        float len = max - min;
        do
        {
            x -= len;
        } while (x > max);
    }
    else if (x < min)
    {
        float len = max - min;
        do
        {
            x += len;
        } while (x < min);
    }
    return x;
}

/**
 * @}              End of CA_MATH group
*/

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
