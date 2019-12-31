/*!
 @file sha3.h
 @brief SHA3 implementation
 @details https://en.wikipedia.org/wiki/SHA-3
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_SHA3_H__
#define __A_SHA3_H__

#include "../def.h"

#define A_SHA3_224_BUFSIZ (200 - (224 >> 2))
#define A_SHA3_256_BUFSIZ (200 - (256 >> 2))
#define A_SHA3_384_BUFSIZ (200 - (384 >> 2))
#define A_SHA3_512_BUFSIZ (200 - (512 >> 2))
#define A_SHA3_224_OUTSIZ (224 >> 3)
#define A_SHA3_256_OUTSIZ (256 >> 3)
#define A_SHA3_384_OUTSIZ (384 >> 3)
#define A_SHA3_512_OUTSIZ (512 >> 3)

typedef struct a_sha3_s
{
    uint64_t __s[25];
    uint64_t __saved;                /* the portion of the input message that we didn't consume yet */
    unsigned char out[200];          /* used for storing `uint64_t s[25]` as little-endian bytes */
    unsigned short __byte_index;     /* 0..7--the next byte after the set one (starts from 0; 0--none are buffered) */
    unsigned short __word_index;     /* 0..24--the next word to integrate input (starts from 0) */
    unsigned short __capacity_words; /* the double length of the hash output in words (e.g. 16 for Keccak 512) */
    unsigned short __xof_flag;
} a_sha3_s;

#define A_KECCAK224_BUFSIZ (200 - (224 >> 2))
#define A_KECCAK256_BUFSIZ (200 - (256 >> 2))
#define A_KECCAK384_BUFSIZ (200 - (384 >> 2))
#define A_KECCAK512_BUFSIZ (200 - (512 >> 2))
#define A_KECCAK224_OUTSIZ (224 >> 3)
#define A_KECCAK256_OUTSIZ (256 >> 3)
#define A_KECCAK384_OUTSIZ (384 >> 3)
#define A_KECCAK512_OUTSIZ (512 >> 3)

typedef a_sha3_s a_keccak_s;

#define A_SHAKE128_BUFSIZ (200 - (128 >> 2))
#define A_SHAKE256_BUFSIZ (200 - (256 >> 2))
#define A_SHAKE128_OUTSIZ (128 >> 3)
#define A_SHAKE256_OUTSIZ (256 >> 3)

typedef a_sha3_s a_sha3_shake_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_sha3_224_init(a_sha3_s *ctx);
A_PUBLIC void a_sha3_256_init(a_sha3_s *ctx);
A_PUBLIC void a_sha3_384_init(a_sha3_s *ctx);
A_PUBLIC void a_sha3_512_init(a_sha3_s *ctx);

A_PUBLIC int a_sha3_proc(a_sha3_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_sha3_done(a_sha3_s *ctx, void *out);

#define a_keccak224_init(ctx) a_sha3_224_init(ctx)
#define a_keccak256_init(ctx) a_sha3_256_init(ctx)
#define a_keccak384_init(ctx) a_sha3_384_init(ctx)
#define a_keccak512_init(ctx) a_sha3_512_init(ctx)

#define a_keccak_proc(ctx, pdata, nbyte) a_sha3_proc(ctx, pdata, nbyte)
A_PUBLIC unsigned char *a_keccak_done(a_sha3_s *ctx, void *out);

A_PUBLIC void a_shake128_init(a_sha3_s *ctx);
A_PUBLIC void a_shake256_init(a_sha3_s *ctx);
A_PUBLIC unsigned char *a_shake128_done(a_sha3_s *ctx, void *out);
A_PUBLIC unsigned char *a_shake256_done(a_sha3_s *ctx, void *out);

A_PUBLIC int a_sha3shake_init(a_sha3_s *ctx, unsigned int num);
#define a_sha3shake_proc(ctx, pdata, nbyte) a_sha3_proc(ctx, pdata, nbyte)
A_PUBLIC void a_sha3shake_done(a_sha3_s *ctx, unsigned char *out, unsigned int siz);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_SHA3_H__ */
