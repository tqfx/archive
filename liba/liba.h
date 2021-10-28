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

/* ignore some GCC warnings */
#ifndef _MSC_VER
#pragma GCC diagnostic push
#endif /* _MSC_VER */

/* fallback for __has_builtin */
#ifndef __has_builtin
#define __has_builtin(_x) 0
#endif /* __has_builtin */

/* gcc version check */
#ifndef __GNUC_PREREQ
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
#define __GNUC_PREREQ(_maj, _min) \
    ((__GNUC__ << 0x10) + __GNUC_MINOR__ >= ((_maj) << 0x10) + (_min))
#else
#define __GNUC_PREREQ(_maj, _min) 0
#endif /* defined(__GNUC__) && defined(__GNUC_MINOR__) */
#endif /* __GNUC_PREREQ */

/* clang version check */
#ifndef __glibc_clang_prereq
#if defined(__clang_major__) && defined(__clang_minor__)
#define __glibc_clang_prereq(_maj, _min) \
    ((__clang_major__ << 0x10) + __clang_minor__ >= ((_maj) << 0x10) + (_min))
#else
#define __glibc_clang_prereq(_maj, _min) 0
#endif /* defined(__clang_major__) && defined(__clang_minor__) */
#endif /* __glibc_clang_prereq */

/* C --> C++ */
#undef __END_DECLS
#undef __BEGIN_DECLS
#if defined(__cplusplus)
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS \
    }
#else
#define __END_DECLS
#define __BEGIN_DECLS
#endif /* __cplusplus */

/* attribute nonnull */
#ifndef __NONNULL
#if __GNUC_PREREQ(3, 3)
#define __NONNULL(_x) __attribute__((__nonnull__ _x))
#else
#define __NONNULL(_x)
#endif /* __GNUC_PREREQ(3, 3) */
#endif /* __NONNULL */
#ifndef __NONNULL_ALL
#if __GNUC_PREREQ(3, 3)
#define __NONNULL_ALL __attribute__((__nonnull__))
#else
#define __NONNULL_ALL
#endif /* __GNUC_PREREQ(3, 3) */
#endif /* __NONNULL_ALL */

/* attribute warn unused result */
#ifndef __RESULT_USE_CHECK
#if __GNUC_PREREQ(3, 4)
#define __RESULT_USE_CHECK __attribute__((__warn_unused_result__))
#else
#define __RESULT_USE_CHECK
#endif /* __GNUC_PREREQ(3, 4) */
#endif /* __RESULT_USE_CHECK */

/* attribute always inline */
#ifndef __ALWAYS_INLINE
#if __GNUC_PREREQ(3, 2)
#define __ALWAYS_INLINE __inline __attribute__((__always_inline__))
#else
#define __ALWAYS_INLINE
#endif /* __GNUC_PREREQ (3, 2) */
#endif /* __ALWAYS_INLINE */

/* attribute used */
#ifndef __USED
#if __GNUC_PREREQ(3, 0)
#define __USED __attribute__((__used__))
#else
#define __USED
#endif /* __GNUC_PREREQ (3, 0) */
#endif /* __USED */

/* attribute weak */
#ifndef __WEAK
#if __GNUC_PREREQ(3, 0)
#define __WEAK __attribute__((__weak__))
#else
#define __WEAK
#endif /* __GNUC_PREREQ (3, 0) */
#endif /* __WEAK */

/* attribute aligned */
#ifndef __ALIGNED
#if __GNUC_PREREQ(3, 0)
#define __ALIGNED(_x) __attribute__((__aligned__(_x)))
#else
#define __ALIGNED(_x)
#endif /* __GNUC_PREREQ (3, 0) */
#endif /* __ALIGNED */

/* attribute packed */
#ifndef __PACKED
#if __GNUC_PREREQ(3, 0)
#define __PACKED __attribute__((__packed__, __aligned__(1)))
#else
#define __PACKED
#endif /* __GNUC_PREREQ (3, 0) */
#endif /* __PACKED */

/* attribute packed struct */
#ifndef __PACKED_STRUCT
#if __GNUC_PREREQ(3, 0)
#define __PACKED_STRUCT struct __attribute__((__packed__, __aligned__(1)))
#else
#define __PACKED_STRUCT
#endif /* __GNUC_PREREQ (3, 0) */
#endif /* __PACKED_STRUCT */

/* attribute packed union */
#ifndef __PACKED_UNION
#if __GNUC_PREREQ(3, 0)
#define __PACKED_UNION struct __attribute__((__packed__, __aligned__(1)))
#else
#define __PACKED_UNION
#endif /* __GNUC_PREREQ (3, 0) */
#endif /* __PACKED_UNION */

/* builtin expect */
#ifndef __PREDICT_TRUE
#if __GNUC_PREREQ(3, 0)
#define __PREDICT_TRUE(_exp) __builtin_expect((_exp), 1)
#else
#define __PREDICT_TRUE(_exp) (_exp)
#endif /* __GNUC_PREREQ (3, 0) */
#endif /* __PREDICT_TRUE */
#ifndef __PREDICT_FALSE
#if __GNUC_PREREQ(3, 0)
#define __PREDICT_FALSE(_exp) __builtin_expect((_exp), 0)
#else
#define __PREDICT_FALSE(_exp) (_exp)
#endif /* __GNUC_PREREQ (3, 0) */
#endif /* __PREDICT_FALSE */

/* attribute unused */
#ifndef __UNUSED
#if __glibc_clang_prereq(3, 3)
#define __UNUSED __attribute__((__unused__))
#else
#define __UNUSED
#endif /* __glibc_clang_prereq(3, 3) */
#endif /* __UNUSED */

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

/* extract a byte portably */
#undef A_BYTE
#define A_BYTE(_x, _n) ((uint8_t)((_x) >> ((_n) << 3)))

/* assertion */
#ifndef a_assert
#define a_assert(_e)
#endif /* a_assert */

/* allocate memory */
#ifndef a_alloc
#define a_alloc(_z) malloc(_z)
#endif /* a_alloc */

/* callocate memory */
#ifndef a_calloc
#define a_calloc(_n, _z) calloc(_n, _z)
#endif /* a_calloc */

/* reallocate memory */
#ifndef a_realloc
#define a_realloc(_p, _z) realloc(_p, _z)
#endif /* a_realloc */

/* free memory */
#ifndef a_free
#define a_free(_p) free(_p)
#endif /* a_free */

/* reset some GCC warnings */
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

/* Enddef to prevent recursive inclusion */
#endif /* __LIBA_H__ */

/* END OF FILE */
