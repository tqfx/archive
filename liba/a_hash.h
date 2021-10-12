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

#define A_RIPEMD_BUFSIZ    0x40
#define A_RIPEMD128_OUTSIZ (128 >> 3)
#define A_RIPEMD160_OUTSIZ (160 >> 3)
#define A_RIPEMD256_OUTSIZ (256 >> 3)
#define A_RIPEMD320_OUTSIZ (320 >> 3)

#undef __A_RMD_T
#define __A_RMD_T(bit)                      \
    typedef struct a_rmd##bit##_t           \
    {                                       \
        uint64_t length;                    \
        unsigned char buf[A_RIPEMD_BUFSIZ]; \
        unsigned char out[bit >> 3];        \
        uint32_t state[(bit >> 3) >> 2];    \
        uint32_t cursiz;                    \
    } a_rmd##bit##_t
__A_RMD_T(128);
__A_RMD_T(160);
__A_RMD_T(256);
__A_RMD_T(320);
#undef __A_RMD_T

#define A_MD2_BUFSIZ 0x10
#define A_MD2_OUTSIZ 0x10

typedef struct a_md2_t
{
    unsigned char x[0x30];
    unsigned char buf[A_MD2_BUFSIZ];
    unsigned char chksum[A_MD2_BUFSIZ];
    uint32_t cursiz;
} a_md2_t;

#define A_MD4_BUFSIZ 0x40
#define A_MD4_OUTSIZ 0x10

typedef struct a_md4_t
{
    uint64_t length;
    unsigned char buf[A_MD4_BUFSIZ];
    unsigned char out[A_MD4_OUTSIZ];
    uint32_t state[A_MD4_OUTSIZ >> 2];
    uint32_t cursiz;
} a_md4_t;

#define A_MD5_BUFSIZ 0x40
#define A_MD5_OUTSIZ 0x10

typedef struct a_md5_t
{
    uint64_t length;
    unsigned char buf[A_MD5_BUFSIZ];
    unsigned char out[A_MD5_OUTSIZ];
    uint32_t state[A_MD5_OUTSIZ >> 2];
    uint32_t cursiz;
} a_md5_t;

#define A_SHA1_BUFSIZ 0x40
#define A_SHA1_OUTSIZ 20

typedef struct a_sha1_t
{
    uint64_t length;
    unsigned char buf[A_SHA1_BUFSIZ];
    unsigned char out[A_SHA1_OUTSIZ];
    uint32_t state[A_SHA1_OUTSIZ >> 2];
    uint32_t cursiz;
} a_sha1_t;

#define A_TIGER_BUFSIZ 0x40
#define A_TIGER_OUTSIZ 24

typedef struct a_tiger_t
{
    uint64_t length;
    unsigned char buf[A_TIGER_BUFSIZ];
    unsigned char out[A_TIGER_OUTSIZ];
    uint64_t state[A_TIGER_OUTSIZ >> 3];
    uint32_t cursiz;
} a_tiger_t;

#define A_SHA256_BUFSIZ 0x40
#define A_SHA256_OUTSIZ (256 >> 3)

typedef struct a_sha256_t
{
    uint64_t length;
    unsigned char buf[A_SHA256_BUFSIZ];
    unsigned char out[A_SHA256_OUTSIZ];
    uint32_t state[A_SHA256_OUTSIZ >> 2];
    uint32_t cursiz;
} a_sha256_t;

#define A_SHA224_OUTSIZ (224 >> 3)

#ifndef a_sha224_t
#define a_sha224_t a_sha256_t
#endif /* a_sha224_t */

#define A_SHA512_BUFSIZ 0x80
#define A_SHA512_OUTSIZ (512 >> 3)

typedef struct a_sha512_t
{
    uint64_t length;
    unsigned char buf[A_SHA512_BUFSIZ];
    unsigned char out[A_SHA512_OUTSIZ];
    uint64_t state[A_SHA512_OUTSIZ >> 3];
    uint32_t cursiz;
} a_sha512_t;

#define A_SHA384_OUTSIZ     (384 >> 3)
#define A_SHA512_224_OUTSIZ (224 >> 3)
#define A_SHA512_256_OUTSIZ (256 >> 3)

