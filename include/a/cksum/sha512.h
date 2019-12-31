/*!
 @file sha512.h
 @brief RFC 5754 compliant SHA2 implementation
 @details https://www.ietf.org/rfc/rfc5754.txt
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_SHA512_H__
#define __A_SHA512_H__

#include "../def.h"

#define A_SHA512_BUFSIZ 0x80
#define A_SHA512_OUTSIZ (512 >> 3)

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct a_sha512_s
{
    uint64_t __length;
    uint64_t __state[A_SHA512_OUTSIZ >> 3];
    unsigned char __buf[A_SHA512_BUFSIZ];
    unsigned char out[A_SHA512_OUTSIZ];
    uint32_t __cursiz;
} a_sha512_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#define A_SHA384_OUTSIZ     (384 >> 3)
#define A_SHA512_224_OUTSIZ (224 >> 3)
#define A_SHA512_256_OUTSIZ (256 >> 3)

typedef a_sha512_s a_sha384_s;
typedef a_sha512_s a_sha512_224_s;
typedef a_sha512_s a_sha512_256_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_sha512_init(a_sha512_s *ctx);
A_PUBLIC int a_sha512_proc(a_sha512_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_sha512_done(a_sha512_s *ctx, void *out);

A_PUBLIC void a_sha384_init(a_sha512_s *ctx);
#define a_sha384_proc(ctx, pdata, nbyte) a_sha512_proc(ctx, pdata, nbyte)
A_PUBLIC unsigned char *a_sha384_done(a_sha512_s *ctx, void *out);

A_PUBLIC void a_sha512_224_init(a_sha512_s *ctx);
#define a_sha512_224_proc(ctx, pdata, nbyte) a_sha512_proc(ctx, pdata, nbyte)
A_PUBLIC unsigned char *a_sha512_224_done(a_sha512_s *ctx, void *out);

A_PUBLIC void a_sha512_256_init(a_sha512_s *ctx);
#define a_sha512_256_proc(ctx, pdata, nbyte) a_sha512_proc(ctx, pdata, nbyte)
A_PUBLIC unsigned char *a_sha512_256_done(a_sha512_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_SHA512_H__ */
