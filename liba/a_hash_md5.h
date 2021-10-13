/*!
 @file           a_hash_md5.h
 @brief          RFC 1321 compliant MD5 implementation
 @details        https://www.ietf.org/rfc/rfc1321.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_MD5_H__
#define __A_HASH_MD5_H__

#include "liba.h"

#define A_MD5_BUFSIZ 0x40
#define A_MD5_OUTSIZ 0x10

typedef struct a_md5_t
{
    uint64_t length;
    unsigned char buf[A_MD5_BUFSIZ];
    unsigned char out[A_MD5_OUTSIZ];
    uint32_t state[A_MD5_OUTSIZ >> 2];
    uint32_t cursiz;
} a_md5_t;

__BEGIN_DECLS

extern void a_md5_init(a_md5_t *ctx);
extern int a_md5_process(a_md5_t *ctx, const void *p, size_t n);
extern unsigned char *a_md5_done(a_md5_t *ctx, void *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_MD5_H__ */

/* END OF FILE */
