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

#include <stdlib.h> /* alloc */
#include <string.h> /* memset, memcpy */

typedef enum a_hash_state_t
{
    A_HASH_SUCCESS = 0,   /* hash function success */
    A_HASH_FAILURE = -1,  /* hash function failure */
    A_HASH_INVALID = -2,  /* generic invalid */
    A_HASH_OVERFLOW = -3, /* generic overflow */
} a_hash_state_t;

#define A_HASH32_BLOCKSIZE 0x40
#define A_HASH64_BLOCKSIZE 0x80

#undef __A_HASH_PROCESS
#define __A_HASH_PROCESS(hash, func, compress)                    \
    int func(hash *ctx, const void *p, size_t n)                  \
    {                                                             \
        if (sizeof(ctx->buf) < ctx->curlen)                       \
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
        return A_HASH_SUCCESS;                                    \
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
        ctx->length += sizeof(ctx->length) * ctx->curlen;                            \
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
            storeout(ctx->state[i], ctx->out + sizeof(*ctx->state) * i);             \
        }                                                                            \
        if (out && (out != ctx->out))                                                \
        {                                                                            \
            memcpy(out, ctx->out, sizeof(ctx->state));                               \
        }                                                                            \
        return ctx->out;                                                             \
    }

#define A_RIPEMD128_DIGESTSIZE (128 >> 3)
#define A_RIPEMD160_DIGESTSIZE (160 >> 3)
#define A_RIPEMD256_DIGESTSIZE (256 >> 3)
#define A_RIPEMD320_DIGESTSIZE (320 >> 3)

#undef __A_RMD_T
#define __A_RMD_T(bit)                         \
    typedef struct a_rmd##bit##_t              \
    {                                          \
        uint64_t length;                       \
        unsigned char buf[A_HASH32_BLOCKSIZE]; \
        unsigned char out[bit >> 3];           \
        uint32_t state[(bit >> 3) >> 2];       \
        uint32_t curlen;                       \
    } a_rmd##bit##_t
__A_RMD_T(128);
__A_RMD_T(160);
__A_RMD_T(256);
__A_RMD_T(320);
#undef __A_RMD_T

#define A_MD2_DIGESTSIZE 0x10

typedef struct a_md2_t
{
    unsigned char x[0x30];
    unsigned char buf[0x10];
    unsigned char chksum[0x10];
    uint32_t curlen;
} a_md2_t;

#define A_MD4_DIGESTSIZE 0x10

typedef struct a_md4_t
{
    uint64_t length;
    unsigned char buf[A_HASH32_BLOCKSIZE];
    unsigned char out[A_MD4_DIGESTSIZE];
    uint32_t state[A_MD4_DIGESTSIZE >> 2];
    uint32_t curlen;
} a_md4_t;

#define A_MD5_DIGESTSIZE 0x10

typedef struct a_md5_t
{
    uint64_t length;
    unsigned char buf[A_HASH32_BLOCKSIZE];
    unsigned char out[A_MD5_DIGESTSIZE];
    uint32_t state[A_MD5_DIGESTSIZE >> 2];
    uint32_t curlen;
} a_md5_t;

#define A_SHA1_DIGESTSIZE 20

typedef struct a_sha1_t
{
    uint64_t length;
    unsigned char buf[A_HASH32_BLOCKSIZE];
    unsigned char out[A_SHA1_DIGESTSIZE];
    uint32_t state[A_SHA1_DIGESTSIZE >> 2];
    uint32_t curlen;
} a_sha1_t;

#define A_SHA256_DIGESTSIZE (0x100 >> 3)

typedef struct a_sha256_t
{
    uint64_t length;
    unsigned char buf[A_HASH32_BLOCKSIZE];
    unsigned char out[A_SHA256_DIGESTSIZE];
    uint32_t state[A_SHA256_DIGESTSIZE >> 2];
    uint32_t curlen;
} a_sha256_t;

#define A_SHA224_DIGESTSIZE (0xE0 >> 3)

#ifndef a_sha224_t
#define a_sha224_t a_sha256_t
#endif /* a_sha224_t */

#define A_SHA512_DIGESTSIZE (0x200 >> 3)

