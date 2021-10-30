/*!
 @file           liba.h
 @brief          algorithm library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
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
#define __BEGIN_DECLS \
    extern "C" {
#define __END_DECLS \
    }
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
#define __has_builtin(_x) 0
#endif /* __has_builtin */

/* fallback for __has_attribute */
#ifndef __has_attribute
#define __has_attribute(_x) 0
#endif /* __has_attribute */

/* attribute nonnull */
#if !defined(__NONNULL) && __has_attribute(__nonnull__)
#define __NONNULL(_x) __attribute__((__nonnull__ _x))
#else
#define __NONNULL(_x)
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
#define __ALIGNED(_x) __attribute__((__aligned__(_x)))
#else
#define __ALIGNED(_x)
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
#define __PREDICT_TRUE(_exp) __builtin_expect((_exp), 1)
#else
#define __PREDICT_TRUE(_exp) (_exp)
#endif /* __PREDICT_TRUE */
#if !defined(__PREDICT_FALSE) && __has_builtin(__builtin_expect)
#define __PREDICT_FALSE(_exp) __builtin_expect((_exp), 0)
#else
#define __PREDICT_FALSE(_exp) (_exp)
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
#define __UNUSED_PARAM(_x) (void)(_x)
#endif /* __UNUSED_PARAM */

/*!
 @endcond
 @defgroup       LIBA Algorithm library
*/

#include <stdint.h>
#if defined(_MSC_VER)
#include <stdlib.h>
#endif /* _MSC_VER */

enum
{
    A_SUCCESS = 0,
    A_WARNING = -1,
    A_FAILURE = -2,
    A_INVALID = -3,
    A_OVERFLOW = -4,
    A_NOTFOUND = -5,
};

typedef float float32_t;
typedef double float64_t;

/* Endian Neutral macros that work on all platforms */

#undef BSWAP
#define BSWAP(_x) ((((_x) >> 0x18) & 0x000000FF) | \
                   (((_x) << 0x18) & 0xFF000000) | \
                   (((_x) >> 0x08) & 0x0000FF00) | \
                   (((_x) << 0x08) & 0x00FF0000))

#undef LOAD32L
#undef LOAD64L
#undef STORE32L
#undef STORE64L
#ifndef ENDIAN_NEUTRAL
#define LOAD32L(_x, _y)       \
    do                        \
    {                         \
        memcpy(&(_x), _y, 4); \
        (_x) &= 0xFFFFFFFF;   \
    } while (0)
#define STORE32L(_x, _y)    \
    do                      \
    {                       \
        uint32_t _t = _x;   \
        memcpy(_y, &_t, 4); \
    } while (0)
#define LOAD64L(_x, _y)       \
    do                        \
    {                         \
        memcpy(&(_x), _y, 8); \
    } while (0)
#define STORE64L(_x, _y)    \
    do                      \
    {                       \
        uint64_t _t = _x;   \
        memcpy(_y, &_t, 8); \
    } while (0)
#else
#define LOAD32L(_x, _y)                               \
    do                                                \
    {                                                 \
        (_x) = ((uint32_t)((_y)[3] & 0xFF) << 0x18) | \
               ((uint32_t)((_y)[2] & 0xFF) << 0x10) | \
               ((uint32_t)((_y)[1] & 0xFF) << 0x08) | \
               ((uint32_t)((_y)[0] & 0xFF) << 0x00);  \
    } while (0)
#define STORE32L(_x, _y)                            \
    do                                              \
    {                                               \
        (_y)[3] = (uint8_t)(((_x) >> 0x18) & 0xFF); \
        (_y)[2] = (uint8_t)(((_x) >> 0x10) & 0xFF); \
        (_y)[1] = (uint8_t)(((_x) >> 0x08) & 0xFF); \
        (_y)[0] = (uint8_t)(((_x) >> 0x00) & 0xFF); \
    } while (0)
#define LOAD64L(_x, _y)                                 \
    do                                                  \
    {                                                   \
        (_x) = (((uint64_t)((_y)[7] & 0xFF)) << 0x38) | \
               (((uint64_t)((_y)[6] & 0xFF)) << 0x30) | \
               (((uint64_t)((_y)[5] & 0xFF)) << 0x28) | \
               (((uint64_t)((_y)[4] & 0xFF)) << 0x20) | \
               (((uint64_t)((_y)[3] & 0xFF)) << 0x18) | \
               (((uint64_t)((_y)[2] & 0xFF)) << 0x10) | \
               (((uint64_t)((_y)[1] & 0xFF)) << 0x08) | \
               (((uint64_t)((_y)[0] & 0xFF)) << 0x00);  \
    } while (0)
