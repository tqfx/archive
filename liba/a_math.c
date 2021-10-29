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

float a_inv_sqrt(float _x)
{
    b32->f32 = _x;

    if (b32->u32 & 0x80000000)
    {
        b32->u32 = 0xFFC00000;
        _x = b32->f32;
    }
    else if (b32->u32 & 0x7FFFFFFF)
    {
        float xh = 0.5F * _x;

        b32->u32 = 0x5F3759DF - (b32->u32 >> 1);
        _x = b32->f32;

        _x = _x * (1.5F - (xh * _x * _x));
        _x = _x * (1.5F - (xh * _x * _x));
    }
    else
    {
        b32->u32 = 0x7F800000;
        _x = b32->f32;
    }

    return _x;
}

#undef __A_SQRT_UINT
#define __A_SQRT_UINT(_bit, _func, _type, _k)       \
    _type _func(_type _x)                           \
    {                                               \
        _type y = 0;                                \
        for (unsigned int i = 0; i != _bit; i += 2) \
        {                                           \
            _type k = _k >> i;                      \
            if (k + y <= _x)                        \
            {                                       \
                _x -= k + y;                        \
                y = (y >> 1) | k;                   \
            }                                       \
            else                                    \
            {                                       \
                y >>= 1;                            \
            }                                       \
        }                                           \
        return y;                                   \
    }
__A_SQRT_UINT(32, a_sqrtul, unsigned long, 0x40000000UL)
__A_SQRT_UINT(64, a_sqrtull, unsigned long long, 0x4000000000000000ULL)
#undef __A_SQRT_UINT

void a_normalizef(float *_p, size_t _n)
{
    aassert(!_n || _p);

    float norm = 0;
    float *q = _p + _n;

    for (float *p = _p; p != q; ++p)
    {
        norm += A_SQ(*p);
    }

    norm = a_inv_sqrt(norm);

    for (float *p = _p; p != q; ++p)
    {
        *p *= norm;
    }
}

void a_normalizevf(unsigned int _n, ...)
{
    va_list ap;
    float norm = 0;

    va_start(ap, _n);
    for (unsigned int n = _n; n; --n)
    {
        float *p = va_arg(ap, float *);
        norm += A_SQ(*p);
    }
    va_end(ap);

    norm = a_inv_sqrt(norm);

    va_start(ap, _n);
    for (unsigned int n = _n; n; --n)
    {
        float *p = va_arg(ap, float *);
        *p *= norm;
    }
    va_end(ap);
}

#undef __A_RESTRICT_LOOP
#define __A_RESTRICT_LOOP(_func, _type)           \
    _type _func(_type _x, _type _min, _type _max) \
    {                                             \
        _type siz = _max - _min;                  \
        if (_x > _max)                            \
        {                                         \
            do                                    \
            {                                     \
                _x -= siz;                        \
            } while (_x > _max);                  \
        }                                         \
        else if (_x < _min)                       \
        {                                         \
            do                                    \
            {                                     \
                _x += siz;                        \
            } while (_x < _min);                  \
        }                                         \
        return _x;                                \
    }
__A_RESTRICT_LOOP(a_restrict_loop, double)
__A_RESTRICT_LOOP(a_restrict_loopf, float)
#undef __A_RESTRICT_LOOP

/* END OF FILE */
