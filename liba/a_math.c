/*!
 @file           a_math.c
 @brief          Calculate math library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_math.h"

#include <stdarg.h>

static union
{
    float f32;
    unsigned long u32;
} b32[1];

float a_inv_sqrt(float x)
{
    b32->f32 = x;

    if (b32->u32 & 0x80000000)
    {
        b32->u32 = 0x7FC00000;
        x = b32->f32;
    }
    else if (b32->u32 & 0x7FFFFFFF)
    {
        float xh = 0.5F * x;

        b32->u32 = 0x5F3759DF - (b32->u32 >> 1);
        x = b32->f32;

        x = x * (1.5F - (xh * x * x));
        x = x * (1.5F - (xh * x * x));
    }
    else
    {
        b32->u32 = 0x7F800000;
        x = b32->f32;
    }

    return x;
}

unsigned long a_sqrt_u32(unsigned long x)
{
    unsigned long y = 0;

    for (unsigned int i = 0; i != 32; i += 2)
    {
        unsigned long k = 0x40000000UL >> i;

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
