/*!
 @file str.h
 @brief basic string library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_STR_H__
#define __A_STR_H__

#include "../def.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/*!
 @brief Instance structure for string
*/
typedef struct a_str_s
{
    size_t __m; /*!< memory */
    size_t __n; /*!< length */
    char *__s;  /*!< string */
} a_str_s;

#ifndef A_STR_NUL
#define A_STR_NUL \
    {             \
        0, 0, 0,  \
    }
#endif /* A_STR_NUL */

/*!
 @brief memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of memory
*/
A_INLINE size_t a_str_mem(const a_str_s *ctx) { return ctx->__m; }

/*!
 @brief length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of length
*/
A_INLINE size_t a_str_len(const a_str_s *ctx) { return ctx->__n; }

/*!
 @brief string for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return string
*/
A_INLINE char *a_str_val(const a_str_s *ctx) { return ctx->__s; }

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief Allocate a pointer to string structure from memory
*/
A_PUBLIC a_str_s *a_str_new(void);

/*!
 @brief Deallocate a pointer to string structure
 @param[in] ctx points to an instance of string structure
*/
A_PUBLIC void a_str_die(a_str_s *ctx);

/*!
 @brief Constructor for string structure
 @param[in] ctx points to an instance of string structure
*/
A_PUBLIC void a_str_ctor(a_str_s *ctx);

/*!
 @brief Destructor for string structure
 @param[in] ctx points to an instance of string structure
*/
A_PUBLIC void a_str_dtor(a_str_s *ctx);

/*!
 @brief Initialize a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to data to initialize
 @param[in] nbyte length of data to initialize
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
A_PUBLIC int a_str_init(a_str_s *ctx, const void *pdata, size_t nbyte);

/*!
 @brief Initialize a pointer to string structure by copying
 @param[in] ctx points to an instance of string structure
 @param[in] in input source pointing to an instance
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
A_PUBLIC int a_str_copy(a_str_s *ctx, const a_str_s *in);

/*!
 @brief Initialize a pointer to string structure by moving
 @param[in] ctx points to an instance of string structure
 @param[in] in input source pointing to an instance
*/
A_PUBLIC void a_str_move(a_str_s *ctx, a_str_s *in);

/*!
 @brief Terminate a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return string of string structure
 @note You need to use free to release the memory
*/
A_PUBLIC char *a_str_done(a_str_s *ctx);

/*!
 @brief Resize memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] m length of real memory
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
A_PUBLIC int a_str_resize(a_str_s *ctx, size_t m);
A_PUBLIC int a_str_resize_(a_str_s *ctx, size_t m);

/*!
 @brief Put character to an instance of string structure
 @param[in] ctx points to an instance of string structure
 @param[in] c character
 @return character
  @retval -1 failure
*/
A_PUBLIC int a_str_putc(a_str_s *ctx, int c);
A_PUBLIC int a_str_putc_(a_str_s *ctx, int c);

/*!
 @brief Put data to an instance of string structure
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to data to put
 @param[in] nbyte length of data to put
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
A_PUBLIC int a_str_putn(a_str_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC int a_str_putn_(a_str_s *ctx, const void *pdata, size_t nbyte);

/*!
 @brief Put string to an instance of string structure
 @param[in] ctx points to an instance of string structure
 @param[in] str string
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
A_PUBLIC int a_str_puts(a_str_s *ctx, const void *str);

/*!
 @brief Print string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] fmt print format
 @param[in] va va_list
 @return number of print
  @retval -1 failure
*/
A_PUBLIC int a_str_vprintf(a_str_s *ctx, const char *fmt, va_list va) __attribute__((__format__(__printf__, 2, 0)));

/*!
 @brief Print string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] fmt print format
 @return number of print
  @retval -1 failure
*/
A_PUBLIC int a_str_printf(a_str_s *ctx, const char *fmt, ...) __attribute__((__format__(__printf__, 2, 3)));

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_STR_H__ */
