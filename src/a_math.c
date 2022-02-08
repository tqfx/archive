/*!
 @file a_math.c
 @brief Calculate math library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_math.h"

#include <stdarg.h>

float a_inv_sqrt(float x)
{
    if (x > 0)
    {
        float xh = 0.5F * x;

        uint32_t ul = *(uint32_t *)&x;
        ul = 0x5F3759DF - (ul >> 1);
        x = *(float *)&ul;

        x = x * (1.5F - (xh * x * x));
        x = x * (1.5F - (xh * x * x));
    }
    else if (x < 0)
    {
        uint32_t ul = 0xFFC00000;
        x = *(float *)&ul;
    }
    else
    {
        uint32_t ul = 0x7F800000;
        x = *(float *)&ul;
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
