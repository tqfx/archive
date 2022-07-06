/*!
 @file test.cpp
 @brief Testing algorithm library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/def.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    (void)argc, (void)argv;
    std::cout << "version " << a::version() << std::endl;
    return 0;
}
