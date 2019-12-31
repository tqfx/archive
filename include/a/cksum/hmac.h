/*!
 @file hmac.h
 @brief RFC 2104 compliant HMAC implementation
 @details https://www.ietf.org/rfc/rfc2104.txt
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_HMAC_H__
#define __A_HMAC_H__

#include "hash.h"

#define A_HMAC_BUFSIZ A_HASH_BUFSIZ

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct a_hmac_s
{
    a_hash_u __state[1];
    unsigned int outsiz;
    const a_hash_s *__hash;
    unsigned char buf[A_HMAC_BUFSIZ];
} a_hmac_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief Initialize function for HMAC.
 @param[in,out] ctx points to an instance of HMAC.
 @param[in] hash points to an instance of hash descriptor.
 @param[in] pdata points to key.
 @param[in] nbyte length of key.
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_hmac_init(a_hmac_s *ctx, const a_hash_s *hash, const void *pdata, size_t nbyte);

/*!
 @brief Process function for HMAC.
 @param[in,out] ctx points to an instance of HMAC.
 @param[in] pdata points to text.
 @param[in] nbyte length of text.
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_hmac_proc(a_hmac_s *ctx, const void *pdata, size_t nbyte);

/*!
 @brief Terminate function for HMAC.
 @param[in,out] ctx points to an instance of HMAC.
 @param[in,out] out points to buffer that holds the digest.
 @return the digest internal buffer.
  @retval 0 generic invalid argument.
*/
A_PUBLIC unsigned char *a_hmac_done(a_hmac_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_HMAC_H__ */
