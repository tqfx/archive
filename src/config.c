/*!
 @file config.c
 @brief algorithm library configuration
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#if defined(A_CONFIG)
#include "config.h"
#endif /* A_CONFIG */
#include "a/def.h"

const char *a_version(void)
{
#if defined(A_VERSION)
    return A_VERSION;
#else /* !A_VERSION */
    return "";
#endif /* A_VERSION */
}
