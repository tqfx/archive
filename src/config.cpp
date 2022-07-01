/*!
 @file config.cpp
 @brief algorithm library configuration
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#if defined(A_CONFIG)
#include "config.hpp"
#endif /* A_CONFIG */
#include "a/def.hpp"

namespace a
{

const char *version(void)
{
#if defined(A_VERSION)

    return A_VERSION;

#else /* !A_VERSION */

    return "";

#endif /* A_VERSION */
}

} // namespace a
