/*!
 @file           a_sha512.h
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_SHA512_h__
#define __A_SHA512_h__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_SHA512_BLOCKSIZE  0x80
#define A_SHA512_DIGESTSIZE (512 >> 3)

typedef struct a_sha512_t
{
    uint64_t length; /*!< total lenght */
    uint32_t curlen; /*!< current length */
    uint64_t state[A_SHA512_DIGESTSIZE >> 3];
    unsigned char buf[A_SHA512_BLOCKSIZE];
    unsigned char out[A_SHA512_DIGESTSIZE];
} a_sha512_t;

__BEGIN_DECLS

/*!
 @brief          Compress function for SHA512.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in]      buf: points to buffer(1024-bits).
*/
extern void a_sha512_compress(a_sha512_t *ctx, const unsigned char *buf);

/*!
 @brief          Initialize function for SHA512.
 @param[in,out]  ctx: points to an instance of SHA512.
*/
extern void a_sha512_init(a_sha512_t *ctx);

/*!
 @brief          Process function for SHA512.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_sha512_process(a_sha512_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for SHA512.
 @param[in,out]  ctx: points to an instance of SHA512.
 @param[in,out]  out: points to buffer(64-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 Generic invalid argument.
*/
extern unsigned char *a_sha512_done(a_sha512_t *ctx, unsigned char *out);

/*!
 @brief          Create SHA512 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(64-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_sha512(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_SHA512_H__ */

/* END OF FILE */
