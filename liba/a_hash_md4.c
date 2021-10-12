/*!
 @file           a_hash_md4.c
 @brief          RFC 1320 compliant MD4 implementation
 @details        https://www.ietf.org/rfc/rfc1320.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_hash.h"

#undef F
#undef G
#undef H
#undef I
#undef FF
#undef GG
#undef HH
#undef II

static void a_md4_compress(a_md4_t *ctx, const unsigned char *buf)
{
    uint32_t s[sizeof(ctx->state) / sizeof(*ctx->state)];

    /* (unsigned char *) -> (uint32_t *) */
    union
    {
        uint32_t *w;
        unsigned char *buf;
    } up[1];
    up->buf = ctx->buf;
    if (ctx->buf != buf)
    {
        /* copy the state into 512-bits into w[0..15] */
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD32L(up->w[i], buf + sizeof(*ctx->state) * i);
        }
    }

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        s[i] = ctx->state[i];
    }

    /* compress */

#define F(x, y, z) (z ^ (x & (y ^ z)))
#define G(x, y, z) ((x & y) | (z & (x | y)))
#define H(x, y, z) ((x) ^ (y) ^ (z))

#define FF(a, b, c, d, x, s)       \
    (a) += F((b), (c), (d)) + (x); \
    (a) = ROLc((a), (s));
#define GG(a, b, c, d, x, s)                    \
    (a) += G((b), (c), (d)) + (x) + 0x5A827999; \
    (a) = ROLc((a), (s));
#define HH(a, b, c, d, x, s)                    \
    (a) += H((b), (c), (d)) + (x) + 0x6ED9EBA1; \
    (a) = ROLc((a), (s));

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
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        ctx->state[i] += s[i];
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

void a_md4_init(a_md4_t *ctx)
{
    /* assert(ctx) */
    ctx->cursiz = 0;
    ctx->length = 0;

    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
}

__A_HASH_PROCESS(a_md4_t, a_md4_process, a_md4_compress)

__A_HASH_DONE(a_md4_t, a_md4_done, a_md4_compress, STORE64L, STORE32L, 0x80, 0x38, 0x38)

/* END OF FILE */
