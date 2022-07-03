/*!
 @file def.h
 @brief algorithm library definition
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

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
#else /* !__has_attribute(visibility) */
#define A_EXPORT
#define A_IMPORT
#define A_HIDDEN
#endif /* __has_attribute(visibility) */
#if defined(A_EXPORTS)
#define A_PUBLIC A_EXPORT
#elif defined(A_SHARED)
#define A_PUBLIC A_IMPORT
#else /* !A_PUBLIC */
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

/* reset some warnings */
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

/*! @endcond */

#include <stddef.h>
#include <stdint.h>

/*!
 @addtogroup A algorithm library based on C
 @{
*/

/*!
 @brief define the floating-point type
 @arg 0 float
 @arg 1 double (default)
 @arg 2 long double
*/
#ifndef A_DEF_FLT
#define A_DEF_FLT 1
#endif /* A_DEF_FLT */

/*!
 @brief the offset of a structure member
 @param type structure type
 @param member member variable
*/
#ifndef offsetof
#define offsetof(type, member) (size_t)(&(((type *)0)->member))
#endif /* offsetof */

/*!
 @brief the container of a structure member
 @param ptr pointer to a member variable
 @param type structure type
 @param member member variable
*/
#ifndef containerof
#define containerof(ptr, type, member) ((type *)((size_t)(ptr)-offsetof(type, member)))
#endif /* containerof */

/*!
 @brief enumeration of return values
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

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief algorithm library version
*/
A_PUBLIC const char *a_version(void);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A */

#endif /* __A_DEF_H__ */