#ifndef a_sha384_t
#define a_sha384_t a_sha512_t
#endif /* a_sha384_t */
#ifndef a_sha512_224_t
#define a_sha512_224_t a_sha512_t
#endif /* a_sha512_224_t */
#ifndef a_sha512_256_t
#define a_sha512_256_t a_sha512_t
#endif /* a_sha512_256_t */

#define A_SHA3_224_BUFSIZ (200 - (224 >> 2))
#define A_SHA3_256_BUFSIZ (200 - (256 >> 2))
#define A_SHA3_384_BUFSIZ (200 - (384 >> 2))
#define A_SHA3_512_BUFSIZ (200 - (512 >> 2))
#define A_SHA3_224_OUTSIZ (224 >> 3)
#define A_SHA3_256_OUTSIZ (256 >> 3)
#define A_SHA3_384_OUTSIZ (384 >> 3)
#define A_SHA3_512_OUTSIZ (512 >> 3)

typedef struct a_sha3_t
{
    uint64_t s[25];
    uint64_t saved;                /* the portion of the input message that we didn't consume yet */
    unsigned char out[200];        /* used for storing `uint64_t s[25]` as little-endian bytes */
    unsigned short byte_index;     /* 0..7--the next byte after the set one (starts from 0; 0--none are buffered) */
    unsigned short word_index;     /* 0..24--the next word to integrate input (starts from 0) */
    unsigned short capacity_words; /* the double length of the hash output in words (e.g. 16 for Keccak 512) */
    unsigned short xof_flag;
} a_sha3_t;

#define A_KECCAK224_BUFSIZ (200 - (224 >> 2))
#define A_KECCAK256_BUFSIZ (200 - (256 >> 2))
#define A_KECCAK384_BUFSIZ (200 - (384 >> 2))
#define A_KECCAK512_BUFSIZ (200 - (512 >> 2))
#define A_KECCAK224_OUTSIZ (224 >> 3)
#define A_KECCAK256_OUTSIZ (256 >> 3)
#define A_KECCAK384_OUTSIZ (384 >> 3)
#define A_KECCAK512_OUTSIZ (512 >> 3)

#ifndef a_keccak_t
#define a_keccak_t a_sha3_t
#endif /* a_keccak_t */

#define A_SHAKE128_BUFSIZ (200 - (128 >> 2))
#define A_SHAKE256_BUFSIZ (200 - (256 >> 2))
#define A_SHAKE128_OUTSIZ (128 >> 3)
#define A_SHAKE256_OUTSIZ (256 >> 3)

#ifndef a_sha3_shake_t
#define a_sha3_shake_t a_sha3_t
#endif /* a_sha3_shake_t */

#define A_BLAKE2S_BUFSIZ     0x40
#define A_BLAKE2S_OUTSIZ     0x20
#define A_BLAKE2S_128_OUTSIZ (128 >> 3)
#define A_BLAKE2S_160_OUTSIZ (160 >> 3)
#define A_BLAKE2S_224_OUTSIZ (224 >> 3)
#define A_BLAKE2S_256_OUTSIZ (256 >> 3)

typedef struct a_blake2s_t
{
    uint32_t t[2];
    uint32_t f[2];
    uint32_t cursiz;
    uint32_t outsiz;
    uint32_t state[A_BLAKE2S_OUTSIZ >> 2];
    unsigned char out[A_BLAKE2S_OUTSIZ];
    unsigned char buf[A_BLAKE2S_BUFSIZ];
    unsigned char lastnode;
} a_blake2s_t;

#define A_BLAKE2B_BUFSIZ     0x80
#define A_BLAKE2B_OUTSIZ     0x40
#define A_BLAKE2B_160_OUTSIZ (160 >> 3)
#define A_BLAKE2B_256_OUTSIZ (256 >> 3)
#define A_BLAKE2B_384_OUTSIZ (384 >> 3)
#define A_BLAKE2B_512_OUTSIZ (512 >> 3)

typedef struct a_blake2b_t
{
    uint64_t t[2];
    uint64_t f[2];
    uint32_t cursiz;
    uint32_t outsiz;
    uint64_t state[A_BLAKE2B_OUTSIZ >> 3];
    unsigned char out[A_BLAKE2B_OUTSIZ];
    unsigned char buf[A_BLAKE2B_BUFSIZ];
    unsigned char lastnode;
} a_blake2b_t;

#define A_WHIRLPOOL_BUFSIZ 0x40
#define A_WHIRLPOOL_OUTSIZ 0x40

