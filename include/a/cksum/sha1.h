/*!
 @file sha1.h
 @brief RFC 3174 compliant SHA1 implementation
 @details https://www.ietf.org/rfc/rfc3174.txt
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_SHA1_H__
#define __A_SHA1_H__

#include "../def.h"

#define A_SHA1_BUFSIZ 0x40
#define A_SHA1_OUTSIZ 20

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct a_sha1_s
{
    uint64_t __length;
    unsigned char __buf[A_SHA1_BUFSIZ];
    uint32_t __state[A_SHA1_OUTSIZ >> 2];
    unsigned char out[A_SHA1_OUTSIZ];
    uint32_t __cursiz;
} a_sha1_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_sha1_init(a_sha1_s *ctx);
A_PUBLIC int a_sha1_proc(a_sha1_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_sha1_done(a_sha1_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_SHA1_H__ */
