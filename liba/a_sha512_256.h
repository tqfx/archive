/*!
 @file           a_sha512_256.h
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_SHA512_256_h__
#define __A_SHA512_256_h__

#include "liba.h"

#include "a_sha512.h"

#include <stdlib.h> /* alloc */

#define A_SHA512_256_BLOCKSIZE  A_SHA512_BLOCKSIZE
#define A_SHA512_256_DIGESTSIZE (256 >> 3)

#define a_sha512_256_t a_sha512_t

__BEGIN_DECLS

/*!
 @brief          Compress function for SHA512/256.
 @param[in,out]  ctx: points to an instance of SHA512/256.
 @param[in]      buf: points to buffer(512-bits).
*/
#define a_sha512_256_compress(ctx, buf) a_sha512_compress(ctx, buf)

/*!
 @brief          Initialize function for SHA512/256.
 @param[in,out]  ctx: points to an instance of SHA512/256.
*/
extern void a_sha512_256_init(a_sha512_256_t *ctx);

/*!
 @brief          Process function for SHA512/256.
 @param[in,out]  ctx: points to an instance of SHA512/256.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
#define a_sha512_256_process(ctx, p, n) a_sha512_process(ctx, p, n)

/*!
 @brief          Terminate function for SHA512/256.
 @param[in,out]  ctx: points to an instance of SHA512/256.
 @param[in,out]  out: points to buffer(32-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 Generic invalid argument.
*/
extern unsigned char *a_sha512_256_done(a_sha512_256_t *ctx, unsigned char *out);

/*!
 @brief          Create SHA512_256 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(32-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_sha512_256(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_SHA512_256_H__ */

/* END OF FILE */
