/*!
 @file           a_whirl.h
 @brief          WHIRLPOOL implementation
 @details        https://web.archive.org/web/20171129084214/http://www.larc.usp.br/~pbarreto/WhirlpoolPage.html
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_WHIRL_H__
#define __A_HASH_WHIRL_H__

#include "liba.h"

#define A_WHIRLPOOL_BUFSIZ 0x40
#define A_WHIRLPOOL_OUTSIZ 0x40

typedef struct a_whirlpool_t
{
    uint64_t length;
    unsigned char buf[A_WHIRLPOOL_BUFSIZ];
    unsigned char out[A_WHIRLPOOL_OUTSIZ];
    uint64_t state[A_WHIRLPOOL_OUTSIZ >> 3];
    uint32_t cursiz;
} a_whirlpool_t;

__BEGIN_DECLS

extern void a_whirlpool_init(a_whirlpool_t *ctx);
extern int a_whirlpool_process(a_whirlpool_t *ctx, const void *p, size_t n);
extern unsigned char *a_whirlpool_done(a_whirlpool_t *ctx, void *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_WHIRL_H__ */

/* END OF FILE */
