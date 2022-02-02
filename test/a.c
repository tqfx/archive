/*!
 @file a.c
 @brief test algorithm library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "liba.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    (void)argc, (void)argv;
    printf("0x%X 0x%X\n", ~0, -1);
    return 0;
}
