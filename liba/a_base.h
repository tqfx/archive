/*!
 @file a_base.h
 @brief RFC 4648 compliant base implementation
 @details https://www.ietf.org/rfc/rfc4648.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_BASE_H__
#define __A_BASE_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

enum
{
    A_BASE_SUCCESS = A_SUCCESS,
    A_BASE_FAILURE = A_FAILURE,
    A_BASE_INVALID = A_INVALID,
    A_BASE_OVERFLOW = A_OVERFLOW,
};

enum
{
    A_BASE16_LOWER,
    A_BASE16_UPPER,
    A_BASE16_ALL,
};

enum
{
    A_BASE32_RFC4648,
    A_BASE32_BASE32HEX,
    A_BASE32_ZBASE32,
    A_BASE32_CROCKFORD,
    A_BASE32_ALL,
};

__BEGIN_DECLS

/*!
 @brief Base16 encode a buffer
 @param[in] p: input buffer to encode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the binary encoded data
 @param[in,out] siz: max size and resulting size of the encoded data
 @param[in] id:
  @arg A_BASE16_LOWER
  @arg A_BASE16_UPPER
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base16_encode(const void *p, size_t n,
                           void *out, size_t *siz,
                           unsigned int id) __NONNULL((3, 4));

/*!
 @brief Base16 decode a buffer
 @param[in] p: input buffer to decode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the binary decoded data
 @param[in,out] siz: max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base16_decode(const void *p, size_t n,
                           void *out, size_t *siz) __NONNULL((3, 4));

/*!
 @brief Base32 encode a buffer
 @param[in] p: input buffer to encode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the binary encoded data
 @param[in,out] siz: max size and resulting size of the encoded data
 @param[in] id:
  @arg A_BASE32_RFC4648
  @arg A_BASE32_BASE32HEX
  @arg A_BASE32_ZBASE32
  @arg A_BASE32_CROCKFORD
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base32_encode(const void *p, size_t n,
                           void *out, size_t *siz,
                           unsigned int id) __NONNULL((3, 4));

/*!
 @brief Base32 decode a buffer
 @param[in] p: input buffer to decode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the binary decoded data
 @param[in,out] siz: max size and resulting size of the decoded data
 @param[in] id:
  @arg A_BASE32_RFC4648
  @arg A_BASE32_BASE32HEX
  @arg A_BASE32_ZBASE32
  @arg A_BASE32_CROCKFORD
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base32_decode(const void *p, size_t n,
                           void *out, size_t *siz,
                           unsigned int id) __NONNULL((3, 4));

/*!
 @brief base64 Encode a buffer (NUL terminated)
 @param[in] p: input buffer to encode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the base64 encoded data
 @param[in,out] siz: max size and resulting size of the encoded data
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base64_encode(const void *p, size_t n,
                           void *out, size_t *siz) __NONNULL((3, 4));

/*!
 @brief Dangerously relaxed base64 decode a block of memory
 @param[in] p: input buffer to decode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the base64 decoded data
 @param[in,out] siz: max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base64_decode(const void *p, size_t n,
                           void *out, size_t *siz) __NONNULL((3, 4));

/*!
 @brief Strict base64 decode a block of memory
 @param[in] p: input buffer to decode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the base64 decoded data
 @param[in,out] siz: max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base64_decode_strict(const void *p, size_t n,
                                  void *out, size_t *siz) __NONNULL((3, 4));

/*!
 @brief Sane base64 decode a block of memory
 @param[in] p: input buffer to decode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the base64 decoded data
 @param[in,out] siz: max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base64_decode_sane(const void *p, size_t n,
                                void *out, size_t *siz) __NONNULL((3, 4));

/*!
 @brief base64 (URL Safe, RFC 4648 section 5) Encode a buffer (NUL terminated)
 @param[in] p: input buffer to encode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the base64 encoded data
 @param[in,out] siz: max size and resulting size of the encoded data
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base64url_encode(const void *p, size_t n,
                              void *out, size_t *siz) __NONNULL((3, 4));

/*!
 @brief base64 (URL Safe, RFC 4648 section 5) Encode a buffer (NUL terminated)
 @param[in] p: input buffer to encode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the base64 encoded data
 @param[in,out] siz: max size and resulting size of the encoded data
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base64url_encode_strict(const void *p, size_t n,
                                     void *out, size_t *siz) __NONNULL((3, 4));

/*!
 @brief Dangerously relaxed base64 (URL Safe, RFC 4648 section 5) decode a block of memory
 @param[in] p: input buffer to decode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the base64 decoded data
 @param[in,out] siz: max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base64url_decode(const void *p, size_t n,
                              void *out, size_t *siz) __NONNULL((3, 4));

/*!
 @brief Strict base64 (URL Safe, RFC 4648 section 5) decode a block of memory
 @param[in] p: input buffer to decode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the base64 decoded data
 @param[in,out] siz: max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base64url_decode_strict(const void *p, size_t n,
                                     void *out, size_t *siz) __NONNULL((3, 4));

/*!
 @brief Sane base64 (URL Safe, RFC 4648 section 5) decode a block of memory
 @param[in] p: input buffer to decode
 @param[in] n: length of the input buffer
 @param[out] out: destination of the base64 decoded data
 @param[in,out] siz: max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
extern int a_base64url_decode_sane(const void *p, size_t n,
                                   void *out, size_t *siz) __NONNULL((3, 4));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_BASE_H__ */

/* END OF FILE */
