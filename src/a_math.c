/*!
 @file a_math.c
 @brief Calculate math library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
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
        b32->u32 = 0xFFC00000;
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

#undef __A_SQRT_UINT
#define __A_SQRT_UINT(bit, func, type, mask)       \
    type func(type x)                              \
    {                                              \
        type y = 0;                                \
        for (unsigned int i = 0; i != bit; i += 2) \
        {                                          \
            type k = mask >> i;                    \
            if (k + y <= x)                        \
            {                                      \
                x -= k + y;                        \
                y = (y >> 1) | k;                  \
            }                                      \
            else                                   \
            {                                      \
                y >>= 1;                           \
            }                                      \
        }                                          \
        return y;                                  \
    }
__A_SQRT_UINT(32, a_sqrtul, unsigned long, 0x40000000UL)
__A_SQRT_UINT(64, a_sqrtull, unsigned long long, 0x4000000000000000ULL)
#undef __A_SQRT_UINT

void a_normalizef(float *dat, size_t num)
{
    AASSERT(!num || dat);

    float norm = 0;
    float *q = dat + num;

    for (float *p = dat; p != q; ++p)
    {
        norm += A_SQ(*p);
    }

    norm = a_inv_sqrt(norm);

    for (float *p = dat; p != q; ++p)
    {
        *p *= norm;
    }
}

void a_normalizevf(unsigned int num, ...)
{
    va_list ap;
    float norm = 0;

    va_start(ap, num);
    for (unsigned int n = num; n; --n)
    {
        float *p = va_arg(ap, float *);
        norm += A_SQ(*p);
    }
    va_end(ap);

    norm = a_inv_sqrt(norm);

    va_start(ap, num);
    for (unsigned int n = num; n; --n)
    {
        float *p = va_arg(ap, float *);
        *p *= norm;
    }
    va_end(ap);
}

#undef __A_RESTRICT_LOOP
#define __A_RESTRICT_LOOP(func, type)     \
    type func(type x, type min, type max) \
    {                                     \
        type siz = max - min;             \
        if (x > max)                      \
        {                                 \
            do                            \
            {                             \
                x -= siz;                 \
            } while (x > max);            \
        }                                 \
        else if (x < min)                 \
        {                                 \
            do                            \
            {                             \
                x += siz;                 \
            } while (x < min);            \
        }                                 \
        return x;                         \
    }
__A_RESTRICT_LOOP(a_restrict_loop, double)
__A_RESTRICT_LOOP(a_restrict_loopf, float)
#undef __A_RESTRICT_LOOP
