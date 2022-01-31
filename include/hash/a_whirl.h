/*!
 @file a_whirl.h
 @brief whirlpool implementation
 @details https://web.archive.org/web/20171129084214/http://www.larc.usp.br/~pbarreto/WhirlpoolPage.html
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_WHIRL_H__
#define __A_HASH_WHIRL_H__

#include "liba.h"

#define A_WHIRLPOOL_BUFSIZ 0x40
#define A_WHIRLPOOL_OUTSIZ 0x40

#pragma pack(push, 4)
typedef struct a_whirlpool_s
{
    uint64_t length;
    unsigned char buf[A_WHIRLPOOL_BUFSIZ];
    unsigned char out[A_WHIRLPOOL_OUTSIZ];
    uint64_t state[A_WHIRLPOOL_OUTSIZ >> 3];
    uint32_t cursiz;
} a_whirlpool_s;
#pragma pack(pop)

__BEGIN_DECLS

void a_whirlpool_init(a_whirlpool_s *ctx) __NONNULL_ALL;
int a_whirlpool_process(a_whirlpool_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));
unsigned char *a_whirlpool_done(a_whirlpool_s *ctx, void *out) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_WHIRL_H__ */
