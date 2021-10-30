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
 @param[in] ctx: points to an instance of hash.
 @param[in] key: points to secret key to HMAC.
 @param[in] keysiz: length of secret key to HMAC.
 @param[in] msg: points to data to HMAC.
 @param[in] msgsiz: length of data to HMAC.
 @param[out] out: where to store the authentication tag.
 @param[in,out] siz: max size and resulting size of the authentication tag.
 @return the execution state of the function.
  @retval 0 success
*/
extern int a_hmac_memory(const a_hash_t *ctx,
                         const void *key,
                         size_t keysiz,
                         const void *msg,
                         size_t msgsiz,
                         void *out,
                         size_t *siz) __NONNULL((1, 6, 7));

/*!
 @brief HMAC multiple blocks of memory to produce the authentication tag.
 @param[in] ctx: points to an instance of hash.
 @param[out] out: where to store the authentication tag.
 @param[in,out] siz: max size and resulting size of the authentication tag.
 @param[in] key: points to secret key to HMAC.
 @param[in] keysiz: length of secret key to HMAC.
 @param[in] msg: points to data to HMAC.
 @param[in] msgsiz: length of data to HMAC.
 @param[in] ...: tuples of (p,n) pairs to hmac, terminated with a (NULL,x) (x=don't care)
 @return the execution state of the function.
  @retval 0 success
*/
extern int a_hmac_mmulti(const a_hash_t *ctx,
                         void *out,
                         size_t *siz,
                         const void *key,
                         size_t keysiz,
                         const void *msg,
                         size_t msgsiz,
                         ...) __NONNULL((1, 2, 3));

/*!
 @brief HMAC data from an file.
 @param[in] ctx: points to an instance of hash.
 @param[in] key: points to secret key to HMAC.
 @param[in] keysiz: length of secret key to HMAC.
 @param[in] in: points to FILE handle to HMAC.
 @param[out] out: where to store the authentication tag.
 @param[in,out] siz: max size and resulting size of the authentication tag.
 @return the execution state of the function.
  @retval 0 success
*/
extern int a_hmac_filehandle(const a_hash_t *ctx,
                             const void *key,
                             size_t keysiz,
                             FILE *in,
                             void *out,
                             size_t *siz) __NONNULL((1, 4, 5, 6));

/*!
 @brief HMAC data from an open file handle.
 @param[in] ctx: points to an instance of hash.
 @param[in] key: points to secret key to HMAC.
 @param[in] keysiz: length of secret key to HMAC.
 @param[in] fname: name of file to HMAC.
 @param[out] out: where to store the authentication tag.
 @param[in,out] siz: max size and resulting size of the authentication tag.
 @return the execution state of the function.
  @retval 0 success
*/
extern int a_hmac_file(const a_hash_t *ctx,
                       const void *key,
                       size_t keysiz,
                       const char *fname,
                       void *out,
                       size_t *siz) __NONNULL((1, 4, 5, 6));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HMAC_UTIL_H__ */

/* END OF FILE */
