/*!
 @file rmd160.c
 @brief ripemd implementation
 @details https://homes.esat.kuleuven.be/~bosselae/ripemd160.html
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/cksum/rmd160.h"
#include "a/cksum/hash.h"
#include "hash__.h"

#undef F
#undef G
#undef H
#undef I
#undef J
/* the basic functions */
#define F(x, y, z) ((x) ^ (y) ^ (z))
#define G(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define H(x, y, z) (((x) | ~(y)) ^ (z))
#define I(x, y, z) (((x) & (z)) | ((y) & ~(z)))
#define J(x, y, z) ((x) ^ ((y) | ~(z)))

#undef FF
#undef GG
#undef HH
#undef II
#undef JJ
#undef FFF
#undef GGG
#undef HHH
#undef III
#undef JJJ
/* the ten basic operations FF() through III() */
#define FF(a, b, c, d, e, x, s)    \
    (a) += F((b), (c), (d)) + (x); \
    (a) = ROLc((a), (s)) + (e);    \
    (c) = ROLc((c), 10)
#define GG(a, b, c, d, e, x, s)                 \
    (a) += G((b), (c), (d)) + (x) + 0x5A827999; \
    (a) = ROLc((a), (s)) + (e);                 \
    (c) = ROLc((c), 10)
#define HH(a, b, c, d, e, x, s)                 \
    (a) += H((b), (c), (d)) + (x) + 0x6ED9EBA1; \
    (a) = ROLc((a), (s)) + (e);                 \
    (c) = ROLc((c), 10)
#define II(a, b, c, d, e, x, s)                 \
    (a) += I((b), (c), (d)) + (x) + 0x8F1BBCDC; \
    (a) = ROLc((a), (s)) + (e);                 \
    (c) = ROLc((c), 10)
#define JJ(a, b, c, d, e, x, s)                 \
    (a) += J((b), (c), (d)) + (x) + 0xA953FD4E; \
    (a) = ROLc((a), (s)) + (e);                 \
    (c) = ROLc((c), 10)
#define FFF(a, b, c, d, e, x, s)   \
    (a) += F((b), (c), (d)) + (x); \
    (a) = ROLc((a), (s)) + (e);    \
    (c) = ROLc((c), 10)
#define GGG(a, b, c, d, e, x, s)                \
    (a) += G((b), (c), (d)) + (x) + 0x7A6D76E9; \
    (a) = ROLc((a), (s)) + (e);                 \
    (c) = ROLc((c), 10)
#define HHH(a, b, c, d, e, x, s)                \
    (a) += H((b), (c), (d)) + (x) + 0x6D703EF3; \
    (a) = ROLc((a), (s)) + (e);                 \
    (c) = ROLc((c), 10)
#define III(a, b, c, d, e, x, s)                \
    (a) += I((b), (c), (d)) + (x) + 0x5C4DD124; \
    (a) = ROLc((a), (s)) + (e);                 \
    (c) = ROLc((c), 10)
#define JJJ(a, b, c, d, e, x, s)                \
    (a) += J((b), (c), (d)) + (x) + 0x50A28BE6; \
    (a) = ROLc((a), (s)) + (e);                 \
    (c) = ROLc((c), 10)

