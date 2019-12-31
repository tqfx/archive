/*!
 @file rmd256.h
 @brief ripemd implementation
 @details https://homes.esat.kuleuven.be/~bosselae/ripemd160.html
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_RMD256_H__
#define __A_RMD256_H__

#include "../def.h"

#define A_RIPEMD256_BUFSIZ 0x40
#define A_RIPEMD256_OUTSIZ (256 >> 3)

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct a_rmd256_s
{
    uint64_t __length;
    unsigned char __buf[A_RIPEMD256_BUFSIZ];
    uint32_t __state[A_RIPEMD256_OUTSIZ >> 2];
    unsigned char out[A_RIPEMD256_OUTSIZ];
    uint32_t __cursiz;
} a_rmd256_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_rmd256_init(a_rmd256_s *ctx);
A_PUBLIC int a_rmd256_proc(a_rmd256_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_rmd256_done(a_rmd256_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_RMD256_H__ */
