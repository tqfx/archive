/*!
 @file version.cpp
 @brief algorithm library version
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/version.hpp"

namespace a
{

const char_t *version(void_t)
{
    return A_VERSION;
}

uint_t version_major(void_t)
{
    return A_VERSION_MAJOR;
}

uint_t version_minor(void_t)
{
    return A_VERSION_MINOR;
}

uint_t version_patch(void_t)
{
    return A_VERSION_PATCH;
}

} // namespace a
