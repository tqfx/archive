/*!
 @file real.c
 @brief real number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/real.h"

void a_real_nadd(size_t n, a_real_t *p, a_real_t *l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_real_add(*l, *r);
    }
}

void a_real_nsub(size_t n, a_real_t *p, a_real_t *l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_real_sub(*l, *r);
    }
}

void a_real_nmul(size_t n, a_real_t *p, a_real_t *l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_real_mul(*l, *r);
    }
}

void a_real_ndiv(size_t n, a_real_t *p, a_real_t *l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = a_real_div(*l, *r);
    }
}

void a_real_nadd1(size_t n, a_real_t *p, a_real_t *l, a_real_t r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++p)
    {
        *p = a_real_add(*l, r);
    }
}

void a_real_nsubl(size_t n, a_real_t *p, a_real_t l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++r, ++p)
    {
        *p = a_real_sub(l, *r);
    }
}

void a_real_nsubr(size_t n, a_real_t *p, a_real_t *l, a_real_t r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++p)
    {
        *p = a_real_sub(*l, r);
    }
}

void a_real_nmul1(size_t n, a_real_t *p, a_real_t *l, a_real_t r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++p)
    {
        *p = a_real_mul(*l, r);
    }
}

void a_real_ndivl(size_t n, a_real_t *p, a_real_t l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++r, ++p)
    {
        *p = a_real_div(l, *r);
    }
}

void a_real_ndivr(size_t n, a_real_t *p, a_real_t *l, a_real_t r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++p)
    {
        *p = a_real_div(*l, r);
    }
}
