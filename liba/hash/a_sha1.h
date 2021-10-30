/*!
 @file a_sha1.h
 @brief RFC 3174 compliant SHA1 implementation
 @details https://www.ietf.org/rfc/rfc3174.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_SHA1_H__
#define __A_HASH_SHA1_H__

#include "liba.h"

#define A_SHA1_BUFSIZ 0x40
#define A_SHA1_OUTSIZ 20

typedef struct a_sha1_t
{
    uint64_t length;
    unsigned char buf[A_SHA1_BUFSIZ];
    unsigned char out[A_SHA1_OUTSIZ];
    uint32_t state[A_SHA1_OUTSIZ >> 2];
    uint32_t cursiz;
} a_sha1_t;

__BEGIN_DECLS

extern void a_sha1_init(a_sha1_t *ctx) __NONNULL_ALL;
extern int a_sha1_process(a_sha1_t *ctx, const void *p, size_t n) __NONNULL((1));
extern unsigned char *a_sha1_done(a_sha1_t *ctx, void *out) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_SHA1_H__ */

/* END OF FILE */
