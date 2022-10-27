#include "a/math.h"
#include "test.h"
#include <math.h>

A_STATIC a_void_t test_sq(void)
{
    a_int_t x = 2;

    TEST_BUG(A_SQ(x) == 4);
}

A_STATIC a_void_t test_abs(void)
{
    long double x = -1.0L;

    TEST_BUG(A_ABS(x) > 0);
}

A_STATIC a_void_t test_sgn(void)
{
    double pos = +10.0;
    double neg = -10.0;
    double zero = 0.0;

    TEST_BUG(A_SGN(pos) == 1);
    TEST_BUG(A_SGN(neg) == -1);
    TEST_BUG(A_SGN(zero) == 0);
}

A_STATIC a_void_t test_sqrt_inv(void)
{
    a_f32_t data[] = {
        -1.0F,
        -0.0F,
        1e-10F,
        1.0F,
        4.0F,
        2.5F * 2.5F,
    };
    for (a_uint_t i = 0; i != sizeof(data) / sizeof(a_f32_t); ++i)
    {
        printf("1/sqrt(%g):\t%-10g%-10g\n", (double)data[i],
               1.0 / (double)sqrtf(data[i]),
               (double)a_sqrt_inv(data[i]));
    }
}

int main(void)
{
    test_sq();
    test_abs();
    test_sgn();
    test_sqrt_inv();

    return A_SUCCESS;
}
