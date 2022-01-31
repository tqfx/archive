/*!
 @file a_hmac_util.h
 @brief hmac library utils
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HMAC_UTIL_H__
#define __A_HMAC_UTIL_H__

#include "a_hmac.h"

#include <stdio.h>

__BEGIN_DECLS

/*!
 @brief HMAC a block of memory to produce the authentication tag.
 @param[in] hash: points to an instance of hash.
 @param[in] pkey: points to secret key to HMAC.
 @param[in] nkey: length of secret key to HMAC.
 @param[in] pmsg: points to data to HMAC.
 @param[in] nmsg: length of data to HMAC.
 @param[out] out: where to store the authentication tag.
 @param[in,out] siz: max size and resulting size of the authentication tag.
 @return the execution state of the function.
  @retval 0 success
*/
int a_hmac_memory(const a_hash_s *hash,
                  const void *pkey, size_t nkey,
                  const void *pmsg, size_t nmsg,
                  void *out, size_t *siz) __NONNULL((1, 6, 7));

/*!
 @brief HMAC multiple blocks of memory to produce the authentication tag.
 @param[in] hash: points to an instance of hash.
 @param[out] out: where to store the authentication tag.
 @param[in,out] siz: max size and resulting size of the authentication tag.
 @param[in] pkey: points to secret key to HMAC.
 @param[in] nkey: length of secret key to HMAC.
 @param[in] pmsg: points to data to HMAC.
 @param[in] nmsg: length of data to HMAC.
 @param[in] ...: tuples of (p,n) pairs to hmac, terminated with a (NULL,x) (x=don't care)
 @return the execution state of the function.
  @retval 0 success
*/
int a_hmac_mmulti(const a_hash_s *hash,
                  void *out, size_t *siz,
                  const void *pkey, size_t nkey,
                  const void *pmsg, size_t nmsg,
                  ...) __NONNULL((1, 2, 3));

/*!
 @brief HMAC data from an file.
 @param[in] hash: points to an instance of hash.
 @param[in] pkey: points to secret key to HMAC.
 @param[in] nkey: length of secret key to HMAC.
 @param[in] in: points to FILE handle to HMAC.
 @param[out] out: where to store the authentication tag.
 @param[in,out] siz: max size and resulting size of the authentication tag.
 @return the execution state of the function.
  @retval 0 success
*/
int a_hmac_filehandle(const a_hash_s *hash,
                      const void *pkey, size_t nkey, FILE *in,
                      void *out, size_t *siz) __NONNULL((1, 4, 5, 6));

/*!
 @brief HMAC data from an open file handle.
 @param[in] hash: points to an instance of hash.
 @param[in] pkey: points to secret key to HMAC.
 @param[in] nkey: length of secret key to HMAC.
 @param[in] fname: name of file to HMAC.
 @param[out] out: where to store the authentication tag.
 @param[in,out] siz: max size and resulting size of the authentication tag.
 @return the execution state of the function.
  @retval 0 success
*/
int a_hmac_file(const a_hash_s *hash,
                const void *pkey, size_t nkey, const char *fname,
                void *out, size_t *siz) __NONNULL((1, 4, 5, 6));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HMAC_UTIL_H__ */
