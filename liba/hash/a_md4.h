/*!
 @file           a_md4.h
 @brief          RFC 1320 compliant MD4 implementation
 @details        https://www.ietf.org/rfc/rfc1320.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_MD4_H__
#define __A_HASH_MD4_H__

#include "liba.h"

#define A_MD4_BUFSIZ 0x40
#define A_MD4_OUTSIZ 0x10

typedef struct a_md4_t
{
    uint64_t length;
    unsigned char buf[A_MD4_BUFSIZ];
    unsigned char out[A_MD4_OUTSIZ];
    uint32_t state[A_MD4_OUTSIZ >> 2];
    uint32_t cursiz;
} a_md4_t;

__BEGIN_DECLS

extern void a_md4_init(a_md4_t *ctx) __NONNULL_ALL;
extern int a_md4_process(a_md4_t *ctx, const void *p, size_t n) __NONNULL((1));
extern unsigned char *a_md4_done(a_md4_t *ctx, void *out) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_MD4_H__ */

/* END OF FILE */
