/*!
 @file imag.c
 @brief imaginary number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/imag.h"

void a_imag_add(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r)
{
    for (a_imag_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        p->r = l->r + r->r;
        p->i = l->i + r->i;
    }
}

void a_imag_sub(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r)
{
    for (a_imag_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        p->r = l->r - r->r;
        p->i = l->i - r->i;
    }
}

void a_imag_mul(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r)
{
    for (a_imag_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        p->r = l->r * r->r - l->i * r->i;
        p->i = l->i * r->r + l->r * r->i;
    }
}

void a_imag_div(size_t n, a_imag_t *p, a_imag_t *l, a_imag_t *r)
{
    for (a_imag_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        a_real_t den_inv = 1 / (r->r * r->r + r->i * r->i);
        p->r = (l->r * r->r + l->i * r->i) * den_inv;
        p->i = (l->i * r->r - l->r * r->i) * den_inv;
    }
}
