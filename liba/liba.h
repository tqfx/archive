/*!
 @file           liba.h
 @brief          Algorithm library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __LIBA_H__
#define __LIBA_H__

/*!
 @cond
*/

/* C --> C++ */
#undef __BEGIN_DECLS
#undef __END_DECLS

#ifdef __cplusplus
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS \
    }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

/* gcc version check */
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
#define __GNUC_PREREQ(maj, min) \
    ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
#define __GNUC_PREREQ(maj, min) 0
#endif /* defined(__GNUC__) && defined(__GNUC_MINOR__) */

/* clang version check */
#if defined(__clang_major__) && defined(__clang_minor__)
#define __glibc_clang_prereq(maj, min) \
    ((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#else
#define __glibc_clang_prereq(maj, min) 0
#endif /* defined(__clang_major__) && defined(__clang_minor__) */

/* attribute nonnull */
#undef __NONNULL
#undef __NONNULL_ALL

#if __GNUC_PREREQ(3, 3)
#define __NONNULL(_X_) __attribute__((__nonnull__ _X_))
#define __NONNULL_ALL  __attribute__((__nonnull__))
#else
#define __NONNULL(_X_)
#define __NONNULL_ALL
#endif /* __GNUC_PREREQ(3, 3) */

#ifndef __nonnull
#define __nonnull(_x_) __NONNULL(_x_)
#endif /* __nonnull */
#ifndef __nonnull_all
#define __nonnull_all __NONNULL_ALL
#endif /* __nonnull_all */

/* attribute warn unused result */
#undef __RESULT_USE_CHECK

#if __GNUC_PREREQ(3, 4)
#define __RESULT_USE_CHECK __attribute__((__warn_unused_result__))
#else
#define __RESULT_USE_CHECK
#endif /* __GNUC_PREREQ(3, 4) */

#ifndef __result_use_check
#define __result_use_check __RESULT_USE_CHECK
#endif /* __result_use_check */

/* static inline */
#undef __STATIC_INLINE

#define __STATIC_INLINE static __inline

#ifndef __static_inline
#define __static_inline __STATIC_INLINE
#endif /* __static_inline */

/* attribute always inline */
#undef __ALWAYS_INLINE

#if __GNUC_PREREQ(3, 2)
#define __ALWAYS_INLINE __inline __attribute__((__always_inline__))
#else
#define __ALWAYS_INLINE
#endif /* __GNUC_PREREQ (3,2) */

#ifndef __always_inline
#define __always_inline __ALWAYS_INLINE
#endif /* __always_inline */

/* builtin expect */
#undef __PREDICT_TRUE
#undef __PREDICT_FALSE

#if defined(__GNUC__)
#if __GNUC__ >= 3
#define __PREDICT_TRUE(_EXP_)  __builtin_expect((_EXP_), 1)
#define __PREDICT_FALSE(_EXP_) __builtin_expect((_EXP_), 0)
#else /* __GNUC__ < 3 */
#define __PREDICT_TRUE(_EXP_)  (_EXP_)
#define __PREDICT_FALSE(_EXP_) (_EXP_)
#endif /* __GNUC__ >= 3 */
#else  /* Not GCC */
#define __PREDICT_TRUE(_EXP_)  (_EXP_)
#define __PREDICT_FALSE(_EXP_) (_EXP_)
#endif /* __GNUC__ */

#ifndef __predict_true
#define __predict_true(_exp_) __PREDICT_TRUE(_exp_)
#endif /* __predict_true */
#ifndef __predict_false
#define __predict_false(_exp_) __PREDICT_FALSE(_exp_)
#endif /* __predict_false */

/* attribute weak */
#undef __WEAK

#if defined(__GNUC__)
#if __GNUC__ >= 3
#define __WEAK __attribute__((__weak__))
#else /* __GNUC__ < 3 */
#define __WEAK
#endif /* __GNUC__ >= 3 */
#else  /* Not GCC */
#define __WEAK
#endif /* __GNUC__ */

#ifndef __weak
#define __weak __WEAK
#endif /* __weak */

/* attribute unused */
#undef __UNUSED

#if __glibc_clang_prereq(3, 3)
#define __UNUSED __attribute__((__unused__))
#else
#define __UNUSED
#endif /* __glibc_clang_prereq(3, 3) */

#ifndef __unused
#define __unused __UNUSED
#endif /* __unused */

#include <stdint.h>

/*!
 @endcond
 @defgroup       LIBA Algorithm library
*/

typedef float float32_t;
typedef double float64_t;

/* Endian Neutral macros that work on all platforms */

#undef BSWAP
#define BSWAP(x) (((x >> 0x18) & 0x000000FF) | \
                  ((x << 0x18) & 0xFF000000) | \
                  ((x >> 0x08) & 0x0000FF00) | \
                  ((x << 0x08) & 0x00FF0000))

#undef STORE32L
#define STORE32L(x, y)                            \
    do                                            \
    {                                             \
        (y)[3] = (uint8_t)(((x) >> 0x18) & 0xFF); \
        (y)[2] = (uint8_t)(((x) >> 0x10) & 0xFF); \
        (y)[1] = (uint8_t)(((x) >> 0x08) & 0xFF); \
        (y)[0] = (uint8_t)(((x) >> 0x00) & 0xFF); \
    } while (0)

#undef LOAD32L
#define LOAD32L(x, y)                             \
    do                                            \
    {                                             \
        x = ((uint32_t)((y)[3] & 0xFF) << 0x18) | \
            ((uint32_t)((y)[2] & 0xFF) << 0x10) | \
            ((uint32_t)((y)[1] & 0xFF) << 0x08) | \
            ((uint32_t)((y)[0] & 0xFF) << 0x00);  \
    } while (0)

#undef STORE64L
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

#undef LOAD64L
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

#undef STORE32H
#define STORE32H(x, y)                            \
    do                                            \
    {                                             \
        (y)[0] = (uint8_t)(((x) >> 0x18) & 0xFF); \
        (y)[1] = (uint8_t)(((x) >> 0x10) & 0xFF); \
        (y)[2] = (uint8_t)(((x) >> 0x08) & 0xFF); \
        (y)[3] = (uint8_t)(((x) >> 0x00) & 0xFF); \
    } while (0)

#undef LOAD32H
#define LOAD32H(x, y)                             \
    do                                            \
    {                                             \
        x = ((uint32_t)((y)[0] & 0xFF) << 0x18) | \
            ((uint32_t)((y)[1] & 0xFF) << 0x10) | \
            ((uint32_t)((y)[2] & 0xFF) << 0x08) | \
            ((uint32_t)((y)[3] & 0xFF) << 0x00);  \
    } while (0)

#undef STORE64H
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

#undef LOAD64H
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

#undef __A_HASH_PROCESS
#define __A_HASH_PROCESS(hash, func, compress)                    \
    void func(hash *ctx, const void *p, size_t n)                 \
    {                                                             \
        const unsigned char *s = (const unsigned char *)p;        \
        while (n)                                                 \
        {                                                         \
            if ((0 == ctx->curlen) && (sizeof(ctx->buf) - 1 < n)) \
            {                                                     \
                compress(ctx, s);                                 \
                ctx->length += (sizeof(ctx->buf) << 3);           \
                s += sizeof(ctx->buf);                            \
                n -= sizeof(ctx->buf);                            \
            }                                                     \
            else                                                  \
            {                                                     \
                uint32_t m = sizeof(ctx->buf) - ctx->curlen;      \
                m = m < n ? m : (uint32_t)n;                      \
                memcpy(ctx->buf + ctx->curlen, s, m);             \
                ctx->curlen += m;                                 \
                s += m;                                           \
                n -= m;                                           \
                if (sizeof(ctx->buf) == ctx->curlen)              \
                {                                                 \
                    compress(ctx, ctx->buf);                      \
                    ctx->length += (sizeof(ctx->buf) << 3);       \
                    ctx->curlen = 0;                              \
                }                                                 \
            }                                                     \
        }                                                         \
    }

#undef __A_HASH_DONE
#define __A_HASH_DONE(hash, func, compress, storelen, storeout, append, above, zero) \
    unsigned char *func(hash *ctx, unsigned char *out)                               \
    {                                                                                \
        if (sizeof(ctx->buf) - 1 < ctx->curlen)                                      \
        {                                                                            \
            return 0;                                                                \
        }                                                                            \
        /* increase the length of the message */                                     \
        ctx->length += (sizeof(ctx->length) * ctx->curlen);                          \
        /* append the '1' bit */                                                     \
        ctx->buf[ctx->curlen++] = (append);                                          \
        /* if the length is currently above (above) bytes we append zeros   */       \
        /* then compress. Then we can fall back to padding zeros and length */       \
        /* encoding like normal.                                            */       \
        if ((above) < ctx->curlen)                                                   \
        {                                                                            \
            while (sizeof(ctx->buf) != ctx->curlen)                                  \
            {                                                                        \
                ctx->buf[ctx->curlen++] = 0;                                         \
            }                                                                        \
            compress(ctx, ctx->buf);                                                 \
            ctx->curlen = 0;                                                         \
        }                                                                            \
        /* pad up to (zero) bytes of zeroes */                                       \
        while (ctx->curlen < (zero))                                                 \
        {                                                                            \
            ctx->buf[ctx->curlen++] = 0;                                             \
        }                                                                            \
        /* store length */                                                           \
        storelen(ctx->length, ctx->buf + (zero));                                    \
        compress(ctx, ctx->buf);                                                     \
        /* copy output */                                                            \
        for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i) \
        {                                                                            \
            storeout(ctx->state[i], ctx->out + (sizeof(*ctx->state) * i));           \
        }                                                                            \
        if (out && out != ctx->out)                                                  \
        {                                                                            \
            memcpy(out, ctx->out, sizeof(ctx->state));                               \
        }                                                                            \
        return ctx->out;                                                             \
    }

/* Enddef to prevent recursive inclusion */
#endif /* __LIBA_H__ */

/* END OF FILE */
