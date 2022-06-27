/*!
 @file real.c
 @brief Testing real number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/real.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* __GNUC__ || __clang__ */

static void test(void)
{
    a_real_t l = 1;
    a_real_t r = 2;

    printf(A_REAL_PRI(, "g+") A_REAL_PRI(, "g=") A_REAL_PRI(, "g\n"), l, r, a_real_add(l, r));
    printf(A_REAL_PRI(, "g-") A_REAL_PRI(, "g=") A_REAL_PRI(, "g\n"), l, r, a_real_add(l, r));
    printf(A_REAL_PRI(, "g*") A_REAL_PRI(, "g=") A_REAL_PRI(, "g\n"), l, r, a_real_add(l, r));
    printf(A_REAL_PRI(, "g/") A_REAL_PRI(, "g=") A_REAL_PRI(, "g\n"), l, r, a_real_add(l, r));
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

static void real_add1(size_t n, a_real_t *p, a_real_t *l, a_real_t *r)
{
    for (a_real_t *q = p + n; p != q; ++l, ++r, ++p)
    {
        *p = *l + *r;
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

static void real_add2(size_t n, a_real_t *p, a_real_t *l, a_real_t *r)
{
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif /* __GNUC__ || __clang__ */
    if (n)
    {
        DUFF_DEVICE_8(n, *p++ = *l++ + *r++);
    }
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */
}

static void real_add3(size_t n, a_real_t *p, a_real_t *l, a_real_t *r)
{
    a_real_t *b = p;
    for (a_real_t *q = b + (n >> 3 << 3); p != q; l += 8, r += 8, p += 8)
    {
        p[0] = l[0] + r[0];
        p[1] = l[1] + r[1];
        p[2] = l[2] + r[2];
        p[3] = l[3] + r[3];
        p[4] = l[4] + r[4];
        p[5] = l[5] + r[5];
        p[6] = l[6] + r[6];
        p[7] = l[7] + r[7];
    }
    for (a_real_t *q = b + (n >> 2 << 2); p != q; l += 4, r += 4, p += 4)
    {
        p[0] = l[0] + r[0];
        p[1] = l[1] + r[1];
        p[2] = l[2] + r[2];
        p[3] = l[3] + r[3];
    }
    for (a_real_t *q = b + (n >> 1 << 1); p != q; l += 2, r += 2, p += 2)
    {
        p[0] = l[0] + r[0];
        p[1] = l[1] + r[1];
    }
    for (a_real_t *q = b + n; p != q; ++l, ++r, ++p)
    {
        *p = *l + *r;
    }
}

static void test_diff(size_t n)
{
    if (n == 0)
    {
        return;
    }

    a_real_t *p = (a_real_t *)malloc(sizeof(a_real_t) * n);

    clock_t t1;
    {
        a_real_t *l = (a_real_t *)malloc(sizeof(a_real_t) * n);
        a_real_t *r = (a_real_t *)malloc(sizeof(a_real_t) * n);

        memset(p, 0, sizeof(a_real_t) * n);

        t1 = clock();
        real_add1(n, p, l, r);
        t1 = clock() - t1;

        free(l);
        free(r);
    }

    clock_t t2;
    {
        a_real_t *l = (a_real_t *)malloc(sizeof(a_real_t) * n);
        a_real_t *r = (a_real_t *)malloc(sizeof(a_real_t) * n);

        memset(p, 0, sizeof(a_real_t) * n);

        t2 = clock();
        real_add2(n, p, l, r);
        t2 = clock() - t2;

        free(l);
        free(r);
    }

    clock_t t3;
    {
        a_real_t *l = (a_real_t *)malloc(sizeof(a_real_t) * n);
        a_real_t *r = (a_real_t *)malloc(sizeof(a_real_t) * n);

        memset(p, 0, sizeof(a_real_t) * n);

        t3 = clock();
        real_add3(n, p, l, r);
        t3 = clock() - t3;

        free(l);
        free(r);
    }

    free(p);

    printf("algorithm(1) %ld\nalgorithm(2) %ld\nalgorithm(3) %ld\n", t1, t2, t3);
}

int main(int argc, char *argv[])
{
    test();

    if (argc > 1)
    {
        char *endptr;
        size_t n = (size_t)strtoull(argv[argc - 1], &endptr, 0);
        test_diff(n);
    }

    return 0;
}
