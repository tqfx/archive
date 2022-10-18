/*!
 @file config.h
 @brief algorithm library default configuration
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef A_CONFIG_H
#define A_CONFIG_H

/*! @cond */
#if defined(__clang__)
#pragma clang diagnostic push
#if __has_warning("-Wreserved-identifier")
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif /* -Wreserved-identifier */
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif /* __clang__ */

#if defined(__STDC_LIB_EXT1__)
#if !defined __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif /* __STDC_WANT_LIB_EXT1__ */
#endif /* __STDC_LIB_EXT1__ */

#if defined(__MINGW32__)
#undef __USE_MINGW_ANSI_STDIO
#define __USE_MINGW_ANSI_STDIO 1
#endif /* __MINGW32__ */
#if defined(__clang__)
#pragma clang diagnostic pop
#endif /* __clang__ */

#define A_HAVE_INLINE

/*! @endcond */

#if defined(A_CONFIG)
#include "a.config.h"
#endif /* A_CONFIG */

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

#endif /* A_CONFIG_H */
