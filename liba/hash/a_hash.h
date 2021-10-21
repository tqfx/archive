/*!
 @file           a_hash.h
 @brief          hash library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_H__
#define __A_HASH_H__

#include "liba.h"

#include <string.h> /* memset, memcpy */

#include "a_md2.h"
#include "a_md4.h"
#include "a_md5.h"
#include "a_rmd.h"
#include "a_sha1.h"
#include "a_sha2.h"
#include "a_sha3.h"
#include "a_tiger.h"
#include "a_whirl.h"
#include "a_blake2s.h"
#include "a_blake2b.h"

/*!
    shake128    0xA8    168
    sha3-224    0x90    144
*/
#define A_HASH_BUFSIZ 0xA8

enum
{
    A_HASH_SUCCESS = A_SUCCESS,
    A_HASH_WARNING = A_WARNING,
    A_HASH_FAILURE = A_FAILURE,
    A_HASH_INVALID = A_INVALID,
    A_HASH_OVERFLOW = A_OVERFLOW,
    A_HASH_NOTFOUND = A_NOTFOUND,
};

typedef union a_hash_stat_t
{
    int state;
#if defined(__A_HASH_MD2_H__)
    a_md2_t md2[1];
#endif /* __A_HASH_MD2_H__ */
#if defined(__A_HASH_MD4_H__)
    a_md4_t md4[1];
#endif /* __A_HASH_MD4_H__ */
#if defined(__A_HASH_MD5_H__)
    a_md5_t md5[1];
#endif /* __A_HASH_MD5_H__ */
#if defined(__A_HASH_RMD_H__)
    a_rmd128_t rmd128[1];
    a_rmd160_t rmd160[1];
    a_rmd256_t rmd256[1];
    a_rmd320_t rmd320[1];
#endif /* __A_HASH_RMD_H__ */
#if defined(__A_HASH_SHA1_H__)
    a_sha1_t sha1[1];
#endif /* __A_HASH_SHA1_H__ */
#if defined(__A_HASH_SHA2_H__)
    a_sha256_t sha256[1];
    a_sha512_t sha512[1];
#endif /* __A_HASH_SHA2_H__ */
#if defined(__A_HASH_SHA3_H__)
    a_sha3_t sha3[1];
#endif /* __A_HASH_SHA3_H__ */
#if defined(__A_HASH_TIGER_H__)
    a_tiger_t tiger[1];
#endif /* __A_HASH_TIGER_H__ */
#if defined(__A_HASH_BLAKE2S_H__)
    a_blake2s_t blake2s[1];
#endif /* __A_HASH_BLAKE2S_H__ */
#if defined(__A_HASH_BLAKE2B_H__)
    a_blake2b_t blake2b[1];
#endif /* __A_HASH_BLAKE2B_H__ */
#if defined(__A_HASH_WHIRL_H__)
    a_whirlpool_t whirlpool[1];
#endif /* __A_HASH_WHIRL_H__ */
} a_hash_stat_t;

typedef struct a_hash_t
{
    /*!< size of block */
    unsigned int bufsiz;
    /*!< size of digest */
    unsigned int outsiz;
    /*!
     @brief          Initialize function for hash.
     @param[in,out]  ctx: points to an instance of hash state.
    */
    void (*init)(a_hash_stat_t *ctx);
    /*!
     @brief          Process function for hash.
     @param[in,out]  ctx: points to an instance of hash state.
     @param[in]      p: points to data to hash.
     @param[in]      n: length of data to hash.
     @return         the execution state of the function.
      @retval        0 success
    */
    int (*process)(a_hash_stat_t *ctx, const void *p, size_t n);
    /*!
     @brief          Terminate function for hash.
     @param[in,out]  ctx: points to an instance of hash state.
     @param[in,out]  out: points to buffer that holds the digest.
     @return         p the digest internal buffer.
      @retval        p the digest internal buffer.
      @retval        0 generic invalid argument.
    */
    unsigned char *(*done)(a_hash_stat_t *ctx, void *out);
} a_hash_t;

__BEGIN_DECLS

