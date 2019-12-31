/*!
 @file md4.h
 @brief RFC 1320 compliant MD4 implementation
 @details https://www.ietf.org/rfc/rfc1320.txt
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_MD4_H__
#define __A_MD4_H__

#include "../def.h"

#define A_MD4_BUFSIZ 0x40
#define A_MD4_OUTSIZ 0x10

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct a_md4_s
{
    uint64_t __length;
    uint32_t __state[A_MD4_OUTSIZ >> 2];
    unsigned char __buf[A_MD4_BUFSIZ];
    unsigned char out[A_MD4_OUTSIZ];
    uint32_t __cursiz;
} a_md4_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_md4_init(a_md4_s *ctx);
A_PUBLIC int a_md4_proc(a_md4_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_md4_done(a_md4_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_MD4_H__ */
