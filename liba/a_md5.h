/*!
 @file           a_md5.h
 @brief          RFC 1321 compliant MD5 implementation
 @details        https://www.ietf.org/rfc/rfc1321.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_MD5_h__
#define __A_MD5_h__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_MD5_BLOCKSIZE  0x40
#define A_MD5_DIGESTSIZE 0x10

typedef struct a_md5_t
{
    uint64_t length; /*!< total lenght */
    uint32_t curlen; /*!< current length */
    uint32_t state[4];
    unsigned char buf[A_MD5_BLOCKSIZE];
    unsigned char out[A_MD5_DIGESTSIZE];
} a_md5_t;

__BEGIN_DECLS

/*!
 @brief          Initialization function for MD5.
 @param[in,out]  ctx: points to an instance of MD5.
*/
extern void a_md5_init(a_md5_t *ctx);

/*!
 @brief          Compress function for MD5.
 @param[in,out]  ctx: points to an instance of MD5.
 @param[in]      buf: points to buffer(512-bits).
*/
extern void a_md5_compress(a_md5_t *ctx, const unsigned char *buf);

/*!
 @brief          Process function for MD5.
 @param[in,out]  ctx: points to an instance of MD5.
 @param[in]      p: points to data.
 @param[in]      n: size of data.
*/
extern void a_md5_process(a_md5_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for MD5.
 @param[in,out]  ctx: points to an instance of MD5.
 @param[in,out]  out: points to buffer(16-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 Generic invalid argument.
*/
extern unsigned char *a_md5_done(a_md5_t *ctx, unsigned char *out);

/*!
 @brief          Created MD5 hash from a string of characters on hex encoding.
 @param[in]      p: points to an array.
 @param[in]      n: size of an array.
 @param[in,out]  out: points to buffer(16-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_md5(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_MD5_H__ */

/* END OF FILE */