#define STORE64L(_x, _y)                            \
    do                                              \
    {                                               \
        (_y)[7] = (uint8_t)(((_x) >> 0x38) & 0xFF); \
        (_y)[6] = (uint8_t)(((_x) >> 0x30) & 0xFF); \
        (_y)[5] = (uint8_t)(((_x) >> 0x28) & 0xFF); \
        (_y)[4] = (uint8_t)(((_x) >> 0x20) & 0xFF); \
        (_y)[3] = (uint8_t)(((_x) >> 0x18) & 0xFF); \
        (_y)[2] = (uint8_t)(((_x) >> 0x10) & 0xFF); \
        (_y)[1] = (uint8_t)(((_x) >> 0x08) & 0xFF); \
        (_y)[0] = (uint8_t)(((_x) >> 0x00) & 0xFF); \
    } while (0)
#endif /* ENDIAN_NEUTRAL */

#undef LOAD32H
#undef STORE32H
#if __has_builtin(__builtin_bswap32)
#define LOAD32H(_x, _y)               \
    do                                \
    {                                 \
        memcpy(&(_x), _y, 4);         \
        (_x) = __builtin_bswap32(_x); \
    } while (0)
#define STORE32H(_x, _y)                     \
    do                                       \
    {                                        \
        uint32_t _t = __builtin_bswap32(_x); \
        memcpy(_y, &_t, 4);                  \
    } while (0)
#else
#define LOAD32H(_x, _y)                               \
    do                                                \
    {                                                 \
        (_x) = ((uint32_t)((_y)[0] & 0xFF) << 0x18) | \
               ((uint32_t)((_y)[1] & 0xFF) << 0x10) | \
               ((uint32_t)((_y)[2] & 0xFF) << 0x08) | \
               ((uint32_t)((_y)[3] & 0xFF) << 0x00);  \
    } while (0)
#define STORE32H(_x, _y)                            \
    do                                              \
    {                                               \
        (_y)[0] = (uint8_t)(((_x) >> 0x18) & 0xFF); \
        (_y)[1] = (uint8_t)(((_x) >> 0x10) & 0xFF); \
        (_y)[2] = (uint8_t)(((_x) >> 0x08) & 0xFF); \
        (_y)[3] = (uint8_t)(((_x) >> 0x00) & 0xFF); \
    } while (0)
#endif /* __has_builtin(__builtin_bswap32) */

#undef LOAD64H
#undef STORE64H
#if __has_builtin(__builtin_bswap64)
#define LOAD64H(_x, _y)               \
    do                                \
    {                                 \
        memcpy(&(_x), _y, 8);         \
        (_x) = __builtin_bswap64(_x); \
    } while (0)
#define STORE64H(_x, _y)                     \
    do                                       \
    {                                        \
        uint64_t _t = __builtin_bswap64(_x); \
        memcpy(_y, &_t, 8);                  \
    } while (0)
#else
#define LOAD64H(_x, _y)                                 \
    do                                                  \
    {                                                   \
        (_x) = (((uint64_t)((_y)[0] & 0xFF)) << 0x38) | \
               (((uint64_t)((_y)[1] & 0xFF)) << 0x30) | \
               (((uint64_t)((_y)[2] & 0xFF)) << 0x28) | \
               (((uint64_t)((_y)[3] & 0xFF)) << 0x20) | \
               (((uint64_t)((_y)[4] & 0xFF)) << 0x18) | \
               (((uint64_t)((_y)[5] & 0xFF)) << 0x10) | \
               (((uint64_t)((_y)[6] & 0xFF)) << 0x08) | \
               (((uint64_t)((_y)[7] & 0xFF)) << 0x00);  \
    } while (0)
#define STORE64H(_x, _y)                            \
    do                                              \
    {                                               \
        (_y)[0] = (uint8_t)(((_x) >> 0x38) & 0xFF); \
        (_y)[1] = (uint8_t)(((_x) >> 0x30) & 0xFF); \
        (_y)[2] = (uint8_t)(((_x) >> 0x28) & 0xFF); \
        (_y)[3] = (uint8_t)(((_x) >> 0x20) & 0xFF); \
        (_y)[4] = (uint8_t)(((_x) >> 0x18) & 0xFF); \
        (_y)[5] = (uint8_t)(((_x) >> 0x10) & 0xFF); \
        (_y)[6] = (uint8_t)(((_x) >> 0x08) & 0xFF); \
        (_y)[7] = (uint8_t)(((_x) >> 0x00) & 0xFF); \
    } while (0)
