/*!
 @file a_poly.c
 @brief polynomial
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_poly.h"

#undef a_horner
#undef A_HORNER
#define A_HORNER(func, type)                     \
    type func(const type *a, size_t n, type x)   \
    {                                            \
        AASSERT(!n || a);                        \
                                                 \
        type y = 0;                              \
                                                 \
        for (const type *q = a + n; a != q; ++a) \
        {                                        \
            y = y * x + *a;                      \
        }                                        \
                                                 \
        return y;                                \
    }
A_HORNER(a_horner, double)
A_HORNER(a_hornerf, float)
#undef A_HORNER

#undef a_hornerr
#undef A_HORNERR
#define A_HORNERR(func, type)                      \
    type func(const type *a, size_t n, type x)     \
    {                                              \
        AASSERT(!n || a);                          \
                                                   \
        type y = 0;                                \
                                                   \
        for (const type *q = --a + n; q != a; --q) \
        {                                          \
            y = y * x + *q;                        \
        }                                          \
                                                   \
        return y;                                  \
    }
A_HORNERR(a_hornerr, double)
A_HORNERR(a_hornerrf, float)
#undef A_HORNERR
