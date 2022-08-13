/*!
 @file test.cc
 @brief Test algorithm library foreach
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "for.h"

#include <stdlib.h>
#include <stdio.h>

static a_noret_t test(a_size_t n)
{
    a_int_t *p = a_cast(a_int_t *, malloc(sizeof(a_int_t) * n));
    a_int_t *d = p + n;

    a_forenum(a_size_t, i, n)
    {
        p[i] = a_cast(a_int_t, i);
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
        p[i] = a_cast(a_int_t, i);
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

a_int_t main(a_noarg_t)
{
    test(10);

    a_str_t a = a_null;
    a_foreach(a_char_t, it, a, 0);
    a_foreach_reverse(a_char_t, it, a, 0);

    return A_SUCCESS;
}
