/*!
 @file           a_sha3.h
 @brief          SHA3 implementation
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_SHA3_h__
#define __A_SHA3_h__

#include "liba.h"

#include <stdlib.h> /* alloc */

#define A_SHA3_224_DIGESTSIZE (224 >> 3)
#define A_SHA3_256_DIGESTSIZE (256 >> 3)
#define A_SHA3_384_DIGESTSIZE (384 >> 3)
#define A_SHA3_512_DIGESTSIZE (512 >> 3)

#define A_KECCAK_224_DIGESTSIZE A_SHA3_224_DIGESTSIZE
#define A_KECCAK_256_DIGESTSIZE A_SHA3_256_DIGESTSIZE
#define A_KECCAK_384_DIGESTSIZE A_SHA3_384_DIGESTSIZE
#define A_KECCAK_512_DIGESTSIZE A_SHA3_512_DIGESTSIZE

typedef struct a_sha3_t
{
    uint64_t s[25];
    uint64_t saved;                /* the portion of the input message that we didn't consume yet */
    unsigned char sb[25 << 3];     /* used for storing `uint64_t s[25]` as little-endian bytes */
    unsigned short byte_index;     /* 0..7--the next byte after the set one (starts from 0; 0--none are buffered) */
    unsigned short word_index;     /* 0..24--the next word to integrate input (starts from 0) */
    unsigned short capacity_words; /* the double length of the hash output in words (e.g. 16 for Keccak 512) */
    unsigned short xof_flag;
} a_sha3_t;

#define a_keccak_t     a_sha3_t
#define a_sha3_shake_t a_sha3_t

__BEGIN_DECLS

#define a_sha3_init(bit, ctx) \
    void a_sha3_##bit##_init(a_sha3_t *ctx)
extern a_sha3_init(224, ctx);
extern a_sha3_init(256, ctx);
extern a_sha3_init(384, ctx);
extern a_sha3_init(512, ctx);
#undef a_sha3_init

/*!
 @brief          Initialize function for SHA3.
 @param[in]      bit: bits for SHA3.
  @arg           224 0x0E0
  @arg           256 0x100
  @arg           384 0x180
  @arg           512 0x200
 @param[in,out]  ctx: points to an instance of SHA3.
*/
#define a_sha3_init(bit, ctx) a_sha3_##bit##_init(ctx)

/*!
 @brief          Process function for SHA3.
 @param[in,out]  ctx: points to an instance of SHA3.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
extern void a_sha3_process(a_sha3_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for SHA3.
 @param[in,out]  ctx: points to an instance of SHA3.
 @param[in,out]  out: points to buffer that holds the digest.
 @return         ctx->sb the digest internal buffer.
*/
extern unsigned char *a_sha3_done(a_sha3_t *ctx, unsigned char *out);

#define a_sha3(bit, p, n, out) \
    unsigned char *a_sha3_##bit(const void *p, size_t n, unsigned char *out)
extern a_sha3(224, p, n, out);
extern a_sha3(256, p, n, out);
extern a_sha3(384, p, n, out);
extern a_sha3(512, p, n, out);
#undef a_sha3

/*!
 @brief          Create SHA3 hash from a string of characters on hex encoding.
 @param[in]      bit: bits for SHA3.
  @arg           224 0x0E0
  @arg           256 0x100
  @arg           384 0x180
  @arg           512 0x200
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(bit >> 3) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
#define a_sha3(bit, p, n, out) a_sha3_##bit(p, n, out)

/*!
 @brief          Initialize function for KECCAK.
 @param[in]      bit: bits for KECCAK.
  @arg           224 0x0E0
  @arg           256 0x100
  @arg           384 0x180
  @arg           512 0x200
 @param[in,out]  ctx: points to an instance of SHA3.
*/
#define a_keccak_init(bit, ctx) a_sha3_##bit##_init(ctx)

#define a_keccak_224_init(ctx) a_sha3_224_init(ctx)
#define a_keccak_256_init(ctx) a_sha3_256_init(ctx)
#define a_keccak_384_init(ctx) a_sha3_384_init(ctx)
#define a_keccak_512_init(ctx) a_sha3_512_init(ctx)

/*!
 @brief          Process function for KECCAK.
 @param[in,out]  ctx: points to an instance of SHA3.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
#define a_keccak_process(ctx, p, n) a_sha3_process(ctx, p, n)

/*!
 @brief          Terminate function for KECCAK.
 @param[in,out]  ctx: points to an instance of SHA3.
 @param[in,out]  out: points to buffer that holds the digest.
 @return         ctx->sb the digest internal buffer.
*/
extern unsigned char *a_keccak_done(a_sha3_t *ctx, unsigned char *out);

#define a_keccak(bit, p, n, out) \
    unsigned char *a_keccak_##bit(const void *p, size_t n, unsigned char *out)
extern a_keccak(224, p, n, out);
extern a_keccak(256, p, n, out);
extern a_keccak(384, p, n, out);
extern a_keccak(512, p, n, out);
#undef a_keccak

/*!
 @brief          Create KECCAK hash from a string of characters on hex encoding.
 @param[in]      bit: bits for KECCAK.
  @arg           224 0x0E0
  @arg           256 0x100
  @arg           384 0x180
  @arg           512 0x200
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer(bit >> 3) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
#define a_keccak(bit, p, n, out) a_keccak_##bit(p, n, out)

/*!
 @brief          Initialize function for SHA3/SHAKE.
 @param[in,out]  ctx: points to an instance of SHA3.
 @param[in]      num: initialize for SHA3/SHAKE
  @arg           128 0x080
  @arg           256 0x100
 @return         the execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int a_sha3_shake_init(a_sha3_t *ctx, unsigned int num);

/*!
 @brief          Process function for SHA3/SHAKE.
 @param[in,out]  ctx: points to an instance of SHA3.
 @param[in]      p: points to data.
 @param[in]      n: length of data.
*/
#define a_sha3_shake_process(ctx, p, n) a_sha3_process(ctx, p, n)

/*!
 @brief          Terminate function for SHA3/SHAKE.
 @param[in,out]  ctx: points to an instance of SHA3.
 @param[in,out]  out: points to buffer that holds the digest.
 @param[in]      len: length of buffer that holds the digest.
 @return         ctx->sb the digest internal buffer.
*/
extern void a_sha3_shake_done(a_sha3_t *ctx, unsigned char *out, unsigned int len);

/*!
 @brief          Create SHA3/SHAKE hash from a string of characters on hex encoding.
 @param[in]      num: Create for SHA3/SHAKE
  @arg           128 0x080
  @arg           256 0x100
 @param[in]      p: points to data.
 @param[in]      n: length of data.
 @param[in,out]  out: points to buffer that holds the digest.
 @param[in]      len: length of buffer that holds the digest.
 @return         the execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int a_sha3_shake(unsigned int num,
                        const void *p,
                        size_t n,
                        unsigned char *out,
                        unsigned int len);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_SHA3_H__ */

/* END OF FILE */
