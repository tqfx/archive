/*!
 @file sha256.h
 @brief RFC 5754 compliant SHA2 implementation
 @details https://www.ietf.org/rfc/rfc5754.txt
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_SHA256_H__
#define __A_SHA256_H__

#include "../def.h"

#define A_SHA256_BUFSIZ 0x40
#define A_SHA256_OUTSIZ (256 >> 3)

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct a_sha256_s
{
    uint64_t __length;
    uint32_t __state[A_SHA256_OUTSIZ >> 2];
    unsigned char __buf[A_SHA256_BUFSIZ];
    unsigned char out[A_SHA256_OUTSIZ];
    uint32_t __cursiz;
} a_sha256_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#define A_SHA224_OUTSIZ (224 >> 3)

typedef a_sha256_s a_sha224_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_sha256_init(a_sha256_s *ctx);
A_PUBLIC int a_sha256_proc(a_sha256_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_sha256_done(a_sha256_s *ctx, void *out);

A_PUBLIC void a_sha224_init(a_sha256_s *ctx);
#define a_sha224_proc(ctx, pdata, nbyte) a_sha256_proc(ctx, pdata, nbyte)
A_PUBLIC unsigned char *a_sha224_done(a_sha256_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_SHA256_H__ */