typedef struct a_whirlpool_t
{
    uint64_t length;
    unsigned char buf[A_WHIRLPOOL_BUFSIZ];
    unsigned char out[A_WHIRLPOOL_OUTSIZ];
    uint64_t state[A_WHIRLPOOL_OUTSIZ >> 3];
    uint32_t cursiz;
} a_whirlpool_t;

__BEGIN_DECLS

extern void a_md2_init(a_md2_t *ctx);
extern int a_md2_process(a_md2_t *ctx, const void *p, size_t n);
extern unsigned char *a_md2_done(a_md2_t *ctx, void *out);

extern void a_md4_init(a_md4_t *ctx);
extern int a_md4_process(a_md4_t *ctx, const void *p, size_t n);
extern unsigned char *a_md4_done(a_md4_t *ctx, void *out);

extern void a_md5_init(a_md5_t *ctx);
extern int a_md5_process(a_md5_t *ctx, const void *p, size_t n);
extern unsigned char *a_md5_done(a_md5_t *ctx, void *out);

extern void a_sha1_init(a_sha1_t *ctx);
extern int a_sha1_process(a_sha1_t *ctx, const void *p, size_t n);
extern unsigned char *a_sha1_done(a_sha1_t *ctx, void *out);

extern void a_tiger_init(a_tiger_t *ctx);
extern int a_tiger_process(a_tiger_t *ctx, const void *p, size_t n);
extern unsigned char *a_tiger_done(a_tiger_t *ctx, void *out);

extern void a_rmd128_init(a_rmd128_t *ctx);
extern int a_rmd128_process(a_rmd128_t *ctx, const void *p, size_t n);
extern unsigned char *a_rmd128_done(a_rmd128_t *ctx, void *out);

extern void a_rmd160_init(a_rmd160_t *ctx);
extern int a_rmd160_process(a_rmd160_t *ctx, const void *p, size_t n);
extern unsigned char *a_rmd160_done(a_rmd160_t *ctx, void *out);

extern void a_rmd256_init(a_rmd256_t *ctx);
extern int a_rmd256_process(a_rmd256_t *ctx, const void *p, size_t n);
extern unsigned char *a_rmd256_done(a_rmd256_t *ctx, void *out);

extern void a_rmd320_init(a_rmd320_t *ctx);
extern int a_rmd320_process(a_rmd320_t *ctx, const void *p, size_t n);
extern unsigned char *a_rmd320_done(a_rmd320_t *ctx, void *out);

extern void a_sha256_init(a_sha256_t *ctx);
extern int a_sha256_process(a_sha256_t *ctx, const void *p, size_t n);
extern unsigned char *a_sha256_done(a_sha256_t *ctx, void *out);

extern void a_sha224_init(a_sha256_t *ctx);
#ifndef a_sha224_process
#define a_sha224_process(ctx, p, n) a_sha256_process(ctx, p, n)
#endif /* a_sha224_process */
extern unsigned char *a_sha224_done(a_sha256_t *ctx, void *out);

extern void a_sha512_init(a_sha512_t *ctx);
extern int a_sha512_process(a_sha512_t *ctx, const void *p, size_t n);
extern unsigned char *a_sha512_done(a_sha512_t *ctx, void *out);

extern void a_sha384_init(a_sha512_t *ctx);
#ifndef a_sha384_process
#define a_sha384_process(ctx, p, n) a_sha512_process(ctx, p, n)
#endif /* a_sha384_process */
extern unsigned char *a_sha384_done(a_sha512_t *ctx, void *out);

extern void a_sha512_224_init(a_sha512_t *ctx);
#ifndef a_sha512_224_process
#define a_sha512_224_process(ctx, p, n) a_sha512_process(ctx, p, n)
#endif /* a_sha512_224_process */
extern unsigned char *a_sha512_224_done(a_sha512_t *ctx, void *out);

extern void a_sha512_256_init(a_sha512_t *ctx);
#ifndef a_sha512_256_process
#define a_sha512_256_process(ctx, p, n) a_sha512_process(ctx, p, n)
#endif /* a_sha512_256_process */
extern unsigned char *a_sha512_256_done(a_sha512_t *ctx, void *out);

