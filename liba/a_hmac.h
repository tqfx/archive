/*!
 @file           a_hmac.h
 @brief          RFC 2104 compliant HMAC implementation
 @details        https://www.ietf.org/rfc/rfc2104.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HMAC_H__
#define __A_HMAC_H__

#include "a_hash.h"

#define A_HMAC_BUFSIZ A_HASH_BUFSIZ

enum
{
    A_HMAC_SUCCESS = 0,
    A_HMAC_FAILURE = -1,
    A_HMAC_INVALID = -2,
    A_HMAC_OVERFLOW = -3,
};

typedef struct a_hmac_t
{
    unsigned int outsiz;
    const a_hash_t *hash;
    a_hash_stat_t state[1];
    unsigned char buf[A_HMAC_BUFSIZ];
} a_hmac_t;

__BEGIN_DECLS

/*!
 @brief          Initialize function for hmac.
 @param[in,out]  ctx: points to an instance of hmac.
 @param[in]      hash: points to an instance of hash descriptor.
 @param[in]      p: points to key.
 @param[in]      n: length of key.
 @return         the execution state of the function
  @retval        0 success
*/
extern int a_hmac_init(a_hmac_t *ctx, const a_hash_t *hash, const void *p, size_t n);

/*!
 @brief          Process function for hmac.
 @param[in,out]  ctx: points to an instance of hmac.
 @param[in]      p: points to text.
 @param[in]      n: length of text.
 @return         the execution state of the function
  @retval        0 success
*/
extern int a_hmac_process(a_hmac_t *ctx, const void *p, size_t n);

/*!
 @brief          Terminate function for hmac.
 @param[in,out]  ctx: points to an instance of hmac.
 @param[in,out]  out: points to buffer that holds the digest.
 @return         p the digest internal buffer.
  @retval        p the digest internal buffer.
  @retval        0 generic invalid argument.
*/
extern unsigned char *a_hmac_done(a_hmac_t *ctx, unsigned char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HMAC_H__ */

/* END OF FILE */
