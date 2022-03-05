/*!
 @file liba.c
 @brief algorithm library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "liba.h"
#include "liba_private.h"

const char *a_version(void)
{
#ifndef LIBA_VERSION
#define LIBA_VERSION ""
#endif /* LIBA_VERSION */
    static const char version[] = LIBA_VERSION;
    return version;
}
