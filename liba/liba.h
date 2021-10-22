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
#define __has_builtin(x) 0
#endif /* __has_builtin */

/* gcc version check */
#ifndef __GNUC_PREREQ
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
#define __GNUC_PREREQ(maj, min) \
    ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
#define __GNUC_PREREQ(maj, min) 0
#endif /* defined(__GNUC__) && defined(__GNUC_MINOR__) */
#endif /* __GNUC_PREREQ */

/* clang version check */
#ifndef __glibc_clang_prereq
#if defined(__clang_major__) && defined(__clang_minor__)
#define __glibc_clang_prereq(maj, min) \
    ((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#else
#define __glibc_clang_prereq(maj, min) 0
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
#define __NONNULL(_X_) __attribute__((__nonnull__ _X_))
#else
#define __NONNULL(_X_)
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
#endif /* __GNUC_PREREQ (3,2) */
#endif /* __ALWAYS_INLINE */

/* attribute used */
#ifndef __USED
#if defined(__GNUC__) && (__GNUC__ >= 3)
#define __USED __attribute__((__used__))
#else
#define __USED
#endif /* defined(__GNUC__) && (__GNUC__ >= 3) */
#endif /* __USED */

/* attribute weak */
#ifndef __WEAK
#if defined(__GNUC__) && (__GNUC__ >= 3)
#define __WEAK __attribute__((__weak__))
#else
#define __WEAK
#endif /* defined(__GNUC__) && (__GNUC__ >= 3) */
#endif /* __WEAK */

/* attribute aligned */
#ifndef __ALIGNED
#if defined(__GNUC__) && (__GNUC__ >= 3)
#define __ALIGNED(x) __attribute__((__aligned__(x)))
#else
#define __ALIGNED(x)
#endif /* defined(__GNUC__) && (__GNUC__ >= 3) */
#endif /* __ALIGNED */

/* attribute packed */
#ifndef __PACKED
#if defined(__GNUC__) && (__GNUC__ >= 3)
#define __PACKED __attribute__((__packed__, __aligned__(1)))
#else
#define __PACKED
#endif /* defined(__GNUC__) && (__GNUC__ >= 3) */
#endif /* __PACKED */

/* attribute packed struct */
#ifndef __PACKED_STRUCT
#if defined(__GNUC__) && (__GNUC__ >= 3)
#define __PACKED_STRUCT struct __attribute__((__packed__, __aligned__(1)))
#else
#define __PACKED_STRUCT
#endif /* defined(__GNUC__) && (__GNUC__ >= 3) */
#endif /* __PACKED_STRUCT */

/* attribute packed union */
#ifndef __PACKED_UNION
#if defined(__GNUC__) && (__GNUC__ >= 3)
#define __PACKED_UNION struct __attribute__((__packed__, __aligned__(1)))
#else
#define __PACKED_UNION
#endif /* defined(__GNUC__) && (__GNUC__ >= 3) */
#endif /* __PACKED_UNION */

/* builtin expect */
#ifndef __PREDICT_TRUE
#if defined(__GNUC__) && (__GNUC__ >= 3)
#define __PREDICT_TRUE(_EXP_) __builtin_expect((_EXP_), 1)
#else
#define __PREDICT_TRUE(_EXP_) (_EXP_)
#endif /* defined(__GNUC__) && (__GNUC__ >= 3) */
#endif /* __PREDICT_TRUE */
#ifndef __PREDICT_FALSE
#if defined(__GNUC__) && (__GNUC__ >= 3)
#define __PREDICT_FALSE(_EXP_) __builtin_expect((_EXP_), 0)
#else
#define __PREDICT_FALSE(_EXP_) (_EXP_)
#endif /* defined(__GNUC__) && (__GNUC__ >= 3) */
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

/* unused param */
#ifndef __UNUSED_PARAM
#define __UNUSED_PARAM(x) (void)(x)
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
#define BSWAP(x) (((x >> 0x18) & 0x000000FF) | \
                  ((x << 0x18) & 0xFF000000) | \
                  ((x >> 0x08) & 0x0000FF00) | \
                  ((x << 0x08) & 0x00FF0000))

#undef LOAD32L
#undef LOAD64L
#undef STORE32L
#undef STORE64L
#ifndef ENDIAN_NEUTRAL
#define LOAD32L(x, y)       \
    do                      \
    {                       \
        memcpy(&(x), y, 4); \
        x &= 0xFFFFFFFF;    \
    } while (0)
#define STORE32L(x, y)     \
    do                     \
    {                      \
        uint32_t _t = (x); \
        memcpy(y, &_t, 4); \
    } while (0)
#define LOAD64L(x, y)       \
    do                      \
    {                       \
        memcpy(&(x), y, 8); \
    } while (0)
#define STORE64L(x, y)     \
    do                     \
    {                      \
        uint64_t _t = (x); \
        memcpy(y, &_t, 8); \
    } while (0)
#else
#define LOAD32L(x, y)                             \
    do                                            \
    {                                             \
        x = ((uint32_t)((y)[3] & 0xFF) << 0x18) | \
            ((uint32_t)((y)[2] & 0xFF) << 0x10) | \
            ((uint32_t)((y)[1] & 0xFF) << 0x08) | \
            ((uint32_t)((y)[0] & 0xFF) << 0x00);  \
    } while (0)
#define STORE32L(x, y)                            \
    do                                            \
    {                                             \
        (y)[3] = (uint8_t)(((x) >> 0x18) & 0xFF); \
        (y)[2] = (uint8_t)(((x) >> 0x10) & 0xFF); \
        (y)[1] = (uint8_t)(((x) >> 0x08) & 0xFF); \
        (y)[0] = (uint8_t)(((x) >> 0x00) & 0xFF); \
    } while (0)
#define LOAD64L(x, y)                               \
    do                                              \
    {                                               \
        x = (((uint64_t)((y)[7] & 0xFF)) << 0x38) | \
            (((uint64_t)((y)[6] & 0xFF)) << 0x30) | \
            (((uint64_t)((y)[5] & 0xFF)) << 0x28) | \
            (((uint64_t)((y)[4] & 0xFF)) << 0x20) | \
            (((uint64_t)((y)[3] & 0xFF)) << 0x18) | \
            (((uint64_t)((y)[2] & 0xFF)) << 0x10) | \
            (((uint64_t)((y)[1] & 0xFF)) << 0x08) | \
            (((uint64_t)((y)[0] & 0xFF)) << 0x00);  \
    } while (0)
#define STORE64L(x, y)                            \
    do                                            \
    {                                             \
        (y)[7] = (uint8_t)(((x) >> 0x38) & 0xFF); \
        (y)[6] = (uint8_t)(((x) >> 0x30) & 0xFF); \
        (y)[5] = (uint8_t)(((x) >> 0x28) & 0xFF); \
        (y)[4] = (uint8_t)(((x) >> 0x20) & 0xFF); \
        (y)[3] = (uint8_t)(((x) >> 0x18) & 0xFF); \
        (y)[2] = (uint8_t)(((x) >> 0x10) & 0xFF); \
        (y)[1] = (uint8_t)(((x) >> 0x08) & 0xFF); \
        (y)[0] = (uint8_t)(((x) >> 0x00) & 0xFF); \
    } while (0)
#endif /* ENDIAN_NEUTRAL */

#undef LOAD32H
#undef STORE32H
#if __has_builtin(__builtin_bswap32)
#define LOAD32H(x, y)                 \
    do                                \
    {                                 \
        memcpy(&(x), (y), 4);         \
        (x) = __builtin_bswap32((x)); \
    } while (0)
#define STORE32H(x, y)                        \
    do                                        \
    {                                         \
        uint32_t _t = __builtin_bswap32((x)); \
        memcpy((y), &_t, 4);                  \
    } while (0)
#else
#define LOAD32H(x, y)                             \
    do                                            \
    {                                             \
        x = ((uint32_t)((y)[0] & 0xFF) << 0x18) | \
            ((uint32_t)((y)[1] & 0xFF) << 0x10) | \
            ((uint32_t)((y)[2] & 0xFF) << 0x08) | \
            ((uint32_t)((y)[3] & 0xFF) << 0x00);  \
    } while (0)
#define STORE32H(x, y)                            \
    do                                            \
    {                                             \
        (y)[0] = (uint8_t)(((x) >> 0x18) & 0xFF); \
        (y)[1] = (uint8_t)(((x) >> 0x10) & 0xFF); \
        (y)[2] = (uint8_t)(((x) >> 0x08) & 0xFF); \
        (y)[3] = (uint8_t)(((x) >> 0x00) & 0xFF); \
    } while (0)
#endif /* __has_builtin(__builtin_bswap32) */

#undef LOAD64H
#undef STORE64H
#if __has_builtin(__builtin_bswap64)
#define LOAD64H(x, y)                 \
    do                                \
    {                                 \
        memcpy(&(x), (y), 8);         \
        (x) = __builtin_bswap64((x)); \
    } while (0)
#define STORE64H(x, y)                        \
    do                                        \
    {                                         \
        uint64_t _t = __builtin_bswap64((x)); \
        memcpy((y), &_t, 8);                  \
    } while (0)
#else
#define LOAD64H(x, y)                               \
    do                                              \
    {                                               \
        x = (((uint64_t)((y)[0] & 0xFF)) << 0x38) | \
            (((uint64_t)((y)[1] & 0xFF)) << 0x30) | \
            (((uint64_t)((y)[2] & 0xFF)) << 0x28) | \
            (((uint64_t)((y)[3] & 0xFF)) << 0x20) | \
            (((uint64_t)((y)[4] & 0xFF)) << 0x18) | \
            (((uint64_t)((y)[5] & 0xFF)) << 0x10) | \
            (((uint64_t)((y)[6] & 0xFF)) << 0x08) | \
            (((uint64_t)((y)[7] & 0xFF)) << 0x00);  \
    } while (0)
#define STORE64H(x, y)                            \
    do                                            \
    {                                             \
        (y)[0] = (uint8_t)(((x) >> 0x38) & 0xFF); \
        (y)[1] = (uint8_t)(((x) >> 0x30) & 0xFF); \
        (y)[2] = (uint8_t)(((x) >> 0x28) & 0xFF); \
        (y)[3] = (uint8_t)(((x) >> 0x20) & 0xFF); \
        (y)[4] = (uint8_t)(((x) >> 0x18) & 0xFF); \
        (y)[5] = (uint8_t)(((x) >> 0x10) & 0xFF); \
        (y)[6] = (uint8_t)(((x) >> 0x08) & 0xFF); \
        (y)[7] = (uint8_t)(((x) >> 0x00) & 0xFF); \
    } while (0)
#endif /* __has_builtin(__builtin_bswap64) */

/* 32-bit Rotates */
#undef ROR
#undef ROL
#undef RORc
#undef ROLc
#if defined(_MSC_VER)
/* instrinsic rotate */
#pragma intrinsic(_rotr, _rotl)
#define ROR(x, n)  _rotr(x, n)
#define ROL(x, n)  _rotl(x, n)
#define RORc(x, n) ROR(x, n)
#define ROLc(x, n) ROL(x, n)
#elif __has_builtin(__builtin_rotateright32) && __has_builtin(__builtin_rotateleft32)
#define ROR(x, n)  __builtin_rotateright32(x, n)
#define ROL(x, n)  __builtin_rotateleft32(x, n)
#define RORc(x, n) ROR(x, n)
#define ROLc(x, n) ROL(x, n)
#else /* rotates the hard way */
#define ROL(x, y)  ((((uint32_t)(x) << (uint32_t)((y)&31)) | (((uint32_t)(x)&0xFFFFFFFF) >> (uint32_t)((32 - ((y)&31)) & 31))) & 0xFFFFFFFF)
#define ROR(x, y)  (((((uint32_t)(x)&0xFFFFFFFF) >> (uint32_t)((y)&31)) | ((uint32_t)(x) << (uint32_t)((32 - ((y)&31)) & 31))) & 0xFFFFFFFF)
#define ROLc(x, y) ((((uint32_t)(x) << (uint32_t)((y)&31)) | (((uint32_t)(x)&0xFFFFFFFF) >> (uint32_t)((32 - ((y)&31)) & 31))) & 0xFFFFFFFF)
#define RORc(x, y) (((((uint32_t)(x)&0xFFFFFFFF) >> (uint32_t)((y)&31)) | ((uint32_t)(x) << (uint32_t)((32 - ((y)&31)) & 31))) & 0xFFFFFFFF)
#endif /* 32-bit Rotates */

/* 64-bit Rotates */
#undef ROR64
#undef ROL64
#undef ROR64c
#undef ROL64c
#if defined(_MSC_VER)
/* instrinsic rotate */
#pragma intrinsic(_rotr64, _rotr64)
#define ROR64(x, n)  _rotr64(x, n)
#define ROL64(x, n)  _rotl64(x, n)
#define ROR64c(x, n) ROR64(x, n)
#define ROL64c(x, n) ROL64(x, n)
#elif __has_builtin(__builtin_rotateright64) && __has_builtin(__builtin_rotateleft64)
#define ROR64(x, n)  __builtin_rotateright64(x, n)
#define ROL64(x, n)  __builtin_rotateleft64(x, n)
#define ROR64c(x, n) ROR64(x, n)
#define ROL64c(x, n) ROL64(x, n)
#else /* rotates the hard way */
#define ROL64(x, y)  ((((uint64_t)(x) << ((uint64_t)(y)&63)) | (((uint64_t)(x)&0xFFFFFFFFFFFFFFFF) >> (uint64_t)((64 - ((y)&63)) & 63))) & 0xFFFFFFFFFFFFFFFF)
#define ROR64(x, y)  ((((uint64_t)((x)&0xFFFFFFFFFFFFFFFF) >> ((uint64_t)(y)&63)) | ((uint64_t)(x) << (uint64_t)((64 - ((y)&63)) & 63))) & 0xFFFFFFFFFFFFFFFF)
#define ROL64c(x, y) ((((uint64_t)(x) << ((uint64_t)(y)&63)) | (((uint64_t)(x)&0xFFFFFFFFFFFFFFFF) >> (uint64_t)((64 - ((y)&63)) & 63))) & 0xFFFFFFFFFFFFFFFF)
#define ROR64c(x, y) (((((uint64_t)(x)&0xFFFFFFFFFFFFFFFF) >> ((uint64_t)(y)&63)) | ((uint64_t)(x) << (uint64_t)((64 - ((y)&63)) & 63))) & 0xFFFFFFFFFFFFFFFF)
#endif /* 64-bit Rotates */

/* extract a byte portably */
#undef A_BYTE
#define A_BYTE(x, n) ((uint8_t)((x) >> ((n) << 3)))

/* allocate memory */
#ifndef a_alloc
#define a_alloc(n) malloc(n)
#endif /* a_alloc */

/* callocate memory */
#ifndef a_calloc
#define a_calloc(n, sz) calloc(n, sz)
#endif /* a_calloc */

/* reallocate memory */
#ifndef a_realloc
#define a_realloc(p, n) realloc(p, n)
#endif /* a_realloc */

/* free memory */
#ifndef a_free
#define a_free(p) free(p)
#endif /* a_free */

/* reset some GCC warnings */
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

/* Enddef to prevent recursive inclusion */
#endif /* __LIBA_H__ */

/* END OF FILE */
