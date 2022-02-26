/*!
 @file a_md5.h
 @brief RFC 1321 compliant MD5 implementation
 @details https://www.ietf.org/rfc/rfc1321.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_MD5_H__
#define __A_HASH_MD5_H__

#include "liba.h"

#define A_MD5_BUFSIZ 0x40
#define A_MD5_OUTSIZ 0x10

#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* _MSC_VER */
typedef struct a_md5_s
{
    uint64_t length;
    unsigned char buf[A_MD5_BUFSIZ];
    unsigned char out[A_MD5_OUTSIZ];
    uint32_t state[A_MD5_OUTSIZ >> 2];
    uint32_t cursiz;
} a_md5_s;
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

__BEGIN_DECLS

void a_md5_init(a_md5_s *ctx) __NONNULL_ALL;
int a_md5_process(a_md5_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));
unsigned char *a_md5_done(a_md5_s *ctx, void *out) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_MD5_H__ */
