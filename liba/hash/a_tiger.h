/*!
 @file           a_tiger.h
 @brief          TIGER implementation
 @details        https://www.cs.technion.ac.il/~biham/Reports/Tiger
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_TIGER_H__
#define __A_HASH_TIGER_H__

#include "liba.h"

#define A_TIGER_BUFSIZ 0x40
#define A_TIGER_OUTSIZ 24

typedef struct a_tiger_t
{
    uint64_t length;
    unsigned char buf[A_TIGER_BUFSIZ];
    unsigned char out[A_TIGER_OUTSIZ];
    uint64_t state[A_TIGER_OUTSIZ >> 3];
    uint32_t cursiz;
} a_tiger_t;

__BEGIN_DECLS

extern void a_tiger_init(a_tiger_t *ctx);
extern int a_tiger_process(a_tiger_t *ctx, const void *p, size_t n);
extern unsigned char *a_tiger_done(a_tiger_t *ctx, void *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_TIGER_H__ */

/* END OF FILE */
