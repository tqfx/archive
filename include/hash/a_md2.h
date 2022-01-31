/*!
 @file a_md2.h
 @brief RFC 1319 compliant MD2 implementation
 @details https://www.ietf.org/rfc/rfc1319.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_MD2_H__
#define __A_HASH_MD2_H__

#include "liba.h"

#define A_MD2_BUFSIZ 0x10
#define A_MD2_OUTSIZ 0x10

typedef struct a_md2_s
{
    unsigned char x[0x30];
    unsigned char buf[A_MD2_BUFSIZ];
    unsigned char chksum[A_MD2_BUFSIZ];
    uint32_t cursiz;
} a_md2_s;

__BEGIN_DECLS

void a_md2_init(a_md2_s *ctx) __NONNULL_ALL;
int a_md2_process(a_md2_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));
unsigned char *a_md2_done(a_md2_s *ctx, void *out) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_MD2_H__ */
