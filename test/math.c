/*!
 @file math.c
 @brief Test mathematical algorithm library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/math.h"

#include "test.h"

#include <math.h>

static void test_sq(void)
{
    int x = 2;

    TEST_BUG(A_SQ(x) == 4);
}

static void test_abs(void)
{
    long double x = A_LDBL_C(-1.0);

    TEST_BUG(A_ABS(x) > 0);
}

static void test_sgn(void)
{
    double pos = A_DBL_C(+10.0);
    double neg = A_DBL_C(-10.0);
    double zero = A_DBL_C(0.0);

    TEST_BUG(A_SGN(pos) == 1);
    TEST_BUG(A_SGN(neg) == -1);
    TEST_BUG(A_SGN(zero) == 0);
}

static void test_inv_sqrt(void)
{
    float data[] = {
        A_FLT_C(-1.0),
        A_FLT_C(-0.0),
        A_FLT_C(1e-10),
        A_FLT_C(1.0),
        A_FLT_C(4.0),
        A_FLT_C(2.5) * A_FLT_C(2.5),
    };
    for (unsigned int i = 0; i != sizeof(data) / sizeof(float); ++i)
    {
        printf("1/sqrt(%g):\t%-10g%-10g\n", (double)data[i],
               1 / (double)A_FLT_F(sqrt, data[i]),
               (double)a_inv_sqrt(data[i]));
    }
}

int main(int argc, char *argv[])
{
    test_sq();
    test_abs();
    test_sgn();
    test_inv_sqrt();

    if (argc > 1)
    {
        (void)(argv);
    }

    return 0;
}
