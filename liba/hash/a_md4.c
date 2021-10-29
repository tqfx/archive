/*!
 @file           a_md4.c
 @brief          RFC 1320 compliant MD4 implementation
 @details        https://www.ietf.org/rfc/rfc1320.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_md4.h"

#include "a_hash.h"

#undef F
#undef G
#undef H
#undef I
#undef FF
#undef GG
#undef HH
#undef II

static void a_md4_compress(a_md4_t *_ctx, const unsigned char *_buf)
{
    uint32_t s[sizeof(_ctx->state) / sizeof(*_ctx->state)];

    /* (unsigned char *) -> (uint32_t *) */
    union
    {
        uint32_t *w;
        unsigned char *buf;
    } up[1];
    up->buf = _ctx->buf;
    if (_ctx->buf != _buf)
    {
        /* copy the state into 512-bits into w[0..15] */
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD32L(up->w[i], _buf + sizeof(*_ctx->state) * i);
        }
    }

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        s[i] = _ctx->state[i];
    }

    /* compress */

#define F(_x, _y, _z) (_z ^ (_x & (_y ^ _z)))
#define G(_x, _y, _z) ((_x & _y) | (_z & (_x | _y)))
#define H(_x, _y, _z) ((_x) ^ (_y) ^ (_z))

#define FF(_a, _b, _c, _d, _x, _s)      \
    (_a) += F((_b), (_c), (_d)) + (_x); \
    (_a) = ROLc((_a), (_s));
#define GG(_a, _b, _c, _d, _x, _s)                   \
    (_a) += G((_b), (_c), (_d)) + (_x) + 0x5A827999; \
    (_a) = ROLc((_a), (_s));
#define HH(_a, _b, _c, _d, _x, _s)                   \
    (_a) += H((_b), (_c), (_d)) + (_x) + 0x6ED9EBA1; \
    (_a) = ROLc((_a), (_s));

    /* Round 1 */
    FF(s[0], s[1], s[2], s[3], up->w[0x0], 0x03);
    FF(s[3], s[0], s[1], s[2], up->w[0x1], 0x07);
    FF(s[2], s[3], s[0], s[1], up->w[0x2], 0x0B);
    FF(s[1], s[2], s[3], s[0], up->w[0x3], 0x13);
    FF(s[0], s[1], s[2], s[3], up->w[0x4], 0x03);
    FF(s[3], s[0], s[1], s[2], up->w[0x5], 0x07);
    FF(s[2], s[3], s[0], s[1], up->w[0x6], 0x0B);
    FF(s[1], s[2], s[3], s[0], up->w[0x7], 0x13);
    FF(s[0], s[1], s[2], s[3], up->w[0x8], 0x03);
    FF(s[3], s[0], s[1], s[2], up->w[0x9], 0x07);
    FF(s[2], s[3], s[0], s[1], up->w[0xA], 0x0B);
    FF(s[1], s[2], s[3], s[0], up->w[0xB], 0x13);
    FF(s[0], s[1], s[2], s[3], up->w[0xC], 0x03);
    FF(s[3], s[0], s[1], s[2], up->w[0xD], 0x07);
    FF(s[2], s[3], s[0], s[1], up->w[0xE], 0x0B);
    FF(s[1], s[2], s[3], s[0], up->w[0xF], 0x13);
    /* Round 2 */
    GG(s[0], s[1], s[2], s[3], up->w[0x0], 0x03);
    GG(s[3], s[0], s[1], s[2], up->w[0x4], 0x05);
    GG(s[2], s[3], s[0], s[1], up->w[0x8], 0x09);
    GG(s[1], s[2], s[3], s[0], up->w[0xC], 0x0D);
    GG(s[0], s[1], s[2], s[3], up->w[0x1], 0x03);
    GG(s[3], s[0], s[1], s[2], up->w[0x5], 0x05);
    GG(s[2], s[3], s[0], s[1], up->w[0x9], 0x09);
    GG(s[1], s[2], s[3], s[0], up->w[0xD], 0x0D);
    GG(s[0], s[1], s[2], s[3], up->w[0x2], 0x03);
    GG(s[3], s[0], s[1], s[2], up->w[0x6], 0x05);
    GG(s[2], s[3], s[0], s[1], up->w[0xA], 0x09);
    GG(s[1], s[2], s[3], s[0], up->w[0xE], 0x0D);
    GG(s[0], s[1], s[2], s[3], up->w[0x3], 0x03);
    GG(s[3], s[0], s[1], s[2], up->w[0x7], 0x05);
    GG(s[2], s[3], s[0], s[1], up->w[0xB], 0x09);
    GG(s[1], s[2], s[3], s[0], up->w[0xF], 0x0D);
    /* Round 3 */
    HH(s[0], s[1], s[2], s[3], up->w[0x0], 0x03);
    HH(s[3], s[0], s[1], s[2], up->w[0x8], 0x09);
    HH(s[2], s[3], s[0], s[1], up->w[0x4], 0x0B);
    HH(s[1], s[2], s[3], s[0], up->w[0xC], 0x0F);
    HH(s[0], s[1], s[2], s[3], up->w[0x2], 0x03);
    HH(s[3], s[0], s[1], s[2], up->w[0xA], 0x09);
    HH(s[2], s[3], s[0], s[1], up->w[0x6], 0x0B);
    HH(s[1], s[2], s[3], s[0], up->w[0xE], 0x0F);
    HH(s[0], s[1], s[2], s[3], up->w[0x1], 0x03);
    HH(s[3], s[0], s[1], s[2], up->w[0x9], 0x09);
    HH(s[2], s[3], s[0], s[1], up->w[0x5], 0x0B);
    HH(s[1], s[2], s[3], s[0], up->w[0xD], 0x0F);
    HH(s[0], s[1], s[2], s[3], up->w[0x3], 0x03);
    HH(s[3], s[0], s[1], s[2], up->w[0xB], 0x09);
    HH(s[2], s[3], s[0], s[1], up->w[0x7], 0x0B);
    HH(s[1], s[2], s[3], s[0], up->w[0xF], 0x0F);

    /* feedback */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        _ctx->state[i] += s[i];
    }
}

#undef FF
#undef GG
#undef HH
#undef II
#undef F
#undef G
#undef H
#undef I

void a_md4_init(a_md4_t *_ctx)
{
    aassert(_ctx);

    _ctx->cursiz = 0;
    _ctx->length = 0;

    _ctx->state[0] = 0x67452301;
    _ctx->state[1] = 0xEFCDAB89;
    _ctx->state[2] = 0x98BADCFE;
    _ctx->state[3] = 0x10325476;
}

__A_HASH_PROCESS(a_md4_t, a_md4_process, a_md4_compress)

__A_HASH_DONE(a_md4_t, a_md4_done, a_md4_compress, STORE64L, STORE32L, 0x80, 0x38, 0x38)

/* END OF FILE */
