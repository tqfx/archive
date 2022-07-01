/*!
 @file mean.cc
 @brief Testing mean calculation
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/misc/mean.h"

#include <cstdlib>
#include <cstdio>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* __GNUC__ || __clang__ */

static void test(int argc, char *argv[])
{
    a_mean_s ctx[1];

    size_t n = static_cast<size_t>(argc - 1);
    a_real_t *a = static_cast<a_real_t *>(malloc(sizeof(a_real_t) * n));
    a_real_t *p = a;

    printf("%zu: ", n);
    for (int i = 1; i != argc; ++i, ++p)
    {
        *p = static_cast<a_real_t>(atof(argv[i]));
        printf(A_REAL_PRI(, "g "), *p);
    }
    printf("\n");

    a_mean_init(ctx, A_MEAN_ARITHMETIC);
    a_mean_proc(ctx, a, n);
    printf("arithmetic: " A_REAL_PRI(, "g\n"), a_mean_done(ctx));

    a_mean_init(ctx, A_MEAN_GEOMETRIC);
    a_mean_proc(ctx, a, n);
    printf("geometric: " A_REAL_PRI(, "g\n"), a_mean_done(ctx));

    a_mean_init(ctx, A_MEAN_HARMONIC);
    a_mean_proc(ctx, a, n);
    printf("harmonic: " A_REAL_PRI(, "g\n"), a_mean_done(ctx));

    a_mean_init(ctx, A_MEAN_SQUARE);
    a_mean_proc(ctx, a, n);
    printf("square: " A_REAL_PRI(, "g\n"), a_mean_done(ctx));

    free(a);
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

int main(int argc, char *argv[])
{
    test(argc, argv);
    return 0;
}
