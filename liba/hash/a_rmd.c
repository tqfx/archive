/*!
 @file           a_rmd.c
 @brief          RIPEMD implementation
 @details        https://homes.esat.kuleuven.be/~bosselae/ripemd160.html
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_rmd.h"

#include "a_hash.h"

#undef F
#undef G
#undef H
#undef I
#undef J
/* the four basic functions F(), G() and H() */
#define F(_x, _y, _z) ((_x) ^ (_y) ^ (_z))
#define G(_x, _y, _z) (((_x) & (_y)) | (~(_x) & (_z)))
#define H(_x, _y, _z) (((_x) | ~(_y)) ^ (_z))
#define I(_x, _y, _z) (((_x) & (_z)) | ((_y) & ~(_z)))
#define J(_x, _y, _z) ((_x) ^ ((_y) | ~(_z)))

#undef SWAP
#define SWAP(_x, _y) (t = _x, _x = _y, _y = t)

#undef FF
#undef FFF
#undef GG
#undef GGG
#undef HH
#undef HHH
#undef II
#undef III
/* the eight basic operations FF() through III() */
#define FF(_a, _b, _c, _d, _x, _s)      \
    (_a) += F((_b), (_c), (_d)) + (_x); \
    (_a) = ROLc((_a), (_s));
#define GG(_a, _b, _c, _d, _x, _s)                   \
    (_a) += G((_b), (_c), (_d)) + (_x) + 0x5A827999; \
    (_a) = ROLc((_a), (_s));
#define HH(_a, _b, _c, _d, _x, _s)                   \
    (_a) += H((_b), (_c), (_d)) + (_x) + 0x6ED9EBA1; \
    (_a) = ROLc((_a), (_s));
#define II(_a, _b, _c, _d, _x, _s)                   \
    (_a) += I((_b), (_c), (_d)) + (_x) + 0x8F1BBCDC; \
    (_a) = ROLc((_a), (_s));
#define FFF(_a, _b, _c, _d, _x, _s)     \
    (_a) += F((_b), (_c), (_d)) + (_x); \
    (_a) = ROLc((_a), (_s));
#define GGG(_a, _b, _c, _d, _x, _s)                  \
    (_a) += G((_b), (_c), (_d)) + (_x) + 0x6D703EF3; \
    (_a) = ROLc((_a), (_s));
#define HHH(_a, _b, _c, _d, _x, _s)                  \
    (_a) += H((_b), (_c), (_d)) + (_x) + 0x5C4DD124; \
    (_a) = ROLc((_a), (_s));
#define III(_a, _b, _c, _d, _x, _s)                  \
    (_a) += I((_b), (_c), (_d)) + (_x) + 0x50A28BE6; \
    (_a) = ROLc((_a), (_s));