extern void a_sha3_224_init(a_sha3_t *ctx);
extern void a_sha3_256_init(a_sha3_t *ctx);
extern void a_sha3_384_init(a_sha3_t *ctx);
extern void a_sha3_512_init(a_sha3_t *ctx);
extern int a_sha3_process(a_sha3_t *ctx, const void *p, size_t n);
extern unsigned char *a_sha3_done(a_sha3_t *ctx, void *out);

extern void a_shake128_init(a_sha3_t *ctx);
extern void a_shake256_init(a_sha3_t *ctx);
#ifndef a_sha3shake_process
#define a_sha3shake_process(ctx, p, n) a_sha3_process(ctx, p, n)
#endif /* a_sha3shake_process */
extern unsigned char *a_shake128_done(a_sha3_t *ctx, void *out);
extern unsigned char *a_shake256_done(a_sha3_t *ctx, void *out);
extern int a_sha3shake_init(a_sha3_t *ctx, unsigned int num);
extern void a_sha3shake_done(a_sha3_t *ctx, unsigned char *out, unsigned int siz);

#ifndef a_keccak224_init
#define a_keccak224_init(ctx) a_sha3_224_init(ctx)
#endif /* a_keccak224_init */
#ifndef a_keccak256_init
#define a_keccak256_init(ctx) a_sha3_256_init(ctx)
#endif /* a_keccak256_init */
#ifndef a_keccak384_init
#define a_keccak384_init(ctx) a_sha3_384_init(ctx)
#endif /* a_keccak384_init */
#ifndef a_keccak512_init
#define a_keccak512_init(ctx) a_sha3_512_init(ctx)
#endif /* a_keccak512_init */
#ifndef a_keccak_process
#define a_keccak_process(ctx, p, n) a_sha3_process(ctx, p, n)
#endif /* a_keccak_process */
extern unsigned char *a_keccak_done(a_sha3_t *ctx, void *out);

extern void a_blake2s_128_init(a_blake2s_t *ctx);
extern void a_blake2s_160_init(a_blake2s_t *ctx);
extern void a_blake2s_224_init(a_blake2s_t *ctx);
extern void a_blake2s_256_init(a_blake2s_t *ctx);
extern int a_blake2s_process(a_blake2s_t *ctx, const void *p, size_t n);
extern unsigned char *a_blake2s_done(a_blake2s_t *ctx, void *out);
extern int a_blake2s_init(a_blake2s_t *ctx, size_t siz, const void *p, size_t n);

extern void a_blake2b_160_init(a_blake2b_t *ctx);
extern void a_blake2b_256_init(a_blake2b_t *ctx);
extern void a_blake2b_384_init(a_blake2b_t *ctx);
extern void a_blake2b_512_init(a_blake2b_t *ctx);
extern int a_blake2b_process(a_blake2b_t *ctx, const void *p, size_t n);
extern unsigned char *a_blake2b_done(a_blake2b_t *ctx, void *out);
extern int a_blake2b_init(a_blake2b_t *ctx, size_t siz, const void *p, size_t n);

extern void a_whirlpool_init(a_whirlpool_t *ctx);
extern int a_whirlpool_process(a_whirlpool_t *ctx, const void *p, size_t n);
extern unsigned char *a_whirlpool_done(a_whirlpool_t *ctx, void *out);

__END_DECLS

/*!
    shake128    0xA8    168
    sha3-224    0x90    144
*/
#define A_HASH_BUFSIZ 0xA8

enum
{
    A_HASH_SUCCESS = 0,
    A_HASH_FAILURE = -1,
    A_HASH_INVALID = -2,
    A_HASH_OVERFLOW = -3,
};

typedef union a_hash_stat_t
{
    int state;
    a_md2_t md2[1];
    a_md4_t md4[1];
    a_md5_t md5[1];
    a_sha1_t sha1[1];
    a_sha3_t sha3[1];
    a_tiger_t tiger[1];
    a_sha256_t sha256[1];
    a_sha512_t sha512[1];
    a_rmd128_t rmd128[1];
    a_rmd160_t rmd160[1];
    a_rmd256_t rmd256[1];
    a_rmd320_t rmd320[1];
    a_blake2s_t blake2s[1];
    a_blake2b_t blake2b[1];
    a_whirlpool_t whirlpool[1];
} a_hash_stat_t;

