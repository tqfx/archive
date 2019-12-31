/*!
 @file test.c
 @brief Test the algorithm library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/def.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    (void)argc, (void)argv;
    printf("version %s\n", a_version());
    return 0;
}
