/*!
 @file str.h
 @brief basic string library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_HOST_STR_H__
#define __A_HOST_STR_H__

#include "../a.h"

#include <string.h>

#if __STDC_HOSTED__

#include <stdarg.h>
#include <stdlib.h>

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
    a_str_t __str; /*!< string */
    a_size_t __num; /*!< length */
    a_size_t __mem; /*!< memory */
} a_str_s;

#ifndef A_STR_NIL
// clang-format off
#define A_STR_NIL {a_null, a_zero, a_zero}
// clang-format on
#endif /* A_STR_NIL */

/*!
 @brief string for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return string
*/
A_INLINE a_str_t a_str_val(const a_str_s *ctx) { return ctx->__str; }

/*!
 @brief length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of length
*/
A_INLINE a_size_t a_str_len(const a_str_s *ctx) { return ctx->__num; }

/*!
 @brief memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of memory
*/
A_INLINE a_size_t a_str_mem(const a_str_s *ctx) { return ctx->__mem; }

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to string structure from memory
*/
A_PUBLIC a_str_s *a_str_new(a_noarg_t);

/*!
 @brief deallocate a pointer to string structure
 @param[in] ctx points to an instance of string structure
*/
A_PUBLIC a_noret_t a_str_die(a_str_s *ctx);

/*!
 @brief constructor for string structure
 @param[in] ctx points to an instance of string structure
*/
A_PUBLIC a_noret_t a_str_ctor(a_str_s *ctx);

/*!
 @brief destructor for string structure
 @param[in] ctx points to an instance of string structure
*/
A_PUBLIC a_noret_t a_str_dtor(a_str_s *ctx);

/*!
 @brief initialize a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to data to initialize
 @param[in] nbyte length of data to initialize
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_str_init(a_str_s *ctx, a_cptr_t pdata, a_size_t nbyte);

/*!
 @brief initialize a pointer to string structure by copying
 @param[in] ctx points to an instance of string structure
 @param[in] obj input source pointing to an instance
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_str_copy(a_str_s *ctx, const a_str_s *obj);

/*!
 @brief initialize a pointer to string structure by moving
 @param[in] ctx points to an instance of string structure
 @param[in] obj input source pointing to an instance
*/
A_PUBLIC a_str_s *a_str_move(a_str_s *ctx, a_str_s *obj);

/*!
 @brief terminate a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return string of string structure
 @note need to use free to release this memory
*/
A_PUBLIC a_str_t a_str_exit(a_str_s *ctx);

/*!
 @brief compare the string lhs to the string rhs
 @param[in] lhs string structure to be compared
 @param[in] rhs string structure to be compared
 @return relationship between the strings
  @retval <0 lhs < rhs
  @retval >0 lhs > rhs
  @retval 0 lhs == rhs
*/
A_PUBLIC a_int_t a_str_cmp(const a_str_s *lhs, const a_str_s *rhs);

/*!
 @brief resize memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] mem length of real memory
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_str_resize(a_str_s *ctx, a_size_t mem);
A_PUBLIC a_int_t a_str_resize_(a_str_s *ctx, a_size_t mem);

/*!
 @brief put character to an instance of string structure
 @param[in] ctx points to an instance of string structure
 @param[in] c character
 @return character
  @retval EOF failure
*/
A_PUBLIC a_int_t a_str_putc(a_str_s *ctx, a_int_t c);
A_PUBLIC a_int_t a_str_putc_(a_str_s *ctx, a_int_t c);

/*!
 @brief put data to an instance of string structure
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to data to put
 @param[in] nbyte length of data to put
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_str_putn(a_str_s *ctx, a_cptr_t pdata, a_size_t nbyte);
A_PUBLIC a_int_t a_str_putn_(a_str_s *ctx, a_cptr_t pdata, a_size_t nbyte);

/*!
 @brief put string to an instance of string structure
 @param[in] ctx points to an instance of string structure
 @param[in] str string terminated with a null character
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_PUBLIC a_int_t a_str_puts(a_str_s *ctx, a_cptr_t str);

/*!
 @brief print string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] fmt format of string to be printed
 @param[in] va instance of variable argument
 @return number of printed characters
  @retval EOF failure
*/
A_PUBLIC a_int_t a_str_vprintf(a_str_s *ctx, a_cstr_t fmt, va_list va) __attribute__((__format__(__printf__, 2, 0)));

/*!
 @brief print string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] fmt format of string to be printed
 @return number of printed characters
  @retval EOF failure
*/
A_PUBLIC a_int_t a_str_printf(a_str_s *ctx, a_cstr_t fmt, ...) __attribute__((__format__(__printf__, 2, 3)));

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_STR */

#endif /* __STDC_HOSTED__ */

#endif /* __A_HOST_STR_H__ */
