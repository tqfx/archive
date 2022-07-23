/*!
 @file test.cc
 @brief Test algorithm library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/def.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

static void test_for(size_t n)
{
    int *p = static_cast<int *>(malloc(sizeof(int) * n));

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
        int *it = nullptr;
        a_forboth(size_t, i, int, it, p, n)
        {
            *it = static_cast<int>(i);
        }
    }
    a_foreach(int, it, p, n)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    {
        int *it = nullptr;
        a_forboth_reverse(size_t, i, int, it, p, n)
        {
            *it = static_cast<int>(i);
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

    std::cout << "version " << a_version() << std::endl;

    test_for(10);

    return 0;
}