static void a_rmd160_compress(a_rmd160_s *ctx, const unsigned char *buf)
{
    uint32_t s[(sizeof(ctx->__state) / sizeof(*ctx->__state)) << 1];
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
        s[i] = s[i + ((sizeof(s) / sizeof(*s)) >> 1)] = ctx->__state[i];
    }

    /* round 1 */
    FF(s[0], s[1], s[2], s[3], s[4], x[0x0], 0xB);
    FF(s[4], s[0], s[1], s[2], s[3], x[0x1], 0xE);
    FF(s[3], s[4], s[0], s[1], s[2], x[0x2], 0xF);
    FF(s[2], s[3], s[4], s[0], s[1], x[0x3], 0xC);
    FF(s[1], s[2], s[3], s[4], s[0], x[0x4], 0x5);
    FF(s[0], s[1], s[2], s[3], s[4], x[0x5], 0x8);
    FF(s[4], s[0], s[1], s[2], s[3], x[0x6], 0x7);
    FF(s[3], s[4], s[0], s[1], s[2], x[0x7], 0x9);
    FF(s[2], s[3], s[4], s[0], s[1], x[0x8], 0xB);
    FF(s[1], s[2], s[3], s[4], s[0], x[0x9], 0xD);
    FF(s[0], s[1], s[2], s[3], s[4], x[0xA], 0xE);
    FF(s[4], s[0], s[1], s[2], s[3], x[0xB], 0xF);
    FF(s[3], s[4], s[0], s[1], s[2], x[0xC], 0x6);
    FF(s[2], s[3], s[4], s[0], s[1], x[0xD], 0x7);
    FF(s[1], s[2], s[3], s[4], s[0], x[0xE], 0x9);
    FF(s[0], s[1], s[2], s[3], s[4], x[0xF], 0x8);

    /* round 2 */
    GG(s[4], s[0], s[1], s[2], s[3], x[0x7], 0x7);
    GG(s[3], s[4], s[0], s[1], s[2], x[0x4], 0x6);
    GG(s[2], s[3], s[4], s[0], s[1], x[0xD], 0x8);
    GG(s[1], s[2], s[3], s[4], s[0], x[0x1], 0xD);
    GG(s[0], s[1], s[2], s[3], s[4], x[0xA], 0xB);
    GG(s[4], s[0], s[1], s[2], s[3], x[0x6], 0x9);
    GG(s[3], s[4], s[0], s[1], s[2], x[0xF], 0x7);
    GG(s[2], s[3], s[4], s[0], s[1], x[0x3], 0xF);
    GG(s[1], s[2], s[3], s[4], s[0], x[0xC], 0x7);
    GG(s[0], s[1], s[2], s[3], s[4], x[0x0], 0xC);
    GG(s[4], s[0], s[1], s[2], s[3], x[0x9], 0xF);
    GG(s[3], s[4], s[0], s[1], s[2], x[0x5], 0x9);
    GG(s[2], s[3], s[4], s[0], s[1], x[0x2], 0xB);
    GG(s[1], s[2], s[3], s[4], s[0], x[0xE], 0x7);
    GG(s[0], s[1], s[2], s[3], s[4], x[0xB], 0xD);
    GG(s[4], s[0], s[1], s[2], s[3], x[0x8], 0xC);

    /* round 3 */
    HH(s[3], s[4], s[0], s[1], s[2], x[0x3], 0xB);
    HH(s[2], s[3], s[4], s[0], s[1], x[0xA], 0xD);
    HH(s[1], s[2], s[3], s[4], s[0], x[0xE], 0x6);
    HH(s[0], s[1], s[2], s[3], s[4], x[0x4], 0x7);
    HH(s[4], s[0], s[1], s[2], s[3], x[0x9], 0xE);
    HH(s[3], s[4], s[0], s[1], s[2], x[0xF], 0x9);
    HH(s[2], s[3], s[4], s[0], s[1], x[0x8], 0xD);
    HH(s[1], s[2], s[3], s[4], s[0], x[0x1], 0xF);
    HH(s[0], s[1], s[2], s[3], s[4], x[0x2], 0xE);
    HH(s[4], s[0], s[1], s[2], s[3], x[0x7], 0x8);
    HH(s[3], s[4], s[0], s[1], s[2], x[0x0], 0xD);
    HH(s[2], s[3], s[4], s[0], s[1], x[0x6], 0x6);
    HH(s[1], s[2], s[3], s[4], s[0], x[0xD], 0x5);
    HH(s[0], s[1], s[2], s[3], s[4], x[0xB], 0xC);
    HH(s[4], s[0], s[1], s[2], s[3], x[0x5], 0x7);
    HH(s[3], s[4], s[0], s[1], s[2], x[0xC], 0x5);

    /* round 4 */
    II(s[2], s[3], s[4], s[0], s[1], x[0x1], 0xB);
    II(s[1], s[2], s[3], s[4], s[0], x[0x9], 0xC);
    II(s[0], s[1], s[2], s[3], s[4], x[0xB], 0xE);
    II(s[4], s[0], s[1], s[2], s[3], x[0xA], 0xF);
    II(s[3], s[4], s[0], s[1], s[2], x[0x0], 0xE);
    II(s[2], s[3], s[4], s[0], s[1], x[0x8], 0xF);
    II(s[1], s[2], s[3], s[4], s[0], x[0xC], 0x9);
    II(s[0], s[1], s[2], s[3], s[4], x[0x4], 0x8);
    II(s[4], s[0], s[1], s[2], s[3], x[0xD], 0x9);
    II(s[3], s[4], s[0], s[1], s[2], x[0x3], 0xE);
    II(s[2], s[3], s[4], s[0], s[1], x[0x7], 0x5);
    II(s[1], s[2], s[3], s[4], s[0], x[0xF], 0x6);
    II(s[0], s[1], s[2], s[3], s[4], x[0xE], 0x8);
    II(s[4], s[0], s[1], s[2], s[3], x[0x5], 0x6);
    II(s[3], s[4], s[0], s[1], s[2], x[0x6], 0x5);
    II(s[2], s[3], s[4], s[0], s[1], x[0x2], 0xC);

    /* round 5 */
    JJ(s[1], s[2], s[3], s[4], s[0], x[0x4], 0x9);
    JJ(s[0], s[1], s[2], s[3], s[4], x[0x0], 0xF);
    JJ(s[4], s[0], s[1], s[2], s[3], x[0x5], 0x5);
    JJ(s[3], s[4], s[0], s[1], s[2], x[0x9], 0xB);
    JJ(s[2], s[3], s[4], s[0], s[1], x[0x7], 0x6);
    JJ(s[1], s[2], s[3], s[4], s[0], x[0xC], 0x8);
    JJ(s[0], s[1], s[2], s[3], s[4], x[0x2], 0xD);
    JJ(s[4], s[0], s[1], s[2], s[3], x[0xA], 0xC);
    JJ(s[3], s[4], s[0], s[1], s[2], x[0xE], 0x5);
    JJ(s[2], s[3], s[4], s[0], s[1], x[0x1], 0xC);
    JJ(s[1], s[2], s[3], s[4], s[0], x[0x3], 0xD);
    JJ(s[0], s[1], s[2], s[3], s[4], x[0x8], 0xE);
    JJ(s[4], s[0], s[1], s[2], s[3], x[0xB], 0xB);
    JJ(s[3], s[4], s[0], s[1], s[2], x[0x6], 0x8);
    JJ(s[2], s[3], s[4], s[0], s[1], x[0xF], 0x5);
    JJ(s[1], s[2], s[3], s[4], s[0], x[0xD], 0x6);

    /* parallel round 1 */
    JJJ(s[5], s[6], s[7], s[8], s[9], x[0x5], 0x8);
    JJJ(s[9], s[5], s[6], s[7], s[8], x[0xE], 0x9);
    JJJ(s[8], s[9], s[5], s[6], s[7], x[0x7], 0x9);
    JJJ(s[7], s[8], s[9], s[5], s[6], x[0x0], 0xB);
    JJJ(s[6], s[7], s[8], s[9], s[5], x[0x9], 0xD);
    JJJ(s[5], s[6], s[7], s[8], s[9], x[0x2], 0xF);
    JJJ(s[9], s[5], s[6], s[7], s[8], x[0xB], 0xF);
    JJJ(s[8], s[9], s[5], s[6], s[7], x[0x4], 0x5);
    JJJ(s[7], s[8], s[9], s[5], s[6], x[0xD], 0x7);
    JJJ(s[6], s[7], s[8], s[9], s[5], x[0x6], 0x7);
    JJJ(s[5], s[6], s[7], s[8], s[9], x[0xF], 0x8);
    JJJ(s[9], s[5], s[6], s[7], s[8], x[0x8], 0xB);
    JJJ(s[8], s[9], s[5], s[6], s[7], x[0x1], 0xE);
    JJJ(s[7], s[8], s[9], s[5], s[6], x[0xA], 0xE);
    JJJ(s[6], s[7], s[8], s[9], s[5], x[0x3], 0xC);
    JJJ(s[5], s[6], s[7], s[8], s[9], x[0xC], 0x6);

    /* parallel round 2 */
    III(s[9], s[5], s[6], s[7], s[8], x[0x6], 0x9);
    III(s[8], s[9], s[5], s[6], s[7], x[0xB], 0xD);
    III(s[7], s[8], s[9], s[5], s[6], x[0x3], 0xF);
    III(s[6], s[7], s[8], s[9], s[5], x[0x7], 0x7);
    III(s[5], s[6], s[7], s[8], s[9], x[0x0], 0xC);
    III(s[9], s[5], s[6], s[7], s[8], x[0xD], 0x8);
    III(s[8], s[9], s[5], s[6], s[7], x[0x5], 0x9);
    III(s[7], s[8], s[9], s[5], s[6], x[0xA], 0xB);
    III(s[6], s[7], s[8], s[9], s[5], x[0xE], 0x7);
    III(s[5], s[6], s[7], s[8], s[9], x[0xF], 0x7);
    III(s[9], s[5], s[6], s[7], s[8], x[0x8], 0xC);
    III(s[8], s[9], s[5], s[6], s[7], x[0xC], 0x7);
    III(s[7], s[8], s[9], s[5], s[6], x[0x4], 0x6);
    III(s[6], s[7], s[8], s[9], s[5], x[0x9], 0xF);
    III(s[5], s[6], s[7], s[8], s[9], x[0x1], 0xD);
    III(s[9], s[5], s[6], s[7], s[8], x[0x2], 0xB);

    /* parallel round 3 */
    HHH(s[8], s[9], s[5], s[6], s[7], x[0xF], 0x9);
    HHH(s[7], s[8], s[9], s[5], s[6], x[0x5], 0x7);
    HHH(s[6], s[7], s[8], s[9], s[5], x[0x1], 0xF);
    HHH(s[5], s[6], s[7], s[8], s[9], x[0x3], 0xB);
    HHH(s[9], s[5], s[6], s[7], s[8], x[0x7], 0x8);
    HHH(s[8], s[9], s[5], s[6], s[7], x[0xE], 0x6);
    HHH(s[7], s[8], s[9], s[5], s[6], x[0x6], 0x6);
    HHH(s[6], s[7], s[8], s[9], s[5], x[0x9], 0xE);
    HHH(s[5], s[6], s[7], s[8], s[9], x[0xB], 0xC);
    HHH(s[9], s[5], s[6], s[7], s[8], x[0x8], 0xD);
    HHH(s[8], s[9], s[5], s[6], s[7], x[0xC], 0x5);
    HHH(s[7], s[8], s[9], s[5], s[6], x[0x2], 0xE);
    HHH(s[6], s[7], s[8], s[9], s[5], x[0xA], 0xD);
    HHH(s[5], s[6], s[7], s[8], s[9], x[0x0], 0xD);
    HHH(s[9], s[5], s[6], s[7], s[8], x[0x4], 0x7);
    HHH(s[8], s[9], s[5], s[6], s[7], x[0xD], 0x5);

    /* parallel round 4 */
    GGG(s[7], s[8], s[9], s[5], s[6], x[0x8], 0xF);
    GGG(s[6], s[7], s[8], s[9], s[5], x[0x6], 0x5);
    GGG(s[5], s[6], s[7], s[8], s[9], x[0x4], 0x8);
    GGG(s[9], s[5], s[6], s[7], s[8], x[0x1], 0xB);
    GGG(s[8], s[9], s[5], s[6], s[7], x[0x3], 0xE);
    GGG(s[7], s[8], s[9], s[5], s[6], x[0xB], 0xE);
    GGG(s[6], s[7], s[8], s[9], s[5], x[0xF], 0x6);
    GGG(s[5], s[6], s[7], s[8], s[9], x[0x0], 0xE);
    GGG(s[9], s[5], s[6], s[7], s[8], x[0x5], 0x6);
    GGG(s[8], s[9], s[5], s[6], s[7], x[0xC], 0x9);
    GGG(s[7], s[8], s[9], s[5], s[6], x[0x2], 0xC);
    GGG(s[6], s[7], s[8], s[9], s[5], x[0xD], 0x9);
    GGG(s[5], s[6], s[7], s[8], s[9], x[0x9], 0xC);
    GGG(s[9], s[5], s[6], s[7], s[8], x[0x7], 0x5);
    GGG(s[8], s[9], s[5], s[6], s[7], x[0xA], 0xF);
    GGG(s[7], s[8], s[9], s[5], s[6], x[0xE], 0x8);

    /* parallel round 5 */
    FFF(s[6], s[7], s[8], s[9], s[5], x[0xC], 0x8);
    FFF(s[5], s[6], s[7], s[8], s[9], x[0xF], 0x5);
    FFF(s[9], s[5], s[6], s[7], s[8], x[0xA], 0xC);
    FFF(s[8], s[9], s[5], s[6], s[7], x[0x4], 0x9);
    FFF(s[7], s[8], s[9], s[5], s[6], x[0x1], 0xC);
    FFF(s[6], s[7], s[8], s[9], s[5], x[0x5], 0x5);
    FFF(s[5], s[6], s[7], s[8], s[9], x[0x8], 0xE);
    FFF(s[9], s[5], s[6], s[7], s[8], x[0x7], 0x6);
    FFF(s[8], s[9], s[5], s[6], s[7], x[0x6], 0x8);
    FFF(s[7], s[8], s[9], s[5], s[6], x[0x2], 0xD);
    FFF(s[6], s[7], s[8], s[9], s[5], x[0xD], 0x6);
    FFF(s[5], s[6], s[7], s[8], s[9], x[0xE], 0x5);
    FFF(s[9], s[5], s[6], s[7], s[8], x[0x0], 0xF);
    FFF(s[8], s[9], s[5], s[6], s[7], x[0x3], 0xD);
    FFF(s[7], s[8], s[9], s[5], s[6], x[0x9], 0xB);
    FFF(s[6], s[7], s[8], s[9], s[5], x[0xB], 0xB);

    /* combine results */
    s[8] += s[2] + ctx->__state[0x1];
    ctx->__state[0x1] = ctx->__state[0x2] + s[3] + s[9];
    ctx->__state[0x2] = ctx->__state[0x3] + s[4] + s[5];
    ctx->__state[0x3] = ctx->__state[0x4] + s[0] + s[6];
    ctx->__state[0x4] = ctx->__state[0x0] + s[1] + s[7];
    ctx->__state[0x0] = s[8];
}

#undef JJJ
#undef III
#undef HHH
#undef GGG
#undef FFF
#undef JJ
#undef II
#undef HH
#undef GG
#undef FF
#undef J
#undef I
#undef H
#undef J
#undef F

void a_rmd160_init(a_rmd160_s *ctx)
{
    assert(ctx);

    ctx->__cursiz = 0;
    ctx->__length = 0;

    ctx->__state[0] = 0x67452301;
    ctx->__state[1] = 0xEFCDAB89; // 0x10325476 ^ 0xFFFFFFFF
    ctx->__state[2] = 0x98BADCFE; // 0x67452301 ^ 0xFFFFFFFF
    ctx->__state[3] = 0x10325476;
    ctx->__state[4] = 0xC3D2E1F0;
}

A_HASH_PROC(a_rmd160_s, a_rmd160_proc, a_rmd160_compress)

A_HASH_DONE(a_rmd160_s, a_rmd160_done, a_rmd160_compress, STORE64L, STORE32L, 0x80, 0x38, 0x38)
