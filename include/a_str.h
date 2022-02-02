/*!
 @file a_str.h
 @brief basic string library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_STR_H__
#define __A_STR_H__

#include "liba.h"

#include <stdlib.h> /* alloc */
#include <string.h> /* memcpy */
#include <stdarg.h> /* va_list */

/*!
 @brief Instance structure for string
*/
typedef struct a_str_s
{
    size_t m; /*!< memory */
    size_t n; /*!< length */
    char *s;  /*!< string */
} a_str_s;

#ifndef A_STR_INITS
/*!
 @brief Initialize an instance of string structure
 @return {.m = 0, .n = 0, .s = 0}
*/
#define A_STR_INITS() \
    {                 \
        0, 0, 0,      \
    }
#endif /* A_STR_INITS */

#ifndef A_STR_SFREE
/*!
 @brief Free an instance of string structure
*/
#define A_STR_SFREE(ctx) ( \
    (ctx).m = (ctx).n = 0, (ctx).s ? (free((ctx).s), (ctx).s = 0) : 0)
#endif /* A_STR_SFREE */

__NONNULL_ALL
__STATIC_INLINE
/*!
 @brief memory for a pointer to string structure
 @param[in] ctx: points to an instance of string structure
 @return size of memory
*/
size_t a_str_mem(const a_str_s *ctx)
{
    AASSERT(ctx);
    return ctx->m;
}

__NONNULL_ALL
__STATIC_INLINE
/*!
 @brief length for a pointer to string structure
 @param[in] ctx: points to an instance of string structure
 @return size of length
*/
size_t a_str_len(const a_str_s *ctx)
{
    AASSERT(ctx);
    return ctx->n;
}

__NONNULL_ALL
__STATIC_INLINE
/*!
 @brief string for a pointer to string structure
 @param[in] ctx: points to an instance of string structure
 @return string
*/
const char *a_str_val(const a_str_s *ctx)
{
    AASSERT(ctx);
    return ctx->s;
}

__BEGIN_DECLS

/*!
 @brief Allocate a pointer to string structure from memory
 @param[in] pdata: points to data to initialize
 @param[in] nbyte: length of data to initialize
 @return a_str_s *
*/
a_str_s *a_str_init(const void *pdata, size_t nbyte) __RESULT_USE_CHECK;

/*!
 @brief Free a pointer to string structure
 @param[in] ctx: points to an instance of string structure
*/
void a_str_free(a_str_s *ctx);

/*!
 @brief Terminate a pointer to string structure
 @param[in] ctx: points to an instance of string structure
 @return string of string structure
 @note You need to use free to release the memory
*/
char *a_str_done(a_str_s *ctx) __NONNULL_ALL __RESULT_USE_CHECK;

/*!
 @brief Resize memory for a pointer to string structure
 @param[in] ctx: points to an instance of string structure
 @param[in] m: length of real memory
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
int a_str_resize(a_str_s *ctx, size_t m) __NONNULL((1));
int a_str_resize_(a_str_s *ctx, size_t m) __NONNULL((1));

/*!
 @brief Put character to an instance of string structure
 @param[in] ctx: points to an instance of string structure
 @param[in] c: character
 @return character
  @retval -1 failure
*/
int a_str_putc(a_str_s *ctx, int c) __NONNULL((1));
int a_str_putc_(a_str_s *ctx, int c) __NONNULL((1));

/*!
 @brief Put data to an instance of string structure
 @param[in] ctx: points to an instance of string structure
 @param[in] pdata: points to data to put
 @param[in] nbyte: length of data to put
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
int a_str_putn(a_str_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));
int a_str_putn_(a_str_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));

/*!
 @brief Put string to an instance of string structure
 @param[in] ctx: points to an instance of string structure
 @param[in] str: string
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
int a_str_puts(a_str_s *ctx, const void *str) __NONNULL_ALL;

#if !defined(__ATTR_PRINTF) && __has_attribute(__format__)
#define __ATTR_PRINTF(fmt, arg) __attribute__((__format__(__printf__, fmt, arg)))
#else
#define __ATTR_PRINTF(fmt, arg)
#endif /* __ATTR_PRINTF */

/*!
 @brief Print string to a pointer to string structure
 @param[in] ctx: points to an instance of string structure
 @param[in] fmt: print format
 @param[in] va: va_list
 @return number of print
  @retval -1 failure
*/
int a_str_vprintf(a_str_s *ctx, const char *fmt, va_list va) __ATTR_PRINTF(2, 0);

/*!
 @brief Print string to a pointer to string structure
 @param[in] ctx: points to an instance of string structure
 @param[in] fmt: print format
 @return number of print
  @retval -1 failure
*/
int a_str_printf(a_str_s *ctx, const char *fmt, ...) __ATTR_PRINTF(2, 3);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_STR_H__ */
