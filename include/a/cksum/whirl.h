/*!
 @file whirl.h
 @brief whirlpool implementation
 @details https://web.archive.org/web/20171129084214/http://www.larc.usp.br/~pbarreto/WhirlpoolPage.html
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_WHIRL_H__
#define __A_WHIRL_H__

#include "../def.h"

#define A_WHIRLPOOL_BUFSIZ 0x40
#define A_WHIRLPOOL_OUTSIZ 0x40

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct a_whirlpool_s
{
    uint64_t __length;
    uint64_t __state[A_WHIRLPOOL_OUTSIZ >> 3];
    unsigned char __buf[A_WHIRLPOOL_BUFSIZ];
    unsigned char out[A_WHIRLPOOL_OUTSIZ];
    uint32_t __cursiz;
} a_whirlpool_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_whirlpool_init(a_whirlpool_s *ctx);
A_PUBLIC int a_whirlpool_proc(a_whirlpool_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_whirlpool_done(a_whirlpool_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_WHIRL_H__ */
