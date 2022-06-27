/*!
 @file zyx.c
 @brief test convert between quat and euler by ZYX.
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/misc/zyx.h"

#include <stdio.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* __GNUC__ || __clang__ */

static void test(void)
{
    static a_real_t q[4] = {0, 0, 0, 1};
    static a_real_t e[3] = {1, 0, 0};
    a_zyx_quat2euler(q, e);
    a_zyx_euler2quat(e, q);
    printf(A_REAL_PRI(, "g ") A_REAL_PRI(, "g ") A_REAL_PRI(, "g\n"), e[0], e[1], e[2]);
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

int main(void)
{
    test();
    return 0;
}
