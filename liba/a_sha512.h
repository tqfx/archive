/*!
 @file           a_sha512.h
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_SHA512_H__
#define __A_SHA512_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_SHA512_BLOCKSIZE 0x80

#define A_SHA512_DIGESTSIZE     (512 >> 3)
#define A_SHA384_DIGESTSIZE     (384 >> 3)
#define A_SHA512_224_DIGESTSIZE (224 >> 3)
#define A_SHA512_256_DIGESTSIZE (256 >> 3)

typedef struct a_sha512_t
{
    uint64_t length; /*!< total lenght */
    uint32_t curlen; /*!< current length */
    uint64_t state[A_SHA512_DIGESTSIZE >> 3];
    unsigned char buf[A_SHA512_BLOCKSIZE];
    unsigned char out[A_SHA512_DIGESTSIZE];
} a_sha512_t;

#define a_sha384_t     a_sha512_t
#define a_sha512_224_t a_sha512_t
#define a_sha512_256_t a_sha512_t

__BEGIN_DECLS

/*!
 @brief          Compress function for SHA512.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in]      buf: points to buffer(1024-bits).
*/
extern void a_sha512_compress(a_sha512_t *ctx, const unsigned char *buf);
/*!
 @brief          Compress function for SHA384.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in]      buf: points to buffer(1024-bits).
*/
#define a_sha384_compress(ctx, buf) a_sha512_compress(ctx, buf)
/*!
 @brief          Compress function for SHA512/224.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in]      buf: points to buffer(1024-bits).
*/
#define a_sha512_224_compress(ctx, buf) a_sha512_compress(ctx, buf)
/*!
 @brief          Compress function for SHA512/256.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in]      buf: points to buffer(1024-bits).
*/
#define a_sha512_256_compress(ctx, buf) a_sha512_compress(ctx, buf)

/*!
 @brief          Initialize function for SHA512.
 @param[in,out]  ctx: points to an instance of SHA512.
*/
extern void a_sha512_init(a_sha512_t *ctx);
/*!
 @brief          Initialize function for SHA384.
 @param[in,out]  ctx: points to an instance of SHA512.
*/
extern void a_sha384_init(a_sha512_t *ctx);
/*!
 @brief          Initialize function for SHA512/224.
 @param[in,out]  ctx: points to an instance of SHA512.
*/
extern void a_sha512_224_init(a_sha512_t *ctx);
/*!
 @brief          Initialize function for SHA512/256.
 @param[in,out]  ctx: points to an instance of SHA512.
*/
extern void a_sha512_256_init(a_sha512_t *ctx);

/*!
 @brief          Process function for SHA512.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_sha512_process(a_sha512_t *ctx, const void *p, size_t n);
/*!
 @brief          Process function for SHA384.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
#define a_sha384_process(ctx, p, n) a_sha512_process(ctx, p, n)
/*!
 @brief          Process function for SHA512/224.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
#define a_sha512_224_process(ctx, p, n) a_sha512_process(ctx, p, n)
/*!
 @brief          Process function for SHA512/256.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
#define a_sha512_256_process(ctx, p, n) a_sha512_process(ctx, p, n)

/*!
 @brief          Terminate function for SHA512.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in,out]  out: points to buffer(64-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_sha512_done(a_sha512_t *ctx, unsigned char *out);
/*!
 @brief          Terminate function for SHA384.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in,out]  out: points to buffer(48-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_sha384_done(a_sha512_t *ctx, unsigned char *out);
/*!
 @brief          Terminate function for SHA512/224.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in,out]  out: points to buffer(28-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_sha512_224_done(a_sha512_t *ctx, unsigned char *out);
/*!
 @brief          Terminate function for SHA512/256.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in,out]  out: points to buffer(32-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_sha512_256_done(a_sha512_t *ctx, unsigned char *out);

/*!
 @brief          Create SHA512 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(64-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_sha512(const void *p, size_t n, unsigned char *out);
/*!
 @brief          Create SHA384 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(48-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_sha384(const void *p, size_t n, unsigned char *out);
/*!
 @brief          Create SHA512_224 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(28-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_sha512_224(const void *p, size_t n, unsigned char *out);
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
#endif /* __A_SHA512_H__ */

/* END OF FILE */
