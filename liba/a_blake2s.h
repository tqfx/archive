/*!
 @file           a_blake2s.h
 @brief          RFC 7693 compliant BLAKE implementation
 @details        https://www.ietf.org/rfc/rfc7693.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_BLAKE2S_H__
#define __A_BLAKE2S_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_BLAKE2S_BLOCKSIZE  0x40
#define A_BLAKE2S_DIGESTSIZE 0x20

#define A_BLAKE2S_128_DIGESTSIZE (128 >> 3)
#define A_BLAKE2S_160_DIGESTSIZE (160 >> 3)
#define A_BLAKE2S_224_DIGESTSIZE (224 >> 3)
#define A_BLAKE2S_256_DIGESTSIZE (256 >> 3)

typedef struct a_blake2s_t
{
    uint32_t t[2];
    uint32_t f[2];
    uint32_t curlen;
    uint32_t outlen;
    uint32_t state[A_BLAKE2S_DIGESTSIZE >> 2];
    unsigned char buf[A_BLAKE2S_BLOCKSIZE];
    unsigned char out[A_BLAKE2S_DIGESTSIZE];
    unsigned char lastnode;
} a_blake2s_t;

__BEGIN_DECLS

#undef __A_BLAKE2S_INIT
#define __A_BLAKE2S_INIT(bit, ctx) \
    void a_blake2s_##bit##_init(a_blake2s_t *ctx)
extern __A_BLAKE2S_INIT(128, ctx);
extern __A_BLAKE2S_INIT(160, ctx);
extern __A_BLAKE2S_INIT(224, ctx);
extern __A_BLAKE2S_INIT(256, ctx);
#undef __A_BLAKE2S_INIT

#undef __A_BLAKE2S
#define __A_BLAKE2S(bit, p, n, out) \
    unsigned char *a_blake2s_##bit(const void *p, size_t n, unsigned char *out)
extern __A_BLAKE2S(128, p, n, out);
extern __A_BLAKE2S(160, p, n, out);
extern __A_BLAKE2S(224, p, n, out);
extern __A_BLAKE2S(256, p, n, out);
#undef __A_BLAKE2S

/*!
 @brief          Compress function for BLAKE2S.
 @param[in,out]  ctx: points to an instance of BLAKE2S.
 @param[in]      buf: points to buffer(512-bits).
*/
extern void a_blake2s_compress(a_blake2s_t *ctx, const unsigned char *buf);

/*!
 @brief          Initialize function for BLAKE2S.
 @param[in,out]  ctx: points to an instance of BLAKE2S.
 @param[in]      len: length of buffer that holds the digest.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern int a_blake2s_init(a_blake2s_t *ctx, size_t len, const void *p, size_t n);

/*!
 @brief          Process function for BLAKE2S.
 @param[in,out]  ctx: points to an instance of BLAKE2S.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_blake2s_process(a_blake2s_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for BLAKE2S.
 @param[in,out]  ctx: points to an instance of BLAKE2S.
 @param[in,out]  out: points to buffer that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_blake2s_done(a_blake2s_t *ctx, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_BLAKE2S_H__ */

/* END OF FILE */
