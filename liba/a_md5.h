/*!
 @file           a_md5.h
 @brief          RFC 1321 compliant MD5 implementation
 @details
 This is an OpenSSL-compatible implementation of the RSA Data Security,
 Inc. MD5 Message-Digest Algorithm (RFC 1321).
 \n \n
 Written by Solar Designer <solar at openwall.com> in 2001, and placed
 in the public domain.  There's absolutely no warranty.
 \n \n
 This differs from Colin Plumb's older public domain implementation in
 that no 32-bit integer data type is required, there's no compile-time
 endianness configuration, and the function prototypes match OpenSSL's.
 The primary goals are portability and ease of use.
 \n \n
 This implementation is meant to be fast, but not as fast as possible.
 Some known optimizations are not included to reduce source code size
 and avoid compile-time configuration.
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_MD5_h__
#define __A_MD5_h__

#include "liba.h"

#include <stdlib.h> /* alloc */

/* exported defines */
#define MD5_BLOCKSIZE  0x40
#define MD5_DIGESTSIZE 0x10

/* exported types */
typedef uint32_t md5_u32_t;
typedef uint64_t md5_u64_t;
typedef struct md5_t
{
    md5_u64_t length;
    md5_u32_t curlen;
    md5_u32_t state[4];
    unsigned char buf[MD5_BLOCKSIZE];
    unsigned char out[MD5_DIGESTSIZE];
} md5_t;

__BEGIN_DECLS

/*!
 @brief          Initialization function for MD5.
 @param[in,out]  ctx: points to an instance of MD5.
*/
extern void md5_init(md5_t *ctx);

/*!
 @brief          Compress function for MD5.
 @param[in,out]  ctx: points to an instance of MD5.
 @param[in]      buf: points to buffer(512-bits).
*/
extern void md5_compress(md5_t *ctx, const unsigned char *buf);

/*!
 @brief          Process function for MD5.
 @param[in,out]  ctx: points to an instance of MD5.
 @param[in]      p: points to data.
 @param[in]      n: size of data.
*/
extern void md5_process(md5_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for MD5.
 @param[in,out]  ctx: points to an instance of MD5.
 @param[in,out]  out: points to buffer(16-bytes) that holds the digest.
 @return         ctx->out The digest internal buffer.
  @retval        ctx->out The digest internal buffer.
  @retval        0 Generic invalid argument.
*/
extern unsigned char *md5_done(md5_t *ctx, unsigned char *out);

/*!
 @brief          Created MD5 hash from a string of characters on hex encoding.
 @param[in]      p: points to an array.
 @param[in]      n: size of an array.
 @param[in,out]  out: points to buffer(16-bytes) that holds the digest.
 @return         a pointer containing the digest.
 @note           When out is 0, you need to use @ref md5_free to release the memory.
*/
extern unsigned char *md5_hash(const void *p, size_t n, unsigned char *out);

/*!
 @brief          Converts a digest to a string.
 @param[in]      digest: pointer to an array that holds the digest.
 @param[in]      n: integer defining the lengs of the output, usually 16 for MD5.
 @param[in,out]  out: points to buffer(33-bytes) that holds the string.
 @return         a pointer to the string.
 @note           When out is 0, you need to use @ref md5_free to release the memory.
*/
extern char *md5_digest(const unsigned char *digest, size_t n, char *out);

/*!
 @brief          Automation function. Gets a pointer to a buffer, Then
                 Hashes it, and converts it to a readable form.
 @param[in]      p: points to an array.
 @param[in]      n: size of an array.
 @param[in,out]  out: points to buffer(33-bytes) that holds the string.
 @return         a pointer to the string.
 @note           When digest is 0, you need to use @ref md5_free to release the memory.
*/
extern char *md5(const void *p, size_t n, char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_MD5_H__ */

/* END OF FILE */