#endif /* __has_builtin(__builtin_bswap64) */

/* 32-bit Rotates */
#undef ROL
#undef ROR
#undef ROLc
#undef RORc
#define ROLc(_x, _n) ROL(_x, _n)
#define RORc(_x, _n) ROR(_x, _n)
#if defined(_MSC_VER)
/* instrinsic rotate */
#pragma intrinsic(_rotl, _rotr)
#define ROL(_x, _n) _rotl(_x, _n)
#define ROR(_x, _n) _rotr(_x, _n)
#elif __has_builtin(__builtin_rotateleft32) && __has_builtin(__builtin_rotateright32)
#define ROL(_x, _n) __builtin_rotateleft32(_x, _n)
#define ROR(_x, _n) __builtin_rotateright32(_x, _n)
#else /* rotates the hard way */
#define ROL(_x, _y) ((((uint32_t)(_x) << (uint32_t)((_y)&31)) | (((uint32_t)(_x)&0xFFFFFFFF) >> (uint32_t)((32 - ((_y)&31)) & 31))) & 0xFFFFFFFF)
#define ROR(_x, _y) (((((uint32_t)(_x)&0xFFFFFFFF) >> (uint32_t)((_y)&31)) | ((uint32_t)(_x) << (uint32_t)((32 - ((_y)&31)) & 31))) & 0xFFFFFFFF)
#endif /* 32-bit Rotates */

/* 64-bit Rotates */
#undef ROR64
#undef ROL64
#undef ROL64c
#undef ROR64c
#define ROL64c(_x, _n) ROL64(_x, _n)
#define ROR64c(_x, _n) ROR64(_x, _n)
#if defined(_MSC_VER)
/* instrinsic rotate */
#pragma intrinsic(_rotl64, _rotr64)
#define ROL64(_x, _n) _rotl64(_x, _n)
#define ROR64(_x, _n) _rotr64(_x, _n)
#elif __has_builtin(__builtin_rotateleft64) && __has_builtin(__builtin_rotateright64)
#define ROL64(_x, _n) __builtin_rotateleft64(_x, _n)
#define ROR64(_x, _n) __builtin_rotateright64(_x, _n)
#else /* rotates the hard way */
#define ROL64(_x, _y) ((((uint64_t)(_x) << ((uint64_t)(_y)&63)) | (((uint64_t)(_x)&0xFFFFFFFFFFFFFFFF) >> (uint64_t)((64 - ((_y)&63)) & 63))) & 0xFFFFFFFFFFFFFFFF)
#define ROR64(_x, _y) ((((uint64_t)((_x)&0xFFFFFFFFFFFFFFFF) >> ((uint64_t)(_y)&63)) | ((uint64_t)(_x) << (uint64_t)((64 - ((_y)&63)) & 63))) & 0xFFFFFFFFFFFFFFFF)
#endif /* 64-bit Rotates */

#ifndef aroundup32
#define aroundup32(_x)     \
    (--(_x),               \
     (_x) |= (_x) >> 0x01, \
     (_x) |= (_x) >> 0x02, \
     (_x) |= (_x) >> 0x04, \
     (_x) |= (_x) >> 0x08, \
     (_x) |= (_x) >> 0x10, \
     ++(_x))
#endif /* aroundup32 */

/* assertion */
#ifndef aassert
#define aassert(_e)
#endif /* aassert */

/* allocate memory */
#ifndef amalloc
#define amalloc(_z) malloc(_z)
#endif /* amalloc */

/* callocate memory */
#ifndef acalloc
#define acalloc(_n, _z) calloc(_n, _z)
#endif /* acalloc */

/* reallocate memory */
#ifndef arealloc
#define arealloc(_p, _z) realloc(_p, _z)
#endif /* arealloc */

/* free memory */
#ifndef afree
#define afree(_p) free(_p)
#endif /* afree */

/* reset some GCC warnings */
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

/* Enddef to prevent recursive inclusion */
#endif /* __LIBA_H__ */

/* END OF FILE */
