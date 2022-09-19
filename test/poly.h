/*!
 @file poly.h
 @brief Test polynomial
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_POLY_H__
#define __TEST_POLY_H__

#include "a/poly.h"
#include <stdio.h>

static a_void_t print(const a_real_t *a, a_size_t n)
{
    putchar('{');
    a_forenum(a_size_t, i, n)
    {
        printf("%g", a[i]);
        if (i < n - 1)
        {
            putchar(',');
        }
    }
    putchar('}');
}

static void test(void)
{
    a_real_t x3[] = {A_REAL_C(1.0), A_REAL_C(2.0), A_REAL_C(3.0)};
    print(x3, 3);
    printf("=%g\n", a_poly_c(x3, 3, 2));
    a_poly_inv(x3, 3);
    print(x3, 3);
    printf("=%g\n", a_poly_c(x3, 3, 2));
    print(x3, 3);
    printf("=%g\n", a_poly_r(x3, 3, 2));

    a_real_t x4[] = {A_REAL_C(1.0), A_REAL_C(2.0), A_REAL_C(3.0), A_REAL_C(4.0)};
    print(x4, 4);
    printf("=%g\n", a_poly_c(x4, 4, 2));
    a_poly_inv(x4, 4);
    print(x4, 4);
    printf("=%g\n", a_poly_c(x4, 4, 2));
    print(x4, 4);
    printf("=%g\n", a_poly_r(x4, 4, 2));
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t poly_c(void);
a_int_t poly_cpp(void);
#if defined(__cplusplus)
} /* extern "C" */
#define func poly_cpp
#else /* !__cplusplus */
#define func poly_c
#endif /* __cplusplus */
a_int_t func(void)
{
    printf("%s\n", __func__);
    test();
    return A_SUCCESS;
}

#endif /* __TEST_POLY_H__ */
