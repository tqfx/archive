/*!
 @file mean.h
 @brief mean calculation
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_MEAN_H__
#define __A_MEAN_H__

#include "../def.h"
#include "../real.h"

typedef enum a_mean_e
{
    A_MEAN_ARITHMETIC, //!< arithmetic mean
    A_MEAN_GEOMETRIC,  //!< geometric mean
    A_MEAN_HARMONIC,   //!< harmonic mean
    A_MEAN_SQUARE,     //!< square mean
} a_mean_e;

#pragma pack(push)
#pragma pack(4)
typedef struct a_mean_s
{
    size_t num;
    a_real_t out;
    uint32_t mode;
} a_mean_s;
#pragma pack(pop)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC void a_mean_init(a_mean_s *ctx, unsigned int mode);
A_PUBLIC void a_mean_proc(a_mean_s *ctx, const a_real_t *dat, size_t num);
A_PUBLIC a_real_t a_mean_done(a_mean_s *ctx);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_MEAN_H__ */
