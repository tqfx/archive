/*!
 @file           a_math.c
 @brief          Calculate math library
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

#include "a_math.h"

#include <stdarg.h>

float a_inv_sqrt(float x)
{
    union
    {
        long i32;
        float f32;
    } b32[1] = {
        {
            .f32 = x,
        },
    };
    float xh = 0.5F * x;

    b32->i32 = 0x5F3759DF - (b32->i32 >> 1);
    x = b32->f32;

    x = x * (1.5F - (xh * x * x));
    x = x * (1.5F - (xh * x * x));

    return x;
}

unsigned int a_sqrt_u32(unsigned int x)
{
    unsigned int y = 0;

    for (unsigned int i = 0; i != 32; i += 2)
    {
        unsigned int k = 0x40000000UL >> i;

        if (k + y <= x)
        {
            x -= k + y;
            y = (y >> 1) | k;
        }
        else
        {
            y >>= 1;
        }
    }

    return y;
}

unsigned long long a_sqrt_u64(unsigned long long x)
{
    unsigned long long y = 0;

    for (unsigned int i = 0; i != 64; i += 2)
    {
        unsigned long long k = 0x4000000000000000ULL >> i;

        if (k + y <= x)
        {
            x -= k + y;
            y = (y >> 1) | k;
        }
        else
        {
            y >>= 1;
        }
    }

    return y;
}

void a_normalize_f32(unsigned int n, ...)
{
    va_list ap;

    unsigned int i;

    float norm = 0;

    va_start(ap, n);
    i = n;
    while (i--)
    {
        float *p = va_arg(ap, float *);
        norm += A_SQ(*p);
    }
    va_end(ap);

    norm = a_inv_sqrt(norm);

    va_start(ap, n);
    i = n;
    while (i--)
    {
        float *p = va_arg(ap, float *);
        *p *= norm;
    }
    va_end(ap);
}

double a_restrict_loop(double x, double min, double max)
{
    double len = max - min;
    if (x > max)
    {
        do
        {
            x -= len;
        } while (x > max);
    }
    else if (x < min)
    {
        do
        {
            x += len;
        } while (x < min);
    }
    return x;
}

float a_restrict_loop_f32(float x, float min, float max)
{
    float len = max - min;
    if (x > max)
    {
        do
        {
            x -= len;
        } while (x > max);
    }
    else if (x < min)
    {
        do
        {
            x += len;
        } while (x < min);
    }
    return x;
}

/* END OF FILE */
