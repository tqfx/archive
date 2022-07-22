/*!
 @file test.c
 @brief Test algorithm library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/def.h"

#include <stdlib.h>
#include <stdio.h>

static void test_for(size_t n)
{
    int *p = (int *)malloc(sizeof(int) * n);

    a_forenum(size_t, i, n)
    {
        printf("%zu ", i);
    }
    putchar('\n');
    a_forenum_reverse(size_t, i, n)
    {
        printf("%zu ", i);
    }
    putchar('\n');

    {
        int *it = 0;
        a_forboth(size_t, i, int, it, p, n)
        {
            *it = (int)i;
        }
    }
    a_foreach(int, it, p, n)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    {
        int *it = 0;
        a_forboth_reverse(size_t, i, int, it, p, n)
        {
            *it = (int)i;
        }
    }
    a_foreach_reverse(int, it, p, n)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    free(p);
}

int main(int argc, char *argv[])
{
    (void)argc, (void)argv;

    printf("version %s\n", a_version());

    test_for(10);

    return 0;
}
