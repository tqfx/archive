/*!
 @file def.h
 @brief algorithm library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_DEF_H__
#define __A_DEF_H__

/*! @cond */

/* ignore some warnings */
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#endif /* __GNUC__ || __clang__ */

/* MSVC */
#if defined(_MSC_VER)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif /* _CRT_SECURE_NO_WARNINGS */
#endif /* _MSC_VER */

/* MinGW */
#if defined(__MINGW32__)
#ifndef __USE_MINGW_ANSI_STDIO
#define __USE_MINGW_ANSI_STDIO 1
#endif /* __USE_MINGW_ANSI_STDIO */
#ifndef __format__
#define __format__(...)
#endif /* __format__ */
#endif /* __MINGW32__ */

/* fallback for __has_builtin */
#ifndef __has_builtin
#define __has_builtin(...) 0
#ifndef __builtin_expect
#define __builtin_expect(...)
#endif /* __builtin_expect */
#endif /* __has_builtin */

/* fallback for __has_warning */
#ifndef __has_warning
#define __has_warning(...) 0
#endif /* __has_builtin */

/* fallback for __has_attribute */
#ifndef __has_attribute
#define __has_attribute(...) 0
#define __attribute__(...)
#endif /* __has_attribute */

/* attribute visibility */
#if defined(_WIN32) || defined(__CYGWIN__)
#define A_EXPORT __declspec(dllexport)
#define A_IMPORT __declspec(dllimport)
#define A_HIDDEN
#elif __has_attribute(visibility)
#define A_EXPORT __attribute__((__visibility__("default")))
#define A_IMPORT __attribute__((__visibility__("default")))
#define A_HIDDEN __attribute__((__visibility__("hidden")))
#else
#define A_EXPORT
#define A_IMPORT
#define A_HIDDEN
#endif /* visibility */
#if defined(a_EXPORTS)
#define A_PUBLIC A_EXPORT
#elif defined(a_SHARED)
#define A_PUBLIC A_IMPORT
#else
#define A_PUBLIC
#endif /* A_PUBLIC */

/* restrict */
#ifndef RESTRICT
#define RESTRICT __restrict
#endif /* RESTRICT */
#define A_RESTRICT __restrict

/* inline */
#ifndef INLINE
#define INLINE __inline
#endif /* INLINE */
#define A_INLINE static __inline

/* asm */
#ifndef ASM
#define ASM __asm
#endif /* __ASM */
#define A_ASM __asm

/*! @endcond */

#include <stddef.h>
#include <stdint.h>

/*!
 @defgroup LIBA Algorithm library
*/

enum
{
    A_SUCCESS = 0,
    A_WARNING = -1,
    A_FAILURE = -2,
    A_INVALID = -3,
    A_OVERFLOW = -4,
    A_NOTFOUND = -5,
};

#ifndef A_DEFAULT_FLOAT
#define A_DEFAULT_FLOAT 1
#endif /* A_DEFAULT_FLOAT */
#if A_DEFAULT_FLOAT == 0
typedef float a_real_t;
#define A_REAL_C(X)      X##F
#define A_REAL_P(X)      "%" #X
#define A_REAL_F(F, ...) F##f(__VA_ARGS__)
#elif A_DEFAULT_FLOAT == 1
typedef double a_real_t;
#define A_REAL_C(X)      X
#define A_REAL_P(X)      "%" #X
#define A_REAL_F(F, ...) F(__VA_ARGS__)
#elif A_DEFAULT_FLOAT == 2
typedef long double a_real_t;
#define A_REAL_C(X)      X##L
#define A_REAL_P(X)      "%L" #X
#define A_REAL_F(F, ...) F##l(__VA_ARGS__)
#else /* !A_DEFAULT_FLOAT */
#error unknown default float
#endif /* A_DEFAULT_FLOAT */

#ifndef offsetof
#define offsetof(type, member) (size_t)(&(((type *)0)->member))
#endif /* offsetof */

#ifndef containerof
#define containerof(ptr, type, member) ((type *)((size_t)(ptr)-offsetof(type, member)))
#endif /* containerof */

#ifndef roundup32
#define roundup32(x)     \
    (--(x),              \
     (x) |= (x) >> 0x01, \
     (x) |= (x) >> 0x02, \
     (x) |= (x) >> 0x04, \
     (x) |= (x) >> 0x08, \
     (x) |= (x) >> 0x10, \
     ++(x))
#endif /* roundup32 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief algorithm library version
*/
A_PUBLIC const char *a_version(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* reset some warnings */
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#endif /* __A_DEF_H__ */
