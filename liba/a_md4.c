/*!
 @file           a_md4.c
 @brief          RFC 1320 compliant MD4 implementation
 @details        https://www.ietf.org/rfc/rfc1320.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_md4.h"

#include <string.h> /* memcpy */

#undef F
#undef G
#undef H
#undef I
#undef FF
#undef GG
#undef HH
#undef II

void a_md4_compress(a_md4_t *ctx, const unsigned char *buf)
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
            LOAD32L(up->w[i], buf + (i << 2));
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
    (a) += G((b), (c), (d)) + (x) + 0x5a827999; \
    (a) = ROLc((a), (s));
#define HH(a, b, c, d, x, s)                    \
    (a) += H((b), (c), (d)) + (x) + 0x6ed9eba1; \
    (a) = ROLc((a), (s));

    /* Round 1 */
    FF(s[0], s[1], s[2], s[3], up->w[0x0], 0x03);
    FF(s[3], s[0], s[1], s[2], up->w[0x1], 0x07);
    FF(s[2], s[3], s[0], s[1], up->w[0x2], 0x0b);
    FF(s[1], s[2], s[3], s[0], up->w[0x3], 0x13);
    FF(s[0], s[1], s[2], s[3], up->w[0x4], 0x03);
    FF(s[3], s[0], s[1], s[2], up->w[0x5], 0x07);
    FF(s[2], s[3], s[0], s[1], up->w[0x6], 0x0b);
    FF(s[1], s[2], s[3], s[0], up->w[0x7], 0x13);
    FF(s[0], s[1], s[2], s[3], up->w[0x8], 0x03);
    FF(s[3], s[0], s[1], s[2], up->w[0x9], 0x07);
    FF(s[2], s[3], s[0], s[1], up->w[0xa], 0x0b);
    FF(s[1], s[2], s[3], s[0], up->w[0xb], 0x13);
    FF(s[0], s[1], s[2], s[3], up->w[0xc], 0x03);
    FF(s[3], s[0], s[1], s[2], up->w[0xd], 0x07);
    FF(s[2], s[3], s[0], s[1], up->w[0xe], 0x0b);
    FF(s[1], s[2], s[3], s[0], up->w[0xf], 0x13);
    /* Round 2 */
    GG(s[0], s[1], s[2], s[3], up->w[0x0], 0x03);
    GG(s[3], s[0], s[1], s[2], up->w[0x4], 0x05);
    GG(s[2], s[3], s[0], s[1], up->w[0x8], 0x09);
    GG(s[1], s[2], s[3], s[0], up->w[0xc], 0x0d);
    GG(s[0], s[1], s[2], s[3], up->w[0x1], 0x03);
    GG(s[3], s[0], s[1], s[2], up->w[0x5], 0x05);
    GG(s[2], s[3], s[0], s[1], up->w[0x9], 0x09);
    GG(s[1], s[2], s[3], s[0], up->w[0xd], 0x0d);
    GG(s[0], s[1], s[2], s[3], up->w[0x2], 0x03);
    GG(s[3], s[0], s[1], s[2], up->w[0x6], 0x05);
    GG(s[2], s[3], s[0], s[1], up->w[0xa], 0x09);
    GG(s[1], s[2], s[3], s[0], up->w[0xe], 0x0d);
    GG(s[0], s[1], s[2], s[3], up->w[0x3], 0x03);
    GG(s[3], s[0], s[1], s[2], up->w[0x7], 0x05);
    GG(s[2], s[3], s[0], s[1], up->w[0xb], 0x09);
    GG(s[1], s[2], s[3], s[0], up->w[0xf], 0x0d);
    /* Round 3 */
    HH(s[0], s[1], s[2], s[3], up->w[0x0], 0x03);
    HH(s[3], s[0], s[1], s[2], up->w[0x8], 0x09);
    HH(s[2], s[3], s[0], s[1], up->w[0x4], 0x0b);
    HH(s[1], s[2], s[3], s[0], up->w[0xc], 0x0f);
    HH(s[0], s[1], s[2], s[3], up->w[0x2], 0x03);
    HH(s[3], s[0], s[1], s[2], up->w[0xa], 0x09);
    HH(s[2], s[3], s[0], s[1], up->w[0x6], 0x0b);
    HH(s[1], s[2], s[3], s[0], up->w[0xe], 0x0f);
    HH(s[0], s[1], s[2], s[3], up->w[0x1], 0x03);
    HH(s[3], s[0], s[1], s[2], up->w[0x9], 0x09);
    HH(s[2], s[3], s[0], s[1], up->w[0x5], 0x0b);
    HH(s[1], s[2], s[3], s[0], up->w[0xd], 0x0f);
    HH(s[0], s[1], s[2], s[3], up->w[0x3], 0x03);
    HH(s[3], s[0], s[1], s[2], up->w[0xb], 0x09);
    HH(s[2], s[3], s[0], s[1], up->w[0x7], 0x0b);
    HH(s[1], s[2], s[3], s[0], up->w[0xf], 0x0f);

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
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xefcdab89;
    ctx->state[2] = 0x98badcfe;
    ctx->state[3] = 0x10325476;
}

__A_HASH_PROCESS(a_md4_t, a_md4_process, a_md4_compress)

unsigned char *a_md4_done(a_md4_t *ctx, unsigned char *out)
{
    if (sizeof(ctx->buf) - 1 < ctx->curlen)
    {
        return 0;
    }

    /* increase the length of the message */
    ctx->length += (ctx->curlen << 3);

    /* append the '1' bit */
    ctx->buf[ctx->curlen++] = 0x80;

    /* if the length is currently above 56 bytes we append zeros
     * then compress. Then we can fall back to padding zeros and length
     * encoding like normal.
     */
    if (0x38 < ctx->curlen)
    {
        while (ctx->curlen < 0x40)
        {
            ctx->buf[ctx->curlen++] = 0;
        }
        a_md4_compress(ctx, ctx->buf);
        ctx->curlen = 0;
    }

    /* pad up to 56 bytes of zeroes */
    while (ctx->curlen < 0x38)
    {
        ctx->buf[ctx->curlen++] = 0;
    }

    /* store length */
    STORE64L(ctx->length, ctx->buf + 0x38);
    a_md4_compress(ctx, ctx->buf);

    /* copy output */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        STORE32L(ctx->state[i], ctx->out + (i << 2));
    }
    if (out && out != ctx->out)
    {
        (void)memcpy(out, ctx->out, sizeof(ctx->state));
    }

    return ctx->out;
}

unsigned char *a_md4(const void *p, size_t n, unsigned char *out)
{
    a_md4_t ctx[1];

    a_md4_init(ctx);
    a_md4_process(ctx, p, n);
    a_md4_done(ctx, out);

    if (0 == out && (out = (unsigned char *)a_alloc(sizeof(ctx->state))))
    {
        (void)memcpy(out, ctx->out, sizeof(ctx->state));
    }

    return out;
}

/* END OF FILE */
