/*!
 @file           a_blake2b.h
 @brief          RFC 7693 compliant BLAKE implementation
 @details        https://www.ietf.org/rfc/rfc7693.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_BLAKE2B_H__
#define __A_BLAKE2B_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_BLAKE2B_BLOCKSIZE  0x80
#define A_BLAKE2B_DIGESTSIZE 0x40

#define A_BLAKE2B_160_DIGESTSIZE (160 >> 3)
#define A_BLAKE2B_256_DIGESTSIZE (256 >> 3)
#define A_BLAKE2B_384_DIGESTSIZE (384 >> 3)
#define A_BLAKE2B_512_DIGESTSIZE (512 >> 3)

typedef struct a_blake2b_t
{
    uint64_t t[2];
    uint64_t f[2];
    uint32_t curlen;
    uint32_t outlen;
    uint64_t state[A_BLAKE2B_DIGESTSIZE >> 3];
    unsigned char buf[A_BLAKE2B_BLOCKSIZE];
    unsigned char out[A_BLAKE2B_DIGESTSIZE];
    unsigned char lastnode;
} a_blake2b_t;

__BEGIN_DECLS

#undef __A_BLAKE2B_INIT
#define __A_BLAKE2B_INIT(bit, ctx) \
    void a_blake2b_##bit##_init(a_blake2b_t *ctx)
extern __A_BLAKE2B_INIT(160, ctx);
extern __A_BLAKE2B_INIT(256, ctx);
extern __A_BLAKE2B_INIT(384, ctx);
extern __A_BLAKE2B_INIT(512, ctx);
#undef __A_BLAKE2B_INIT

#undef __A_BLAKE2B
#define __A_BLAKE2B(bit, p, n, out) \
    unsigned char *a_blake2b_##bit(const void *p, size_t n, unsigned char *out)
extern __A_BLAKE2B(160, p, n, out);
extern __A_BLAKE2B(256, p, n, out);
extern __A_BLAKE2B(384, p, n, out);
extern __A_BLAKE2B(512, p, n, out);
#undef __A_BLAKE2B

/*!
 @brief          Compress function for BLAKE2B.
 @param[in,out]  ctx: points to an instance of BLAKE2B.
 @param[in]      buf: points to buffer(1024-bits).
*/
extern void a_blake2b_compress(a_blake2b_t *ctx, const unsigned char *buf);

/*!
 @brief          Initialize function for BLAKE2B.
 @param[in,out]  ctx: points to an instance of BLAKE2B.
 @param[in]      len: length of buffer that holds the digest.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern int a_blake2b_init(a_blake2b_t *ctx, size_t len, const void *p, size_t n);

/*!
 @brief          Process function for BLAKE2B.
 @param[in,out]  ctx: points to an instance of BLAKE2B.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_blake2b_process(a_blake2b_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for BLAKE2B.
 @param[in,out]  ctx: points to an instance of BLAKE2B.
 @param[in,out]  out: points to buffer that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_blake2b_done(a_blake2b_t *ctx, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_BLAKE2B_H__ */

/* END OF FILE */
