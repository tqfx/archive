/*!
 @file           a_md5.c
 @brief          RFC 1321 compliant MD5 implementation
 @details        https://www.ietf.org/rfc/rfc1321.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_md5.h"

#include <string.h> /* memcpy */

#undef F
#undef G
#undef H
#undef I
#undef FF
#undef GG
#undef HH
#undef II

void a_md5_compress(a_md5_t *ctx, const unsigned char *buf)
{
    /* copy state */
    uint32_t a = ctx->state[0];
    uint32_t b = ctx->state[1];
    uint32_t c = ctx->state[2];
    uint32_t d = ctx->state[3];

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

    /* compress */

#define F(x, y, z) ((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z) ((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | ~(z)))

#define FF(a, b, c, d, M, s, t)   \
    a = (a + F(b, c, d) + M + t); \
    a = ROLc(a, s) + b;
#define GG(a, b, c, d, M, s, t)   \
    a = (a + G(b, c, d) + M + t); \
    a = ROLc(a, s) + b;
#define HH(a, b, c, d, M, s, t)   \
    a = (a + H(b, c, d) + M + t); \
    a = ROLc(a, s) + b;
#define II(a, b, c, d, M, s, t)   \
    a = (a + I(b, c, d) + M + t); \
    a = ROLc(a, s) + b;

    /* round one */
    FF(a, b, c, d, up->w[0x0], 0x07, 0xd76aa478)
    FF(d, a, b, c, up->w[0x1], 0x0c, 0xe8c7b756)
    FF(c, d, a, b, up->w[0x2], 0x11, 0x242070db)
    FF(b, c, d, a, up->w[0x3], 0x16, 0xc1bdceee)
    FF(a, b, c, d, up->w[0x4], 0x07, 0xf57c0faf)
    FF(d, a, b, c, up->w[0x5], 0x0c, 0x4787c62a)
    FF(c, d, a, b, up->w[0x6], 0x11, 0xa8304613)
    FF(b, c, d, a, up->w[0x7], 0x16, 0xfd469501)
    FF(a, b, c, d, up->w[0x8], 0x07, 0x698098d8)
    FF(d, a, b, c, up->w[0x9], 0x0c, 0x8b44f7af)
    FF(c, d, a, b, up->w[0xa], 0x11, 0xffff5bb1)
    FF(b, c, d, a, up->w[0xb], 0x16, 0x895cd7be)
    FF(a, b, c, d, up->w[0xc], 0x07, 0x6b901122)
    FF(d, a, b, c, up->w[0xd], 0x0c, 0xfd987193)
    FF(c, d, a, b, up->w[0xe], 0x11, 0xa679438e)
    FF(b, c, d, a, up->w[0xf], 0x16, 0x49b40821)
    /* round two */
    GG(a, b, c, d, up->w[0x1], 0x05, 0xf61e2562)
    GG(d, a, b, c, up->w[0x6], 0x09, 0xc040b340)
    GG(c, d, a, b, up->w[0xb], 0x0e, 0x265e5a51)
    GG(b, c, d, a, up->w[0x0], 0x14, 0xe9b6c7aa)
    GG(a, b, c, d, up->w[0x5], 0x05, 0xd62f105d)
    GG(d, a, b, c, up->w[0xa], 0x09, 0x02441453)
    GG(c, d, a, b, up->w[0xf], 0x0e, 0xd8a1e681)
    GG(b, c, d, a, up->w[0x4], 0x14, 0xe7d3fbc8)
    GG(a, b, c, d, up->w[0x9], 0x05, 0x21e1cde6)
    GG(d, a, b, c, up->w[0xe], 0x09, 0xc33707d6)
    GG(c, d, a, b, up->w[0x3], 0x0e, 0xf4d50d87)
    GG(b, c, d, a, up->w[0x8], 0x14, 0x455a14ed)
    GG(a, b, c, d, up->w[0xd], 0x05, 0xa9e3e905)
    GG(d, a, b, c, up->w[0x2], 0x09, 0xfcefa3f8)
    GG(c, d, a, b, up->w[0x7], 0x0e, 0x676f02d9)
    GG(b, c, d, a, up->w[0xc], 0x14, 0x8d2a4c8a)
    /* round three */
    HH(a, b, c, d, up->w[0x5], 0x04, 0xfffa3942)
    HH(d, a, b, c, up->w[0x8], 0x0b, 0x8771f681)
    HH(c, d, a, b, up->w[0xb], 0x10, 0x6d9d6122)
    HH(b, c, d, a, up->w[0xe], 0x17, 0xfde5380c)
    HH(a, b, c, d, up->w[0x1], 0x04, 0xa4beea44)
    HH(d, a, b, c, up->w[0x4], 0x0b, 0x4bdecfa9)
    HH(c, d, a, b, up->w[0x7], 0x10, 0xf6bb4b60)
    HH(b, c, d, a, up->w[0xa], 0x17, 0xbebfbc70)
    HH(a, b, c, d, up->w[0xd], 0x04, 0x289b7ec6)
    HH(d, a, b, c, up->w[0x0], 0x0b, 0xeaa127fa)
    HH(c, d, a, b, up->w[0x3], 0x10, 0xd4ef3085)
    HH(b, c, d, a, up->w[0x6], 0x17, 0x04881d05)
    HH(a, b, c, d, up->w[0x9], 0x04, 0xd9d4d039)
    HH(d, a, b, c, up->w[0xc], 0x0b, 0xe6db99e5)
    HH(c, d, a, b, up->w[0xf], 0x10, 0x1fa27cf8)
    HH(b, c, d, a, up->w[0x2], 0x17, 0xc4ac5665)
    /* round four */
    II(a, b, c, d, up->w[0x0], 0x06, 0xf4292244)
    II(d, a, b, c, up->w[0x7], 0x0a, 0x432aff97)
    II(c, d, a, b, up->w[0xe], 0x0f, 0xab9423a7)
    II(b, c, d, a, up->w[0x5], 0x15, 0xfc93a039)
    II(a, b, c, d, up->w[0xc], 0x06, 0x655b59c3)
    II(d, a, b, c, up->w[0x3], 0x0a, 0x8f0ccc92)
    II(c, d, a, b, up->w[0xa], 0x0f, 0xffeff47d)
    II(b, c, d, a, up->w[0x1], 0x15, 0x85845dd1)
    II(a, b, c, d, up->w[0x8], 0x06, 0x6fa87e4f)
    II(d, a, b, c, up->w[0xf], 0x0a, 0xfe2ce6e0)
    II(c, d, a, b, up->w[0x6], 0x0f, 0xa3014314)
    II(b, c, d, a, up->w[0xd], 0x15, 0x4e0811a1)
    II(a, b, c, d, up->w[0x4], 0x06, 0xf7537e82)
    II(d, a, b, c, up->w[0xb], 0x0a, 0xbd3af235)
    II(c, d, a, b, up->w[0x2], 0x0f, 0x2ad7d2bb)
    II(b, c, d, a, up->w[0x9], 0x15, 0xeb86d391)

    /* store */
    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
}

