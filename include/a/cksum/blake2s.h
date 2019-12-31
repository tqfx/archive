/*!
 @file blake2s.h
 @brief RFC 7693 compliant BLAKE implementation
 @details https://www.ietf.org/rfc/rfc7693.txt
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_BLAKE2S_H__
#define __A_BLAKE2S_H__

#include "../def.h"

#define A_BLAKE2S_BUFSIZ     0x40
#define A_BLAKE2S_OUTSIZ     0x20
#define A_BLAKE2S_128_OUTSIZ (128 >> 3)
#define A_BLAKE2S_160_OUTSIZ (160 >> 3)
#define A_BLAKE2S_224_OUTSIZ (224 >> 3)
#define A_BLAKE2S_256_OUTSIZ (256 >> 3)

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct a_blake2s_s
{
    uint32_t __t[2];
    uint32_t __f[2];
    uint32_t __cursiz;
    uint32_t outsiz;
    uint32_t __state[A_BLAKE2S_OUTSIZ >> 2];
    unsigned char out[A_BLAKE2S_OUTSIZ];
    unsigned char __buf[A_BLAKE2S_BUFSIZ];
    unsigned char __lastnode;
} a_blake2s_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_blake2s_128_init(a_blake2s_s *ctx);
A_PUBLIC void a_blake2s_160_init(a_blake2s_s *ctx);
A_PUBLIC void a_blake2s_224_init(a_blake2s_s *ctx);
A_PUBLIC void a_blake2s_256_init(a_blake2s_s *ctx);
A_PUBLIC int a_blake2s_init(a_blake2s_s *ctx, size_t siz, const void *pdata, size_t nbyte);
A_PUBLIC int a_blake2s_proc(a_blake2s_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_blake2s_done(a_blake2s_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_BLAKE2S_H__ */
