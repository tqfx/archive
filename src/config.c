/*!
 @file config.c
 @brief algorithm library configuration
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#if defined(a_CONFIGS)
#include "config.h"
#endif /* a_CONFIGS */
#include "a/def.h"

const char *a_version(void)
{
#if defined(a_VERSION)
    return a_VERSION;
#else
    return "";
#endif /* a_VERSION */
}
