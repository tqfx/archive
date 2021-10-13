/*!
 @file           a_hash_sha3.h
 @brief          SHA3 implementation
 @details        https://en.wikipedia.org/wiki/SHA-3
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_SHA3_H__
#define __A_HASH_SHA3_H__

#include "liba.h"

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

__BEGIN_DECLS

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

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_SHA3_H__ */

/* END OF FILE */
