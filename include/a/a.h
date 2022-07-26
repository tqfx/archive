/*!
 @file a.h
 @brief algorithm library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_A_H__
#define __A_A_H__

#include "a.config.h"

/*!
 @addtogroup A algorithm library based on C
 @{
*/

#include <stddef.h>
#include <stdint.h>

/* extern "C" */
#if defined(__cplusplus)
#define A_EXTERN_C extern "C"
#define A_EXTERN_C_ENTER extern "C" {
#define A_EXTERN_C_LEAVE }
#else /* !__cplusplus */
#define A_EXTERN_C
#define A_EXTERN_C_ENTER
#define A_EXTERN_C_LEAVE
#endif /* __cplusplus */

/*! @cond */

/* has builtin */
#if defined(__has_builtin)
#define a_has_builtin(...) __has_builtin(__VA_ARGS__)
#else /* !__has_builtin */
#define a_has_builtin(...) 0
#endif /* __has_builtin */

/* has feature */
#if defined(__has_feature)
#define a_has_feature(...) __has_feature(__VA_ARGS__)
#else /* !__has_feature */
#define a_has_feature(...) 0
#endif /* __has_feature */

/* has include */
#if defined(__has_include)
#define a_has_include(...) __has_include(__VA_ARGS__)
#else /* !__has_include */
#define a_has_include(...) 0
#endif /* __has_include */

/* has warning */
#if defined(__has_warning)
#define a_has_warning(...) __has_warning(__VA_ARGS__)
#else /* !__has_warning */
#define a_has_warning(...) 0
#endif /* __has_warning */

/* has attribute */
#if defined(__has_attribute)
#define a_has_attribute(...) __has_attribute(__VA_ARGS__)
#else /* !__has_attribute */
#define a_has_attribute(...) 0
#endif /* __has_attribute */

/* has builtin expect */
#if defined(__builtin_expect)
#define a_builtin_likey(...) __builtin_expect((__VA_ARGS__), 1)
#define a_builtin_unlikey(...) __builtin_expect((__VA_ARGS__), 0)
#else /* !__builtin_expect */
#define a_builtin_likey(...) (__VA_ARGS__)
#define a_builtin_unlikey(...) (__VA_ARGS__)
#endif /* __builtin_expect */

/* attribute deprecated */
#if defined(_WIN32) || defined(__CYGWIN__)
#define A_DEPRECATED __declspec(deprecated)
#elif a_has_attribute(deprecated)
#define A_DEPRECATED __attribute__((__deprecated__))
#else /* !a_has_attribute(deprecated) */
#define A_DEPRECATED
#endif /* a_has_attribute(deprecated) */

/* attribute visibility */
#if defined(_WIN32) || defined(__CYGWIN__)
#define A_EXPORT __declspec(dllexport)
#define A_IMPORT __declspec(dllimport)
#define A_HIDDEN
#elif a_has_attribute(visibility)
#define A_EXPORT __attribute__((__visibility__("default")))
#define A_IMPORT __attribute__((__visibility__("default")))
#define A_HIDDEN __attribute__((__visibility__("hidden")))
#else /* !a_has_attribute(visibility) */
#define A_EXPORT
#define A_IMPORT
#define A_HIDDEN
#endif /* a_has_attribute(visibility) */
#define A_INLINE static __inline
#if defined(A_EXPORTS)
#define A_PUBLIC A_EXPORT
#elif defined(A_SHARED)
#define A_PUBLIC A_IMPORT
#else /* !A_PUBLIC */
#define A_PUBLIC
#endif /* A_PUBLIC */

/*! @endcond */

/* register keyword */
#if defined(__cplusplus)
#define a_register register
#else /* !__cplusplus */
#define a_register
#endif /* __cplusplus */
#define a_volatile volatile

typedef int a_bool_t;

#if defined(__cplusplus)
#define a_true true
#define a_false false
#else /* !__cplusplus */
#define a_true (!0)
#define a_false (0)
#endif /* __cplusplus */

typedef void a_void_t;

#if defined(__cplusplus)
#define a_cast(T, ...) static_cast<T>(__VA_ARGS__)
#define a_null nullptr
#else /* !__cplusplus */
#define a_cast(T, ...) (T)(__VA_ARGS__)
#define a_null NULL
#endif /* __cplusplus */

typedef size_t a_size_t;

#define A_SIZE_MAX SIZE_MAX

// clang-format off

typedef  int8_t  a_int8_t;
typedef  int8_t a_sint8_t;
typedef uint8_t a_uint8_t;

#define  A_INT8_C(X)  INT8_C(X)
#define A_SINT8_C(X)  INT8_C(X)
#define A_UINT8_C(X) UINT8_C(X)

