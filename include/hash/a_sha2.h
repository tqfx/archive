/*!
 @file a_sha2.h
 @brief RFC 5754 compliant SHA2 implementation
 @details https://www.ietf.org/rfc/rfc5754.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_SHA2_H__
#define __A_HASH_SHA2_H__

#include "liba.h"

#define A_SHA256_BUFSIZ 0x40
#define A_SHA256_OUTSIZ (256 >> 3)

#pragma pack(push, 4)
typedef struct a_sha256_s
{
    uint64_t length;
    unsigned char buf[A_SHA256_BUFSIZ];
    unsigned char out[A_SHA256_OUTSIZ];
    uint32_t state[A_SHA256_OUTSIZ >> 2];
    uint32_t cursiz;
} a_sha256_s;
#pragma pack(pop)

#define A_SHA224_OUTSIZ (224 >> 3)

#ifndef a_sha224_s
#define a_sha224_s a_sha256_s
#endif /* a_sha224_s */

#define A_SHA512_BUFSIZ 0x80
#define A_SHA512_OUTSIZ (512 >> 3)

#pragma pack(push, 4)
typedef struct a_sha512_s
{
    uint64_t length;
    unsigned char buf[A_SHA512_BUFSIZ];
    unsigned char out[A_SHA512_OUTSIZ];
    uint64_t state[A_SHA512_OUTSIZ >> 3];
    uint32_t cursiz;
} a_sha512_s;
#pragma pack(pop)

#define A_SHA384_OUTSIZ     (384 >> 3)
#define A_SHA512_224_OUTSIZ (224 >> 3)
#define A_SHA512_256_OUTSIZ (256 >> 3)

#ifndef a_sha384_s
#define a_sha384_s a_sha512_s
#endif /* a_sha384_s */

#ifndef a_sha512_224_s
#define a_sha512_224_s a_sha512_s
#endif /* a_sha512_224_s */

#ifndef a_sha512_256_s
#define a_sha512_256_s a_sha512_s
#endif /* a_sha512_256_s */

__BEGIN_DECLS

void a_sha256_init(a_sha256_s *ctx) __NONNULL_ALL;
int a_sha256_process(a_sha256_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));
unsigned char *a_sha256_done(a_sha256_s *ctx, void *out) __NONNULL((1));

void a_sha224_init(a_sha256_s *ctx) __NONNULL_ALL;
#ifndef a_sha224_process
#define a_sha224_process(ctx, pdata, nbyte) a_sha256_process(ctx, pdata, nbyte)
#endif /* a_sha224_process */
unsigned char *a_sha224_done(a_sha256_s *ctx, void *out) __NONNULL((1));

void a_sha512_init(a_sha512_s *ctx) __NONNULL_ALL;
int a_sha512_process(a_sha512_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));
unsigned char *a_sha512_done(a_sha512_s *ctx, void *out) __NONNULL((1));

void a_sha384_init(a_sha512_s *ctx) __NONNULL_ALL;
#ifndef a_sha384_process
#define a_sha384_process(ctx, pdata, nbyte) a_sha512_process(ctx, pdata, nbyte)
#endif /* a_sha384_process */
unsigned char *a_sha384_done(a_sha512_s *ctx, void *out) __NONNULL((1));

void a_sha512_224_init(a_sha512_s *ctx) __NONNULL_ALL;
#ifndef a_sha512_224_process
#define a_sha512_224_process(ctx, pdata, nbyte) a_sha512_process(ctx, pdata, nbyte)
#endif /* a_sha512_224_process */
unsigned char *a_sha512_224_done(a_sha512_s *ctx, void *out) __NONNULL((1));

void a_sha512_256_init(a_sha512_s *ctx) __NONNULL_ALL;
#ifndef a_sha512_256_process
#define a_sha512_256_process(ctx, pdata, nbyte) a_sha512_process(ctx, pdata, nbyte)
#endif /* a_sha512_256_process */
unsigned char *a_sha512_256_done(a_sha512_s *ctx, void *out) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_SHA2_H__ */
