/*!
 @file md5.h
 @brief RFC 1321 compliant MD5 implementation
 @details https://www.ietf.org/rfc/rfc1321.txt
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_MD5_H__
#define __A_MD5_H__

#include "../def.h"

#define A_MD5_BUFSIZ 0x40
#define A_MD5_OUTSIZ 0x10

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct a_md5_s
{
    uint64_t __length;
    uint32_t __state[A_MD5_OUTSIZ >> 2];
    unsigned char __buf[A_MD5_BUFSIZ];
    unsigned char out[A_MD5_OUTSIZ];
    uint32_t __cursiz;
} a_md5_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_md5_init(a_md5_s *ctx);
A_PUBLIC int a_md5_proc(a_md5_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_md5_done(a_md5_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_MD5_H__ */