#undef FF
#undef GG
#undef HH
#undef II
#undef F
#undef G
#undef H
#undef I

void a_md5_init(a_md5_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xefcdab89;
    ctx->state[2] = 0x98badcfe;
    ctx->state[3] = 0x10325476;
}

void a_md5_process(a_md5_t *ctx, const void *p, size_t n)
{
    const unsigned char *s = (const unsigned char *)p;

    while (n)
    {
        if ((0 == ctx->curlen) && (A_MD5_BLOCKSIZE - 1 < n))
        {
            a_md5_compress(ctx, s);
            ctx->length += (A_MD5_BLOCKSIZE << 3);
            s += A_MD5_BLOCKSIZE;
            n -= A_MD5_BLOCKSIZE;
        }
        else
        {
            uint32_t m = A_MD5_BLOCKSIZE - ctx->curlen;
            m = n < m ? (uint32_t)n : m;
            (void)memcpy(ctx->buf + ctx->curlen, s, m);
            ctx->curlen += m;
            s += m;
            n -= m;
            if (A_MD5_BLOCKSIZE == ctx->curlen)
            {
                a_md5_compress(ctx, ctx->buf);
                ctx->length += (A_MD5_BLOCKSIZE << 3);
                ctx->curlen = 0;
            }
        }
    }
}

unsigned char *a_md5_done(a_md5_t *ctx, unsigned char *out)
{
    if (A_MD5_BLOCKSIZE - 1 < ctx->curlen)
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
        a_md5_compress(ctx, ctx->buf);
        ctx->curlen = 0;
    }

    /* pad up to 56 bytes of zeroes */
    while (ctx->curlen < 0x38)
    {
        ctx->buf[ctx->curlen++] = 0;
    }

    /* store length */
    STORE64L(ctx->length, ctx->buf + 0x38);
    a_md5_compress(ctx, ctx->buf);

    /* copy output */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        STORE32L(ctx->state[i], ctx->out + (i << 2));
    }
    if (out && ctx->out != out)
    {
        (void)memcpy(out, ctx->out, sizeof(ctx->state));
    }

    return ctx->out;
}

unsigned char *a_md5(const void *p, size_t n, unsigned char *out)
{
    a_md5_t ctx[1];

    a_md5_init(ctx);
    a_md5_process(ctx, p, n);
    a_md5_done(ctx, out);

    if (0 == out && (out = (unsigned char *)a_alloc(sizeof(ctx->state))))
    {
        (void)memcpy(out, ctx->out, sizeof(ctx->state));
    }

    return out;
}

/* END OF FILE */
