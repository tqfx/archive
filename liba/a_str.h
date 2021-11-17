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

#if !defined(__ATTR_PRINTF) && __has_attribute(__format__)
#define __ATTR_PRINTF(_fmt, _arg) __attribute__((__format__(__printf__, _fmt, _arg)))
#else
#define __ATTR_PRINTF(_fmt, _arg)
#endif /* __ATTR_PRINTF */

/*!
 @brief Instance structure for c string
*/
typedef struct a_str_s
{
    size_t m; /*!< memory */
    size_t n; /*!< length */
    char *s;  /*!< string */
} a_str_s;

#ifndef a_str_inits
/*!
 @brief Initialize an instance of c string structure
 @return {.s = 0, .m = 0, .n = 0}
*/
#define a_str_inits() \
    {                 \
        0             \
    }
#endif /* a_str_inits */

#ifndef a_str_sfree
/*!
 @brief Free an instance of c string structure
*/
#define a_str_sfree(_ctx) ( \
    (_ctx).s ? (afree((_ctx).s), (_ctx).s = 0) : 0, (_ctx).m = (_ctx).n = 0)
#endif /* a_str_sfree */

__NONNULL_ALL
__STATIC_INLINE
/*!
 @brief string for a pointer to c string structure
 @param[in] _ctx: points to an instance of c string structure
 @return string
*/
const char *a_str_val(a_str_s *_ctx)
{
    aassert(_ctx);
    return _ctx->s;
}

__NONNULL_ALL
__STATIC_INLINE
/*!
 @brief length for a pointer to c string structure
 @param[in] _ctx: points to an instance of c string structure
 @return length
*/
size_t a_str_len(a_str_s *_ctx)
{
    aassert(_ctx);
    return _ctx->n;
}

__NONNULL_ALL
__STATIC_INLINE
/*!
 @brief memory for a pointer to c string structure
 @param[in] _ctx: points to an instance of c string structure
 @return memory
*/
size_t a_str_mem(a_str_s *_ctx)
{
    aassert(_ctx);
    return _ctx->m;
}

__BEGIN_DECLS

/*!
 @brief Allocate a pointer to c string structure from memory
 @param[in] p: points to data to initialize
 @param[in] n: length of data to initialize
 @return a_str_s *
*/
a_str_s *a_str_init(const void *p, size_t n) __RESULT_USE_CHECK;

/*!
 @brief Terminate a pointer to c string structure
 @param[in] ctx: points to an instance of c string structure
 @return string of c string structure
 @note You need to use @ref afree to release the memory
*/
char *a_str_done(a_str_s *ctx) __NONNULL_ALL __RESULT_USE_CHECK;

/*!
 @brief Free a pointer to c string structure
 @param[in] ctx: points to an instance of c string structure
*/
void a_str_free(a_str_s *ctx);

/*!
 @brief Resize memory for a pointer to c string structure
 @param[in] ctx: points to an instance of c string structure
 @param[in] m: length of real memory
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
int a_str_resize(a_str_s *ctx, size_t m) __NONNULL((1));
int a_str_resize_(a_str_s *ctx, size_t m) __NONNULL((1));

/*!
 @brief Put data to an instance of c string structure
 @param[in] ctx: points to an instance of c string structure
 @param[in] p: points to data to put
 @param[in] n: length of data to put
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
int a_str_putn(a_str_s *ctx, const void *p, size_t n) __NONNULL((1));
int a_str_putn_(a_str_s *ctx, const void *p, size_t n) __NONNULL((1));

/*!
 @brief Put string to an instance of c string structure
 @param[in] ctx: points to an instance of c string structure
 @param[in] s: c string
 @return the execution state of the function
  @retval -1 failure
  @retval 0 success
*/
int a_str_puts(a_str_s *ctx, const void *s) __NONNULL_ALL;

/*!
 @brief Put character to an instance of c string structure
 @param[in] ctx: points to an instance of c string structure
 @param[in] c: character
 @return character
  @retval -1 failure
*/
int a_str_putc(a_str_s *ctx, int c) __NONNULL((1));
int a_str_putc_(a_str_s *ctx, int c) __NONNULL((1));

/*!
 @brief Locate the cache
 @param[in] str: pointer of data
 @param[in] n: length of data
 @param[in] pat: pointer of search patterns
 @param[in] m: length of search patterns
 @param[in,out] prep: address of temporary patterns
  @arg 0 no external memory is used.
  @arg &(0) store patterns to external variables. You need to free memory.
  @arg &(p) use previous temporary patterns.
 @return address at the head of the block found
  @retval 0 failure
*/
void *a_memmem(const void *str, int n, const void *pat, int m, int **prep) __NONNULL((1, 3));

/*!
 @brief Locate the substring
 @param[in] str: pointer of string
 @param[in] pat: pointer of search patterns
 @param[in,out] prep: address of temporary patterns
  @arg 0 no external memory is used.
  @arg &(0) store patterns to external variables. You need to free memory.
  @arg &(p) use previous temporary patterns.
 @return address at the head of the block found
  @retval 0 failure
*/
char *a_strstr(const void *str, const void *pat, int **prep) __NONNULL((1, 2));

/*!
 @brief Locate the substring
 @param[in] str: pointer of string
 @param[in] n: length of string
 @param[in] pat: pointer of search patterns
 @param[in,out] prep: address of temporary patterns
  @arg 0 no external memory is used.
  @arg &(0) store patterns to external variables. You need to free memory.
  @arg &(p) use previous temporary patterns.
 @return address at the head of the block found
  @retval 0 failure
*/
char *a_strnstr(const void *str, int n, const void *pat, int **prep) __NONNULL((1, 3));

/*!
 @brief Print string to a pointer to c string structure
 @param[in] ctx: points to an instance of c string structure
 @param[in] fmt: print format
 @param[in] ap: va_list
 @return number of print
  @retval -1 failure
*/
int a_str_vprintf(a_str_s *ctx, const char *fmt, va_list ap) __ATTR_PRINTF(2, 0);

/*!
 @brief Print string to a pointer to c string structure
 @param[in] ctx: points to an instance of c string structure
 @param[in] fmt: print format
 @return number of print
  @retval -1 failure
*/
int a_str_printf(a_str_s *ctx, const char *fmt, ...) __ATTR_PRINTF(2, 3);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_STR_H__ */

/* END OF FILE */
