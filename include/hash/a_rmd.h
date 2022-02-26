/*!
 @file a_rmd.h
 @brief RIPEMD implementation
 @details https://homes.esat.kuleuven.be/~bosselae/ripemd160.html
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_RMD_H__
#define __A_HASH_RMD_H__

#include "liba.h"

#define A_RIPEMD_BUFSIZ    0x40
#define A_RIPEMD128_OUTSIZ (128 >> 3)
#define A_RIPEMD160_OUTSIZ (160 >> 3)
#define A_RIPEMD256_OUTSIZ (256 >> 3)
#define A_RIPEMD320_OUTSIZ (320 >> 3)

#undef __A_RMD_T
#define __A_RMD_T(bit)                      \
    typedef struct a_rmd##bit##_s           \
    {                                       \
        uint64_t length;                    \
        unsigned char buf[A_RIPEMD_BUFSIZ]; \
        unsigned char out[bit >> 3];        \
        uint32_t state[(bit >> 3) >> 2];    \
        uint32_t cursiz;                    \
    } a_rmd##bit##_s
#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* _MSC_VER */
__A_RMD_T(128);
__A_RMD_T(160);
__A_RMD_T(256);
__A_RMD_T(320);
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */
#undef __A_RMD_T

__BEGIN_DECLS

void a_rmd128_init(a_rmd128_s *ctx) __NONNULL_ALL;
int a_rmd128_process(a_rmd128_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));
unsigned char *a_rmd128_done(a_rmd128_s *ctx, void *out) __NONNULL((1));

void a_rmd160_init(a_rmd160_s *ctx) __NONNULL_ALL;
int a_rmd160_process(a_rmd160_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));
unsigned char *a_rmd160_done(a_rmd160_s *ctx, void *out) __NONNULL((1));

void a_rmd256_init(a_rmd256_s *ctx) __NONNULL_ALL;
int a_rmd256_process(a_rmd256_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));
unsigned char *a_rmd256_done(a_rmd256_s *ctx, void *out) __NONNULL((1));

void a_rmd320_init(a_rmd320_s *ctx) __NONNULL_ALL;
int a_rmd320_process(a_rmd320_s *ctx, const void *pdata, size_t nbyte) __NONNULL((1));
unsigned char *a_rmd320_done(a_rmd320_s *ctx, void *out) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_RMD_H__ */
