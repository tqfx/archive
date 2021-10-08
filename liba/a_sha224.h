/*!
 @file           a_sha224.h
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_SHA224_h__
#define __A_SHA224_h__

#include "liba.h"

#include "a_sha256.h"

#include <stdlib.h> /* alloc */

#define A_SHA224_BLOCKSIZE  A_SHA256_BLOCKSIZE
#define A_SHA224_DIGESTSIZE (224 >> 3)

#define a_sha224_t a_sha256_t

__BEGIN_DECLS

/*!
 @brief          Compress function for SHA224.
 @param[in,out]  ctx: points to an instance of SHA224.
 @param[in]      buf: points to buffer(512-bits).
*/
#define a_sha224_compress(ctx, buf) a_sha256_compress(ctx, buf)

/*!
 @brief          Initialize function for SHA224.
 @param[in,out]  ctx: points to an instance of SHA224.
*/
extern void a_sha224_init(a_sha224_t *ctx);

/*!
 @brief          Process function for SHA224.
 @param[in,out]  ctx: points to an instance of SHA224.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
#define a_sha224_process(ctx, p, n) a_sha256_process(ctx, p, n)

/*!
 @brief          Terminate function for SHA224.
 @param[in,out]  ctx: points to an instance of SHA224.
 @param[in,out]  out: points to buffer(28-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 Generic invalid argument.
*/
extern unsigned char *a_sha224_done(a_sha224_t *ctx, unsigned char *out);

/*!
 @brief          Create SHA224 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(28-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_sha224(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_SHA224_H__ */

/* END OF FILE */
