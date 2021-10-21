/*!
 @file           a_rmd.h
 @brief          RIPEMD implementation
 @details        https://homes.esat.kuleuven.be/~bosselae/ripemd160.html
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
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
    typedef struct a_rmd##bit##_t           \
    {                                       \
        uint64_t length;                    \
        unsigned char buf[A_RIPEMD_BUFSIZ]; \
        unsigned char out[bit >> 3];        \
        uint32_t state[(bit >> 3) >> 2];    \
        uint32_t cursiz;                    \
    } a_rmd##bit##_t
__A_RMD_T(128);
__A_RMD_T(160);
__A_RMD_T(256);
__A_RMD_T(320);
#undef __A_RMD_T

__BEGIN_DECLS

extern void a_rmd128_init(a_rmd128_t *ctx);
extern int a_rmd128_process(a_rmd128_t *ctx, const void *p, size_t n);
extern unsigned char *a_rmd128_done(a_rmd128_t *ctx, void *out);

extern void a_rmd160_init(a_rmd160_t *ctx);
extern int a_rmd160_process(a_rmd160_t *ctx, const void *p, size_t n);
extern unsigned char *a_rmd160_done(a_rmd160_t *ctx, void *out);

extern void a_rmd256_init(a_rmd256_t *ctx);
extern int a_rmd256_process(a_rmd256_t *ctx, const void *p, size_t n);
extern unsigned char *a_rmd256_done(a_rmd256_t *ctx, void *out);

extern void a_rmd320_init(a_rmd320_t *ctx);
extern int a_rmd320_process(a_rmd320_t *ctx, const void *p, size_t n);
extern unsigned char *a_rmd320_done(a_rmd320_t *ctx, void *out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_RMD_H__ */

/* END OF FILE */
