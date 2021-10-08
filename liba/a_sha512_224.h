/*!
 @file           a_sha512_224.h
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_SHA512_224_h__
#define __A_SHA512_224_h__

#include "liba.h"

#include "a_sha512.h"

#include <stdlib.h> /* alloc */

#define A_SHA512_224_BLOCKSIZE  A_SHA512_BLOCKSIZE
#define A_SHA512_224_DIGESTSIZE 0x1c

#define a_sha512_224_t a_sha512_t

/*!
 @brief          Compress function for SHA512_224.
 @param[in,out]  ctx: points to an instance of SHA512_224.
 @param[in]      buf: points to buffer(512-bits).
*/
#define a_sha512_224_compress(ctx, buf) a_sha512_compress(ctx, buf)

/*!
 @brief          Process function for SHA512_224.
 @param[in,out]  ctx: points to an instance of SHA512_224.
 @param[in]      p: points to data.
 @param[in]      n: size of data.
*/
#define a_sha512_224_process(ctx, p, n) a_sha512_process(ctx, p, n)

__BEGIN_DECLS

/*!
 @brief          Initialize function for SHA512_224.
 @param[in,out]  ctx: points to an instance of SHA512_224.
*/
extern void a_sha512_224_init(a_sha512_224_t *ctx);

/*!
 @brief          Terminate function for SHA512_224.
 @param[in,out]  ctx: points to an instance of SHA512_224.
 @param[in,out]  out: points to buffer(28-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 Generic invalid argument.
*/
extern unsigned char *a_sha512_224_done(a_sha512_224_t *ctx, unsigned char *out);

/*!
 @brief          Created SHA512_224 hash from a string of characters on hex encoding.
 @param[in]      p: points to an array.
 @param[in]      n: size of an array.
 @param[in,out]  out: points to buffer(28-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_sha512_224(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_SHA512_224_H__ */

/* END OF FILE */
