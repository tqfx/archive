/*!
 @file a_tiger.h
 @brief tiger implementation
 @details https://www.cs.technion.ac.il/~biham/Reports/Tiger
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_TIGER_H__
#define __A_HASH_TIGER_H__

#include "liba.h"

#define A_TIGER_BUFSIZ 0x40
#define A_TIGER_OUTSIZ 24

#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* _MSC_VER */
typedef struct a_tiger_s
{
    uint64_t length;
    unsigned char buf[A_TIGER_BUFSIZ];
    unsigned char out[A_TIGER_OUTSIZ];
    uint64_t state[A_TIGER_OUTSIZ >> 3];
    uint32_t cursiz;
} a_tiger_s;
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

__BEGIN_DECLS

void a_tiger_init(a_tiger_s *ctx) __NONNULL_ALL;
int a_tiger_process(a_tiger_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));
unsigned char *a_tiger_done(a_tiger_s *ctx, void *out) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_TIGER_H__ */
