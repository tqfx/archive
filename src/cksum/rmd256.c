/*!
 @file rmd256.c
 @brief ripemd implementation
 @details https://homes.esat.kuleuven.be/~bosselae/ripemd160.html
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/cksum/rmd256.h"
#include "a/cksum/hash.h"
#include "hash__.h"

#undef F
#undef G
#undef H
#undef I
/* the basic functions */
#define F(x, y, z) ((x) ^ (y) ^ (z))
#define G(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define H(x, y, z) (((x) | ~(y)) ^ (z))
#define I(x, y, z) (((x) & (z)) | ((y) & ~(z)))

#undef FF
#undef GG
#undef HH
#undef II
#undef FFF
#undef GGG
#undef HHH
#undef III
/* the eight basic operations FF() through III() */
#define FF(a, b, c, d, x, s)       \
    (a) += F((b), (c), (d)) + (x); \
    (a) = ROLc((a), (s))
#define GG(a, b, c, d, x, s)                    \
    (a) += G((b), (c), (d)) + (x) + 0x5A827999; \
    (a) = ROLc((a), (s))
#define HH(a, b, c, d, x, s)                    \
    (a) += H((b), (c), (d)) + (x) + 0x6ED9EBA1; \
    (a) = ROLc((a), (s))
#define II(a, b, c, d, x, s)                    \
    (a) += I((b), (c), (d)) + (x) + 0x8F1BBCDC; \
    (a) = ROLc((a), (s))
#define FFF(a, b, c, d, x, s)      \
    (a) += F((b), (c), (d)) + (x); \
    (a) = ROLc((a), (s))
#define GGG(a, b, c, d, x, s)                   \
    (a) += G((b), (c), (d)) + (x) + 0x6D703EF3; \
    (a) = ROLc((a), (s))
#define HHH(a, b, c, d, x, s)                   \
    (a) += H((b), (c), (d)) + (x) + 0x5C4DD124; \
    (a) = ROLc((a), (s))
#define III(a, b, c, d, x, s)                   \
    (a) += I((b), (c), (d)) + (x) + 0x50A28BE6; \
    (a) = ROLc((a), (s))

static void a_rmd256_compress(a_rmd256_s *ctx, const unsigned char *buf)
{
    uint32_t s[sizeof(ctx->__state) / sizeof(*ctx->__state)];
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-align"
#endif /* __GNUC__ || __clang__ */
    uint32_t *x = (uint32_t *)ctx->__buf;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */
    if (ctx->__buf != buf)
    {
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD32L(x[i], buf + sizeof(*ctx->__state) * i);
        }
    }

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(ctx->__state) / sizeof(*ctx->__state); ++i)
    {
        s[i] = ctx->__state[i];
    }

