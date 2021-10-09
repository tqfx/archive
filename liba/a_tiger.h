/*!
 @file           a_tiger.h
 @brief          TIGER implementation
 @details        https://www.cs.technion.ac.il/~biham/Reports/Tiger
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_TIGER_h__
#define __A_TIGER_h__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_TIGER_BLOCKSIZE  0x40
#define A_TIGER_DIGESTSIZE 0x18

typedef struct a_tiger_t
{
    uint64_t length; /*!< total lenght */
    uint32_t curlen; /*!< current length */
    uint64_t state[A_TIGER_DIGESTSIZE >> 3];
    unsigned char buf[A_TIGER_BLOCKSIZE];
    unsigned char out[A_TIGER_DIGESTSIZE];
} a_tiger_t;

__BEGIN_DECLS

/*!
 @brief          Compress function for TIGER.
 @param[in,out]  ctx: points to an instance of TIGER.
 @param[in]      buf: points to buffer(512-bits).
*/
extern void a_tiger_compress(a_tiger_t *ctx, const unsigned char *buf);

/*!
 @brief          Initialize function for TIGER.
 @param[in,out]  ctx: points to an instance of TIGER.
*/
extern void a_tiger_init(a_tiger_t *ctx);

/*!
 @brief          Process function for TIGER.
 @param[in,out]  ctx: points to an instance of TIGER.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_tiger_process(a_tiger_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for TIGER.
 @param[in,out]  ctx: points to an instance of TIGER.
 @param[in,out]  out: points to buffer(20-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_tiger_done(a_tiger_t *ctx, unsigned char *out);

/*!
 @brief          Create TIGER hash from a string of characters on hex encoding.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(24-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern unsigned char *a_tiger(const void *p, size_t n, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_TIGER_H__ */

/* END OF FILE */
