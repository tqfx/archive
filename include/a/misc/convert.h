/*!
 @file convert.h
 @brief convert library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_CONVERT_H__
#define __A_CONVERT_H__

#include "../def.h"

#include <stdlib.h>

enum
{
    A_DIGEST_LOWER,
    A_DIGEST_UPPER,
    A_DIGEST_ALL,
};

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief convert hexadecimal to decimal.
 @param[in] x '0'-'9', 'a'-'f', 'A'-'F'
 @return 0 ~ 15
  @retval -1 failure
*/
A_PUBLIC int a_xdigit(int x);

/*!
 @brief convert a string to a lower string.
 @param[in] pdata points to data to convert.
 @param[in] nbyte length of data to convert.
 @param[in,out] out points to buffer that holds the string.
 @return a pointer to the string.
 @note When out is 0, you need to use free to release the memory.
*/
A_PUBLIC void *a_lower(const void *pdata, size_t nbyte, void *out);

/*!
 @brief convert a string to a upper string.
 @param[in] pdata points to data to convert.
 @param[in] nbyte length of data to convert.
 @param[in,out] out points to buffer that holds the string.
 @return a pointer to the string.
 @note When out is 0, you need to use free to release the memory.
*/
A_PUBLIC void *a_upper(const void *pdata, size_t nbyte, void *out);

/*!
 @brief convert a digest to a string.
 @param[in] pdata points to data to convert.
 @param[in] nbyte length of data to convert.
 @param[in] cases select the converted case.
  @arg A_DIGEST_LOWER lower
  @arg A_DIGEST_UPPER upper
 @param[in,out] out points to buffer that holds the string.
 @return a pointer to the string.
 @note When out is 0, you need to use free to release the memory.
*/
A_PUBLIC void *a_digest(const void *pdata, size_t nbyte, unsigned int cases, void *out);
A_PUBLIC void *a_digest_lower(const void *pdata, size_t nbyte, void *out);
A_PUBLIC void *a_digest_upper(const void *pdata, size_t nbyte, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_CONVERT_H__ */
