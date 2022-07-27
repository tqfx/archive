/*!
 @file version.c
 @brief Test algorithm library version
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/version.h"

#include <stdio.h>

a_int_t main(a_noret_t)
{
    printf("version %s\n", a_version());
    printf("major %u", a_version_major());
    printf("minor %u", a_version_minor());
    printf("patch %u", a_version_patch());
    printf("tweak %zu", A_VERSION_TWEAK);
    return A_SUCCESS;
}
