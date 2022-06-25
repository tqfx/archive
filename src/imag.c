/*!
 @file imag.c
 @brief imaginary number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/imag.h"

void a_imag_nadd(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r)
{
    for (a_imag_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_imag_add(*l, *r);
    }
}

void a_imag_nsub(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r)
{
    for (a_imag_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_imag_sub(*l, *r);
    }
}

void a_imag_nmul(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r)
{
    for (a_imag_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_imag_mul(*l, *r);
    }
}

void a_imag_ndiv(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r)
{
    for (a_imag_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_imag_div(*l, *r);
    }
}
