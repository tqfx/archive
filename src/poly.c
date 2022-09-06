/*!
 @file poly.c
 @brief polynomial
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/poly.h"

#include <assert.h>

a_real_t a_horner(const a_real_t *a, size_t n, a_real_t x)
{
    assert(!n || a);
    a_real_t y = 0;
    for (const a_real_t *q = a + n; a != q; ++a)
    {
        y = y * x + *a;
    }
    return y;
}

a_real_t a_hornerr(const a_real_t *a, size_t n, a_real_t x)
{
    assert(!n || a);
    a_real_t y = 0;
    for (const a_real_t *q = --a + n; q != a; --q)
    {
        y = y * x + *q;
    }
    return y;
}
