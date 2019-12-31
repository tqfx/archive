/*!
 @file tiger.h
 @brief tiger implementation
 @details https://www.cs.technion.ac.il/~biham/Reports/Tiger
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_TIGER_H__
#define __A_TIGER_H__

#include "../def.h"

#define A_TIGER_BUFSIZ 0x40
#define A_TIGER_OUTSIZ 24

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct a_tiger_s
{
    uint64_t __length;
    uint64_t __state[A_TIGER_OUTSIZ >> 3];
    unsigned char __buf[A_TIGER_BUFSIZ];
    unsigned char out[A_TIGER_OUTSIZ];
    uint32_t __cursiz;
} a_tiger_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_tiger_init(a_tiger_s *ctx);
A_PUBLIC int a_tiger_proc(a_tiger_s *ctx, const void *pdata, size_t nbyte);
A_PUBLIC unsigned char *a_tiger_done(a_tiger_s *ctx, void *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_TIGER_H__ */
