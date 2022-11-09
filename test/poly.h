#ifndef TEST_POLY_H
#define TEST_POLY_H
#define MAIN_(s, argc, argv) poly##s(argc, argv)
#include "test.h"
#include "a/poly.h"

#if a_prereq_gnuc(4, 6) || __has_warning("-Wdouble-promotion")
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* -Wdouble-promotion */

static void print(const a_real_t *a, a_size_t n)
{
    putchar('{');
    a_forenum(a_size_t, i, n)
    {
        printf(A_REAL_PRI("", "g"), a[i]);
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
    printf("=" A_REAL_PRI("", "g") "\n", a_poly_eval(x3, 3, 2));
    a_poly_inv(x3, 3);
    print(x3, 3);
    printf("=" A_REAL_PRI("", "g") "\n", a_poly_eval(x3, 3, 2));
    print(x3, 3);
    printf("=" A_REAL_PRI("", "g") "\n", a_poly_evar(x3, 3, 2));

    a_real_t x4[] = {A_REAL_C(1.0), A_REAL_C(2.0), A_REAL_C(3.0), A_REAL_C(4.0)};
    print(x4, 4);
    printf("=" A_REAL_PRI("", "g") "\n", a_poly_eval(x4, 4, 2));
    a_poly_inv(x4, 4);
    print(x4, 4);
    printf("=" A_REAL_PRI("", "g") "\n", a_poly_eval(x4, 4, 2));
    print(x4, 4);
    printf("=" A_REAL_PRI("", "g") "\n", a_poly_evar(x4, 4, 2));
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", __FUNCTION__);
    test();
    return 0;
}

#endif /* TEST_POLY_H */
