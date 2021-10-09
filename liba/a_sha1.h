/*!
 @file           a_sha1.h
 @brief          RFC 3174 compliant SHA1 implementation
 @details        https://www.ietf.org/rfc/rfc3174.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_SHA1_H__
#define __A_SHA1_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_SHA1_BLOCKSIZE  0x40
#define A_SHA1_DIGESTSIZE 0x14

typedef struct a_sha1_t
{
    uint64_t length; /*!< total lenght */
    uint32_t curlen; /*!< current length */
    uint32_t state[A_SHA1_DIGESTSIZE >> 2];
    unsigned char buf[A_SHA1_BLOCKSIZE];
    unsigned char out[A_SHA1_DIGESTSIZE];
} a_sha1_t;

__BEGIN_DECLS

/*!
 @brief          Compress function for SHA1.
 @param[in,out]  ctx: points to an instance of SHA1.
 @param[in]      buf: points to buffer(512-bits).
*/
extern void a_sha1_compress(a_sha1_t *ctx, const unsigned char *buf);

/*!
 @brief          Initialize function for SHA1.
 @param[in,out]  ctx: points to an instance of SHA1.
*/
extern void a_sha1_init(a_sha1_t *ctx);

/*!
 @brief          Process function for SHA1.
 @param[in,out]  ctx: points to an instance of SHA1.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_sha1_process(a_sha1_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for SHA1.
 @param[in,out]  ctx: points to an instance of SHA1.
 @param[in,out]  out: points to buffer(20-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_sha1_done(a_sha1_t *ctx, unsigned char *out);

/*!
 @brief          Create SHA1 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(20-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_sha1(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_SHA1_H__ */

/* END OF FILE */
