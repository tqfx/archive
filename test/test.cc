/*!
 @file test.cc
 @brief Test algorithm library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/def.h"

#include <iostream>

int main(int argc, char *argv[])
{
    (void)argc, (void)argv;
    std::cout << "version " << a_version() << std::endl;
    return 0;
}
