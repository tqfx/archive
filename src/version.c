/*!
 @file version.c
 @brief algorithm library version
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/version.h"

const a_char_t *a_version(a_noarg_t)
{
    return A_VERSION;
}

a_uint_t a_version_major(a_noarg_t)
{
    return A_VERSION_MAJOR;
}

a_uint_t a_version_minor(a_noarg_t)
{
    return A_VERSION_MINOR;
}

a_uint_t a_version_patch(a_noarg_t)
{
    return A_VERSION_PATCH;
}
