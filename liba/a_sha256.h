/*!
 @file           a_sha256.h
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_SHA256_h__
#define __A_SHA256_h__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_SHA256_BLOCKSIZE  0x40
#define A_SHA256_DIGESTSIZE (256 >> 3)

typedef struct a_sha256_t
{
    uint64_t length; /*!< total lenght */
    uint32_t curlen; /*!< current length */
    uint32_t state[A_SHA256_DIGESTSIZE >> 2];
    unsigned char buf[A_SHA256_BLOCKSIZE];
    unsigned char out[A_SHA256_DIGESTSIZE];
} a_sha256_t;

__BEGIN_DECLS

/*!
 @brief          Compress function for SHA256.
 @param[in,out]  ctx: points to an instance of SHA256.
 @param[in]      buf: points to buffer(512-bits).
*/
extern void a_sha256_compress(a_sha256_t *ctx, const unsigned char *buf);

/*!
 @brief          Initialize function for SHA256.
 @param[in,out]  ctx: points to an instance of SHA256.
*/
extern void a_sha256_init(a_sha256_t *ctx);

/*!
 @brief          Process function for SHA256.
 @param[in,out]  ctx: points to an instance of SHA256.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_sha256_process(a_sha256_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for SHA256.
 @param[in,out]  ctx: points to an instance of SHA256.
 @param[in,out]  out: points to buffer(32-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 Generic invalid argument.
*/
extern unsigned char *a_sha256_done(a_sha256_t *ctx, unsigned char *out);

/*!
 @brief          Create SHA256 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(32-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_sha256(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_SHA256_H__ */

/* END OF FILE */
