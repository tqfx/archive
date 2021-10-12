/*!
 @file           a_base.h
 @brief          RFC 4648 compliant base implementation
 @details        https://www.ietf.org/rfc/rfc4648.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_BASE_H__
#define __A_BASE_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

enum
{
    A_BASE_SUCCESS = 0,
    A_BASE_FAILURE = -1,
    A_BASE_INVALID = -2,
    A_BASE_OVERFLOW = -3,
};

enum
{
    A_BASE32_RFC4648 = 0,
    A_BASE32_BASE32HEX = 1,
    A_BASE32_ZBASE32 = 2,
    A_BASE32_CROCKFORD = 3,
    A_BASE32_BUFSIZ = 4,
};

__BEGIN_DECLS

extern int a_base16_encode(const void *p, size_t n, void *out, size_t *siz, unsigned int id);
extern int a_base16_decode(const void *p, size_t n, void *out, size_t *siz);

extern int a_base32_encode(const void *p, size_t n, void *out, size_t *siz, unsigned int id);
extern int a_base32_decode(const void *p, size_t n, void *out, size_t *siz, unsigned int id);

extern int a_base64_encode(const void *p, size_t n, void *out, size_t *siz);
extern int a_base64_decode(const void *p, size_t n, void *out, size_t *siz);
extern int a_base64_decode_strict(const void *p, size_t n, void *out, size_t *siz);
extern int a_base64_decode_sane(const void *p, size_t n, void *out, size_t *siz);

extern int a_base64url_encode(const void *p, size_t n, void *out, size_t *siz);
extern int a_base64url_decode(const void *p, size_t n, void *out, size_t *siz);
extern int a_base64url_encode_strict(const void *p, size_t n, void *out, size_t *siz);
extern int a_base64url_decode_strict(const void *p, size_t n, void *out, size_t *siz);
extern int a_base64url_decode_sane(const void *p, size_t n, void *out, size_t *siz);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_BASE_H__ */

/* END OF FILE */
