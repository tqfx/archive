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
#define __A_RMD_T(_bit)                     \
    typedef struct a_rmd##_bit##_s          \
    {                                       \
        uint64_t length;                    \
        unsigned char buf[A_RIPEMD_BUFSIZ]; \
        unsigned char out[_bit >> 3];       \
        uint32_t state[(_bit >> 3) >> 2];   \
        uint32_t cursiz;                    \
    } a_rmd##_bit##_s
#pragma pack(push, 4)
__A_RMD_T(128);
__A_RMD_T(160);
__A_RMD_T(256);
__A_RMD_T(320);
#pragma pack(pop)
#undef __A_RMD_T

__BEGIN_DECLS

extern void a_rmd128_init(a_rmd128_s *ctx) __NONNULL_ALL;
extern int a_rmd128_process(a_rmd128_s *ctx, const void *p, size_t n) __NONNULL((1));
extern unsigned char *a_rmd128_done(a_rmd128_s *ctx, void *out) __NONNULL((1));

extern void a_rmd160_init(a_rmd160_s *ctx) __NONNULL_ALL;
extern int a_rmd160_process(a_rmd160_s *ctx, const void *p, size_t n) __NONNULL((1));
extern unsigned char *a_rmd160_done(a_rmd160_s *ctx, void *out) __NONNULL((1));

extern void a_rmd256_init(a_rmd256_s *ctx) __NONNULL_ALL;
extern int a_rmd256_process(a_rmd256_s *ctx, const void *p, size_t n) __NONNULL((1));
extern unsigned char *a_rmd256_done(a_rmd256_s *ctx, void *out) __NONNULL((1));

extern void a_rmd320_init(a_rmd320_s *ctx) __NONNULL_ALL;
extern int a_rmd320_process(a_rmd320_s *ctx, const void *p, size_t n) __NONNULL((1));
extern unsigned char *a_rmd320_done(a_rmd320_s *ctx, void *out) __NONNULL((1));

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_RMD_H__ */

/* END OF FILE */
