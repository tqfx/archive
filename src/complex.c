/*!
 @file complex.c
 @brief complex number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/complex.h"

void a_complex_nadd(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r)
{
    for (a_complex_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_complex_add(*l, *r);
    }
}

void a_complex_nsub(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r)
{
    for (a_complex_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_complex_sub(*l, *r);
    }
}

void a_complex_nmul(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r)
{
    for (a_complex_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_complex_mul(*l, *r);
    }
}

void a_complex_ndiv(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r)
{
    for (a_complex_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_complex_div(*l, *r);
    }
}
