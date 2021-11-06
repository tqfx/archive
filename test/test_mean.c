/*!
 @file test_mean.c
 @brief test mean
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_mean.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    a_mean_s ctx[1];

    size_t n = (size_t)(argc - 1);
    double *a = (double *)amalloc(sizeof(double) * n);
    double *p = a;

    printf("%zu: ", n);
    for (int i = 1; i != argc; ++i, ++p)
    {
        *p = atof(argv[i]);
        printf("%g ", *p);
    }
    printf("\n");

    a_mean_init(ctx, A_MEAN_ARITHMETIC);
    a_mean_process(ctx, a, n);
    printf("arithmetic: %g\n", a_mean_done(ctx));

    a_mean_init(ctx, A_MEAN_GEOMETRIC);
    a_mean_process(ctx, a, n);
    printf("geometric: %g\n", a_mean_done(ctx));

    a_mean_init(ctx, A_MEAN_HARMONIC);
    a_mean_process(ctx, a, n);
    printf("harmonic: %g\n", a_mean_done(ctx));

    a_mean_init(ctx, A_MEAN_SQUARE);
    a_mean_process(ctx, a, n);
    printf("square: %g\n", a_mean_done(ctx));

    afree(a);

    return 0;
}

/* END OF FILE */
