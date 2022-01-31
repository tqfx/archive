/*!
 @file liba.h
 @brief algorithm library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __LIBA_H__
#define __LIBA_H__

#include <stddef.h>

/*! @cond */

/* C --> C++ */
#undef __END_DECLS
#undef __BEGIN_DECLS
#if defined(__cplusplus)
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS   }
#else
#define __END_DECLS
#define __BEGIN_DECLS
#endif /* __cplusplus */

/* ignore some GCC warnings */
#ifndef _MSC_VER
#pragma GCC diagnostic push
#endif /* _MSC_VER */

/* fallback for __has_builtin */
#ifndef __has_builtin
#define __has_builtin(x) 0
#endif /* __has_builtin */

/* fallback for __has_attribute */
#ifndef __has_attribute
#define __has_attribute(x) 0
#endif /* __has_attribute */

/* attribute nonnull */
#if !defined(__NONNULL) && __has_attribute(__nonnull__)
#define __NONNULL(x) __attribute__((__nonnull__ x))
#else
#define __NONNULL(x)
#endif /* __NONNULL */
#if !defined(__NONNULL_ALL) && __has_attribute(__nonnull__)
#define __NONNULL_ALL __attribute__((__nonnull__))
#else
#define __NONNULL_ALL
#endif /* __NONNULL_ALL */

/* attribute warn unused result */
#if !defined(__RESULT_USE_CHECK) && __has_attribute(__warn_unused_result__)
#define __RESULT_USE_CHECK __attribute__((__warn_unused_result__))
#else
#define __RESULT_USE_CHECK
#endif /* __RESULT_USE_CHECK */

/* attribute always inline */
#if !defined(__ALWAYS_INLINE) && __has_attribute(__always_inline__)
#define __ALWAYS_INLINE __inline __attribute__((__always_inline__))
#else
#define __ALWAYS_INLINE
#endif /* __ALWAYS_INLINE */

/* attribute weak */
#if !defined(__WEAK) && __has_attribute(__weak__)
#define __WEAK __attribute__((__weak__))
#else
#define __WEAK
#endif /* __WEAK */

/* attribute used */
#if !defined(__USED) && __has_attribute(__used__)
#define __USED __attribute__((__used__))
#else
#define __USED
#endif /* __USED */

/* attribute unused */
#if !defined(__UNUSED) && __has_attribute(__unused__)
#define __UNUSED __attribute__((__unused__))
#else
#define __UNUSED
#endif /* __UNUSED */

/* attribute aligned */
#if !defined(__ALIGNED) && __has_attribute(__aligned__)
#define __ALIGNED(x) __attribute__((__aligned__(x)))
#else
#define __ALIGNED(x)
#endif /* __ALIGNED */

/* attribute packed */
#if !defined(__PACKED) && __has_attribute(__packed__) && __has_attribute(__aligned__)
#define __PACKED __attribute__((__packed__, __aligned__(1)))
#else
#define __PACKED
#endif /* __PACKED */

/* attribute packed struct */
#if !defined(__PACKED_STRUCT) && __has_attribute(__packed__) && __has_attribute(__aligned__)
#define __PACKED_STRUCT struct __attribute__((__packed__, __aligned__(1)))
#else
#define __PACKED_STRUCT
#endif /* __PACKED_STRUCT */

/* attribute packed union */
#if !defined(__PACKED_UNION) && __has_attribute(__packed__) && __has_attribute(__aligned__)
#define __PACKED_UNION struct __attribute__((__packed__, __aligned__(1)))
#else
#define __PACKED_UNION
#endif /* __PACKED_UNION */

/* builtin expect */
#if !defined(__PREDICT_TRUE) && __has_builtin(__builtin_expect)
#define __PREDICT_TRUE(exp) __builtin_expect((exp), 1)
#else
#define __PREDICT_TRUE(exp) (exp)
#endif /* __PREDICT_TRUE */
#if !defined(__PREDICT_FALSE) && __has_builtin(__builtin_expect)
#define __PREDICT_FALSE(exp) __builtin_expect((exp), 0)
#else
#define __PREDICT_FALSE(exp) (exp)
#endif /* __PREDICT_FALSE */

/* asm */
#ifndef __ASM
#define __ASM __asm
#endif /* __ASM */

/* inline */
#ifndef __INLINE
#define __INLINE __inline
#endif /* __INLINE */

/* restrict */
#ifndef __RESTRICT
#define __RESTRICT __restrict
#endif /* __RESTRICT */

/* static inline */
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static __inline
#endif /* __STATIC_INLINE */

/* unused parameter */
#ifndef __UNUSED_PARAM
#define __UNUSED_PARAM(x) (void)(x)
#endif /* __UNUSED_PARAM */

/*!
 @endcond
 @defgroup LIBA Algorithm library
*/

#include <assert.h>
#include <stdint.h>

/* assertion */
#ifndef AASSERT
#define AASSERT(e) assert(e)
#endif /* ASSERT */

enum
{
    A_SUCCESS = 0,
    A_WARNING = -1,
    A_FAILURE = -2,
    A_INVALID = -3,
    A_OVERFLOW = -4,
    A_NOTFOUND = -5,
};

#ifndef aroundup32
#define aroundup32(x)    \
    (--(x),              \
     (x) |= (x) >> 0x01, \
     (x) |= (x) >> 0x02, \
     (x) |= (x) >> 0x04, \
     (x) |= (x) >> 0x08, \
     (x) |= (x) >> 0x10, \
     ++(x))
#endif /* aroundup32 */

/* reset some GCC warnings */
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

/* Enddef to prevent recursive inclusion */
#endif /* __LIBA_H__ */