#if defined(__A_HASH_MD2_H__)
extern const a_hash_t a_hash_md2;
#endif /* __A_HASH_MD2_H__ */
#if defined(__A_HASH_MD4_H__)
extern const a_hash_t a_hash_md4;
#endif /* __A_HASH_MD4_H__ */
#if defined(__A_HASH_MD5_H__)
extern const a_hash_t a_hash_md5;
#endif /* __A_HASH_MD5_H__ */
#if defined(__A_HASH_RMD_H__)
extern const a_hash_t a_hash_rmd128;
extern const a_hash_t a_hash_rmd160;
extern const a_hash_t a_hash_rmd256;
extern const a_hash_t a_hash_rmd320;
#endif /* __A_HASH_RMD_H__ */
#if defined(__A_HASH_SHA1_H__)
extern const a_hash_t a_hash_sha1;
#endif /* __A_HASH_SHA1_H__ */
#if defined(__A_HASH_SHA2_H__)
extern const a_hash_t a_hash_sha224;
extern const a_hash_t a_hash_sha256;
extern const a_hash_t a_hash_sha384;
extern const a_hash_t a_hash_sha512;
extern const a_hash_t a_hash_sha512_224;
extern const a_hash_t a_hash_sha512_256;
#endif /* __A_HASH_SHA2_H__ */
#if defined(__A_HASH_SHA3_H__)
extern const a_hash_t a_hash_sha3_224;
extern const a_hash_t a_hash_sha3_256;
extern const a_hash_t a_hash_sha3_384;
extern const a_hash_t a_hash_sha3_512;
extern const a_hash_t a_hash_shake128;
extern const a_hash_t a_hash_shake256;
extern const a_hash_t a_hash_keccak224;
extern const a_hash_t a_hash_keccak256;
extern const a_hash_t a_hash_keccak384;
extern const a_hash_t a_hash_keccak512;
#endif /* __A_HASH_SHA3_H__ */
#if defined(__A_HASH_TIGER_H__)
extern const a_hash_t a_hash_tiger;
#endif /* __A_HASH_TIGER_H__ */
#if defined(__A_HASH_BLAKE2S_H__)
extern const a_hash_t a_hash_blake2s_128;
extern const a_hash_t a_hash_blake2s_160;
extern const a_hash_t a_hash_blake2s_224;
extern const a_hash_t a_hash_blake2s_256;
#endif /* __A_HASH_BLAKE2S_H__ */
#if defined(__A_HASH_BLAKE2B_H__)
extern const a_hash_t a_hash_blake2b_160;
extern const a_hash_t a_hash_blake2b_256;
extern const a_hash_t a_hash_blake2b_384;
extern const a_hash_t a_hash_blake2b_512;
#endif /* __A_HASH_BLAKE2B_H__ */
#if defined(__A_HASH_WHIRL_H__)
extern const a_hash_t a_hash_whirlpool;
#endif /* __A_HASH_WHIRL_H__ */

__END_DECLS

#undef __A_HASH_PROCESS
#define __A_HASH_PROCESS(hash, func, compress)                    \
    int func(hash *ctx, const void *p, size_t n)                  \
    {                                                             \
        /* assert(ctx) */                                         \
        /* assert(!n || p) */                                     \
        if (sizeof(ctx->buf) < ctx->cursiz)                       \
        {                                                         \
            return A_HASH_INVALID;                                \
        }                                                         \
        if (ctx->length + (n << 3) < ctx->length)                 \
        {                                                         \
            return A_HASH_OVERFLOW;                               \
        }                                                         \
        const unsigned char *s = (const unsigned char *)p;        \
        while (n)                                                 \
        {                                                         \
            if ((0 == ctx->cursiz) && (sizeof(ctx->buf) - 1 < n)) \
            {                                                     \
                compress(ctx, s);                                 \
                ctx->length += sizeof(ctx->buf) << 3;             \
                s += sizeof(ctx->buf);                            \
                n -= sizeof(ctx->buf);                            \
            }                                                     \
            else                                                  \
            {                                                     \
                uint32_t m = sizeof(ctx->buf) - ctx->cursiz;      \
                m = m < n ? m : (uint32_t)n;                      \
                memcpy(ctx->buf + ctx->cursiz, s, m);             \
                ctx->cursiz += m;                                 \
                s += m;                                           \
                n -= m;                                           \
                if (sizeof(ctx->buf) == ctx->cursiz)              \
                {                                                 \
                    compress(ctx, ctx->buf);                      \
                    ctx->length += sizeof(ctx->buf) << 3;         \
                    ctx->cursiz = 0;                              \
                }                                                 \
            }                                                     \
        }                                                         \
        return A_HASH_SUCCESS;                                    \
    }

#undef __A_HASH_DONE
#define __A_HASH_DONE(hash, func, compress, storelen, storeout, append, above, zero) \
    unsigned char *func(hash *ctx, void *out)                                        \
    {                                                                                \
        /* assert(ctx) */                                                            \
        if (sizeof(ctx->buf) - 1 < ctx->cursiz)                                      \
        {                                                                            \
            return 0;                                                                \
        }                                                                            \
        /* increase the length of the message */                                     \
        ctx->length += sizeof(ctx->length) * ctx->cursiz;                            \
        /* append the '1' bit */                                                     \
        ctx->buf[ctx->cursiz++] = (append);                                          \
        /* if the length is currently above (above) bytes we append zeros   */       \
        /* then compress. Then we can fall back to padding zeros and length */       \
        /* encoding like normal.                                            */       \
        if ((above) < ctx->cursiz)                                                   \
        {                                                                            \
            while (sizeof(ctx->buf) != ctx->cursiz)                                  \
            {                                                                        \
                ctx->buf[ctx->cursiz++] = 0;                                         \
            }                                                                        \
            compress(ctx, ctx->buf);                                                 \
            ctx->cursiz = 0;                                                         \
        }                                                                            \
        /* pad up to (zero) bytes of zeroes */                                       \
        while (ctx->cursiz < (zero))                                                 \
        {                                                                            \
            ctx->buf[ctx->cursiz++] = 0;                                             \
        }                                                                            \
        /* store length */                                                           \
        storelen(ctx->length, ctx->buf + (zero));                                    \
        compress(ctx, ctx->buf);                                                     \
        /* copy output */                                                            \
        for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i) \
        {                                                                            \
            storeout(ctx->state[i], ctx->out + sizeof(*ctx->state) * i);             \
        }                                                                            \
        if (out && (out != ctx->out))                                                \
        {                                                                            \
            memcpy(out, ctx->out, sizeof(ctx->state));                               \
        }                                                                            \
        return ctx->out;                                                             \
    }

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_H__ */

/* END OF FILE */