static void a_rmd128_compress(a_rmd128_t *_ctx, const unsigned char *_buf)
{
    uint32_t s[(sizeof(_ctx->state) / sizeof(*_ctx->state)) << 1];

    /* (unsigned char *) -> (uint32_t *) */
    union
    {
        uint32_t *x;
        unsigned char *buf;
    } up[1];
    up->buf = _ctx->buf;
    if (_ctx->buf != _buf)
    {
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD32L(up->x[i], _buf + sizeof(*_ctx->state) * i);
        }
    }

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        s[i] = s[i + ((sizeof(s) / sizeof(*s)) >> 1)] = _ctx->state[i];
    }

    /* round 1 */
    FF(s[0], s[1], s[2], s[3], up->x[0x0], 0xB);
    FF(s[3], s[0], s[1], s[2], up->x[0x1], 0xE);
    FF(s[2], s[3], s[0], s[1], up->x[0x2], 0xF);
    FF(s[1], s[2], s[3], s[0], up->x[0x3], 0xC);
    FF(s[0], s[1], s[2], s[3], up->x[0x4], 0x5);
    FF(s[3], s[0], s[1], s[2], up->x[0x5], 0x8);
    FF(s[2], s[3], s[0], s[1], up->x[0x6], 0x7);
    FF(s[1], s[2], s[3], s[0], up->x[0x7], 0x9);
    FF(s[0], s[1], s[2], s[3], up->x[0x8], 0xB);
    FF(s[3], s[0], s[1], s[2], up->x[0x9], 0xD);
    FF(s[2], s[3], s[0], s[1], up->x[0xA], 0xE);
    FF(s[1], s[2], s[3], s[0], up->x[0xB], 0xF);
    FF(s[0], s[1], s[2], s[3], up->x[0xC], 0x6);
    FF(s[3], s[0], s[1], s[2], up->x[0xD], 0x7);
    FF(s[2], s[3], s[0], s[1], up->x[0xE], 0x9);
    FF(s[1], s[2], s[3], s[0], up->x[0xF], 0x8);

    /* round 2 */
    GG(s[0], s[1], s[2], s[3], up->x[0x7], 0x7);
    GG(s[3], s[0], s[1], s[2], up->x[0x4], 0x6);
    GG(s[2], s[3], s[0], s[1], up->x[0xD], 0x8);
    GG(s[1], s[2], s[3], s[0], up->x[0x1], 0xD);
    GG(s[0], s[1], s[2], s[3], up->x[0xA], 0xB);
    GG(s[3], s[0], s[1], s[2], up->x[0x6], 0x9);
    GG(s[2], s[3], s[0], s[1], up->x[0xF], 0x7);
    GG(s[1], s[2], s[3], s[0], up->x[0x3], 0xF);
    GG(s[0], s[1], s[2], s[3], up->x[0xC], 0x7);
    GG(s[3], s[0], s[1], s[2], up->x[0x0], 0xC);
    GG(s[2], s[3], s[0], s[1], up->x[0x9], 0xF);
    GG(s[1], s[2], s[3], s[0], up->x[0x5], 0x9);
    GG(s[0], s[1], s[2], s[3], up->x[0x2], 0xB);
    GG(s[3], s[0], s[1], s[2], up->x[0xE], 0x7);
    GG(s[2], s[3], s[0], s[1], up->x[0xB], 0xD);
    GG(s[1], s[2], s[3], s[0], up->x[0x8], 0xC);

    /* round 3 */
    HH(s[0], s[1], s[2], s[3], up->x[0x3], 0xB);
    HH(s[3], s[0], s[1], s[2], up->x[0xA], 0xD);
    HH(s[2], s[3], s[0], s[1], up->x[0xE], 0x6);
    HH(s[1], s[2], s[3], s[0], up->x[0x4], 0x7);
    HH(s[0], s[1], s[2], s[3], up->x[0x9], 0xE);
    HH(s[3], s[0], s[1], s[2], up->x[0xF], 0x9);
    HH(s[2], s[3], s[0], s[1], up->x[0x8], 0xD);
    HH(s[1], s[2], s[3], s[0], up->x[0x1], 0xF);
    HH(s[0], s[1], s[2], s[3], up->x[0x2], 0xE);
    HH(s[3], s[0], s[1], s[2], up->x[0x7], 0x8);
    HH(s[2], s[3], s[0], s[1], up->x[0x0], 0xD);
    HH(s[1], s[2], s[3], s[0], up->x[0x6], 0x6);
    HH(s[0], s[1], s[2], s[3], up->x[0xD], 0x5);
    HH(s[3], s[0], s[1], s[2], up->x[0xB], 0xC);
    HH(s[2], s[3], s[0], s[1], up->x[0x5], 0x7);
    HH(s[1], s[2], s[3], s[0], up->x[0xC], 0x5);

    /* round 4 */
    II(s[0], s[1], s[2], s[3], up->x[0x1], 0xB);
    II(s[3], s[0], s[1], s[2], up->x[0x9], 0xC);
    II(s[2], s[3], s[0], s[1], up->x[0xB], 0xE);
    II(s[1], s[2], s[3], s[0], up->x[0xA], 0xF);
    II(s[0], s[1], s[2], s[3], up->x[0x0], 0xE);
    II(s[3], s[0], s[1], s[2], up->x[0x8], 0xF);
    II(s[2], s[3], s[0], s[1], up->x[0xC], 0x9);
    II(s[1], s[2], s[3], s[0], up->x[0x4], 0x8);
    II(s[0], s[1], s[2], s[3], up->x[0xD], 0x9);
    II(s[3], s[0], s[1], s[2], up->x[0x3], 0xE);
    II(s[2], s[3], s[0], s[1], up->x[0x7], 0x5);
    II(s[1], s[2], s[3], s[0], up->x[0xF], 0x6);
    II(s[0], s[1], s[2], s[3], up->x[0xE], 0x8);
    II(s[3], s[0], s[1], s[2], up->x[0x5], 0x6);
    II(s[2], s[3], s[0], s[1], up->x[0x6], 0x5);
    II(s[1], s[2], s[3], s[0], up->x[0x2], 0xC);

    /* parallel round 1 */
    III(s[4], s[5], s[6], s[7], up->x[0x5], 0x8);
    III(s[7], s[4], s[5], s[6], up->x[0xE], 0x9);
    III(s[6], s[7], s[4], s[5], up->x[0x7], 0x9);
    III(s[5], s[6], s[7], s[4], up->x[0x0], 0xB);
    III(s[4], s[5], s[6], s[7], up->x[0x9], 0xD);
    III(s[7], s[4], s[5], s[6], up->x[0x2], 0xF);
    III(s[6], s[7], s[4], s[5], up->x[0xB], 0xF);
    III(s[5], s[6], s[7], s[4], up->x[0x4], 0x5);
    III(s[4], s[5], s[6], s[7], up->x[0xD], 0x7);
    III(s[7], s[4], s[5], s[6], up->x[0x6], 0x7);
    III(s[6], s[7], s[4], s[5], up->x[0xF], 0x8);
    III(s[5], s[6], s[7], s[4], up->x[0x8], 0xB);
    III(s[4], s[5], s[6], s[7], up->x[0x1], 0xE);
    III(s[7], s[4], s[5], s[6], up->x[0xA], 0xE);
    III(s[6], s[7], s[4], s[5], up->x[0x3], 0xC);
    III(s[5], s[6], s[7], s[4], up->x[0xC], 0x6);

    /* parallel round 2 */
    HHH(s[4], s[5], s[6], s[7], up->x[0x6], 0x9);
    HHH(s[7], s[4], s[5], s[6], up->x[0xB], 0xD);
    HHH(s[6], s[7], s[4], s[5], up->x[0x3], 0xF);
    HHH(s[5], s[6], s[7], s[4], up->x[0x7], 0x7);
    HHH(s[4], s[5], s[6], s[7], up->x[0x0], 0xC);
    HHH(s[7], s[4], s[5], s[6], up->x[0xD], 0x8);
    HHH(s[6], s[7], s[4], s[5], up->x[0x5], 0x9);
    HHH(s[5], s[6], s[7], s[4], up->x[0xA], 0xB);
    HHH(s[4], s[5], s[6], s[7], up->x[0xE], 0x7);
    HHH(s[7], s[4], s[5], s[6], up->x[0xF], 0x7);
    HHH(s[6], s[7], s[4], s[5], up->x[0x8], 0xC);
    HHH(s[5], s[6], s[7], s[4], up->x[0xC], 0x7);
    HHH(s[4], s[5], s[6], s[7], up->x[0x4], 0x6);
    HHH(s[7], s[4], s[5], s[6], up->x[0x9], 0xF);
    HHH(s[6], s[7], s[4], s[5], up->x[0x1], 0xD);
    HHH(s[5], s[6], s[7], s[4], up->x[0x2], 0xB);

    /* parallel round 3 */
    GGG(s[4], s[5], s[6], s[7], up->x[0xF], 0x9);
    GGG(s[7], s[4], s[5], s[6], up->x[0x5], 0x7);
    GGG(s[6], s[7], s[4], s[5], up->x[0x1], 0xF);
    GGG(s[5], s[6], s[7], s[4], up->x[0x3], 0xB);
    GGG(s[4], s[5], s[6], s[7], up->x[0x7], 0x8);
    GGG(s[7], s[4], s[5], s[6], up->x[0xE], 0x6);
    GGG(s[6], s[7], s[4], s[5], up->x[0x6], 0x6);
    GGG(s[5], s[6], s[7], s[4], up->x[0x9], 0xE);
    GGG(s[4], s[5], s[6], s[7], up->x[0xB], 0xC);
    GGG(s[7], s[4], s[5], s[6], up->x[0x8], 0xD);
    GGG(s[6], s[7], s[4], s[5], up->x[0xC], 0x5);
    GGG(s[5], s[6], s[7], s[4], up->x[0x2], 0xE);
    GGG(s[4], s[5], s[6], s[7], up->x[0xA], 0xD);
    GGG(s[7], s[4], s[5], s[6], up->x[0x0], 0xD);
    GGG(s[6], s[7], s[4], s[5], up->x[0x4], 0x7);
    GGG(s[5], s[6], s[7], s[4], up->x[0xD], 0x5);

    /* parallel round 4 */
    FFF(s[4], s[5], s[6], s[7], up->x[0x8], 0xF);
    FFF(s[7], s[4], s[5], s[6], up->x[0x6], 0x5);
    FFF(s[6], s[7], s[4], s[5], up->x[0x4], 0x8);
    FFF(s[5], s[6], s[7], s[4], up->x[0x1], 0xB);
    FFF(s[4], s[5], s[6], s[7], up->x[0x3], 0xE);
    FFF(s[7], s[4], s[5], s[6], up->x[0xB], 0xE);
    FFF(s[6], s[7], s[4], s[5], up->x[0xF], 0x6);
    FFF(s[5], s[6], s[7], s[4], up->x[0x0], 0xE);
    FFF(s[4], s[5], s[6], s[7], up->x[0x5], 0x6);
    FFF(s[7], s[4], s[5], s[6], up->x[0xC], 0x9);
    FFF(s[6], s[7], s[4], s[5], up->x[0x2], 0xC);
    FFF(s[5], s[6], s[7], s[4], up->x[0xD], 0x9);
    FFF(s[4], s[5], s[6], s[7], up->x[0x9], 0xC);
    FFF(s[7], s[4], s[5], s[6], up->x[0x7], 0x5);
    FFF(s[6], s[7], s[4], s[5], up->x[0xA], 0xF);
    FFF(s[5], s[6], s[7], s[4], up->x[0xE], 0x8);

    /* combine results */
    s[7] += s[2] + _ctx->state[1];
    _ctx->state[1] = _ctx->state[2] + s[3] + s[4];
    _ctx->state[2] = _ctx->state[3] + s[0] + s[5];
    _ctx->state[3] = _ctx->state[0] + s[1] + s[6];
    _ctx->state[0] = s[7];
}

