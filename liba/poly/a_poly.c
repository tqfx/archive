/*!
 @file a_poly.c
 @brief polynomial
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_poly.h"

#undef a_horner
#undef __A_HORNER
#define __A_HORNER(_func, _type)                      \
    _type _func(const _type *_a, size_t _n, _type _x) \
    {                                                 \
        aassert(!_n || _a);                           \
                                                      \
        _type y = 0;                                  \
                                                      \
        for (const _type *q = _a + _n; _a != q; ++_a) \
        {                                             \
            y = y * _x + *_a;                         \
        }                                             \
                                                      \
        return y;                                     \
    }
__A_HORNER(a_horner, double)
__A_HORNER(a_hornerf, float)
#undef __A_HORNER

#undef a_hornerr
#undef __A_HORNERR
#define __A_HORNERR(_func, _type)                      \
    _type _func(const _type *_a, size_t _n, _type _x)  \
    {                                                  \
        aassert(!_n || _a);                            \
                                                       \
        _type y = 0;                                   \
                                                       \
        for (const _type *q = --_a + _n; q != _a; --q) \
        {                                              \
            y = y * _x + *q;                           \
        }                                              \
                                                       \
        return y;                                      \
    }
__A_HORNERR(a_hornerr, double)
__A_HORNERR(a_hornerrf, float)
#undef __A_HORNERR

/* END OF FILE */
