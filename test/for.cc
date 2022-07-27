/*!
 @file test.cc
 @brief Test algorithm library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/a.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

static a_noret_t test(a_size_t n)
{
    a_int_t *p = a_cast(a_int_t *, malloc(sizeof(a_int_t) * n));

    a_forenum(a_size_t, i, n)
    {
        printf("%zu ", i);
    }
    putchar('\n');
    a_forenum_reverse(a_size_t, i, n)
    {
        printf("%zu ", i);
    }
    putchar('\n');

    {
        a_int_t *it = a_null;
        a_forboth(a_size_t, i, a_int_t, it, p, n)
        {
            *it = a_cast(a_int_t, i);
        }
    }
    a_foreach(a_int_t, it, p, n)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    {
        a_int_t *it = a_null;
        a_forboth_reverse(a_size_t, i, a_int_t, it, p, n)
        {
            *it = a_cast(a_int_t, i);
        }
    }
    a_foreach_reverse(a_int_t, it, p, n)
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
    a_forsafe(a_char_t, it, a, 0);
    a_forsafe_reverse(a_char_t, it, a, 0);

    return A_SUCCESS;
}
