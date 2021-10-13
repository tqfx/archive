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

__BEGIN_DECLS

/*!
 @brief          Convert a digest to a string.
 @param[in]      p: points to data to convert.
 @param[in]      n: length of data to convert.
 @param[in,out]  out: points to buffer that holds the string.
 @return         a pointer to the string.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern void *a_digest(const void *p, size_t n, void *out);

/*!
 @brief          Convert a string to a lower string.
 @param[in]      p: points to data to convert.
 @param[in]      n: length of data to convert.
 @param[in,out]  out: points to buffer that holds the string.
 @return         a pointer to the string.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern void *a_lower(const void *p, size_t n, void *out);

/*!
 @brief          Convert a string to a upper string.
 @param[in]      p: points to data to convert.
 @param[in]      n: length of data to convert.
 @param[in,out]  out: points to buffer that holds the string.
 @return         a pointer to the string.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern void *a_upper(const void *p, size_t n, void *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_CONVERT_H__ */

/* END OF FILE */
