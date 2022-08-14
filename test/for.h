/*!
 @file for.h
 @brief Test algorithm library foreach
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_FOR_H__
#define __TEST_FOR_H__

#include "a/a.h"
#include <stdio.h>
#include <stdlib.h>

static a_noret_t test(a_size_t n)
{
    a_int_t *p = a_cast_s(a_int_t *, malloc(sizeof(a_int_t) * n));
    a_int_t *d = p + n;

    a_forenum(a_size_t, i, n)
    {
        p[i] = a_cast_s(a_int_t, i);
        printf("%zu ", i);
    }
    putchar('\n');
    a_foreach(a_int_t, it, p, n)
    {
        printf("%i ", *it);
    }
    putchar('\n');
    a_iterate(a_int_t, it, p, d)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    a_forenum_reverse(a_size_t, i, n)
    {
        p[i] = a_cast_s(a_int_t, i);
        printf("%zu ", i);
    }
    putchar('\n');
    a_foreach_reverse(a_int_t, it, p, n)
    {
        printf("%i ", *it);
    }
    putchar('\n');
    a_iterate_reverse(a_int_t, it, p, d)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    free(p);
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t main_c(a_noarg_t);
a_int_t main_cc(a_noarg_t);
#if defined(__cplusplus)
} /* extern "C" */
#define test_main main_cc
#else /* #__cplusplus */
#define test_main main_c
#endif /* __cplusplus */
a_int_t test_main(a_noarg_t)
{
    printf("%s\n", __func__);

    test(10);

    a_str_t a = a_null;
    a_foreach(a_char_t, it, a, 0);
    a_foreach_reverse(a_char_t, it, a, 0);

    return A_SUCCESS;
}

#endif /* __TEST_FOR_H__ */
