/*!
 @file a_convert.h
 @brief convert library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_CONVERT_H__
#define __A_CONVERT_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

enum
{
    A_DIGEST_LOWER,
    A_DIGEST_UPPER,
    A_DIGEST_ALL,
};

__BEGIN_DECLS

/*!
 @brief convert hexadecimal to decimal.
 @param[in] x: '0'-'9', 'a'-'f', 'A'-'F'
 @return 0 ~ 15
  @retval -1 failure
*/
int a_xdigit(int x);

/*!
 @brief convert a string to a lower string.
 @param[in] pdata: points to data to convert.
 @param[in] nbyte: length of data to convert.
 @param[in,out] out: points to buffer that holds the string.
 @return a pointer to the string.
 @note When out is 0, you need to use free to release the memory.
*/
void *a_lower(const void *pdata, size_t nbyte, void *out);

/*!
 @brief convert a string to a upper string.
 @param[in] pdata: points to data to convert.
 @param[in] nbyte: length of data to convert.
 @param[in,out] out: points to buffer that holds the string.
 @return a pointer to the string.
 @note When out is 0, you need to use free to release the memory.
*/
void *a_upper(const void *pdata, size_t nbyte, void *out);

/*!
 @brief convert a digest to a string.
 @param[in] pdata: points to data to convert.
 @param[in] nbyte: length of data to convert.
 @param[in] cases: select the converted case.
  @arg A_DIGEST_LOWER lower
  @arg A_DIGEST_UPPER upper
 @param[in,out] out: points to buffer that holds the string.
 @return a pointer to the string.
 @note When out is 0, you need to use free to release the memory.
*/
void *a_digest(const void *pdata, size_t nbyte, unsigned int cases, void *out);
void *a_digest_lower(const void *pdata, size_t nbyte, void *out);
void *a_digest_upper(const void *pdata, size_t nbyte, void *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_CONVERT_H__ */