typedef struct a_hash_t
{
    /*!< size of block */
    unsigned int bufsiz;
    /*!< size of digest */
    unsigned int outsiz;
    /*!
     @brief          Initialize function for hash.
     @param[in,out]  ctx: points to an instance of hash.
    */
    void (*init)(a_hash_stat_t *ctx);
    /*!
     @brief          Process function for hash.
     @param[in,out]  ctx: points to an instance of hash.
     @param[in]      p: points to data.
     @param[in]      n: length of data.
     @return         the execution state of the function
      @retval        0 success
    */
    int (*process)(a_hash_stat_t *ctx, const void *p, size_t n);
    /*!
     @brief          Terminate function for hash.
     @param[in,out]  ctx: points to an instance of hash.
     @param[in,out]  out: points to buffer that holds the digest.
     @return         p the digest internal buffer.
      @retval        p the digest internal buffer.
      @retval        0 generic invalid argument.
    */
    unsigned char *(*done)(a_hash_stat_t *ctx, void *out);
} a_hash_t;

__BEGIN_DECLS

extern const a_hash_t a_hash_md2;
extern const a_hash_t a_hash_md4;
extern const a_hash_t a_hash_md5;
extern const a_hash_t a_hash_sha1;
extern const a_hash_t a_hash_tiger;
extern const a_hash_t a_hash_rmd128;
extern const a_hash_t a_hash_rmd160;
extern const a_hash_t a_hash_rmd256;
extern const a_hash_t a_hash_rmd320;
extern const a_hash_t a_hash_sha224;
extern const a_hash_t a_hash_sha256;
extern const a_hash_t a_hash_sha384;
extern const a_hash_t a_hash_sha512;
extern const a_hash_t a_hash_sha512_224;
extern const a_hash_t a_hash_sha512_256;
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
extern const a_hash_t a_hash_whirlpool;
extern const a_hash_t a_hash_blake2s_128;
extern const a_hash_t a_hash_blake2s_160;
extern const a_hash_t a_hash_blake2s_224;
extern const a_hash_t a_hash_blake2s_256;
extern const a_hash_t a_hash_blake2b_160;
extern const a_hash_t a_hash_blake2b_256;
extern const a_hash_t a_hash_blake2b_384;
extern const a_hash_t a_hash_blake2b_512;

__END_DECLS

#undef __A_HASH_INIT
#define __A_HASH_INIT(stat, init, func) \
    __STATIC_INLINE                     \
    void func(a_hash_stat_t *ctx)       \
    {                                   \
        /* assert(ctx) */               \
        init(ctx->stat);                \
    }
__A_HASH_INIT(md2, a_md2_init, a_hash_init_md2)
__A_HASH_INIT(md4, a_md4_init, a_hash_init_md4)
__A_HASH_INIT(md5, a_md5_init, a_hash_init_md5)
__A_HASH_INIT(sha1, a_sha1_init, a_hash_init_sha1)
__A_HASH_INIT(tiger, a_tiger_init, a_hash_init_tiger)
__A_HASH_INIT(rmd128, a_rmd128_init, a_hash_init_rmd128)
__A_HASH_INIT(rmd160, a_rmd160_init, a_hash_init_rmd160)
__A_HASH_INIT(rmd256, a_rmd256_init, a_hash_init_rmd256)
__A_HASH_INIT(rmd320, a_rmd320_init, a_hash_init_rmd320)
__A_HASH_INIT(sha256, a_sha256_init, a_hash_init_sha256)
__A_HASH_INIT(sha256, a_sha224_init, a_hash_init_sha224)
__A_HASH_INIT(sha512, a_sha512_init, a_hash_init_sha512)
__A_HASH_INIT(sha512, a_sha384_init, a_hash_init_sha384)
__A_HASH_INIT(sha512, a_sha512_224_init, a_hash_init_sha512_224)
__A_HASH_INIT(sha512, a_sha512_256_init, a_hash_init_sha512_256)
__A_HASH_INIT(sha3, a_sha3_224_init, a_hash_init_sha3_224)
__A_HASH_INIT(sha3, a_sha3_256_init, a_hash_init_sha3_256)
__A_HASH_INIT(sha3, a_sha3_384_init, a_hash_init_sha3_384)
__A_HASH_INIT(sha3, a_sha3_512_init, a_hash_init_sha3_512)
__A_HASH_INIT(sha3, a_shake128_init, a_hash_init_shake128)
__A_HASH_INIT(sha3, a_shake256_init, a_hash_init_shake256)
__A_HASH_INIT(sha3, a_sha3_224_init, a_hash_init_keccak224)
__A_HASH_INIT(sha3, a_sha3_256_init, a_hash_init_keccak256)
__A_HASH_INIT(sha3, a_sha3_384_init, a_hash_init_keccak384)
__A_HASH_INIT(sha3, a_sha3_512_init, a_hash_init_keccak512)
__A_HASH_INIT(whirlpool, a_whirlpool_init, a_hash_init_whirlpool)
__A_HASH_INIT(blake2s, a_blake2s_128_init, a_hash_init_blake2s_128)
__A_HASH_INIT(blake2s, a_blake2s_160_init, a_hash_init_blake2s_160)
__A_HASH_INIT(blake2s, a_blake2s_224_init, a_hash_init_blake2s_224)
__A_HASH_INIT(blake2s, a_blake2s_256_init, a_hash_init_blake2s_256)
__A_HASH_INIT(blake2b, a_blake2b_160_init, a_hash_init_blake2b_160)
__A_HASH_INIT(blake2b, a_blake2b_256_init, a_hash_init_blake2b_256)
__A_HASH_INIT(blake2b, a_blake2b_384_init, a_hash_init_blake2b_384)
__A_HASH_INIT(blake2b, a_blake2b_512_init, a_hash_init_blake2b_512)
#undef __A_HASH_INIT

