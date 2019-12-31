/*!
 @file blake2b.h
 @brief RFC 7693 compliant BLAKE implementation
 @details https://www.ietf.org/rfc/rfc7693.txt
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_BLAKE2B_H__
#define __A_BLAKE2B_H__

#include "../def.h"

#define A_BLAKE2B_BUFSIZ     0x80
#define A_BLAKE2B_OUTSIZ     0x40
#define A_BLAKE2B_160_OUTSIZ (160 >> 3)
#define A_BLAKE2B_256_OUTSIZ (256 >> 3)
#define A_BLAKE2B_384_OUTSIZ (384 >> 3)
#define A_BLAKE2B_512_OUTSIZ (512 >> 3)

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct a_blake2b_s
{
    uint64_t __t[2];
    uint64_t __f[2];
    uint32_t __cursiz;
    uint32_t outsiz;
    uint64_t __state[A_BLAKE2B_OUTSIZ >> 3];
    unsigned char out[A_BLAKE2B_OUTSIZ];
    unsigned char __buf[A_BLAKE2B_BUFSIZ];
    unsigned char __lastnode;
} a_blake2b_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_blake2b_160_init(a_blake2b_s *ctx);
A_PUBLIC void a_blake2b_256_init(a_blake2b_s *ctx);
A_PUBLIC void a_blake2b_384_init(a_blake2b_s *ctx);
A_PUBLIC void a_blake2b_512_init(a_blake2b_s *ctx);
A_PUBLIC int a_blake2b_init(a_blake2b_s *ctx, size_t siz, const void *pdata, size_t nbyte);
A_PUBLIC int a_blake2b_proc(a_blake2b_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_blake2b_done(a_blake2b_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_BLAKE2B_H__ */
