/*!
 @file fuzzy.c
 @brief test fuzzy operator
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/controller/fuzzy.h"

static void test(void)
{
    a_fuzzy_or(0, 0, 0);
    a_fuzzy_or(1, 0, 0);
    a_fuzzy_or(2, 0, 0);
    a_fuzzy_and(0, 0, 0);
    a_fuzzy_and(1, 0, 0);
    a_fuzzy_and(2, 0, 0);
    a_fuzzy_equ(A_REAL_C(0.5), 0, 0);
}

int main(void)
{
    test();
    return 0;
}
