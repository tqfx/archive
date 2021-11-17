/*!
 @file a_hmac.h
 @brief RFC 2104 compliant HMAC implementation
 @details https://www.ietf.org/rfc/rfc2104.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HMAC_H__
#define __A_HMAC_H__

#include "a_hash.h"

#define A_HMAC_BUFSIZ A_HASH_BUFSIZ

enum
{
    A_HMAC_SUCCESS = A_SUCCESS,
    A_HMAC_WARNING = A_WARNING,
    A_HMAC_FAILURE = A_FAILURE,
    A_HMAC_INVALID = A_INVALID,
    A_HMAC_OVERFLOW = A_OVERFLOW,
    A_HMAC_NOTFOUND = A_NOTFOUND,
};

#pragma pack(push, 4)
typedef struct a_hmac_s
{
    a_hash_u state[1];
    unsigned int outsiz;
    const a_hash_s *hash;
    unsigned char buf[A_HMAC_BUFSIZ];
} a_hmac_s;
#pragma pack(pop)

__BEGIN_DECLS

/*!
 @brief Initialize function for HMAC.
 @param[in,out] ctx: points to an instance of HMAC.
 @param[in] hash: points to an instance of hash descriptor.
 @param[in] p: points to key.
 @param[in] n: length of key.
 @return the execution state of the function
  @retval 0 success
*/
int a_hmac_init(a_hmac_s *ctx, const a_hash_s *hash, const void *p, size_t n) __NONNULL((1, 2));

/*!
 @brief Process function for HMAC.
 @param[in,out] ctx: points to an instance of HMAC.
 @param[in] p: points to text.
 @param[in] n: length of text.
 @return the execution state of the function
  @retval 0 success
*/
int a_hmac_process(a_hmac_s *ctx, const void *p, size_t n) __NONNULL((1));

/*!
 @brief Terminate function for HMAC.
 @param[in,out] ctx: points to an instance of HMAC.
 @param[in,out] out: points to buffer that holds the digest.
 @return p the digest internal buffer.
  @retval 0 generic invalid argument.
*/
unsigned char *a_hmac_done(a_hmac_s *ctx, void *out) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HMAC_H__ */

/* END OF FILE */
