/*!
 @file md2.h
 @brief RFC 1319 compliant MD2 implementation
 @details https://www.ietf.org/rfc/rfc1319.txt
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_MD2_H__
#define __A_MD2_H__

#include "../def.h"

#define A_MD2_BUFSIZ 0x10
#define A_MD2_OUTSIZ 0x10

typedef struct a_md2_s
{
    unsigned char x[0x30];
    unsigned char __buf[A_MD2_BUFSIZ];
    unsigned char __chksum[A_MD2_BUFSIZ];
    uint32_t __cursiz;
} a_md2_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_md2_init(a_md2_s *ctx);
A_PUBLIC int a_md2_proc(a_md2_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_md2_done(a_md2_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_MD2_H__ */
