/*!
 @file a_hash_util.h
 @brief hash library utils
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_UTIL_H__
#define __A_HASH_UTIL_H__

#include "a_hash.h"

#include <stdio.h>

__BEGIN_DECLS

/*!
 @brief Hash a block of memory and store the digest.
 @param[in] ctx: points to an instance of hash.
 @param[in] pdata: points to data to hash.
 @param[in] nbyte: length of data to hash.
 @param[out] out: where to store the digest.
 @param[in,out] siz: max size and resulting size of the digest.
 @return the execution state of the function.
  @retval 0 success
*/
int a_hash_memory(const a_hash_s *ctx,
                  const void *pdata, size_t nbyte,
                  void *out, size_t *siz) __NONNULL((1, 4, 5));

/*!
 @brief Hash multiple (non-adjacent) blocks of memory at once.
 @param[in] ctx: points to an instance of hash.
 @param[out] out: where to store the digest.
 @param[in,out] siz: max size and resulting size of the digest.
 @param[in] pdata: points to data to hash.
 @param[in] nbyte: length of data to hash.
 @param[in] ...: tuples of (p,n) pairs to hash, terminated with a (NULL,x) (x=don't care)
 @return the execution state of the function.
  @retval 0 success
*/
int a_hash_mmulti(const a_hash_s *ctx,
                  void *out, size_t *siz,
                  const void *pdata, size_t nbyte,
                  ...) __NONNULL((1, 2, 3));

/*!
 @brief Hash data from an open file handle.
 @param[in] ctx: points to an instance of hash.
 @param[in] in: points to FILE handle to hash.
 @param[out] out: where to store the digest.
 @param[in,out] siz: max size and resulting size of the digest.
 @return the execution state of the function.
  @retval 0 success
*/
int a_hash_filehandle(const a_hash_s *ctx, FILE *in,
                      void *out, size_t *siz) __NONNULL_ALL;

/*!
 @brief Hash data from an file.
 @param[in] ctx: points to an instance of hash.
 @param[in] fname: name of file to hash.
 @param[out] out: where to store the digest.
 @param[in,out] siz: max size and resulting size of the digest.
 @return the execution state of the function.
  @retval 0 success
*/
int a_hash_file(const a_hash_s *ctx, const char *fname,
                void *out, size_t *siz) __NONNULL_ALL;

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_UTIL_H__ */
