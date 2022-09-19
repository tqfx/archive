/*!
 @file fpid.cpp
 @brief Test fuzzy proportional integral derivative controller
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "fpid.h"

int main(void)
{
    return fpid_c() + fpid_cpp();
}
