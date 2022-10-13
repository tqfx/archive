/*!
 @file config.h
 @brief algorithm library default configuration
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_CONFIG_H__
#define __A_CONFIG_H__

/*! @cond */
#if defined(__MINGW32__)
#undef __USE_MINGW_ANSI_STDIO
#define __USE_MINGW_ANSI_STDIO 1
#endif /* __MINGW32__ */
/*! @endcond */

#if defined(A_CONFIG)
#include "a.config.h"
#endif /* A_CONFIG */

/*! algorithm library version major */
#ifndef A_VERSION_MAJOR
#define A_VERSION_MAJOR 0
#endif /* A_VERSION_MAJOR */

/*! algorithm library version minor */
#ifndef A_VERSION_MINOR
#define A_VERSION_MINOR 0
#endif /* A_VERSION_MINOR */

/*! algorithm library version patch */
#ifndef A_VERSION_PATCH
#define A_VERSION_PATCH 0
#endif /* A_VERSION_PATCH */

/*! algorithm library version tweak */
#ifndef A_VERSION_TWEAK
#define A_VERSION_TWEAK A_U64_C(0)
#endif /* A_VERSION_TWEAK */

/*! algorithm library version string */
#ifndef A_VERSION
#define A_VERSION ""
#endif /* A_VERSION */

/*! sizeof pointer */
#if !defined A_SIZEOF_P
#if defined(__SIZEOF_POINTER__)
#define A_SIZEOF_P __SIZEOF_POINTER__
#elif defined(_WIN64)
#define A_SIZEOF_P 8
#elif defined(_WIN32)
#define A_SIZEOF_P 4
#endif /* __SIZEOF_POINTER__ */
#endif /* A_SIZEOF_P */

/*! real number bits */
#ifndef A_REAL_BITS
#define A_REAL_BITS 64
#endif // real bits

#endif /* __A_CONFIG_H__ */