typedef struct a_sha512_t
{
    uint64_t length;
    unsigned char buf[A_HASH64_BLOCKSIZE];
    unsigned char out[A_SHA512_DIGESTSIZE];
    uint64_t state[A_SHA512_DIGESTSIZE >> 3];
    uint32_t curlen;
} a_sha512_t;

#define A_SHA384_DIGESTSIZE     (0x180 >> 3)
#define A_SHA512_224_DIGESTSIZE (0x0E0 >> 3)
#define A_SHA512_256_DIGESTSIZE (0x100 >> 3)

#ifndef a_sha384_t
#define a_sha384_t a_sha512_t
#endif /* a_sha384_t */
#ifndef a_sha512_224_t
#define a_sha512_224_t a_sha512_t
#endif /* a_sha512_224_t */
#ifndef a_sha512_256_t
#define a_sha512_256_t a_sha512_t
#endif /* a_sha512_256_t */

#define A_SHA3_224_DIGESTSIZE (0x0E0 >> 3)
#define A_SHA3_256_DIGESTSIZE (0x100 >> 3)
#define A_SHA3_384_DIGESTSIZE (0x180 >> 3)
#define A_SHA3_512_DIGESTSIZE (0x200 >> 3)

typedef struct a_sha3_t
{
    uint64_t s[25];
    uint64_t saved;                /* the portion of the input message that we didn't consume yet */
    unsigned char sb[25 << 3];     /* used for storing `uint64_t s[25]` as little-endian bytes */
    unsigned short byte_index;     /* 0..7--the next byte after the set one (starts from 0; 0--none are buffered) */
    unsigned short word_index;     /* 0..24--the next word to integrate input (starts from 0) */
    unsigned short capacity_words; /* the double length of the hash output in words (e.g. 16 for Keccak 512) */
    unsigned short xof_flag;
} a_sha3_t;

#define A_KECCAK_224_DIGESTSIZE (0x0E0 >> 3)
#define A_KECCAK_256_DIGESTSIZE (0x100 >> 3)
#define A_KECCAK_384_DIGESTSIZE (0x180 >> 3)
#define A_KECCAK_512_DIGESTSIZE (0x200 >> 3)

#ifndef a_keccak_t
#define a_keccak_t a_sha3_t
#endif /* a_keccak_t */
#ifndef a_sha3_shake_t
#define a_sha3_shake_t a_sha3_t
#endif /* a_sha3_shake_t */

#define A_TIGER_DIGESTSIZE 24

typedef struct a_tiger_t
{
    uint64_t length;
    unsigned char buf[A_HASH32_BLOCKSIZE];
    unsigned char out[A_TIGER_DIGESTSIZE];
    uint64_t state[A_TIGER_DIGESTSIZE >> 3];
    uint32_t curlen;
} a_tiger_t;

#define A_WHIRLPOOL_DIGESTSIZE 0x40

typedef struct a_whirlpool_t
{
    uint64_t length;
    unsigned char buf[A_HASH32_BLOCKSIZE];
    unsigned char out[A_WHIRLPOOL_DIGESTSIZE];
    uint64_t state[A_WHIRLPOOL_DIGESTSIZE >> 3];
    uint32_t curlen;
} a_whirlpool_t;

#define A_BLAKE2S_DIGESTSIZE     0x20
#define A_BLAKE2S_128_DIGESTSIZE (128 >> 3)
#define A_BLAKE2S_160_DIGESTSIZE (160 >> 3)
#define A_BLAKE2S_224_DIGESTSIZE (224 >> 3)
#define A_BLAKE2S_256_DIGESTSIZE (256 >> 3)

typedef struct a_blake2s_t
{
    uint32_t t[2];
    uint32_t f[2];
    uint32_t curlen;
    uint32_t outlen;
    uint32_t state[A_BLAKE2S_DIGESTSIZE >> 2];
    unsigned char out[A_BLAKE2S_DIGESTSIZE];
    unsigned char buf[A_HASH32_BLOCKSIZE];
    unsigned char lastnode;
} a_blake2s_t;

