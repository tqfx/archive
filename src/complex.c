/*!
 @file complex.c
 @brief complex number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/complex.h"

void a_complex_add(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r)
{
    for (a_complex_t *q = p + n; p != q; ++l, ++r, ++p)
    {
#if defined(_MSC_VER)

        p->_Val[0] = l->_Val[0] + r->_Val[0];
        p->_Val[1] = l->_Val[1] + r->_Val[1];

#else /* !_MSC_VER */

        *p = *l + *r;

#endif /* _MSC_VER */
    }
}

void a_complex_sub(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r)
{
    for (a_complex_t *q = p + n; p != q; ++l, ++r, ++p)
    {
#if defined(_MSC_VER)

        p->_Val[0] = l->_Val[0] - r->_Val[0];
        p->_Val[1] = l->_Val[1] - r->_Val[1];

#else /* !_MSC_VER */

        *p = *l - *r;

#endif /* _MSC_VER */
    }
}

void a_complex_mul(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r)
{
    for (a_complex_t *q = p + n; p != q; ++l, ++r, ++p)
    {
#if defined(_MSC_VER)

#if A_DEF_FLOAT == 0
        *p = _FCmulcc(*l, *r);
#elif A_DEF_FLOAT == 1
        *p = _Cmulcc(*l, *r);
#elif A_DEF_FLOAT == 2
        *p = _LCmulcc(*l, *r);
#endif /* A_DEF_FLOAT */

#else /* !_MSC_VER */

        *p = *l * *r;

#endif /* _MSC_VER */
    }
}

void a_complex_div(size_t n, a_complex_t *p, a_complex_t *l, a_complex_t *r)
{
    for (a_complex_t *q = p + n; p != q; ++l, ++r, ++p)
    {
#if defined(_MSC_VER)

        a_real_t den_inv = r->_Val[0] * r->_Val[0] + r->_Val[1] * r->_Val[1];
        p->_Val[0] = (l->_Val[0] * r->_Val[0] + l->_Val[1] * r->_Val[1]) * den_inv;
        p->_Val[1] = (l->_Val[1] * r->_Val[1] - l->_Val[1] * r->_Val[1]) * den_inv;

#else /* !_MSC_VER */

        *p = *l / *r;

#endif /* _MSC_VER */
    }
}