static void a_rmd256_compress(a_rmd256_t *_ctx, const unsigned char *_buf)
{
    uint32_t s[sizeof(_ctx->state) / sizeof(*_ctx->state)];

    /* (unsigned char *) -> (uint32_t *) */
    union
    {
        uint32_t *x;
        unsigned char *buf;
    } up[1];
    up->buf = _ctx->buf;
    if (_ctx->buf != _buf)
    {
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD32L(up->x[i], _buf + sizeof(*_ctx->state) * i);
        }
    }

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        s[i] = _ctx->state[i];
    }

    /* compress */
    uint32_t t;

    /* round 1 */
    FF(s[0], s[1], s[2], s[3], up->x[0x0], 0xB);
    FF(s[3], s[0], s[1], s[2], up->x[0x1], 0xE);
    FF(s[2], s[3], s[0], s[1], up->x[0x2], 0xF);
    FF(s[1], s[2], s[3], s[0], up->x[0x3], 0xC);
    FF(s[0], s[1], s[2], s[3], up->x[0x4], 0x5);
    FF(s[3], s[0], s[1], s[2], up->x[0x5], 0x8);
    FF(s[2], s[3], s[0], s[1], up->x[0x6], 0x7);
    FF(s[1], s[2], s[3], s[0], up->x[0x7], 0x9);
    FF(s[0], s[1], s[2], s[3], up->x[0x8], 0xB);
    FF(s[3], s[0], s[1], s[2], up->x[0x9], 0xD);
    FF(s[2], s[3], s[0], s[1], up->x[0xA], 0xE);
    FF(s[1], s[2], s[3], s[0], up->x[0xB], 0xF);
    FF(s[0], s[1], s[2], s[3], up->x[0xC], 0x6);
    FF(s[3], s[0], s[1], s[2], up->x[0xD], 0x7);
    FF(s[2], s[3], s[0], s[1], up->x[0xE], 0x9);
    FF(s[1], s[2], s[3], s[0], up->x[0xF], 0x8);

    /* parallel round 1 */
    III(s[4], s[5], s[6], s[7], up->x[0x5], 0x8);
    III(s[7], s[4], s[5], s[6], up->x[0xE], 0x9);
    III(s[6], s[7], s[4], s[5], up->x[0x7], 0x9);
    III(s[5], s[6], s[7], s[4], up->x[0x0], 0xB);
    III(s[4], s[5], s[6], s[7], up->x[0x9], 0xD);
    III(s[7], s[4], s[5], s[6], up->x[0x2], 0xF);
    III(s[6], s[7], s[4], s[5], up->x[0xB], 0xF);
    III(s[5], s[6], s[7], s[4], up->x[0x4], 0x5);
    III(s[4], s[5], s[6], s[7], up->x[0xD], 0x7);
    III(s[7], s[4], s[5], s[6], up->x[0x6], 0x7);
    III(s[6], s[7], s[4], s[5], up->x[0xF], 0x8);
    III(s[5], s[6], s[7], s[4], up->x[0x8], 0xB);
    III(s[4], s[5], s[6], s[7], up->x[0x1], 0xE);
    III(s[7], s[4], s[5], s[6], up->x[0xA], 0xE);
    III(s[6], s[7], s[4], s[5], up->x[0x3], 0xC);
    III(s[5], s[6], s[7], s[4], up->x[0xC], 0x6);

    SWAP(s[0], s[0 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* round 2 */
    GG(s[0], s[1], s[2], s[3], up->x[0x7], 0x7);
    GG(s[3], s[0], s[1], s[2], up->x[0x4], 0x6);
    GG(s[2], s[3], s[0], s[1], up->x[0xD], 0x8);
    GG(s[1], s[2], s[3], s[0], up->x[0x1], 0xD);
    GG(s[0], s[1], s[2], s[3], up->x[0xA], 0xB);
    GG(s[3], s[0], s[1], s[2], up->x[0x6], 0x9);
    GG(s[2], s[3], s[0], s[1], up->x[0xF], 0x7);
    GG(s[1], s[2], s[3], s[0], up->x[0x3], 0xF);
    GG(s[0], s[1], s[2], s[3], up->x[0xC], 0x7);
    GG(s[3], s[0], s[1], s[2], up->x[0x0], 0xC);
    GG(s[2], s[3], s[0], s[1], up->x[0x9], 0xF);
    GG(s[1], s[2], s[3], s[0], up->x[0x5], 0x9);
    GG(s[0], s[1], s[2], s[3], up->x[0x2], 0xB);
    GG(s[3], s[0], s[1], s[2], up->x[0xE], 0x7);
    GG(s[2], s[3], s[0], s[1], up->x[0xB], 0xD);
    GG(s[1], s[2], s[3], s[0], up->x[0x8], 0xC);

    /* parallel round 2 */
    HHH(s[4], s[5], s[6], s[7], up->x[0x6], 0x9);
    HHH(s[7], s[4], s[5], s[6], up->x[0xB], 0xD);
    HHH(s[6], s[7], s[4], s[5], up->x[0x3], 0xF);
    HHH(s[5], s[6], s[7], s[4], up->x[0x7], 0x7);
    HHH(s[4], s[5], s[6], s[7], up->x[0x0], 0xC);
    HHH(s[7], s[4], s[5], s[6], up->x[0xD], 0x8);
    HHH(s[6], s[7], s[4], s[5], up->x[0x5], 0x9);
    HHH(s[5], s[6], s[7], s[4], up->x[0xA], 0xB);
    HHH(s[4], s[5], s[6], s[7], up->x[0xE], 0x7);
    HHH(s[7], s[4], s[5], s[6], up->x[0xF], 0x7);
    HHH(s[6], s[7], s[4], s[5], up->x[0x8], 0xC);
    HHH(s[5], s[6], s[7], s[4], up->x[0xC], 0x7);
    HHH(s[4], s[5], s[6], s[7], up->x[0x4], 0x6);
    HHH(s[7], s[4], s[5], s[6], up->x[0x9], 0xF);
    HHH(s[6], s[7], s[4], s[5], up->x[0x1], 0xD);
    HHH(s[5], s[6], s[7], s[4], up->x[0x2], 0xB);

    SWAP(s[1], s[1 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* round 3 */
    HH(s[0], s[1], s[2], s[3], up->x[0x3], 0xB);
    HH(s[3], s[0], s[1], s[2], up->x[0xA], 0xD);
    HH(s[2], s[3], s[0], s[1], up->x[0xE], 0x6);
    HH(s[1], s[2], s[3], s[0], up->x[0x4], 0x7);
    HH(s[0], s[1], s[2], s[3], up->x[0x9], 0xE);
    HH(s[3], s[0], s[1], s[2], up->x[0xF], 0x9);
    HH(s[2], s[3], s[0], s[1], up->x[0x8], 0xD);
    HH(s[1], s[2], s[3], s[0], up->x[0x1], 0xF);
    HH(s[0], s[1], s[2], s[3], up->x[0x2], 0xE);
    HH(s[3], s[0], s[1], s[2], up->x[0x7], 0x8);
    HH(s[2], s[3], s[0], s[1], up->x[0x0], 0xD);
    HH(s[1], s[2], s[3], s[0], up->x[0x6], 0x6);
    HH(s[0], s[1], s[2], s[3], up->x[0xD], 0x5);
    HH(s[3], s[0], s[1], s[2], up->x[0xB], 0xC);
    HH(s[2], s[3], s[0], s[1], up->x[0x5], 0x7);
    HH(s[1], s[2], s[3], s[0], up->x[0xC], 0x5);

    /* parallel round 3 */
    GGG(s[4], s[5], s[6], s[7], up->x[0xF], 0x9);
    GGG(s[7], s[4], s[5], s[6], up->x[0x5], 0x7);
    GGG(s[6], s[7], s[4], s[5], up->x[0x1], 0xF);
    GGG(s[5], s[6], s[7], s[4], up->x[0x3], 0xB);
    GGG(s[4], s[5], s[6], s[7], up->x[0x7], 0x8);
    GGG(s[7], s[4], s[5], s[6], up->x[0xE], 0x6);
    GGG(s[6], s[7], s[4], s[5], up->x[0x6], 0x6);
    GGG(s[5], s[6], s[7], s[4], up->x[0x9], 0xE);
    GGG(s[4], s[5], s[6], s[7], up->x[0xB], 0xC);
    GGG(s[7], s[4], s[5], s[6], up->x[0x8], 0xD);
    GGG(s[6], s[7], s[4], s[5], up->x[0xC], 0x5);
    GGG(s[5], s[6], s[7], s[4], up->x[0x2], 0xE);
    GGG(s[4], s[5], s[6], s[7], up->x[0xA], 0xD);
    GGG(s[7], s[4], s[5], s[6], up->x[0x0], 0xD);
    GGG(s[6], s[7], s[4], s[5], up->x[0x4], 0x7);
    GGG(s[5], s[6], s[7], s[4], up->x[0xD], 0x5);

    SWAP(s[2], s[2 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* round 4 */
    II(s[0], s[1], s[2], s[3], up->x[0x1], 0xB);
    II(s[3], s[0], s[1], s[2], up->x[0x9], 0xC);
    II(s[2], s[3], s[0], s[1], up->x[0xB], 0xE);
    II(s[1], s[2], s[3], s[0], up->x[0xA], 0xF);
    II(s[0], s[1], s[2], s[3], up->x[0x0], 0xE);
    II(s[3], s[0], s[1], s[2], up->x[0x8], 0xF);
    II(s[2], s[3], s[0], s[1], up->x[0xC], 0x9);
    II(s[1], s[2], s[3], s[0], up->x[0x4], 0x8);
    II(s[0], s[1], s[2], s[3], up->x[0xD], 0x9);
    II(s[3], s[0], s[1], s[2], up->x[0x3], 0xE);
    II(s[2], s[3], s[0], s[1], up->x[0x7], 0x5);
    II(s[1], s[2], s[3], s[0], up->x[0xF], 0x6);
    II(s[0], s[1], s[2], s[3], up->x[0xE], 0x8);
    II(s[3], s[0], s[1], s[2], up->x[0x5], 0x6);
    II(s[2], s[3], s[0], s[1], up->x[0x6], 0x5);
    II(s[1], s[2], s[3], s[0], up->x[0x2], 0xC);

    /* parallel round 4 */
    FFF(s[4], s[5], s[6], s[7], up->x[0x8], 0xF);
    FFF(s[7], s[4], s[5], s[6], up->x[0x6], 0x5);
    FFF(s[6], s[7], s[4], s[5], up->x[0x4], 0x8);
    FFF(s[5], s[6], s[7], s[4], up->x[0x1], 0xB);
    FFF(s[4], s[5], s[6], s[7], up->x[0x3], 0xE);
    FFF(s[7], s[4], s[5], s[6], up->x[0xB], 0xE);
    FFF(s[6], s[7], s[4], s[5], up->x[0xF], 0x6);
    FFF(s[5], s[6], s[7], s[4], up->x[0x0], 0xE);
    FFF(s[4], s[5], s[6], s[7], up->x[0x5], 0x6);
    FFF(s[7], s[4], s[5], s[6], up->x[0xC], 0x9);
    FFF(s[6], s[7], s[4], s[5], up->x[0x2], 0xC);
    FFF(s[5], s[6], s[7], s[4], up->x[0xD], 0x9);
    FFF(s[4], s[5], s[6], s[7], up->x[0x9], 0xC);
    FFF(s[7], s[4], s[5], s[6], up->x[0x7], 0x5);
    FFF(s[6], s[7], s[4], s[5], up->x[0xA], 0xF);
    FFF(s[5], s[6], s[7], s[4], up->x[0xE], 0x8);

    SWAP(s[3], s[3 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* feedback */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        _ctx->state[i] += s[i];
    }
}

#undef FF
#undef FFF
#undef GG
#undef GGG
#undef HH
#undef HHH
#undef II
#undef III
#undef JJ
#undef JJJ
/* the ten basic operations FF() through III() */
#define FF(_a, _b, _c, _d, _e, _x, _s)  \
    (_a) += F((_b), (_c), (_d)) + (_x); \
    (_a) = ROLc((_a), (_s)) + (_e);     \
    (_c) = ROLc((_c), 10);
#define GG(_a, _b, _c, _d, _e, _x, _s)               \
    (_a) += G((_b), (_c), (_d)) + (_x) + 0x5A827999; \
    (_a) = ROLc((_a), (_s)) + (_e);                  \
    (_c) = ROLc((_c), 10);
#define HH(_a, _b, _c, _d, _e, _x, _s)               \
    (_a) += H((_b), (_c), (_d)) + (_x) + 0x6ED9EBA1; \
    (_a) = ROLc((_a), (_s)) + (_e);                  \
    (_c) = ROLc((_c), 10);
#define II(_a, _b, _c, _d, _e, _x, _s)               \
    (_a) += I((_b), (_c), (_d)) + (_x) + 0x8F1BBCDC; \
    (_a) = ROLc((_a), (_s)) + (_e);                  \
    (_c) = ROLc((_c), 10);
#define JJ(_a, _b, _c, _d, _e, _x, _s)               \
    (_a) += J((_b), (_c), (_d)) + (_x) + 0xA953FD4E; \
    (_a) = ROLc((_a), (_s)) + (_e);                  \
    (_c) = ROLc((_c), 10);
#define FFF(_a, _b, _c, _d, _e, _x, _s) \
    (_a) += F((_b), (_c), (_d)) + (_x); \
    (_a) = ROLc((_a), (_s)) + (_e);     \
    (_c) = ROLc((_c), 10);
#define GGG(_a, _b, _c, _d, _e, _x, _s)              \
    (_a) += G((_b), (_c), (_d)) + (_x) + 0x7A6D76E9; \
    (_a) = ROLc((_a), (_s)) + (_e);                  \
    (_c) = ROLc((_c), 10);
#define HHH(_a, _b, _c, _d, _e, _x, _s)              \
    (_a) += H((_b), (_c), (_d)) + (_x) + 0x6D703EF3; \
    (_a) = ROLc((_a), (_s)) + (_e);                  \
    (_c) = ROLc((_c), 10);
#define III(_a, _b, _c, _d, _e, _x, _s)              \
    (_a) += I((_b), (_c), (_d)) + (_x) + 0x5C4DD124; \
    (_a) = ROLc((_a), (_s)) + (_e);                  \
    (_c) = ROLc((_c), 10);
#define JJJ(_a, _b, _c, _d, _e, _x, _s)              \
    (_a) += J((_b), (_c), (_d)) + (_x) + 0x50A28BE6; \
    (_a) = ROLc((_a), (_s)) + (_e);                  \
    (_c) = ROLc((_c), 10);

static void a_rmd160_compress(a_rmd160_t *_ctx, const unsigned char *_buf)
{
    uint32_t s[(sizeof(_ctx->state) / sizeof(*_ctx->state)) << 1];

    /* (unsigned char *) -> (uint32_t *) */
    union
    {
        uint32_t *x;
        unsigned char *buf;
    } up[1];
    up->buf = _ctx->buf;
    if (_ctx->buf != _buf)
    {
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD32L(up->x[i], _buf + sizeof(*_ctx->state) * i);
        }
    }

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        s[i] = s[i + ((sizeof(s) / sizeof(*s)) >> 1)] = _ctx->state[i];
    }

    /* round 1 */
    FF(s[0], s[1], s[2], s[3], s[4], up->x[0x0], 0xB);
    FF(s[4], s[0], s[1], s[2], s[3], up->x[0x1], 0xE);
    FF(s[3], s[4], s[0], s[1], s[2], up->x[0x2], 0xF);
    FF(s[2], s[3], s[4], s[0], s[1], up->x[0x3], 0xC);
    FF(s[1], s[2], s[3], s[4], s[0], up->x[0x4], 0x5);
    FF(s[0], s[1], s[2], s[3], s[4], up->x[0x5], 0x8);
    FF(s[4], s[0], s[1], s[2], s[3], up->x[0x6], 0x7);
    FF(s[3], s[4], s[0], s[1], s[2], up->x[0x7], 0x9);
    FF(s[2], s[3], s[4], s[0], s[1], up->x[0x8], 0xB);
    FF(s[1], s[2], s[3], s[4], s[0], up->x[0x9], 0xD);
    FF(s[0], s[1], s[2], s[3], s[4], up->x[0xA], 0xE);
    FF(s[4], s[0], s[1], s[2], s[3], up->x[0xB], 0xF);
    FF(s[3], s[4], s[0], s[1], s[2], up->x[0xC], 0x6);
    FF(s[2], s[3], s[4], s[0], s[1], up->x[0xD], 0x7);
    FF(s[1], s[2], s[3], s[4], s[0], up->x[0xE], 0x9);
    FF(s[0], s[1], s[2], s[3], s[4], up->x[0xF], 0x8);

    /* round 2 */
    GG(s[4], s[0], s[1], s[2], s[3], up->x[0x7], 0x7);
    GG(s[3], s[4], s[0], s[1], s[2], up->x[0x4], 0x6);
    GG(s[2], s[3], s[4], s[0], s[1], up->x[0xD], 0x8);
    GG(s[1], s[2], s[3], s[4], s[0], up->x[0x1], 0xD);
    GG(s[0], s[1], s[2], s[3], s[4], up->x[0xA], 0xB);
    GG(s[4], s[0], s[1], s[2], s[3], up->x[0x6], 0x9);
    GG(s[3], s[4], s[0], s[1], s[2], up->x[0xF], 0x7);
    GG(s[2], s[3], s[4], s[0], s[1], up->x[0x3], 0xF);
    GG(s[1], s[2], s[3], s[4], s[0], up->x[0xC], 0x7);
    GG(s[0], s[1], s[2], s[3], s[4], up->x[0x0], 0xC);
    GG(s[4], s[0], s[1], s[2], s[3], up->x[0x9], 0xF);
    GG(s[3], s[4], s[0], s[1], s[2], up->x[0x5], 0x9);
    GG(s[2], s[3], s[4], s[0], s[1], up->x[0x2], 0xB);
    GG(s[1], s[2], s[3], s[4], s[0], up->x[0xE], 0x7);
    GG(s[0], s[1], s[2], s[3], s[4], up->x[0xB], 0xD);
    GG(s[4], s[0], s[1], s[2], s[3], up->x[0x8], 0xC);

    /* round 3 */
    HH(s[3], s[4], s[0], s[1], s[2], up->x[0x3], 0xB);
    HH(s[2], s[3], s[4], s[0], s[1], up->x[0xA], 0xD);
    HH(s[1], s[2], s[3], s[4], s[0], up->x[0xE], 0x6);
    HH(s[0], s[1], s[2], s[3], s[4], up->x[0x4], 0x7);
    HH(s[4], s[0], s[1], s[2], s[3], up->x[0x9], 0xE);
    HH(s[3], s[4], s[0], s[1], s[2], up->x[0xF], 0x9);
    HH(s[2], s[3], s[4], s[0], s[1], up->x[0x8], 0xD);
    HH(s[1], s[2], s[3], s[4], s[0], up->x[0x1], 0xF);
    HH(s[0], s[1], s[2], s[3], s[4], up->x[0x2], 0xE);
    HH(s[4], s[0], s[1], s[2], s[3], up->x[0x7], 0x8);
    HH(s[3], s[4], s[0], s[1], s[2], up->x[0x0], 0xD);
    HH(s[2], s[3], s[4], s[0], s[1], up->x[0x6], 0x6);
    HH(s[1], s[2], s[3], s[4], s[0], up->x[0xD], 0x5);
    HH(s[0], s[1], s[2], s[3], s[4], up->x[0xB], 0xC);
    HH(s[4], s[0], s[1], s[2], s[3], up->x[0x5], 0x7);
    HH(s[3], s[4], s[0], s[1], s[2], up->x[0xC], 0x5);

    /* round 4 */
    II(s[2], s[3], s[4], s[0], s[1], up->x[0x1], 0xB);
    II(s[1], s[2], s[3], s[4], s[0], up->x[0x9], 0xC);
    II(s[0], s[1], s[2], s[3], s[4], up->x[0xB], 0xE);
    II(s[4], s[0], s[1], s[2], s[3], up->x[0xA], 0xF);
    II(s[3], s[4], s[0], s[1], s[2], up->x[0x0], 0xE);
    II(s[2], s[3], s[4], s[0], s[1], up->x[0x8], 0xF);
    II(s[1], s[2], s[3], s[4], s[0], up->x[0xC], 0x9);
    II(s[0], s[1], s[2], s[3], s[4], up->x[0x4], 0x8);
    II(s[4], s[0], s[1], s[2], s[3], up->x[0xD], 0x9);
    II(s[3], s[4], s[0], s[1], s[2], up->x[0x3], 0xE);
    II(s[2], s[3], s[4], s[0], s[1], up->x[0x7], 0x5);
    II(s[1], s[2], s[3], s[4], s[0], up->x[0xF], 0x6);
    II(s[0], s[1], s[2], s[3], s[4], up->x[0xE], 0x8);
    II(s[4], s[0], s[1], s[2], s[3], up->x[0x5], 0x6);
    II(s[3], s[4], s[0], s[1], s[2], up->x[0x6], 0x5);
    II(s[2], s[3], s[4], s[0], s[1], up->x[0x2], 0xC);

    /* round 5 */
    JJ(s[1], s[2], s[3], s[4], s[0], up->x[0x4], 0x9);
    JJ(s[0], s[1], s[2], s[3], s[4], up->x[0x0], 0xF);
    JJ(s[4], s[0], s[1], s[2], s[3], up->x[0x5], 0x5);
    JJ(s[3], s[4], s[0], s[1], s[2], up->x[0x9], 0xB);
    JJ(s[2], s[3], s[4], s[0], s[1], up->x[0x7], 0x6);
    JJ(s[1], s[2], s[3], s[4], s[0], up->x[0xC], 0x8);
    JJ(s[0], s[1], s[2], s[3], s[4], up->x[0x2], 0xD);
    JJ(s[4], s[0], s[1], s[2], s[3], up->x[0xA], 0xC);
    JJ(s[3], s[4], s[0], s[1], s[2], up->x[0xE], 0x5);
    JJ(s[2], s[3], s[4], s[0], s[1], up->x[0x1], 0xC);
    JJ(s[1], s[2], s[3], s[4], s[0], up->x[0x3], 0xD);
    JJ(s[0], s[1], s[2], s[3], s[4], up->x[0x8], 0xE);
    JJ(s[4], s[0], s[1], s[2], s[3], up->x[0xB], 0xB);
    JJ(s[3], s[4], s[0], s[1], s[2], up->x[0x6], 0x8);
    JJ(s[2], s[3], s[4], s[0], s[1], up->x[0xF], 0x5);
    JJ(s[1], s[2], s[3], s[4], s[0], up->x[0xD], 0x6);

    /* parallel round 1 */
    JJJ(s[5], s[6], s[7], s[8], s[9], up->x[0x5], 0x8);
    JJJ(s[9], s[5], s[6], s[7], s[8], up->x[0xE], 0x9);
    JJJ(s[8], s[9], s[5], s[6], s[7], up->x[0x7], 0x9);
    JJJ(s[7], s[8], s[9], s[5], s[6], up->x[0x0], 0xB);
    JJJ(s[6], s[7], s[8], s[9], s[5], up->x[0x9], 0xD);
    JJJ(s[5], s[6], s[7], s[8], s[9], up->x[0x2], 0xF);
    JJJ(s[9], s[5], s[6], s[7], s[8], up->x[0xB], 0xF);
    JJJ(s[8], s[9], s[5], s[6], s[7], up->x[0x4], 0x5);
    JJJ(s[7], s[8], s[9], s[5], s[6], up->x[0xD], 0x7);
    JJJ(s[6], s[7], s[8], s[9], s[5], up->x[0x6], 0x7);
    JJJ(s[5], s[6], s[7], s[8], s[9], up->x[0xF], 0x8);
    JJJ(s[9], s[5], s[6], s[7], s[8], up->x[0x8], 0xB);
    JJJ(s[8], s[9], s[5], s[6], s[7], up->x[0x1], 0xE);
    JJJ(s[7], s[8], s[9], s[5], s[6], up->x[0xA], 0xE);
    JJJ(s[6], s[7], s[8], s[9], s[5], up->x[0x3], 0xC);
    JJJ(s[5], s[6], s[7], s[8], s[9], up->x[0xC], 0x6);

    /* parallel round 2 */
    III(s[9], s[5], s[6], s[7], s[8], up->x[0x6], 0x9);
    III(s[8], s[9], s[5], s[6], s[7], up->x[0xB], 0xD);
    III(s[7], s[8], s[9], s[5], s[6], up->x[0x3], 0xF);
    III(s[6], s[7], s[8], s[9], s[5], up->x[0x7], 0x7);
    III(s[5], s[6], s[7], s[8], s[9], up->x[0x0], 0xC);
    III(s[9], s[5], s[6], s[7], s[8], up->x[0xD], 0x8);
    III(s[8], s[9], s[5], s[6], s[7], up->x[0x5], 0x9);
    III(s[7], s[8], s[9], s[5], s[6], up->x[0xA], 0xB);
    III(s[6], s[7], s[8], s[9], s[5], up->x[0xE], 0x7);
    III(s[5], s[6], s[7], s[8], s[9], up->x[0xF], 0x7);
    III(s[9], s[5], s[6], s[7], s[8], up->x[0x8], 0xC);
    III(s[8], s[9], s[5], s[6], s[7], up->x[0xC], 0x7);
    III(s[7], s[8], s[9], s[5], s[6], up->x[0x4], 0x6);
    III(s[6], s[7], s[8], s[9], s[5], up->x[0x9], 0xF);
    III(s[5], s[6], s[7], s[8], s[9], up->x[0x1], 0xD);
    III(s[9], s[5], s[6], s[7], s[8], up->x[0x2], 0xB);

    /* parallel round 3 */
    HHH(s[8], s[9], s[5], s[6], s[7], up->x[0xF], 0x9);
    HHH(s[7], s[8], s[9], s[5], s[6], up->x[0x5], 0x7);
    HHH(s[6], s[7], s[8], s[9], s[5], up->x[0x1], 0xF);
    HHH(s[5], s[6], s[7], s[8], s[9], up->x[0x3], 0xB);
    HHH(s[9], s[5], s[6], s[7], s[8], up->x[0x7], 0x8);
    HHH(s[8], s[9], s[5], s[6], s[7], up->x[0xE], 0x6);
    HHH(s[7], s[8], s[9], s[5], s[6], up->x[0x6], 0x6);
    HHH(s[6], s[7], s[8], s[9], s[5], up->x[0x9], 0xE);
    HHH(s[5], s[6], s[7], s[8], s[9], up->x[0xB], 0xC);
    HHH(s[9], s[5], s[6], s[7], s[8], up->x[0x8], 0xD);
    HHH(s[8], s[9], s[5], s[6], s[7], up->x[0xC], 0x5);
    HHH(s[7], s[8], s[9], s[5], s[6], up->x[0x2], 0xE);
    HHH(s[6], s[7], s[8], s[9], s[5], up->x[0xA], 0xD);
    HHH(s[5], s[6], s[7], s[8], s[9], up->x[0x0], 0xD);
    HHH(s[9], s[5], s[6], s[7], s[8], up->x[0x4], 0x7);
    HHH(s[8], s[9], s[5], s[6], s[7], up->x[0xD], 0x5);

    /* parallel round 4 */
    GGG(s[7], s[8], s[9], s[5], s[6], up->x[0x8], 0xF);
    GGG(s[6], s[7], s[8], s[9], s[5], up->x[0x6], 0x5);
    GGG(s[5], s[6], s[7], s[8], s[9], up->x[0x4], 0x8);
    GGG(s[9], s[5], s[6], s[7], s[8], up->x[0x1], 0xB);
    GGG(s[8], s[9], s[5], s[6], s[7], up->x[0x3], 0xE);
    GGG(s[7], s[8], s[9], s[5], s[6], up->x[0xB], 0xE);
    GGG(s[6], s[7], s[8], s[9], s[5], up->x[0xF], 0x6);
    GGG(s[5], s[6], s[7], s[8], s[9], up->x[0x0], 0xE);
    GGG(s[9], s[5], s[6], s[7], s[8], up->x[0x5], 0x6);
    GGG(s[8], s[9], s[5], s[6], s[7], up->x[0xC], 0x9);
    GGG(s[7], s[8], s[9], s[5], s[6], up->x[0x2], 0xC);
    GGG(s[6], s[7], s[8], s[9], s[5], up->x[0xD], 0x9);
    GGG(s[5], s[6], s[7], s[8], s[9], up->x[0x9], 0xC);
    GGG(s[9], s[5], s[6], s[7], s[8], up->x[0x7], 0x5);
    GGG(s[8], s[9], s[5], s[6], s[7], up->x[0xA], 0xF);
    GGG(s[7], s[8], s[9], s[5], s[6], up->x[0xE], 0x8);

    /* parallel round 5 */
    FFF(s[6], s[7], s[8], s[9], s[5], up->x[0xC], 0x8);
    FFF(s[5], s[6], s[7], s[8], s[9], up->x[0xF], 0x5);
    FFF(s[9], s[5], s[6], s[7], s[8], up->x[0xA], 0xC);
    FFF(s[8], s[9], s[5], s[6], s[7], up->x[0x4], 0x9);
    FFF(s[7], s[8], s[9], s[5], s[6], up->x[0x1], 0xC);
    FFF(s[6], s[7], s[8], s[9], s[5], up->x[0x5], 0x5);
    FFF(s[5], s[6], s[7], s[8], s[9], up->x[0x8], 0xE);
    FFF(s[9], s[5], s[6], s[7], s[8], up->x[0x7], 0x6);
    FFF(s[8], s[9], s[5], s[6], s[7], up->x[0x6], 0x8);
    FFF(s[7], s[8], s[9], s[5], s[6], up->x[0x2], 0xD);
    FFF(s[6], s[7], s[8], s[9], s[5], up->x[0xD], 0x6);
    FFF(s[5], s[6], s[7], s[8], s[9], up->x[0xE], 0x5);
    FFF(s[9], s[5], s[6], s[7], s[8], up->x[0x0], 0xF);
    FFF(s[8], s[9], s[5], s[6], s[7], up->x[0x3], 0xD);
    FFF(s[7], s[8], s[9], s[5], s[6], up->x[0x9], 0xB);
    FFF(s[6], s[7], s[8], s[9], s[5], up->x[0xB], 0xB);

    /* combine results */
    s[8] += s[2] + _ctx->state[0x1];
    _ctx->state[0x1] = _ctx->state[0x2] + s[3] + s[9];
    _ctx->state[0x2] = _ctx->state[0x3] + s[4] + s[5];
    _ctx->state[0x3] = _ctx->state[0x4] + s[0] + s[6];
    _ctx->state[0x4] = _ctx->state[0x0] + s[1] + s[7];
    _ctx->state[0x0] = s[8];
}

static void a_rmd320_compress(a_rmd320_t *_ctx, const unsigned char *_buf)
{
    uint32_t s[sizeof(_ctx->state) / sizeof(*_ctx->state)];

    /* (unsigned char *) -> (uint32_t *) */
    union
    {
        uint32_t *x;
        unsigned char *buf;
    } up[1];
    up->buf = _ctx->buf;
    if (_ctx->buf != _buf)
    {
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD32L(up->x[i], _buf + sizeof(*_ctx->state) * i);
        }
    }

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        s[i] = _ctx->state[i];
    }

    /* compress */
    uint32_t t;

    /* round 1 */
    FF(s[0], s[1], s[2], s[3], s[4], up->x[0x0], 0xB);
    FF(s[4], s[0], s[1], s[2], s[3], up->x[0x1], 0xE);
    FF(s[3], s[4], s[0], s[1], s[2], up->x[0x2], 0xF);
    FF(s[2], s[3], s[4], s[0], s[1], up->x[0x3], 0xC);
    FF(s[1], s[2], s[3], s[4], s[0], up->x[0x4], 0x5);
    FF(s[0], s[1], s[2], s[3], s[4], up->x[0x5], 0x8);
    FF(s[4], s[0], s[1], s[2], s[3], up->x[0x6], 0x7);
    FF(s[3], s[4], s[0], s[1], s[2], up->x[0x7], 0x9);
    FF(s[2], s[3], s[4], s[0], s[1], up->x[0x8], 0xB);
    FF(s[1], s[2], s[3], s[4], s[0], up->x[0x9], 0xD);
    FF(s[0], s[1], s[2], s[3], s[4], up->x[0xA], 0xE);
    FF(s[4], s[0], s[1], s[2], s[3], up->x[0xB], 0xF);
    FF(s[3], s[4], s[0], s[1], s[2], up->x[0xC], 0x6);
    FF(s[2], s[3], s[4], s[0], s[1], up->x[0xD], 0x7);
    FF(s[1], s[2], s[3], s[4], s[0], up->x[0xE], 0x9);
    FF(s[0], s[1], s[2], s[3], s[4], up->x[0xF], 0x8);

    /* parallel round 1 */
    JJJ(s[5], s[6], s[7], s[8], s[9], up->x[0x5], 0x8);
    JJJ(s[9], s[5], s[6], s[7], s[8], up->x[0xE], 0x9);
    JJJ(s[8], s[9], s[5], s[6], s[7], up->x[0x7], 0x9);
    JJJ(s[7], s[8], s[9], s[5], s[6], up->x[0x0], 0xB);
    JJJ(s[6], s[7], s[8], s[9], s[5], up->x[0x9], 0xD);
    JJJ(s[5], s[6], s[7], s[8], s[9], up->x[0x2], 0xF);
    JJJ(s[9], s[5], s[6], s[7], s[8], up->x[0xB], 0xF);
    JJJ(s[8], s[9], s[5], s[6], s[7], up->x[0x4], 0x5);
    JJJ(s[7], s[8], s[9], s[5], s[6], up->x[0xD], 0x7);
    JJJ(s[6], s[7], s[8], s[9], s[5], up->x[0x6], 0x7);
    JJJ(s[5], s[6], s[7], s[8], s[9], up->x[0xF], 0x8);
    JJJ(s[9], s[5], s[6], s[7], s[8], up->x[0x8], 0xB);
    JJJ(s[8], s[9], s[5], s[6], s[7], up->x[0x1], 0xE);
    JJJ(s[7], s[8], s[9], s[5], s[6], up->x[0xA], 0xE);
    JJJ(s[6], s[7], s[8], s[9], s[5], up->x[0x3], 0xC);
    JJJ(s[5], s[6], s[7], s[8], s[9], up->x[0xC], 0x6);

    SWAP(s[0], s[0 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* round 2 */
    GG(s[4], s[0], s[1], s[2], s[3], up->x[0x7], 0x7);
    GG(s[3], s[4], s[0], s[1], s[2], up->x[0x4], 0x6);
    GG(s[2], s[3], s[4], s[0], s[1], up->x[0xD], 0x8);
    GG(s[1], s[2], s[3], s[4], s[0], up->x[0x1], 0xD);
    GG(s[0], s[1], s[2], s[3], s[4], up->x[0xA], 0xB);
    GG(s[4], s[0], s[1], s[2], s[3], up->x[0x6], 0x9);
    GG(s[3], s[4], s[0], s[1], s[2], up->x[0xF], 0x7);
    GG(s[2], s[3], s[4], s[0], s[1], up->x[0x3], 0xF);
    GG(s[1], s[2], s[3], s[4], s[0], up->x[0xC], 0x7);
    GG(s[0], s[1], s[2], s[3], s[4], up->x[0x0], 0xC);
    GG(s[4], s[0], s[1], s[2], s[3], up->x[0x9], 0xF);
    GG(s[3], s[4], s[0], s[1], s[2], up->x[0x5], 0x9);
    GG(s[2], s[3], s[4], s[0], s[1], up->x[0x2], 0xB);
    GG(s[1], s[2], s[3], s[4], s[0], up->x[0xE], 0x7);
    GG(s[0], s[1], s[2], s[3], s[4], up->x[0xB], 0xD);
    GG(s[4], s[0], s[1], s[2], s[3], up->x[0x8], 0xC);

    /* parallel round 2 */
    III(s[9], s[5], s[6], s[7], s[8], up->x[0x6], 0x9);
    III(s[8], s[9], s[5], s[6], s[7], up->x[0xB], 0xD);
    III(s[7], s[8], s[9], s[5], s[6], up->x[0x3], 0xF);
    III(s[6], s[7], s[8], s[9], s[5], up->x[0x7], 0x7);
    III(s[5], s[6], s[7], s[8], s[9], up->x[0x0], 0xC);
    III(s[9], s[5], s[6], s[7], s[8], up->x[0xD], 0x8);
    III(s[8], s[9], s[5], s[6], s[7], up->x[0x5], 0x9);
    III(s[7], s[8], s[9], s[5], s[6], up->x[0xA], 0xB);
    III(s[6], s[7], s[8], s[9], s[5], up->x[0xE], 0x7);
    III(s[5], s[6], s[7], s[8], s[9], up->x[0xF], 0x7);
    III(s[9], s[5], s[6], s[7], s[8], up->x[0x8], 0xC);
    III(s[8], s[9], s[5], s[6], s[7], up->x[0xC], 0x7);
    III(s[7], s[8], s[9], s[5], s[6], up->x[0x4], 0x6);
    III(s[6], s[7], s[8], s[9], s[5], up->x[0x9], 0xF);
    III(s[5], s[6], s[7], s[8], s[9], up->x[0x1], 0xD);
    III(s[9], s[5], s[6], s[7], s[8], up->x[0x2], 0xB);

    SWAP(s[1], s[1 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* round 3 */
    HH(s[3], s[4], s[0], s[1], s[2], up->x[0x3], 0xB);
    HH(s[2], s[3], s[4], s[0], s[1], up->x[0xA], 0xD);
    HH(s[1], s[2], s[3], s[4], s[0], up->x[0xE], 0x6);
    HH(s[0], s[1], s[2], s[3], s[4], up->x[0x4], 0x7);
    HH(s[4], s[0], s[1], s[2], s[3], up->x[0x9], 0xE);
    HH(s[3], s[4], s[0], s[1], s[2], up->x[0xF], 0x9);
    HH(s[2], s[3], s[4], s[0], s[1], up->x[0x8], 0xD);
    HH(s[1], s[2], s[3], s[4], s[0], up->x[0x1], 0xF);
    HH(s[0], s[1], s[2], s[3], s[4], up->x[0x2], 0xE);
    HH(s[4], s[0], s[1], s[2], s[3], up->x[0x7], 0x8);
    HH(s[3], s[4], s[0], s[1], s[2], up->x[0x0], 0xD);
    HH(s[2], s[3], s[4], s[0], s[1], up->x[0x6], 0x6);
    HH(s[1], s[2], s[3], s[4], s[0], up->x[0xD], 0x5);
    HH(s[0], s[1], s[2], s[3], s[4], up->x[0xB], 0xC);
    HH(s[4], s[0], s[1], s[2], s[3], up->x[0x5], 0x7);
    HH(s[3], s[4], s[0], s[1], s[2], up->x[0xC], 0x5);

    /* parallel round 3 */
    HHH(s[8], s[9], s[5], s[6], s[7], up->x[0xF], 0x9);
    HHH(s[7], s[8], s[9], s[5], s[6], up->x[0x5], 0x7);
    HHH(s[6], s[7], s[8], s[9], s[5], up->x[0x1], 0xF);
    HHH(s[5], s[6], s[7], s[8], s[9], up->x[0x3], 0xB);
    HHH(s[9], s[5], s[6], s[7], s[8], up->x[0x7], 0x8);
    HHH(s[8], s[9], s[5], s[6], s[7], up->x[0xE], 0x6);
    HHH(s[7], s[8], s[9], s[5], s[6], up->x[0x6], 0x6);
    HHH(s[6], s[7], s[8], s[9], s[5], up->x[0x9], 0xE);
    HHH(s[5], s[6], s[7], s[8], s[9], up->x[0xB], 0xC);
    HHH(s[9], s[5], s[6], s[7], s[8], up->x[0x8], 0xD);
    HHH(s[8], s[9], s[5], s[6], s[7], up->x[0xC], 0x5);
    HHH(s[7], s[8], s[9], s[5], s[6], up->x[0x2], 0xE);
    HHH(s[6], s[7], s[8], s[9], s[5], up->x[0xA], 0xD);
    HHH(s[5], s[6], s[7], s[8], s[9], up->x[0x0], 0xD);
    HHH(s[9], s[5], s[6], s[7], s[8], up->x[0x4], 0x7);
    HHH(s[8], s[9], s[5], s[6], s[7], up->x[0xD], 0x5);

    SWAP(s[2], s[2 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* round 4 */
    II(s[2], s[3], s[4], s[0], s[1], up->x[0x1], 0xB);
    II(s[1], s[2], s[3], s[4], s[0], up->x[0x9], 0xC);
    II(s[0], s[1], s[2], s[3], s[4], up->x[0xB], 0xE);
    II(s[4], s[0], s[1], s[2], s[3], up->x[0xA], 0xF);
    II(s[3], s[4], s[0], s[1], s[2], up->x[0x0], 0xE);
    II(s[2], s[3], s[4], s[0], s[1], up->x[0x8], 0xF);
    II(s[1], s[2], s[3], s[4], s[0], up->x[0xC], 0x9);
    II(s[0], s[1], s[2], s[3], s[4], up->x[0x4], 0x8);
    II(s[4], s[0], s[1], s[2], s[3], up->x[0xD], 0x9);
    II(s[3], s[4], s[0], s[1], s[2], up->x[0x3], 0xE);
    II(s[2], s[3], s[4], s[0], s[1], up->x[0x7], 0x5);
    II(s[1], s[2], s[3], s[4], s[0], up->x[0xF], 0x6);
    II(s[0], s[1], s[2], s[3], s[4], up->x[0xE], 0x8);
    II(s[4], s[0], s[1], s[2], s[3], up->x[0x5], 0x6);
    II(s[3], s[4], s[0], s[1], s[2], up->x[0x6], 0x5);
    II(s[2], s[3], s[4], s[0], s[1], up->x[0x2], 0xC);

    /* parallel round 4 */
    GGG(s[7], s[8], s[9], s[5], s[6], up->x[0x8], 0xF);
    GGG(s[6], s[7], s[8], s[9], s[5], up->x[0x6], 0x5);
    GGG(s[5], s[6], s[7], s[8], s[9], up->x[0x4], 0x8);
    GGG(s[9], s[5], s[6], s[7], s[8], up->x[0x1], 0xB);
    GGG(s[8], s[9], s[5], s[6], s[7], up->x[0x3], 0xE);
    GGG(s[7], s[8], s[9], s[5], s[6], up->x[0xB], 0xE);
    GGG(s[6], s[7], s[8], s[9], s[5], up->x[0xF], 0x6);
    GGG(s[5], s[6], s[7], s[8], s[9], up->x[0x0], 0xE);
    GGG(s[9], s[5], s[6], s[7], s[8], up->x[0x5], 0x6);
    GGG(s[8], s[9], s[5], s[6], s[7], up->x[0xC], 0x9);
    GGG(s[7], s[8], s[9], s[5], s[6], up->x[0x2], 0xC);
    GGG(s[6], s[7], s[8], s[9], s[5], up->x[0xD], 0x9);
    GGG(s[5], s[6], s[7], s[8], s[9], up->x[0x9], 0xC);
    GGG(s[9], s[5], s[6], s[7], s[8], up->x[0x7], 0x5);
    GGG(s[8], s[9], s[5], s[6], s[7], up->x[0xA], 0xF);
    GGG(s[7], s[8], s[9], s[5], s[6], up->x[0xE], 0x8);

    SWAP(s[3], s[3 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* round 5 */
    JJ(s[1], s[2], s[3], s[4], s[0], up->x[0x4], 0x9);
    JJ(s[0], s[1], s[2], s[3], s[4], up->x[0x0], 0xF);
    JJ(s[4], s[0], s[1], s[2], s[3], up->x[0x5], 0x5);
    JJ(s[3], s[4], s[0], s[1], s[2], up->x[0x9], 0xB);
    JJ(s[2], s[3], s[4], s[0], s[1], up->x[0x7], 0x6);
    JJ(s[1], s[2], s[3], s[4], s[0], up->x[0xC], 0x8);
    JJ(s[0], s[1], s[2], s[3], s[4], up->x[0x2], 0xD);
    JJ(s[4], s[0], s[1], s[2], s[3], up->x[0xA], 0xC);
    JJ(s[3], s[4], s[0], s[1], s[2], up->x[0xE], 0x5);
    JJ(s[2], s[3], s[4], s[0], s[1], up->x[0x1], 0xC);
    JJ(s[1], s[2], s[3], s[4], s[0], up->x[0x3], 0xD);
    JJ(s[0], s[1], s[2], s[3], s[4], up->x[0x8], 0xE);
    JJ(s[4], s[0], s[1], s[2], s[3], up->x[0xB], 0xB);
    JJ(s[3], s[4], s[0], s[1], s[2], up->x[0x6], 0x8);
    JJ(s[2], s[3], s[4], s[0], s[1], up->x[0xF], 0x5);
    JJ(s[1], s[2], s[3], s[4], s[0], up->x[0xD], 0x6);

    /* parallel round 5 */
    FFF(s[6], s[7], s[8], s[9], s[5], up->x[0xC], 0x8);
    FFF(s[5], s[6], s[7], s[8], s[9], up->x[0xF], 0x5);
    FFF(s[9], s[5], s[6], s[7], s[8], up->x[0xA], 0xC);
    FFF(s[8], s[9], s[5], s[6], s[7], up->x[0x4], 0x9);
    FFF(s[7], s[8], s[9], s[5], s[6], up->x[0x1], 0xC);
    FFF(s[6], s[7], s[8], s[9], s[5], up->x[0x5], 0x5);
    FFF(s[5], s[6], s[7], s[8], s[9], up->x[0x8], 0xE);
    FFF(s[9], s[5], s[6], s[7], s[8], up->x[0x7], 0x6);
    FFF(s[8], s[9], s[5], s[6], s[7], up->x[0x6], 0x8);
    FFF(s[7], s[8], s[9], s[5], s[6], up->x[0x2], 0xD);
    FFF(s[6], s[7], s[8], s[9], s[5], up->x[0xD], 0x6);
    FFF(s[5], s[6], s[7], s[8], s[9], up->x[0xE], 0x5);
    FFF(s[9], s[5], s[6], s[7], s[8], up->x[0x0], 0xF);
    FFF(s[8], s[9], s[5], s[6], s[7], up->x[0x3], 0xD);
    FFF(s[7], s[8], s[9], s[5], s[6], up->x[0x9], 0xB);
    FFF(s[6], s[7], s[8], s[9], s[5], up->x[0xB], 0xB);

    SWAP(s[4], s[4 + ((sizeof(s) / sizeof(*s)) >> 1)]);

    /* feedback */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        _ctx->state[i] += s[i];
    }
}

#undef F
#undef FF
#undef FFF
#undef G
#undef GG
#undef GGG
#undef H
#undef HH
#undef HHH
#undef I
#undef II
#undef III
#undef J
#undef JJ
#undef JJJ
#undef SWAP

void a_rmd128_init(a_rmd128_t *_ctx)
{
    a_assert(_ctx);

    _ctx->cursiz = 0;
    _ctx->length = 0;

    _ctx->state[0] = 0x67452301;
    _ctx->state[1] = 0xEFCDAB89;
    _ctx->state[2] = 0x98BADCFE;
    _ctx->state[3] = 0x10325476;
}

void a_rmd160_init(a_rmd160_t *_ctx)
{
    a_assert(_ctx);

    _ctx->cursiz = 0;
    _ctx->length = 0;

    _ctx->state[0] = 0x67452301;
    _ctx->state[1] = 0xEFCDAB89;
    _ctx->state[2] = 0x98BADCFE;
    _ctx->state[3] = 0x10325476;
    _ctx->state[4] = 0xC3D2E1F0;
}

void a_rmd256_init(a_rmd256_t *_ctx)
{
    a_assert(_ctx);

    _ctx->cursiz = 0;
    _ctx->length = 0;

    _ctx->state[0] = 0x67452301;
    _ctx->state[1] = 0xEFCDAB89;
    _ctx->state[2] = 0x98BADCFE;
    _ctx->state[3] = 0x10325476;
    _ctx->state[4] = 0x76543210;
    _ctx->state[5] = 0xFEDCBA98;
    _ctx->state[6] = 0x89ABCDEF;
    _ctx->state[7] = 0x01234567;
}

void a_rmd320_init(a_rmd320_t *_ctx)
{
    a_assert(_ctx);

    _ctx->cursiz = 0;
    _ctx->length = 0;

    _ctx->state[0] = 0x67452301;
    _ctx->state[1] = 0xEFCDAB89;
    _ctx->state[2] = 0x98BADCFE;
    _ctx->state[3] = 0x10325476;
    _ctx->state[4] = 0xC3D2E1F0;
    _ctx->state[5] = 0x76543210;
    _ctx->state[6] = 0xFEDCBA98;
    _ctx->state[7] = 0x89ABCDEF;
    _ctx->state[8] = 0x01234567;
    _ctx->state[9] = 0x3C2D1E0F;
}

__A_HASH_PROCESS(a_rmd128_t, a_rmd128_process, a_rmd128_compress)
__A_HASH_PROCESS(a_rmd160_t, a_rmd160_process, a_rmd160_compress)
__A_HASH_PROCESS(a_rmd256_t, a_rmd256_process, a_rmd256_compress)
__A_HASH_PROCESS(a_rmd320_t, a_rmd320_process, a_rmd320_compress)

__A_HASH_DONE(a_rmd128_t, a_rmd128_done, a_rmd128_compress, STORE64L, STORE32L, 0x80, 0x38, 0x38)
__A_HASH_DONE(a_rmd160_t, a_rmd160_done, a_rmd160_compress, STORE64L, STORE32L, 0x80, 0x38, 0x38)
__A_HASH_DONE(a_rmd256_t, a_rmd256_done, a_rmd256_compress, STORE64L, STORE32L, 0x80, 0x38, 0x38)
__A_HASH_DONE(a_rmd320_t, a_rmd320_done, a_rmd320_compress, STORE64L, STORE32L, 0x80, 0x38, 0x38)

/* END OF FILE */
