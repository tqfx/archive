/*!
 @file           a_poly.c
 @brief          polynomial
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_poly.h"

#undef __A_HORNER
#define __A_HORNER(func, type)             \
    type func(type *a, size_t n, type x)   \
    {                                      \
        type y = 0;                        \
        for (type *q = a + n; a != q; ++a) \
        {                                  \
            y = y * x + *a;                \
        }                                  \
        return y;                          \
    }
__A_HORNER(a_horner, double)
__A_HORNER(a_hornerf, float)
#undef __A_HORNER

#undef __A_HORNERR
#define __A_HORNERR(func, type)              \
    type func(type *a, size_t n, type x)     \
    {                                        \
        type y = 0;                          \
        for (type *q = --a + n; q != a; --q) \
        {                                    \
            y = y * x + *q;                  \
        }                                    \
        return y;                            \
    }
__A_HORNERR(a_hornerr, double)
__A_HORNERR(a_hornerrf, float)
#undef __A_HORNERR

/* END OF FILE */
