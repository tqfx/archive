/*!
 @file str.h
 @brief basic string library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#ifndef __A_STR_H__
#define __A_STR_H__

#include "../def.h"

#if __STDC_HOSTED__

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/*!
 @ingroup A
 @addtogroup A_STR basic string library
 @{
*/

/*!
 @brief instance structure for basic string
*/
typedef struct a_str_s
{
    size_t __mem; /*!< memory */
    size_t __num; /*!< length */
    char *__str; /*!< string */
} a_str_s;

#ifndef A_STR_NIL
// clang-format off
#define A_STR_NIL {0, 0, a_null}
// clang-format on
#endif /* A_STR_NIL */

/*!
 @brief memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of memory
*/
A_INLINE size_t a_str_mem(const a_str_s *ctx) { return ctx->__mem; }

/*!
 @brief length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of length
*/
A_INLINE size_t a_str_len(const a_str_s *ctx) { return ctx->__num; }

/*!
 @brief string for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return string
*/
A_INLINE char *a_str_val(const a_str_s *ctx) { return ctx->__str; }

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to string structure from memory
*/
A_PUBLIC a_str_s *a_str_new(void);

/*!
 @brief deallocate a pointer to string structure
 @param[in] ctx points to an instance of string structure
*/
A_PUBLIC void a_str_die(a_str_s *ctx);

/*!
 @brief constructor for string structure
 @param[in] ctx points to an instance of string structure
*/
A_PUBLIC void a_str_ctor(a_str_s *ctx);

/*!
 @brief destructor for string structure
 @param[in] ctx points to an instance of string structure
*/
A_PUBLIC void a_str_dtor(a_str_s *ctx);

/*!
 @brief initialize a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to data to initialize
 @param[in] nbyte length of data to initialize
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
A_PUBLIC int a_str_init(a_str_s *ctx, const void *pdata, size_t nbyte);

/*!
 @brief initialize a pointer to string structure by copying
 @param[in] ctx points to an instance of string structure
 @param[in] str input source pointing to an instance
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
A_PUBLIC int a_str_copy(a_str_s *ctx, const a_str_s *str);

/*!
 @brief initialize a pointer to string structure by moving
 @param[in] ctx points to an instance of string structure
 @param[in] str input source pointing to an instance
*/
A_PUBLIC a_str_s *a_str_move(a_str_s *ctx, a_str_s *str);

/*!
 @brief terminate a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return string of string structure
 @note need to use free to release this memory
*/
A_PUBLIC char *a_str_exit(a_str_s *ctx);

/*!
 @brief resize memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] mem length of real memory
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
A_PUBLIC int a_str_resize(a_str_s *ctx, size_t mem);
A_PUBLIC int a_str_resize_(a_str_s *ctx, size_t mem);

/*!
 @brief put character to an instance of string structure
 @param[in] ctx points to an instance of string structure
 @param[in] c character
 @return character
  @retval -1 failure
*/
A_PUBLIC int a_str_putc(a_str_s *ctx, int c);
A_PUBLIC int a_str_putc_(a_str_s *ctx, int c);

/*!
 @brief put data to an instance of string structure
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
 @brief put string to an instance of string structure
 @param[in] ctx points to an instance of string structure
 @param[in] str string terminated with a null character
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
A_PUBLIC int a_str_puts(a_str_s *ctx, const void *str);

/*!
 @brief print string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] fmt format of string to be printed
 @param[in] va instance of variable argument
 @return number of printed characters
  @retval -1 failure
*/
A_PUBLIC int a_str_vprintf(a_str_s *ctx, const char *fmt, va_list va) __attribute__((__format__(__printf__, 2, 0)));

/*!
 @brief print string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] fmt format of string to be printed
 @return number of printed characters
  @retval -1 failure
*/
A_PUBLIC int a_str_printf(a_str_s *ctx, const char *fmt, ...) __attribute__((__format__(__printf__, 2, 3)));

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_STR */

#endif /* __STDC_HOSTED__ */

#endif /* __A_STR_H__ */