#define A_BLAKE2B_DIGESTSIZE     0x40
#define A_BLAKE2B_160_DIGESTSIZE (160 >> 3)
#define A_BLAKE2B_256_DIGESTSIZE (256 >> 3)
#define A_BLAKE2B_384_DIGESTSIZE (384 >> 3)
#define A_BLAKE2B_512_DIGESTSIZE (512 >> 3)

typedef struct a_blake2b_t
{
    uint64_t t[2];
    uint64_t f[2];
    uint32_t curlen;
    uint32_t outlen;
    uint64_t state[A_BLAKE2B_DIGESTSIZE >> 3];
    unsigned char out[A_BLAKE2B_DIGESTSIZE];
    unsigned char buf[A_HASH64_BLOCKSIZE];
    unsigned char lastnode;
} a_blake2b_t;

__BEGIN_DECLS

/* function for MD2 */
extern void a_md2_init(a_md2_t *ctx);
extern int a_md2_process(a_md2_t *ctx, const void *p, size_t n);
extern unsigned char *a_md2_done(a_md2_t *ctx, unsigned char *out);

/* function for MD4 */
extern void a_md4_init(a_md4_t *ctx);
extern int a_md4_process(a_md4_t *ctx, const void *p, size_t n);
extern unsigned char *a_md4_done(a_md4_t *ctx, unsigned char *out);

/* function for MD5 */
extern void a_md5_init(a_md5_t *ctx);
extern int a_md5_process(a_md5_t *ctx, const void *p, size_t n);
extern unsigned char *a_md5_done(a_md5_t *ctx, unsigned char *out);

/* function for RIPEMD */
extern void a_rmd128_init(a_rmd128_t *ctx);
extern void a_rmd160_init(a_rmd160_t *ctx);
extern void a_rmd256_init(a_rmd256_t *ctx);
extern void a_rmd320_init(a_rmd320_t *ctx);
extern int a_rmd128_process(a_rmd128_t *ctx, const void *p, size_t n);
extern int a_rmd160_process(a_rmd160_t *ctx, const void *p, size_t n);
extern int a_rmd256_process(a_rmd256_t *ctx, const void *p, size_t n);
extern int a_rmd320_process(a_rmd320_t *ctx, const void *p, size_t n);
extern unsigned char *a_rmd128_done(a_rmd128_t *ctx, unsigned char *out);
extern unsigned char *a_rmd160_done(a_rmd160_t *ctx, unsigned char *out);
extern unsigned char *a_rmd256_done(a_rmd256_t *ctx, unsigned char *out);
extern unsigned char *a_rmd320_done(a_rmd320_t *ctx, unsigned char *out);

/* function for SHA1 */
extern void a_sha1_init(a_sha1_t *ctx);
extern int a_sha1_process(a_sha1_t *ctx, const void *p, size_t n);
extern unsigned char *a_sha1_done(a_sha1_t *ctx, unsigned char *out);

/* function for SHA256 */
extern void a_sha256_init(a_sha256_t *ctx);
extern int a_sha256_process(a_sha256_t *ctx, const void *p, size_t n);
extern unsigned char *a_sha256_done(a_sha256_t *ctx, unsigned char *out);

/* function for SHA224 */
extern void a_sha224_init(a_sha256_t *ctx);
#ifndef a_sha224_process
#define a_sha224_process(ctx, p, n) a_sha256_process(ctx, p, n)
#endif /* a_sha224_process */
extern unsigned char *a_sha224_done(a_sha256_t *ctx, unsigned char *out);

/* function for SHA512 */
extern void a_sha512_init(a_sha512_t *ctx);
extern int a_sha512_process(a_sha512_t *ctx, const void *p, size_t n);
extern unsigned char *a_sha512_done(a_sha512_t *ctx, unsigned char *out);

/* function for SHA384 */
extern void a_sha384_init(a_sha512_t *ctx);
#ifndef a_sha384_process
#define a_sha384_process(ctx, p, n) a_sha512_process(ctx, p, n)
#endif /* a_sha384_process */
extern unsigned char *a_sha384_done(a_sha512_t *ctx, unsigned char *out);