#define  A_INT8_MIN  INT8_MIN
#define  A_INT8_MAX  INT8_MAX
#define A_SINT8_MIN  INT8_MIN
#define A_SINT8_MAX  INT8_MAX
#define A_UINT8_MAX UINT8_MAX

typedef  int16_t  a_int16_t;
typedef  int16_t a_sint16_t;
typedef uint16_t a_uint16_t;

#define  A_INT16_C(X)  INT16_C(X)
#define A_SINT16_C(X)  INT16_C(X)
#define A_UINT16_C(X) UINT16_C(X)

#define  A_INT16_MIN  INT16_MIN
#define  A_INT16_MAX  INT16_MAX
#define A_SINT16_MIN  INT16_MIN
#define A_SINT16_MAX  INT16_MAX
#define A_UINT16_MAX UINT16_MAX

typedef  int32_t  a_int32_t;
typedef  int32_t a_sint32_t;
typedef uint32_t a_uint32_t;

#define  A_INT32_C(X)  INT32_C(X)
#define A_SINT32_C(X)  INT32_C(X)
#define A_UINT32_C(X) UINT32_C(X)

#define  A_INT32_MIN  INT32_MIN
#define  A_INT32_MAX  INT32_MAX
#define A_SINT32_MIN  INT32_MIN
#define A_SINT32_MAX  INT32_MAX
#define A_UINT32_MAX UINT32_MAX

typedef  int64_t  a_int64_t;
typedef  int64_t a_sint64_t;
typedef uint64_t a_uint64_t;

#define  A_INT64_C(X)  INT64_C(X)
#define A_SINT64_C(X)  INT64_C(X)
#define A_UINT64_C(X) UINT64_C(X)

#define  A_INT64_MIN  INT64_MIN
#define  A_INT64_MAX  INT64_MAX
#define A_SINT64_MIN  INT64_MIN
#define A_SINT64_MAX  INT64_MAX
#define A_UINT64_MAX UINT64_MAX

typedef  intmax_t  a_intmax_t;
typedef  intmax_t a_sintmax_t;
typedef uintmax_t a_uintmax_t;

#define  A_INTMAX_C(X)  INTMAX_C(X)
#define A_SINTMAX_C(X)  INTMAX_C(X)
#define A_UINTMAX_C(X) UINTMAX_C(X)

#define  A_INTMAX_MIN  INTMAX_MIN
#define  A_INTMAX_MAX  INTMAX_MAX
#define A_SINTMAX_MIN  INTMAX_MIN
#define A_SINTMAX_MAX  INTMAX_MAX
#define A_UINTMAX_MAX UINTMAX_MAX

typedef  intptr_t  a_intptr_t;
typedef  intptr_t a_sintptr_t;
typedef uintptr_t a_uintptr_t;

#define  A_INTPTR_MIN  INTPTR_MIN
#define  A_INTPTR_MAX  INTPTR_MAX
#define A_SINTPTR_MIN  INTPTR_MIN
#define A_SINTPTR_MAX  INTPTR_MAX
#define A_UINTPTR_MAX UINTPTR_MAX

typedef ptrdiff_t a_ptrdiff_t;

#define A_PTRDIFF_MIN PTRDIFF_MIN
#define A_PTRDIFF_MAX PTRDIFF_MAX

typedef          int  a_int_t;
typedef          int a_sint_t;
typedef unsigned int a_uint_t;

typedef unsigned char  a_byte_t;
typedef          char  a_char_t;
typedef   signed char a_schar_t;
typedef unsigned char a_uchar_t;

typedef float  a_float32_t;
typedef double a_float64_t;

// clang-format on

#ifndef A_REAL_BITS
#define A_REAL_BITS 64
#endif // real bits
#if A_REAL_BITS == 32

typedef float a_real_t;

#define A_REAL_C(X) X##F
#define A_REAL_F(F, ...) F##f(__VA_ARGS__)
#define A_REAL_PRI(F, ...) "%" F __VA_ARGS__
#define A_REAL_SCN(F, ...) "%" F __VA_ARGS__

#elif A_REAL_BITS == 64

typedef double a_real_t;

#define A_REAL_C(X) X
#define A_REAL_F(F, ...) F(__VA_ARGS__)
#define A_REAL_PRI(F, ...) "%" F __VA_ARGS__
#define A_REAL_SCN(F, ...) "%" F "l" __VA_ARGS__

#elif A_REAL_BITS == 128

typedef long double a_real_t;

#define A_REAL_C(X) X##L
#define A_REAL_F(F, ...) F##l(__VA_ARGS__)
#define A_REAL_PRI(F, ...) "%" F "L" __VA_ARGS__
#define A_REAL_SCN(F, ...) "%" F "L" __VA_ARGS__

#endif /* A_REAL_BITS */

/*! @} A */

#endif /* __A_A_H__ */
