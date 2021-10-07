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
 @param[in]      p: points to an array that holds the digest.
 @param[in]      n: integer defining the lengs of the output.
 @param[in,out]  out: points to buffer that holds the string.
 @return         a pointer to the string.
 @note           When out is 0, you need to use @ref a_free to release the memory.
*/
extern char *a_digest(const unsigned char *p, size_t n, char *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_CONVERT_H__ */

/* END OF FILE */
