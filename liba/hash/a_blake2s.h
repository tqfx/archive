/*!
 @file a_blake2s.h
 @brief RFC 7693 compliant BLAKE implementation
 @details https://www.ietf.org/rfc/rfc7693.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_BLAKE2S_H__
#define __A_HASH_BLAKE2S_H__

#include "liba.h"

#define A_BLAKE2S_BUFSIZ     0x40
#define A_BLAKE2S_OUTSIZ     0x20
#define A_BLAKE2S_128_OUTSIZ (128 >> 3)
#define A_BLAKE2S_160_OUTSIZ (160 >> 3)
#define A_BLAKE2S_224_OUTSIZ (224 >> 3)
#define A_BLAKE2S_256_OUTSIZ (256 >> 3)

typedef struct a_blake2s_t
{
    uint32_t t[2];
    uint32_t f[2];
    uint32_t cursiz;
    uint32_t outsiz;
    uint32_t state[A_BLAKE2S_OUTSIZ >> 2];
    unsigned char out[A_BLAKE2S_OUTSIZ];
    unsigned char buf[A_BLAKE2S_BUFSIZ];
    unsigned char lastnode;
} a_blake2s_t;

__BEGIN_DECLS

extern void a_blake2s_128_init(a_blake2s_t *ctx) __NONNULL_ALL;
extern void a_blake2s_160_init(a_blake2s_t *ctx) __NONNULL_ALL;
extern void a_blake2s_224_init(a_blake2s_t *ctx) __NONNULL_ALL;
extern void a_blake2s_256_init(a_blake2s_t *ctx) __NONNULL_ALL;
extern int a_blake2s_process(a_blake2s_t *ctx, const void *p, size_t n) __NONNULL((1));
extern unsigned char *a_blake2s_done(a_blake2s_t *ctx, void *out) __NONNULL((1));
extern int a_blake2s_init(a_blake2s_t *ctx, size_t siz, const void *p, size_t n) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_BLAKE2S_H__ */

/* END OF FILE */
