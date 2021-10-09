/*!
 @file           a_rmd.h
 @brief          RIPEMD implementation
 @details        https://homes.esat.kuleuven.be/~bosselae/ripemd160.html
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_RMD_H__
#define __A_RMD_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_RIPEMD_BLOCKSIZE 0x40

#define A_RIPEMD128_DIGESTSIZE (128 >> 3)
#define A_RIPEMD160_DIGESTSIZE (160 >> 3)
#define A_RIPEMD256_DIGESTSIZE (256 >> 3)
#define A_RIPEMD320_DIGESTSIZE (320 >> 3)

#undef __A_RMD_T
#define __A_RMD_T(bit)                                   \
    typedef struct a_rmd##bit##_t                        \
    {                                                    \
        uint64_t length; /*!< total lenght */            \
        uint32_t curlen; /*!< current length */          \
        uint32_t state[A_RIPEMD##bit##_DIGESTSIZE >> 2]; \
        unsigned char buf[A_RIPEMD_BLOCKSIZE];           \
        unsigned char out[A_RIPEMD##bit##_DIGESTSIZE];   \
    } a_rmd##bit##_t
__A_RMD_T(128);
__A_RMD_T(160);
__A_RMD_T(256);
__A_RMD_T(320);
#undef __A_RMD_T

#ifndef a_rmd_t
#define a_rmd_t(bit) a_rmd##bit##_t
#endif /* a_rmd_t */

__BEGIN_DECLS

#undef __A_RMD_COMPRESS
#define __A_RMD_COMPRESS(bit, ctx, buf) \
    void a_rmd##bit##_compress(a_rmd##bit##_t *ctx, const unsigned char *buf)
extern __A_RMD_COMPRESS(128, ctx, buf);
extern __A_RMD_COMPRESS(160, ctx, buf);
extern __A_RMD_COMPRESS(256, ctx, buf);
extern __A_RMD_COMPRESS(320, ctx, buf);
#undef __A_RMD_COMPRESS

#undef __A_RMD_INIT
#define __A_RMD_INIT(bit, ctx) \
    void a_rmd##bit##_init(a_rmd##bit##_t *ctx)
extern __A_RMD_INIT(128, ctx);
extern __A_RMD_INIT(160, ctx);
extern __A_RMD_INIT(256, ctx);
extern __A_RMD_INIT(320, ctx);
#undef __A_RMD_INIT

#undef __A_RMD_PROCESS
#define __A_RMD_PROCESS(bit, ctx, p, n) \
    void a_rmd##bit##_process(a_rmd##bit##_t *ctx, const void *p, size_t n)
extern __A_RMD_PROCESS(128, ctx, p, n);
extern __A_RMD_PROCESS(160, ctx, p, n);
extern __A_RMD_PROCESS(256, ctx, p, n);
extern __A_RMD_PROCESS(320, ctx, p, n);
#undef __A_RMD_PROCESS

#undef __A_RMD_DONE
#define __A_RMD_DONE(bit, ctx, out) \
    unsigned char *a_rmd##bit##_done(a_rmd##bit##_t *ctx, unsigned char *out)
extern __A_RMD_DONE(128, ctx, out);
extern __A_RMD_DONE(160, ctx, out);
extern __A_RMD_DONE(256, ctx, out);
extern __A_RMD_DONE(320, ctx, out);
#undef __A_RMD_DONE

#undef __A_RMD
#define __A_RMD(bit, p, n, out) \
    unsigned char *a_rmd##bit(const void *p, size_t n, unsigned char *out)
extern __A_RMD(128, p, n, out);
extern __A_RMD(160, p, n, out);
extern __A_RMD(256, p, n, out);
extern __A_RMD(320, p, n, out);
#undef __A_RMD

#ifndef a_rmd_compress
/*!
 @brief          Compress function for RIPEMD.
 @param[in]      bit: bits for RIPEMD.
  @arg           128 0x080
  @arg           160 0x0A0
  @arg           256 0x100
  @arg           320 0x140
 @param[in,out]  ctx: points to an instance of RIPEMD.
 @param[in]      buf: points to buffer(512-bits).
*/
#define a_rmd_compress(bit, ctx, buf) a_rmd##bit##_compress(ctx, buf)
#endif /* a_rmd_compress */

#ifndef a_rmd_init
/*!
 @brief          Initialize function for RIPEMD.
 @param[in]      bit: bits for RIPEMD.
  @arg           128 0x080
  @arg           160 0x0A0
  @arg           256 0x100
  @arg           320 0x140
 @param[in,out]  ctx: points to an instance of RIPEMD.
*/
#define a_rmd_init(bit, ctx) a_rmd##bit##_init(ctx)
#endif /* a_rmd_init */

#ifndef a_rmd_process
/*!
 @brief          Process function for RIPEMD.
 @param[in]      bit: bits for RIPEMD.
  @arg           128 0x080
  @arg           160 0x0A0
  @arg           256 0x100
  @arg           320 0x140
 @param[in,out]  ctx: points to an instance of RIPEMD.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
#define a_rmd_process(bit, ctx, p, n) a_rmd##bit##_process(ctx, p, n)
#endif /* a_rmd_process */

#ifndef a_rmd_done
/*!
 @brief          Terminate function for RIPEMD.
 @param[in]      bit: bits for RIPEMD.
  @arg           128 0x080
  @arg           160 0x0A0
  @arg           256 0x100
  @arg           320 0x140
 @param[in,out]  ctx: points to an instance of RIPEMD.
 @param[in,out]  out: points to buffer(32-bytes) that holds the digest.
 @return         ctx->out the digest internal buffer.
  @retval        ctx->out the digest internal buffer.
  @retval        0 generic invalid argument.
*/
#define a_rmd_done(bit, ctx, out) a_rmd##bit##_done(ctx, out)
#endif /* a_rmd_done */

#ifndef a_rmd
/*!
 @brief          Create RIPEMD hash from a string of characters on hex encoding.
 @param[in]      bit: bits for RIPEMD.
  @arg           128 0x080
  @arg           160 0x0A0
  @arg           256 0x100
  @arg           320 0x140
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(32-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
#define a_rmd(bit, p, n, out) a_rmd##bit(p, n, out)
#endif /* a_rmd */

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_RIPEMD256_H__ */

/* END OF FILE */
