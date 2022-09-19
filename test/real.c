/*!
 @file real.c
 @brief Test real number
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/a.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* diagnostic */

A_STATIC a_void_t test(void)
{
    a_real_t lhs = 1;
    a_real_t rhs = 2;

    printf(A_REAL_PRI(, "g+") A_REAL_PRI(, "g=") A_REAL_PRI(, "g\n"), lhs, rhs, lhs + rhs);
    printf(A_REAL_PRI(, "g-") A_REAL_PRI(, "g=") A_REAL_PRI(, "g\n"), lhs, rhs, lhs - rhs);
    printf(A_REAL_PRI(, "g*") A_REAL_PRI(, "g=") A_REAL_PRI(, "g\n"), lhs, rhs, lhs * rhs);
    printf(A_REAL_PRI(, "g/") A_REAL_PRI(, "g=") A_REAL_PRI(, "g\n"), lhs, rhs, lhs / rhs);
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */

A_STATIC a_void_t real_add1(a_size_t n, a_real_t *p, a_real_t *lhs, a_real_t *rhs)
{
    for (a_real_t *q = p + n; p < q; ++lhs, ++rhs, ++p)
    {
        *p = *lhs + *rhs;
    }
}

// https://www.lysator.liu.se/c/duffs-device.html
#define DUFF_DEVICE_8(count, action)       \
    do                                     \
    {                                      \
        size_t times__ = (count + 7) >> 3; \
        switch (count & 7)                 \
        {                                  \
        case 0:                            \
            do                             \
            {                              \
                action;                    \
            case 7:                        \
                action;                    \
            case 6:                        \
                action;                    \
            case 5:                        \
                action;                    \
            case 4:                        \
                action;                    \
            case 3:                        \
                action;                    \
            case 2:                        \
                action;                    \
            case 1:                        \
                action;                    \
            } while (--times__);           \
        default:                           \
            break;                         \
        }                                  \
    } while (0)

A_STATIC a_void_t real_add2(a_size_t n, a_real_t *p, a_real_t *lhs, a_real_t *rhs)
{
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif /* diagnostic */
    if (n)
    {
        DUFF_DEVICE_8(n, *p++ = *lhs++ + *rhs++);
    }
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */
}

A_STATIC a_void_t real_add3(a_size_t n, a_real_t *p, a_real_t *lhs, a_real_t *rhs)
{
    a_real_t *b = p;
    for (a_real_t *q = b + (n >> 3 << 3); p < q; lhs += 8, rhs += 8, p += 8)
    {
        p[0] = lhs[0] + rhs[0];
        p[1] = lhs[1] + rhs[1];
        p[2] = lhs[2] + rhs[2];
        p[3] = lhs[3] + rhs[3];
        p[4] = lhs[4] + rhs[4];
        p[5] = lhs[5] + rhs[5];
        p[6] = lhs[6] + rhs[6];
        p[7] = lhs[7] + rhs[7];
    }
    for (a_real_t *q = b + (n >> 2 << 2); p < q; lhs += 4, rhs += 4, p += 4)
    {
        p[0] = lhs[0] + rhs[0];
        p[1] = lhs[1] + rhs[1];
        p[2] = lhs[2] + rhs[2];
        p[3] = lhs[3] + rhs[3];
    }
    for (a_real_t *q = b + (n >> 1 << 1); p < q; lhs += 2, rhs += 2, p += 2)
    {
        p[0] = lhs[0] + rhs[0];
        p[1] = lhs[1] + rhs[1];
    }
    for (a_real_t *q = b + n; p < q; ++lhs, ++rhs, ++p)
    {
        *p = *lhs + *rhs;
    }
}

A_STATIC a_void_t test_diff(a_size_t n)
{
    if (n == 0)
    {
        return;
    }

    a_real_t *p = (a_real_t *)malloc(sizeof(a_real_t) * n);

    clock_t t1;
    {
        a_real_t *lhs = (a_real_t *)malloc(sizeof(a_real_t) * n);
        a_real_t *rhs = (a_real_t *)malloc(sizeof(a_real_t) * n);

        memset(p, 0, sizeof(a_real_t) * n);

        t1 = clock();
        real_add1(n, p, lhs, rhs);
        t1 = clock() - t1;

        free(lhs);
        free(rhs);
    }

    clock_t t2;
    {
        a_real_t *lhs = (a_real_t *)malloc(sizeof(a_real_t) * n);
        a_real_t *rhs = (a_real_t *)malloc(sizeof(a_real_t) * n);

        memset(p, 0, sizeof(a_real_t) * n);

        t2 = clock();
        real_add2(n, p, lhs, rhs);
        t2 = clock() - t2;

        free(lhs);
        free(rhs);
    }

    clock_t t3;
    {
        a_real_t *lhs = (a_real_t *)malloc(sizeof(a_real_t) * n);
        a_real_t *rhs = (a_real_t *)malloc(sizeof(a_real_t) * n);

        memset(p, 0, sizeof(a_real_t) * n);

        t3 = clock();
        real_add3(n, p, lhs, rhs);
        t3 = clock() - t3;

        free(lhs);
        free(rhs);
    }

    free(p);

    printf("algorithm(1) %li\nalgorithm(2) %li\nalgorithm(3) %li\n",
           a_cast_s(long, t1), a_cast_s(long, t2), a_cast_s(long, t3));
}

int main(int argc, char *argv[])
{
    test();

    if (argc > 1)
    {
        a_str_t endptr;
        unsigned long long n = strtoull(argv[argc - 1], &endptr, 0);
        test_diff(a_cast_s(a_size_t, n));
    }

    return A_SUCCESS;
}
