/*!
 @file version.cc
 @brief Test algorithm library version
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include <stdio.h>
#include "a/version.h"

static a_int_t main_c(a_noret_t)
{
    printf("%s\n", __func__);
    printf("version %s\n", a_version());
    printf("major %u\n", a_version_major());
    printf("minor %u\n", a_version_minor());
    printf("patch %u\n", a_version_patch());
    printf("tweak %zu\n", A_VERSION_TWEAK);
    return A_SUCCESS;
}

#include <iostream>
#include "a/version.hpp"

static a_int_t main_cc(a_noret_t)
{
    printf("%s\n", __func__);
    std::cout << "version " << a::version() << std::endl;
    std::cout << "major " << a::version_major() << std::endl;
    std::cout << "minor " << a::version_minor() << std::endl;
    std::cout << "patch " << a::version_patch() << std::endl;
    std::cout << "tweak " << A_VERSION_TWEAK << std::endl;
    return A_SUCCESS;
}

a_int_t main(a_noret_t)
{
    return main_c() + main_cc();
}
