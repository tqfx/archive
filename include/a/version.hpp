/*!
 @file a.h
 @brief algorithm library version
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_VERSION_HPP__
#define __A_VERSION_HPP__

#include "a.hpp"

namespace a
{
/*!
 @ingroup AA
 @addtogroup AA_VERSION algorithm library version based on C++
 @{
*/

/*!
 @brief algorithm library version string
*/
A_PUBLIC const char_t *version(void_t);

A_PUBLIC uint_t version_major(void_t);
A_PUBLIC uint_t version_minor(void_t);
A_PUBLIC uint_t version_patch(void_t);

/*! @} AA_VERSION */
} // namespace a

#endif /* __A_VERSION_HPP__ */
