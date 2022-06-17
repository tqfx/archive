/*!
 @file real.c
 @brief real number operation
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/real.h"

void a_real_add(size_t n, a_real_t *p, a_real_t *l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = *l + *r;
    }
}

void a_real_sub(size_t n, a_real_t *p, a_real_t *l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = *l - *r;
    }
}

void a_real_mul(size_t n, a_real_t *p, a_real_t *l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = *l * *r;
    }
}

void a_real_div(size_t n, a_real_t *p, a_real_t *l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = *l / *r;
    }
}

void a_real_add1(size_t n, a_real_t *p, a_real_t *l, a_real_t r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++p)
    {
        *p = *l + r;
    }
}

void a_real_subl(size_t n, a_real_t *p, a_real_t l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++r, ++p)
    {
        *p = l - *r;
    }
}

void a_real_subr(size_t n, a_real_t *p, a_real_t *l, a_real_t r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++p)
    {
        *p = *l - r;
    }
}

void a_real_mul1(size_t n, a_real_t *p, a_real_t *l, a_real_t r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++p)
    {
        *p = *l * r;
    }
}

void a_real_divl(size_t n, a_real_t *p, a_real_t l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++r, ++p)
    {
        *p = l / *r;
    }
}

void a_real_divr(size_t n, a_real_t *p, a_real_t *l, a_real_t r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++p)
    {
        *p = *l / r;
    }
}
