/*!
 @file version.cpp
 @brief Test algorithm library version
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/version.hpp"

#include <iostream>

a_int_t main(a_noret_t)
{
    std::cout << "version " << a::version() << std::endl;
    std::cout << "major " << a::version_major() << std::endl;
    std::cout << "minor " << a::version_minor() << std::endl;
    std::cout << "patch " << a::version_patch() << std::endl;
    std::cout << "tweak " << A_VERSION_TWEAK << std::endl;
    return A_SUCCESS;
}
