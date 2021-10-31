/*!
 @file test_str.c
 @brief test vector library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include <cstdio>
#include <cstring>
#include <ctime>
#include <vector>

#include "a_vec.h"

#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif /* _MSC_VER */

a_vec_type(u32, unsigned int);

void tests(void)
{
    a_vec_s(unsigned int) ctx = a_vec_inits();

    for (unsigned int i = 0; i != 0xFF; ++i)
    {
        a_vec_push(unsigned int, ctx, i);
    }
    a_vec_done(ctx);

    a_vec_init(ctx);
    for (unsigned int i = 0; i != 0xFF; ++i)
    {
        *a_vec_pushp(unsigned int, ctx) = i;
    }
    a_vec_done(ctx);

    a_vec_init(ctx);
    for (unsigned int i = 0; i != 0xFF; ++i)
    {
        a_vec_vi(unsigned int, ctx, i) = i;
    }
    a_vec_done(ctx);

    a_vec_init(ctx);
    for (unsigned int i = 0; i != 10; ++i)
    {
        *a_vec_vip(unsigned int, ctx, i) = i;
    }

    a_vec_s(unsigned int) ctx2 = a_vec_inits();
    a_vec_copy(unsigned int, ctx2, ctx);
    a_vec_done(ctx);

    for (unsigned int i = 0; i != 2; ++i)
    {
        printf("%u ", a_vec_pop(ctx2));
    }

    for (unsigned int i = 0; i != 2; ++i)
    {
        printf("%u ", *a_vec_popp(ctx2));
    }

    unsigned int i = 0;
    unsigned int n = (unsigned int)a_vec_siz(ctx2) >> 1;

    while (i != n)
    {
        printf("%u ", a_vec_v(ctx2, i));
        ++i;
    }

    while (a_vec_siz(ctx2) != i)
    {
        printf("%u ", *a_vec_vp(ctx2, i));
        ++i;
    }

    printf("\nmemory = %zu\n", a_vec_max(ctx2));

    a_vec_done(ctx2);
}

void testt(void)
{
    a_vec_t(u32) *ctx = a_vec_initp(u32);

    for (unsigned int i = 0; i != 0xFF; ++i)
    {
        a_vec_ppush(unsigned int, ctx, i);
    }
    a_vec_pdone(ctx);

    a_vec_pinit(u32, ctx);
    for (unsigned int i = 0; i != 0xFF; ++i)
    {
        *a_vec_ppushp(unsigned int, ctx) = i;
    }
    a_vec_pdone(ctx);

    a_vec_pinit(u32, ctx);
    for (unsigned int i = 0; i != 0xFF; ++i)
    {
        a_vec_pvi(unsigned int, ctx, i) = i;
    }
    a_vec_pdone(ctx);

    a_vec_pinit(u32, ctx);
    for (unsigned int i = 0; i != 10; ++i)
    {
        *a_vec_pvip(unsigned int, ctx, i) = i;
    }

    a_vec_t(u32) *pctx = 0;
    a_vec_pcopy(u32, unsigned int, pctx, ctx);
    a_vec_pdone(ctx);

    for (unsigned int i = 0; i != 2; ++i)
    {
        printf("%u ", a_vec_ppop(pctx));
    }

    for (unsigned int i = 0; i != 2; ++i)
    {
        printf("%u ", *a_vec_ppopp(pctx));
    }

    unsigned int i = 0;
    unsigned int n = (unsigned int)a_vec_psiz(pctx) >> 1;

    while (i != n)
    {
        printf("%u ", a_vec_pv(pctx, i));
        ++i;
    }

    while (a_vec_psiz(pctx) != i)
    {
        printf("%u ", *a_vec_pvp(pctx, i));
        ++i;
    }

    printf("\nmemory = %zu\n", a_vec_pmax(pctx));

    a_vec_pdone(pctx);
}

void test(void)
{
    unsigned int M = 10;
    unsigned int N = 20000000;
    unsigned int i = 0;
    unsigned int j = 0;

    clock_t t = clock();
    for (i = 0; i != M; ++i)
    {
        unsigned int *array = (unsigned int *)amalloc(sizeof(int) * N);
        for (j = 0; j != N; ++j)
        {
            array[j] = j;
        }
        afree(array);
    }
    printf("C array, preallocated: %g sec\n", (double)(clock() - t) / CLOCKS_PER_SEC);

    t = clock();
    for (i = 0; i != M; ++i)
    {
        unsigned int max = 0;
        unsigned int *array = 0;
        for (j = 0; j != N; ++j)
        {
            if (j == max)
            {
                max = max ? max << 1 : 2;
                array = (unsigned int *)arealloc(array, sizeof(int) * (size_t)max);
            }
            array[j] = j;
        }
        afree(array);
    }
    printf("C array, dynamic: %g sec\n", (double)(clock() - t) / CLOCKS_PER_SEC);

    t = clock();
    for (i = 0; i != M; ++i)
    {
        a_vec_s(unsigned int) array = a_vec_inits();
        a_vec_resize(unsigned int, array, N);
        for (j = 0; j != N; ++j)
        {
            a_vec_v(array, j) = j;
        }
        a_vec_done(array);
    }
    printf("C vector, dynamic(a_vec_v): %g sec\n", (double)(clock() - t) / CLOCKS_PER_SEC);

    t = clock();
    for (i = 0; i != M; ++i)
    {
        a_vec_s(unsigned int) array = a_vec_inits();
        for (j = 0; j != N; ++j)
        {
            a_vec_push(unsigned int, array, j);
        }
        a_vec_done(array);
    }
    printf("C vector, dynamic(a_vec_push): %g sec\n", (double)(clock() - t) / CLOCKS_PER_SEC);

    t = clock();
    for (i = 0; i != M; ++i)
    {
        std::vector<unsigned int> array = {0};
        array.reserve(N);
        for (j = 0; j != N; ++j)
        {
            array[j] = j;
        }
    }
    printf("C++ vector, preallocated: %g sec\n", (double)(clock() - t) / CLOCKS_PER_SEC);

    t = clock();
    for (i = 0; i != M; ++i)
    {
        std::vector<unsigned int> array = {0};
        for (j = 0; j != N; ++j)
        {
            array.push_back(j);
        }
    }
    printf("C++ vector, dynamic: %g sec\n", (double)(clock() - t) / CLOCKS_PER_SEC);
}

int main(void)
{
    tests();

    testt();

    test();

    return 0;
}

#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

/* END OF FILE */