#undef SWAP
#define SWAP(t, x, y) (t = x, x = y, y = t)
    /* compress */
    uint32_t t;

    /* round 1 */
    FF(s[0], s[1], s[2], s[3], x[0x0], 0xB);
    FF(s[3], s[0], s[1], s[2], x[0x1], 0xE);
    FF(s[2], s[3], s[0], s[1], x[0x2], 0xF);
    FF(s[1], s[2], s[3], s[0], x[0x3], 0xC);
    FF(s[0], s[1], s[2], s[3], x[0x4], 0x5);
    FF(s[3], s[0], s[1], s[2], x[0x5], 0x8);
    FF(s[2], s[3], s[0], s[1], x[0x6], 0x7);
    FF(s[1], s[2], s[3], s[0], x[0x7], 0x9);
    FF(s[0], s[1], s[2], s[3], x[0x8], 0xB);
    FF(s[3], s[0], s[1], s[2], x[0x9], 0xD);
    FF(s[2], s[3], s[0], s[1], x[0xA], 0xE);
    FF(s[1], s[2], s[3], s[0], x[0xB], 0xF);
    FF(s[0], s[1], s[2], s[3], x[0xC], 0x6);
    FF(s[3], s[0], s[1], s[2], x[0xD], 0x7);
    FF(s[2], s[3], s[0], s[1], x[0xE], 0x9);
    FF(s[1], s[2], s[3], s[0], x[0xF], 0x8);

    /* parallel round 1 */
    III(s[4], s[5], s[6], s[7], x[0x5], 0x8);
    III(s[7], s[4], s[5], s[6], x[0xE], 0x9);
    III(s[6], s[7], s[4], s[5], x[0x7], 0x9);
    III(s[5], s[6], s[7], s[4], x[0x0], 0xB);
    III(s[4], s[5], s[6], s[7], x[0x9], 0xD);
    III(s[7], s[4], s[5], s[6], x[0x2], 0xF);
    III(s[6], s[7], s[4], s[5], x[0xB], 0xF);
    III(s[5], s[6], s[7], s[4], x[0x4], 0x5);
    III(s[4], s[5], s[6], s[7], x[0xD], 0x7);
    III(s[7], s[4], s[5], s[6], x[0x6], 0x7);
    III(s[6], s[7], s[4], s[5], x[0xF], 0x8);
    III(s[5], s[6], s[7], s[4], x[0x8], 0xB);
    III(s[4], s[5], s[6], s[7], x[0x1], 0xE);
    III(s[7], s[4], s[5], s[6], x[0xA], 0xE);
    III(s[6], s[7], s[4], s[5], x[0x3], 0xC);
    III(s[5], s[6], s[7], s[4], x[0xC], 0x6);

    SWAP(t, s[0], s[0 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* round 2 */
    GG(s[0], s[1], s[2], s[3], x[0x7], 0x7);
    GG(s[3], s[0], s[1], s[2], x[0x4], 0x6);
    GG(s[2], s[3], s[0], s[1], x[0xD], 0x8);
    GG(s[1], s[2], s[3], s[0], x[0x1], 0xD);
    GG(s[0], s[1], s[2], s[3], x[0xA], 0xB);
    GG(s[3], s[0], s[1], s[2], x[0x6], 0x9);
    GG(s[2], s[3], s[0], s[1], x[0xF], 0x7);
    GG(s[1], s[2], s[3], s[0], x[0x3], 0xF);
    GG(s[0], s[1], s[2], s[3], x[0xC], 0x7);
    GG(s[3], s[0], s[1], s[2], x[0x0], 0xC);
    GG(s[2], s[3], s[0], s[1], x[0x9], 0xF);
    GG(s[1], s[2], s[3], s[0], x[0x5], 0x9);
    GG(s[0], s[1], s[2], s[3], x[0x2], 0xB);
    GG(s[3], s[0], s[1], s[2], x[0xE], 0x7);
    GG(s[2], s[3], s[0], s[1], x[0xB], 0xD);
    GG(s[1], s[2], s[3], s[0], x[0x8], 0xC);

    /* parallel round 2 */
    HHH(s[4], s[5], s[6], s[7], x[0x6], 0x9);
    HHH(s[7], s[4], s[5], s[6], x[0xB], 0xD);
    HHH(s[6], s[7], s[4], s[5], x[0x3], 0xF);
    HHH(s[5], s[6], s[7], s[4], x[0x7], 0x7);
    HHH(s[4], s[5], s[6], s[7], x[0x0], 0xC);
    HHH(s[7], s[4], s[5], s[6], x[0xD], 0x8);
    HHH(s[6], s[7], s[4], s[5], x[0x5], 0x9);
    HHH(s[5], s[6], s[7], s[4], x[0xA], 0xB);
    HHH(s[4], s[5], s[6], s[7], x[0xE], 0x7);
    HHH(s[7], s[4], s[5], s[6], x[0xF], 0x7);
    HHH(s[6], s[7], s[4], s[5], x[0x8], 0xC);
    HHH(s[5], s[6], s[7], s[4], x[0xC], 0x7);
    HHH(s[4], s[5], s[6], s[7], x[0x4], 0x6);
    HHH(s[7], s[4], s[5], s[6], x[0x9], 0xF);
    HHH(s[6], s[7], s[4], s[5], x[0x1], 0xD);
    HHH(s[5], s[6], s[7], s[4], x[0x2], 0xB);

    SWAP(t, s[1], s[1 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* round 3 */
    HH(s[0], s[1], s[2], s[3], x[0x3], 0xB);
    HH(s[3], s[0], s[1], s[2], x[0xA], 0xD);
    HH(s[2], s[3], s[0], s[1], x[0xE], 0x6);
    HH(s[1], s[2], s[3], s[0], x[0x4], 0x7);
    HH(s[0], s[1], s[2], s[3], x[0x9], 0xE);
    HH(s[3], s[0], s[1], s[2], x[0xF], 0x9);
    HH(s[2], s[3], s[0], s[1], x[0x8], 0xD);
    HH(s[1], s[2], s[3], s[0], x[0x1], 0xF);
    HH(s[0], s[1], s[2], s[3], x[0x2], 0xE);
    HH(s[3], s[0], s[1], s[2], x[0x7], 0x8);
    HH(s[2], s[3], s[0], s[1], x[0x0], 0xD);
    HH(s[1], s[2], s[3], s[0], x[0x6], 0x6);
    HH(s[0], s[1], s[2], s[3], x[0xD], 0x5);
    HH(s[3], s[0], s[1], s[2], x[0xB], 0xC);
    HH(s[2], s[3], s[0], s[1], x[0x5], 0x7);
    HH(s[1], s[2], s[3], s[0], x[0xC], 0x5);

    /* parallel round 3 */
    GGG(s[4], s[5], s[6], s[7], x[0xF], 0x9);
    GGG(s[7], s[4], s[5], s[6], x[0x5], 0x7);
    GGG(s[6], s[7], s[4], s[5], x[0x1], 0xF);
    GGG(s[5], s[6], s[7], s[4], x[0x3], 0xB);
    GGG(s[4], s[5], s[6], s[7], x[0x7], 0x8);
    GGG(s[7], s[4], s[5], s[6], x[0xE], 0x6);
    GGG(s[6], s[7], s[4], s[5], x[0x6], 0x6);
    GGG(s[5], s[6], s[7], s[4], x[0x9], 0xE);
    GGG(s[4], s[5], s[6], s[7], x[0xB], 0xC);
    GGG(s[7], s[4], s[5], s[6], x[0x8], 0xD);
    GGG(s[6], s[7], s[4], s[5], x[0xC], 0x5);
    GGG(s[5], s[6], s[7], s[4], x[0x2], 0xE);
    GGG(s[4], s[5], s[6], s[7], x[0xA], 0xD);
    GGG(s[7], s[4], s[5], s[6], x[0x0], 0xD);
    GGG(s[6], s[7], s[4], s[5], x[0x4], 0x7);
    GGG(s[5], s[6], s[7], s[4], x[0xD], 0x5);

    SWAP(t, s[2], s[2 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* round 4 */
    II(s[0], s[1], s[2], s[3], x[0x1], 0xB);
    II(s[3], s[0], s[1], s[2], x[0x9], 0xC);
    II(s[2], s[3], s[0], s[1], x[0xB], 0xE);
    II(s[1], s[2], s[3], s[0], x[0xA], 0xF);
    II(s[0], s[1], s[2], s[3], x[0x0], 0xE);
    II(s[3], s[0], s[1], s[2], x[0x8], 0xF);
    II(s[2], s[3], s[0], s[1], x[0xC], 0x9);
    II(s[1], s[2], s[3], s[0], x[0x4], 0x8);
    II(s[0], s[1], s[2], s[3], x[0xD], 0x9);
    II(s[3], s[0], s[1], s[2], x[0x3], 0xE);
    II(s[2], s[3], s[0], s[1], x[0x7], 0x5);
    II(s[1], s[2], s[3], s[0], x[0xF], 0x6);
    II(s[0], s[1], s[2], s[3], x[0xE], 0x8);
    II(s[3], s[0], s[1], s[2], x[0x5], 0x6);
    II(s[2], s[3], s[0], s[1], x[0x6], 0x5);
    II(s[1], s[2], s[3], s[0], x[0x2], 0xC);

    /* parallel round 4 */
    FFF(s[4], s[5], s[6], s[7], x[0x8], 0xF);
    FFF(s[7], s[4], s[5], s[6], x[0x6], 0x5);
    FFF(s[6], s[7], s[4], s[5], x[0x4], 0x8);
    FFF(s[5], s[6], s[7], s[4], x[0x1], 0xB);
    FFF(s[4], s[5], s[6], s[7], x[0x3], 0xE);
    FFF(s[7], s[4], s[5], s[6], x[0xB], 0xE);
    FFF(s[6], s[7], s[4], s[5], x[0xF], 0x6);
    FFF(s[5], s[6], s[7], s[4], x[0x0], 0xE);
    FFF(s[4], s[5], s[6], s[7], x[0x5], 0x6);
    FFF(s[7], s[4], s[5], s[6], x[0xC], 0x9);
    FFF(s[6], s[7], s[4], s[5], x[0x2], 0xC);
    FFF(s[5], s[6], s[7], s[4], x[0xD], 0x9);
    FFF(s[4], s[5], s[6], s[7], x[0x9], 0xC);
    FFF(s[7], s[4], s[5], s[6], x[0x7], 0x5);
    FFF(s[6], s[7], s[4], s[5], x[0xA], 0xF);
    FFF(s[5], s[6], s[7], s[4], x[0xE], 0x8);

    SWAP(t, s[3], s[3 + ((sizeof(s) / sizeof(*s)) >> 1)]);
#undef SWAP

    /* feedback */
    for (unsigned int i = 0; i != sizeof(ctx->__state) / sizeof(*ctx->__state); ++i)
    {
        ctx->__state[i] += s[i];
    }
}

#undef III
#undef HHH
#undef GGG
#undef FFF
#undef II
#undef HH
#undef GG
#undef FF
#undef I
#undef H
#undef J
#undef F

void a_rmd256_init(a_rmd256_s *ctx)
{
    assert(ctx);

    ctx->__cursiz = 0;
    ctx->__length = 0;

    ctx->__state[0] = 0x67452301;
    ctx->__state[1] = 0xEFCDAB89; // 0x10325476 ^ 0xFFFFFFFF
    ctx->__state[2] = 0x98BADCFE; // 0x67452301 ^ 0xFFFFFFFF
    ctx->__state[3] = 0x10325476;
    ctx->__state[4] = 0x76543210;
    ctx->__state[5] = 0xFEDCBA98; // 0x01234567 ^ 0xFFFFFFFF
    ctx->__state[6] = 0x89ABCDEF; // 0x76543210 ^ 0xFFFFFFFF
    ctx->__state[7] = 0x01234567;
}

A_HASH_PROC(a_rmd256_s, a_rmd256_proc, a_rmd256_compress)

A_HASH_DONE(a_rmd256_s, a_rmd256_done, a_rmd256_compress, STORE64L, STORE32L, 0x80, 0x38, 0x38)
