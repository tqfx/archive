/*!
 @file           a_sha2.h
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_SHA2_H__
#define __A_HASH_SHA2_H__

#include "liba.h"

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

__BEGIN_DECLS

extern void a_sha256_init(a_sha256_t *ctx) __NONNULL_ALL;
extern int a_sha256_process(a_sha256_t *ctx, const void *p, size_t n) __NONNULL((1));
extern unsigned char *a_sha256_done(a_sha256_t *ctx, void *out) __NONNULL((1));

extern void a_sha224_init(a_sha256_t *ctx) __NONNULL_ALL;
#ifndef a_sha224_process
#define a_sha224_process(_ctx, _p, _n) a_sha256_process(_ctx, _p, _n)
#endif /* a_sha224_process */
extern unsigned char *a_sha224_done(a_sha256_t *ctx, void *out) __NONNULL((1));

extern void a_sha512_init(a_sha512_t *ctx) __NONNULL_ALL;
extern int a_sha512_process(a_sha512_t *ctx, const void *p, size_t n) __NONNULL((1));
extern unsigned char *a_sha512_done(a_sha512_t *ctx, void *out) __NONNULL((1));

extern void a_sha384_init(a_sha512_t *ctx) __NONNULL_ALL;
#ifndef a_sha384_process
#define a_sha384_process(_ctx, _p, _n) a_sha512_process(_ctx, _p, _n)
#endif /* a_sha384_process */
extern unsigned char *a_sha384_done(a_sha512_t *ctx, void *out) __NONNULL((1));

extern void a_sha512_224_init(a_sha512_t *ctx) __NONNULL_ALL;
#ifndef a_sha512_224_process
#define a_sha512_224_process(_ctx, _p, _n) a_sha512_process(_ctx, _p, _n)
#endif /* a_sha512_224_process */
extern unsigned char *a_sha512_224_done(a_sha512_t *ctx, void *out) __NONNULL((1));

extern void a_sha512_256_init(a_sha512_t *ctx) __NONNULL_ALL;
#ifndef a_sha512_256_process
#define a_sha512_256_process(_ctx, _p, _n) a_sha512_process(_ctx, _p, _n)
#endif /* a_sha512_256_process */
extern unsigned char *a_sha512_256_done(a_sha512_t *ctx, void *out) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_SHA2_H__ */

/* END OF FILE */