#undef __A_HASH_PROCESS
#define __A_HASH_PROCESS(stat, process, func)             \
    __STATIC_INLINE                                       \
    int func(a_hash_stat_t *ctx, const void *p, size_t n) \
    {                                                     \
        /* assert(ctx) */                                 \
        /* assert(!n || p) */                             \
        return process(ctx->stat, p, n);                  \
    }
__A_HASH_PROCESS(md2, a_md2_process, a_hash_process_md2)
__A_HASH_PROCESS(md4, a_md4_process, a_hash_process_md4)
__A_HASH_PROCESS(md5, a_md5_process, a_hash_process_md5)
__A_HASH_PROCESS(sha1, a_sha1_process, a_hash_process_sha1)
__A_HASH_PROCESS(tiger, a_tiger_process, a_hash_process_tiger)
__A_HASH_PROCESS(rmd128, a_rmd128_process, a_hash_process_rmd128)
__A_HASH_PROCESS(rmd160, a_rmd160_process, a_hash_process_rmd160)
__A_HASH_PROCESS(rmd256, a_rmd256_process, a_hash_process_rmd256)
__A_HASH_PROCESS(rmd320, a_rmd320_process, a_hash_process_rmd320)
__A_HASH_PROCESS(sha256, a_sha256_process, a_hash_process_sha256)
__A_HASH_PROCESS(sha256, a_sha256_process, a_hash_process_sha224)
__A_HASH_PROCESS(sha512, a_sha512_process, a_hash_process_sha512)
__A_HASH_PROCESS(sha512, a_sha512_process, a_hash_process_sha384)
__A_HASH_PROCESS(sha512, a_sha512_process, a_hash_process_sha512_224)
__A_HASH_PROCESS(sha512, a_sha512_process, a_hash_process_sha512_256)
__A_HASH_PROCESS(sha3, a_sha3_process, a_hash_process_sha3_224)
__A_HASH_PROCESS(sha3, a_sha3_process, a_hash_process_sha3_256)
__A_HASH_PROCESS(sha3, a_sha3_process, a_hash_process_sha3_384)
__A_HASH_PROCESS(sha3, a_sha3_process, a_hash_process_sha3_512)
__A_HASH_PROCESS(sha3, a_sha3_process, a_hash_process_shake128)
__A_HASH_PROCESS(sha3, a_sha3_process, a_hash_process_shake256)
__A_HASH_PROCESS(sha3, a_sha3_process, a_hash_process_keccak224)
__A_HASH_PROCESS(sha3, a_sha3_process, a_hash_process_keccak256)
__A_HASH_PROCESS(sha3, a_sha3_process, a_hash_process_keccak384)
__A_HASH_PROCESS(sha3, a_sha3_process, a_hash_process_keccak512)
__A_HASH_PROCESS(whirlpool, a_whirlpool_process, a_hash_process_whirlpool)
__A_HASH_PROCESS(blake2s, a_blake2s_process, a_hash_process_blake2s_128)
__A_HASH_PROCESS(blake2s, a_blake2s_process, a_hash_process_blake2s_160)
__A_HASH_PROCESS(blake2s, a_blake2s_process, a_hash_process_blake2s_224)
__A_HASH_PROCESS(blake2s, a_blake2s_process, a_hash_process_blake2s_256)
__A_HASH_PROCESS(blake2b, a_blake2b_process, a_hash_process_blake2b_160)
__A_HASH_PROCESS(blake2b, a_blake2b_process, a_hash_process_blake2b_256)
__A_HASH_PROCESS(blake2b, a_blake2b_process, a_hash_process_blake2b_384)
__A_HASH_PROCESS(blake2b, a_blake2b_process, a_hash_process_blake2b_512)
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
#define __A_HASH_DONE(stat, done, func)                \
    __STATIC_INLINE                                    \
    unsigned char *func(a_hash_stat_t *ctx, void *out) \
    {                                                  \
        /* assert(ctx) */                              \
        return done(ctx->stat, out);                   \
    }
