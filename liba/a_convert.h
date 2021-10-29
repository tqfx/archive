/*!
 @file           a_convert.h
 @brief          convert library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_CONVERT_H__
#define __A_CONVERT_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

enum
{
    A_DIGEST_LOWER = 0,
    A_DIGEST_UPPER = 1,
};

__BEGIN_DECLS

/*!
 @brief          convert hexadecimal to decimal.
 @param[in]      x: '0'-'9', 'a'-'f', 'A'-'F'
 @return         0 ~ 15
  @retval        -1 failure
*/
extern int a_xdigit(int x);

/*!
 @brief          convert a string to a lower string.
 @param[in]      p: points to data to convert.
 @param[in]      n: length of data to convert.
 @param[in,out]  o: points to buffer that holds the string.
 @return         a pointer to the string.
 @note           When out is 0, you need to use @ref afree to release the memory.
*/
extern void *a_lower(const void *p, size_t n, void *o);

/*!
 @brief          convert a string to a upper string.
 @param[in]      p: points to data to convert.
 @param[in]      n: length of data to convert.
 @param[in,out]  o: points to buffer that holds the string.
 @return         a pointer to the string.
 @note           When out is 0, you need to use @ref afree to release the memory.
*/
extern void *a_upper(const void *p, size_t n, void *o);

/*!
 @brief          convert a digest to a string.
 @param[in]      p: points to data to convert.
 @param[in]      n: length of data to convert.
 @param[in]      x: select the converted case.
  @arg           A_DIGEST_LOWER lower
  @arg           A_DIGEST_UPPER upper
 @param[in,out]  o: points to buffer that holds the string.
 @return         a pointer to the string.
 @note           When out is 0, you need to use @ref afree to release the memory.
*/
extern void *a_digest(const void *p, size_t n, unsigned int x, void *o);
extern void *a_digest_lower(const void *p, size_t n, void *o);
extern void *a_digest_upper(const void *p, size_t n, void *o);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_CONVERT_H__ */

/* END OF FILE */
