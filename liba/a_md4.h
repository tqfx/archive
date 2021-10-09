/*!
 @file           a_md4.h
 @brief          RFC 1320 compliant MD4 implementation
 @details        https://www.ietf.org/rfc/rfc1320.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_MD4_H__
#define __A_MD4_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_MD4_BLOCKSIZE  0x40
#define A_MD4_DIGESTSIZE 0x10

typedef struct a_md4_t
{
    uint64_t length; /*!< total lenght */
    uint32_t curlen; /*!< current length */
    uint32_t state[A_MD4_DIGESTSIZE >> 2];
    unsigned char buf[A_MD4_BLOCKSIZE];
    unsigned char out[A_MD4_DIGESTSIZE];
} a_md4_t;

__BEGIN_DECLS

/*!
 @brief          Compress function for MD4.
 @param[in,out]  ctx: points to an instance of MD4.
 @param[in]      buf: points to buffer(512-bits).
*/
extern void a_md4_compress(a_md4_t *ctx, const unsigned char *buf);

/*!
 @brief          Initialize function for MD4.
 @param[in,out]  ctx: points to an instance of MD4.
*/
extern void a_md4_init(a_md4_t *ctx);

/*!
 @brief          Process function for MD4.
 @param[in,out]  ctx: points to an instance of MD4.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_md4_process(a_md4_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for MD4.
 @param[in,out]  ctx: points to an instance of MD4.
 @param[in,out]  out: points to buffer(16-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_md4_done(a_md4_t *ctx, unsigned char *out);

/*!
 @brief          Create MD4 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(16-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_md4(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_MD4_H__ */

/* END OF FILE */
