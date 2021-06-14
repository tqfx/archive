/*!
 @file           ca-math.c
 @brief          Calculate math library
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-05-25
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

#include "ca-math.h"

#include <stdarg.h>

float inv_sqrt(float x)
{
    float xh = 0.5F * x;
    long i = *(long *)&x;

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

unsigned long long ca_sqrt_u64(unsigned long long x)
{
    unsigned long long y = 0U;

    for (unsigned char i = 0U; i != 64U; i += 2U)
    {
        unsigned long long k = 0x4000000000000000ULL >> i;

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

/* END OF FILE */
