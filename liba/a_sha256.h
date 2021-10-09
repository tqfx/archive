/*!
 @file           a_sha256.h
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_SHA256_H__
#define __A_SHA256_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_SHA256_BLOCKSIZE 0x40

#define A_SHA256_DIGESTSIZE (256 >> 3)
#define A_SHA224_DIGESTSIZE (224 >> 3)

typedef struct a_sha256_t
{
    uint64_t length; /*!< total lenght */
    uint32_t curlen; /*!< current length */
    uint32_t state[A_SHA256_DIGESTSIZE >> 2];
    unsigned char buf[A_SHA256_BLOCKSIZE];
    unsigned char out[A_SHA256_DIGESTSIZE];
} a_sha256_t;

#ifndef a_sha224_t
#define a_sha224_t a_sha256_t
#endif /* a_sha224_t */

__BEGIN_DECLS

/*!
 @brief          Compress function for SHA256.
 @param[in,out]  ctx: points to an instance of SHA256.
 @param[in]      buf: points to buffer(512-bits).
*/
extern void a_sha256_compress(a_sha256_t *ctx, const unsigned char *buf);
#ifndef a_sha224_compress
/*!
 @brief          Compress function for SHA256/224.
 @param[in,out]  ctx: points to an instance of SHA256.
 @param[in]      buf: points to buffer(512-bits).
*/
#define a_sha224_compress(ctx, buf) a_sha256_compress(ctx, buf)
#endif /* a_sha224_compress */

/*!
 @brief          Initialize function for SHA256.
 @param[in,out]  ctx: points to an instance of SHA256.
*/
extern void a_sha256_init(a_sha256_t *ctx);
/*!
 @brief          Initialize function for SHA256/224.
 @param[in,out]  ctx: points to an instance of SHA256.
*/
extern void a_sha224_init(a_sha256_t *ctx);

/*!
 @brief          Process function for SHA256.
 @param[in,out]  ctx: points to an instance of SHA256.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_sha256_process(a_sha256_t *ctx, const void *p, size_t n);
#ifndef a_sha224_process
/*!
 @brief          Process function for SHA256/224.
 @param[in,out]  ctx: points to an instance of SHA256.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
#define a_sha224_process(ctx, p, n) a_sha256_process(ctx, p, n)
#endif /* a_sha224_process */

/*!
 @brief          Terminate function for SHA256.
 @param[in,out]  ctx: points to an instance of SHA256.
 @param[in,out]  out: points to buffer(32-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_sha256_done(a_sha256_t *ctx, unsigned char *out);
/*!
 @brief          Terminate function for SHA256/224.
 @param[in,out]  ctx: points to an instance of SHA256.
 @param[in,out]  out: points to buffer(28-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_sha224_done(a_sha256_t *ctx, unsigned char *out);

/*!
 @brief          Create SHA256 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(32-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_sha256(const void *p, size_t n, unsigned char *out);
/*!
 @brief          Create SHA256/224 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(28-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_sha224(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_SHA256_H__ */

/* END OF FILE */
