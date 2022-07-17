/*!
 @file config.hpp
 @brief algorithm library internal configuration
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include "a/def.hpp"

// clang-format off

#cmakedefine A_VERSION_MAJOR @A_VERSION_MAJOR@
#cmakedefine A_VERSION_MINOR @A_VERSION_MINOR@
#cmakedefine A_VERSION_PATCH @A_VERSION_PATCH@
#cmakedefine A_VERSION_TWEAK @A_VERSION_TWEAK@

// clang-format on

#ifndef A_VERSION_MAJOR
#define A_VERSION_MAJOR 0
#endif /* A_VERSION_MAJOR */
#ifndef A_VERSION_MINOR
#define A_VERSION_MINOR 0
#endif /* A_VERSION_MINOR */
#ifndef A_VERSION_PATCH
#define A_VERSION_PATCH 0
#endif /* A_VERSION_PATCH */
#ifndef A_VERSION_TWEAK
#define A_VERSION_TWEAK 0
#endif /* A_VERSION_TWEAK */

/*! algorithm library version string */
#cmakedefine A_VERSION "@A_VERSION@"

#endif /* __CONFIG_HPP__ */
