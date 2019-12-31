/*!
 @file lpf.c
 @brief test Low Pass Filter
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/filter/lpf.h"

#include <inttypes.h>
#include <stdio.h>
#include <math.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* __GNUC__ || __clang__ */

static void test(size_t n)
{
    a_lpf_s ctx[1];
    a_lpf_init(ctx, A_REAL_C(0.5), A_REAL_C(0.5));
    for (size_t i = 0; i != n; ++i)
    {
        printf(A_REAL_P(g) " ", a_lpf_proc(ctx, A_REAL_F(cos, ctx->o)));
    }
    putchar('\n');
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

int main(void)
{
    test(10);
    return 0;
}