__A_HASH_DONE(md2, a_md2_done, a_hash_done_md2)
__A_HASH_DONE(md4, a_md4_done, a_hash_done_md4)
__A_HASH_DONE(md5, a_md5_done, a_hash_done_md5)
__A_HASH_DONE(sha1, a_sha1_done, a_hash_done_sha1)
__A_HASH_DONE(tiger, a_tiger_done, a_hash_done_tiger)
__A_HASH_DONE(rmd128, a_rmd128_done, a_hash_done_rmd128)
__A_HASH_DONE(rmd160, a_rmd160_done, a_hash_done_rmd160)
__A_HASH_DONE(rmd256, a_rmd256_done, a_hash_done_rmd256)
__A_HASH_DONE(rmd320, a_rmd320_done, a_hash_done_rmd320)
__A_HASH_DONE(sha256, a_sha256_done, a_hash_done_sha256)
__A_HASH_DONE(sha256, a_sha256_done, a_hash_done_sha224)
__A_HASH_DONE(sha512, a_sha512_done, a_hash_done_sha512)
__A_HASH_DONE(sha512, a_sha512_done, a_hash_done_sha384)
__A_HASH_DONE(sha512, a_sha512_done, a_hash_done_sha512_224)
__A_HASH_DONE(sha512, a_sha512_done, a_hash_done_sha512_256)
__A_HASH_DONE(sha3, a_sha3_done, a_hash_done_sha3_224)
__A_HASH_DONE(sha3, a_sha3_done, a_hash_done_sha3_256)
__A_HASH_DONE(sha3, a_sha3_done, a_hash_done_sha3_384)
__A_HASH_DONE(sha3, a_sha3_done, a_hash_done_sha3_512)
__A_HASH_DONE(sha3, a_shake128_done, a_hash_done_shake128)
__A_HASH_DONE(sha3, a_shake256_done, a_hash_done_shake256)
__A_HASH_DONE(sha3, a_keccak_done, a_hash_done_keccak224)
__A_HASH_DONE(sha3, a_keccak_done, a_hash_done_keccak256)
__A_HASH_DONE(sha3, a_keccak_done, a_hash_done_keccak384)
__A_HASH_DONE(sha3, a_keccak_done, a_hash_done_keccak512)
__A_HASH_DONE(whirlpool, a_whirlpool_done, a_hash_done_whirlpool)
__A_HASH_DONE(blake2s, a_blake2s_done, a_hash_done_blake2s_128)
__A_HASH_DONE(blake2s, a_blake2s_done, a_hash_done_blake2s_160)
__A_HASH_DONE(blake2s, a_blake2s_done, a_hash_done_blake2s_224)
__A_HASH_DONE(blake2s, a_blake2s_done, a_hash_done_blake2s_256)
__A_HASH_DONE(blake2b, a_blake2b_done, a_hash_done_blake2b_160)
__A_HASH_DONE(blake2b, a_blake2b_done, a_hash_done_blake2b_256)
__A_HASH_DONE(blake2b, a_blake2b_done, a_hash_done_blake2b_384)
__A_HASH_DONE(blake2b, a_blake2b_done, a_hash_done_blake2b_512)
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
