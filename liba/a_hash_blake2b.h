/*!
 @file           a_hash_blake2b.h
 @brief          RFC 7693 compliant BLAKE implementation
 @details        https://www.ietf.org/rfc/rfc7693.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_BLAKE2B_H__
#define __A_HASH_BLAKE2B_H__

#include "liba.h"

#define A_BLAKE2B_BUFSIZ     0x80
#define A_BLAKE2B_OUTSIZ     0x40
#define A_BLAKE2B_160_OUTSIZ (160 >> 3)
#define A_BLAKE2B_256_OUTSIZ (256 >> 3)
#define A_BLAKE2B_384_OUTSIZ (384 >> 3)
#define A_BLAKE2B_512_OUTSIZ (512 >> 3)

typedef struct a_blake2b_t
{
    uint64_t t[2];
    uint64_t f[2];
    uint32_t cursiz;
    uint32_t outsiz;
    uint64_t state[A_BLAKE2B_OUTSIZ >> 3];
    unsigned char out[A_BLAKE2B_OUTSIZ];
    unsigned char buf[A_BLAKE2B_BUFSIZ];
    unsigned char lastnode;
} a_blake2b_t;

__BEGIN_DECLS

extern void a_blake2b_160_init(a_blake2b_t *ctx);
extern void a_blake2b_256_init(a_blake2b_t *ctx);
extern void a_blake2b_384_init(a_blake2b_t *ctx);
extern void a_blake2b_512_init(a_blake2b_t *ctx);
extern int a_blake2b_process(a_blake2b_t *ctx, const void *p, size_t n);
extern unsigned char *a_blake2b_done(a_blake2b_t *ctx, void *out);
extern int a_blake2b_init(a_blake2b_t *ctx, size_t siz, const void *p, size_t n);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_BLAKE2B_H__ */

/* END OF FILE */
