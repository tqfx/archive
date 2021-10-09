/*!
 @file           a_md2.h
 @brief          RFC 1319 compliant MD2 implementation
 @details        https://www.ietf.org/rfc/rfc1319.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_MD2_H__
#define __A_MD2_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_MD2_BLOCKSIZE  0x10
#define A_MD2_DIGESTSIZE 0x10

typedef struct a_md2_t
{
    uint32_t curlen; /*!< current length */
    unsigned char x[0x30];
    unsigned char buf[0x10];
    unsigned char chksum[0x10];
} a_md2_t;

__BEGIN_DECLS

/*!
 @brief          Initialize function for MD2.
 @param[in,out]  ctx: points to an instance of MD2.
*/
extern void a_md2_init(a_md2_t *ctx);

/*!
 @brief          Process function for MD2.
 @param[in,out]  ctx: points to an instance of MD2.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_md2_process(a_md2_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for MD2.
 @param[in,out]  ctx: points to an instance of MD2.
 @param[in,out]  out: points to buffer(16-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_md2_done(a_md2_t *ctx, unsigned char *out);

/*!
 @brief          Create MD2 hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(16-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_md2(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_MD2_H__ */

/* END OF FILE */
