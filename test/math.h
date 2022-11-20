#ifndef TEST_MATH_H
#define TEST_MATH_H
#define MAIN_(s, argc, argv) math##s(argc, argv)
#include "test.h"
#include "a/math.h"
#include <math.h>

static void test_sq(void)
{
    a_int_t x = 2;
    TEST_BUG(A_SQ(x) == 4);
}

static void test_abs(void)
{
    a_extend_t x = A_EXTEND_C(-1.0);
    TEST_BUG(A_ABS(x) > 0);
}

static void test_sgn(void)
{
    a_double_t pos = A_DOUBLE_C(+10.0);
    a_double_t neg = A_DOUBLE_C(-10.0);
    a_double_t zero = A_DOUBLE_C(0.0);
    TEST_BUG(A_SGN(pos) == 1);
    TEST_BUG(A_SGN(neg) == -1);
    TEST_BUG(A_SGN(zero) == 0);
}

static void test_sqrt_inv(void)
{
    a_f32_t data[] = {
        A_F32_C(-1.0),
        A_F32_C(-0.0),
        A_F32_C(1e-10),
        A_F32_C(1.0),
        A_F32_C(4.0),
        A_F32_C(2.5) * A_F32_C(2.5),
    };
    for (a_uint_t i = 0; i != sizeof(data) / sizeof(a_f32_t); ++i)
    {
        printf("1/sqrt(%g):\t%-10g%-10g\n", a_double_c(data[i]),
               1 / a_double_c(A_F32_F1(sqrt, data[i])),
               a_double_c(a_sqrt_inv(data[i])));
    }
}

static void test_u32_sqrt(void)
{
    TEST_BUG(a_u32_sqrt(A_U32_C(~0)) == A_U16_C(0xFFFF));
    TEST_BUG(a_u32_sqrt(A_U32_C(0x10000)) == A_U16_C(0x100));
    TEST_BUG(a_u32_sqrt(A_U32_C(0xFFFFFFFF)) == A_U16_C(0xFFFF));
}

static void test_u64_sqrt(void)
{
    TEST_BUG(a_u64_sqrt(A_U64_C(~0)) == A_U32_C(0xFFFFFFFF));
    TEST_BUG(a_u64_sqrt(A_U64_C(0x100000000)) == A_U32_C(0x10000));
    TEST_BUG(a_u64_sqrt(A_U64_C(0xFFFFFFFFFFFFFFFF)) == A_U32_C(0xFFFFFFFF));
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", A_FUNC);
    test_sq();
    test_abs();
    test_sgn();
    test_sqrt_inv();
    test_u32_sqrt();
    test_u64_sqrt();
    return 0;
}

#endif /* TEST_MATH_H */
