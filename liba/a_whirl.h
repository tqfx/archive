/*!
 @file           a_whirl.h
 @brief          WHIRLPOOL implementation
 @details        https://web.archive.org/web/20171129084214/http://www.larc.usp.br/~pbarreto/WhirlpoolPage.html
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_WHIRL_H__
#define __A_WHIRL_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_WHIRLPOOL_BLOCKSIZE  0x40
#define A_WHIRLPOOL_DIGESTSIZE 0x40

typedef struct a_whirlpool_t
{
    uint64_t length; /*!< total lenght */
    uint32_t curlen; /*!< current length */
    uint64_t state[A_WHIRLPOOL_DIGESTSIZE >> 3];
    unsigned char buf[A_WHIRLPOOL_BLOCKSIZE];
    unsigned char out[A_WHIRLPOOL_DIGESTSIZE];
} a_whirlpool_t;

__BEGIN_DECLS

/*!
 @brief          Compress function for WHIRLPOOL.
 @param[in,out]  ctx: points to an instance of WHIRLPOOL.
 @param[in]      buf: points to buffer(512-bits).
*/
extern void a_whirlpool_compress(a_whirlpool_t *ctx, const unsigned char *buf);

/*!
 @brief          Initialize function for WHIRLPOOL.
 @param[in,out]  ctx: points to an instance of WHIRLPOOL.
*/
extern void a_whirlpool_init(a_whirlpool_t *ctx);

/*!
 @brief          Process function for WHIRLPOOL.
 @param[in,out]  ctx: points to an instance of WHIRLPOOL.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_whirlpool_process(a_whirlpool_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for WHIRLPOOL.
 @param[in,out]  ctx: points to an instance of WHIRLPOOL.
 @param[in,out]  out: points to buffer(64-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_whirlpool_done(a_whirlpool_t *ctx, unsigned char *out);

/*!
 @brief          Create WHIRLPOOL hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(64-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_whirlpool(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_WHIRL_H__ */

/* END OF FILE */
