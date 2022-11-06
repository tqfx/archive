/*!
 @file config.h
 @brief algorithm library default configuration
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef A_CONFIG_H
#define A_CONFIG_H

#if defined(A_HAVE_H)
#include "a.config.h"
#endif /* A_HAVE_H */

/*! @cond */

#if !defined A_ASSERT && defined(__GNUC__)
#define A_ASSERT(E) assert(E)
#endif /* A_ASSERT */

#if !defined __has_attribute
#define __has_attribute(x) 0
#endif /* __has_attribute */
#if !defined __has_builtin
#define __has_builtin(x) 0
#endif /* __has_builtin */
#if !defined __has_feature
#define __has_feature(x) 0
#endif /* __has_feature */
#if !defined __has_include
#define __has_include(x) 0
#endif /* __has_include */
#if !defined __has_warning
#define __has_warning(x) 0
#endif /* __has_warning */

#if defined(__clang__)
#pragma clang diagnostic push
#endif /* __clang__ */
#if __has_warning("-Wreserved-identifier")
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif /* -Wreserved-identifier */
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif /* -Wreserved-id-macro */

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

#undef a_prereq_msvc
/* https://en.wikipedia.org/wiki/Microsoft_Visual_C++ */
#if defined(_MSC_VER)
#define a_prereq_msvc(maj, min) (_MSC_VER >= (maj * 100 + min))
#else /* !_MSC_VER */
#define a_prereq_msvc(maj, min) 0
#endif /* _MSC_VER */

#undef a_prereq_gnuc
/* https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html */
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
#define a_prereq_gnuc(maj, min) ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else /* !__GNUC__ */
#define a_prereq_gnuc(maj, min) 0
#endif /* __GNUC__ */

#undef a_prereq_clang
/* https://clang.llvm.org/docs/LanguageExtensions.html */
#if defined(__clang_major__) && defined(__clang_minor__)
#define a_prereq_clang(maj, min) ((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#else /* !__clang__ */
#define a_prereq_clang(maj, min) 0
#endif /* __clang__ */

#if a_prereq_gnuc(2, 96) || __has_builtin(__builtin_expect)
#define a_unlikely(x) __builtin_expect(!!(x), 0)
#define a_likely(x) __builtin_expect(!!(x), 1)
#else /* !__GNUC__ */
#define a_unlikely(x) (x)
#define a_likely(x) (x)
#endif /* __GNUC__ */

#if defined(__GNUC__) || defined(__clang__)
#define A_ATTRIBUTE(x) __attribute__(x)
#else /* !__attribute__ */
#define A_ATTRIBUTE(x)
#endif /* __attribute__ */

#if defined(_WIN32) || defined(__CYGWIN__)
#define A_DECLSPEC(x) __declspec(x)
#else /* !__declspec */
#define A_DECLSPEC(x)
#endif /* __declspec */

/* attribute format */
#if a_prereq_gnuc(2, 4) || __has_attribute(format)
#define A_FORMAT(_, a, b) __attribute__((format(_, a, b)))
#else /* !format */
#define A_FORMAT(_, a, b)
#endif /* format */

/* attribute fallthrough */
#if a_prereq_gnuc(7, 1) || __has_attribute(fallthrough)
#define A_FALLTHROUGH __attribute__((fallthrough))
#else /* !fallthrough */
#define A_FALLTHROUGH ((void)(0))
#endif /* fallthrough */

/* attribute deprecated */
#if a_prereq_gnuc(3, 2) || __has_attribute(deprecated)
#define A_DEPRECATED __attribute__((deprecated))
#elif defined(_WIN32) || defined(__CYGWIN__)
#define A_DEPRECATED __declspec(deprecated)
#else /* !deprecated */
#define A_DEPRECATED
#endif /* deprecated */

/* attribute always inline */
#if a_prereq_gnuc(3, 2) || __has_attribute(always_inline)
#define A_INLINE __inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#define A_INLINE __inline __forceinline
#else /* !_MSC_VER */
#define A_INLINE __inline
#endif /* _MSC_VER */
#if !defined A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_INTERN */
#define A_STATIC static

/* attribute visibility */
#if defined(_WIN32) || defined(__CYGWIN__)
#define A_EXPORT __declspec(dllexport)
#define A_IMPORT __declspec(dllimport)
#define A_HIDDEN
#elif a_prereq_gnuc(4, 0) || __has_attribute(visibility)
#define A_EXPORT __attribute__((visibility("default")))
#define A_IMPORT __attribute__((visibility("default")))
#define A_HIDDEN __attribute__((visibility("hidden")))
#else /* !visibility */
#define A_EXPORT
#define A_IMPORT
#define A_HIDDEN
#endif /* visibility */
#if defined(A_EXPORTS)
#define A_PUBLIC extern A_EXPORT
#elif defined(A_IMPORTS)
#define A_PUBLIC extern A_IMPORT
#else /* !A_PUBLIC */
#define A_PUBLIC extern
#endif /* A_PUBLIC */
#define A_EXTERN extern

#if !defined __cplusplus
#define A_EXTERN_C
#define A_EXTERN_C_ENTER
#define A_EXTERN_C_LEAVE
#else /* !__cplusplus */
#define A_EXTERN_C extern "C"
#define A_EXTERN_C_ENTER extern "C" {
#define A_EXTERN_C_LEAVE }
#endif /* __cplusplus */

#if defined(__cplusplus)
#define A_REGISTER
#else /* !__cplusplus */
#define A_REGISTER __register
#endif /* __cplusplus */
#define A_VOLATILE __volatile
#define A_RESTRICT __restrict

#if !defined A_ASSERT
#define A_ASSERT(E) ((void)(0))
#endif /* A_ASSERT */

/*! @endcond */

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

#endif /* A_CONFIG_H */
