/*!
 @file           a_hash_md2.h
 @brief          RFC 1319 compliant MD2 implementation
 @details        https://www.ietf.org/rfc/rfc1319.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_MD2_H__
#define __A_HASH_MD2_H__

#include "liba.h"

#define A_MD2_BUFSIZ 0x10
#define A_MD2_OUTSIZ 0x10

typedef struct a_md2_t
{
    unsigned char x[0x30];
    unsigned char buf[A_MD2_BUFSIZ];
    unsigned char chksum[A_MD2_BUFSIZ];
    uint32_t cursiz;
} a_md2_t;

__BEGIN_DECLS

extern void a_md2_init(a_md2_t *ctx);
extern int a_md2_process(a_md2_t *ctx, const void *p, size_t n);
extern unsigned char *a_md2_done(a_md2_t *ctx, void *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_MD2_H__ */

/* END OF FILE */
