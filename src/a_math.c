/*!
 @file a_math.c
 @brief Calculate math library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_math.h"

#include <stdarg.h>

float a_inv_sqrt(float x)
{
    union
    {
        float x;
        uint32_t l;
    } u[1] = {{x}};
    if (x > 0)
    {
        float xh = 0.5F * x;
        u->l = 0x5F3759DF - (u->l >> 1);
        u->x = u->x * (1.5F - (xh * u->x * u->x));
        u->x = u->x * (1.5F - (xh * u->x * u->x));
    }
    else if (x < 0)
    {
        u->l = 0xFFC00000;
    }
    else
    {
        u->l = 0x7F800000;
    }
    return u->x;
}

#undef A_SQRT_UINT
#define A_SQRT_UINT(bit, func, type, mask)         \
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
A_SQRT_UINT(32, a_sqrtul, unsigned long, 0x40000000UL)
A_SQRT_UINT(64, a_sqrtull, unsigned long long, 0x4000000000000000ULL)
#undef A_SQRT_UINT

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

#undef A_RESTRICT_LOOP
#define A_RESTRICT_LOOP(func, type)       \
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
A_RESTRICT_LOOP(a_restrict_loop, double)
A_RESTRICT_LOOP(a_restrict_loopf, float)
#undef A_RESTRICT_LOOP