/* function for SHA512/224 */
extern void a_sha512_224_init(a_sha512_t *ctx);
#ifndef a_sha512_224_process
#define a_sha512_224_process(ctx, p, n) a_sha512_process(ctx, p, n)
#endif /* a_sha512_224_process */
extern unsigned char *a_sha512_224_done(a_sha512_t *ctx, unsigned char *out);

/* function for SHA512/256 */
extern void a_sha512_256_init(a_sha512_t *ctx);
#ifndef a_sha512_256_process
#define a_sha512_256_process(ctx, p, n) a_sha512_process(ctx, p, n)
#endif /* a_sha512_256_process */
extern unsigned char *a_sha512_256_done(a_sha512_t *ctx, unsigned char *out);

/* function for SHA3 */
extern void a_sha3_224_init(a_sha3_t *ctx);
extern void a_sha3_256_init(a_sha3_t *ctx);
extern void a_sha3_384_init(a_sha3_t *ctx);
extern void a_sha3_512_init(a_sha3_t *ctx);
extern int a_sha3_process(a_sha3_t *ctx, const void *p, size_t n);
extern unsigned char *a_sha3_done(a_sha3_t *ctx, unsigned char *out);

/* function for SHA3/SHAKE */
extern int a_sha3_shake_init(a_sha3_t *ctx, unsigned int num);
#ifndef a_sha3_shake_process
#define a_sha3_shake_process(ctx, p, n) a_sha3_process(ctx, p, n)
#endif /* a_sha3_shake_process */
extern void a_sha3_shake_done(a_sha3_t *ctx, unsigned char *out, unsigned int len);

/* function for KECCAK */
#ifndef a_keccak_224_init
#define a_keccak_224_init(ctx) a_sha3_224_init(ctx)
#endif /* a_keccak_224_init */
#ifndef a_keccak_256_init
#define a_keccak_256_init(ctx) a_sha3_256_init(ctx)
#endif /* a_keccak_256_init */
#ifndef a_keccak_384_init
#define a_keccak_384_init(ctx) a_sha3_384_init(ctx)
#endif /* a_keccak_384_init */
#ifndef a_keccak_512_init
#define a_keccak_512_init(ctx) a_sha3_512_init(ctx)
#endif /* a_keccak_512_init */
#ifndef a_keccak_process
#define a_keccak_process(ctx, p, n) a_sha3_process(ctx, p, n)
#endif /* a_keccak_process */
extern unsigned char *a_keccak_done(a_sha3_t *ctx, unsigned char *out);

/* function for TIGER */
extern void a_tiger_init(a_tiger_t *ctx);
extern int a_tiger_process(a_tiger_t *ctx, const void *p, size_t n);
extern unsigned char *a_tiger_done(a_tiger_t *ctx, unsigned char *out);

/* function for WHIRLPOOL */
extern void a_whirlpool_init(a_whirlpool_t *ctx);
extern int a_whirlpool_process(a_whirlpool_t *ctx, const void *p, size_t n);
extern unsigned char *a_whirlpool_done(a_whirlpool_t *ctx, unsigned char *out);

/* function for BLAKE2S */
extern void a_blake2s_128_init(a_blake2s_t *ctx);
extern void a_blake2s_160_init(a_blake2s_t *ctx);
extern void a_blake2s_224_init(a_blake2s_t *ctx);
extern void a_blake2s_256_init(a_blake2s_t *ctx);
extern int a_blake2s_init(a_blake2s_t *ctx, size_t len, const void *p, size_t n);
extern int a_blake2s_process(a_blake2s_t *ctx, const void *p, size_t n);
extern unsigned char *a_blake2s_done(a_blake2s_t *ctx, unsigned char *out);

/* function for BLAKE2B */
extern void a_blake2b_160_init(a_blake2b_t *ctx);
extern void a_blake2b_256_init(a_blake2b_t *ctx);
extern void a_blake2b_384_init(a_blake2b_t *ctx);
extern void a_blake2b_512_init(a_blake2b_t *ctx);
extern int a_blake2b_init(a_blake2b_t *ctx, size_t len, const void *p, size_t n);
extern int a_blake2b_process(a_blake2b_t *ctx, const void *p, size_t n);
extern unsigned char *a_blake2b_done(a_blake2b_t *ctx, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_H__ */

/* END OF FILE */
