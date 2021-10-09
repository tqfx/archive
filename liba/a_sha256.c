/*!
 @file           a_sha256.c
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha256.h"

#include <string.h> /* memcpy */

#undef Ch
#undef Maj
#undef S
#undef R
#undef Sigma0
#undef Sigma1
#undef Gamma0
#undef Gamma1

/* Various logical functions */
#define S(x, n)      RORc((x), (n))
#define R(x, n)      (((x)&0xFFFFFFFF) >> (n))
#define Ch(x, y, z)  (z ^ (x & (y ^ z)))
#define Maj(x, y, z) (((x | y) & z) | (x & y))
#define Sigma0(x)    (S(x, 2) ^ S(x, 13) ^ S(x, 22))
#define Sigma1(x)    (S(x, 6) ^ S(x, 11) ^ S(x, 25))
#define Gamma0(x)    (S(x, 7) ^ S(x, 18) ^ R(x, 3))
#define Gamma1(x)    (S(x, 17) ^ S(x, 19) ^ R(x, 10))

void a_sha256_compress(a_sha256_t *ctx, const unsigned char *buf)
{
    /* the k array */
    static const uint32_t k[0x40] = {
        0x428a2f98,
        0x71374491,
        0xb5c0fbcf,
        0xe9b5dba5,
        0x3956c25b,
        0x59f111f1,
        0x923f82a4,
        0xab1c5ed5,
        0xd807aa98,
        0x12835b01,
        0x243185be,
        0x550c7dc3,
        0x72be5d74,
        0x80deb1fe,
        0x9bdc06a7,
        0xc19bf174,
        0xe49b69c1,
        0xefbe4786,
        0x0fc19dc6,
        0x240ca1cc,
        0x2de92c6f,
        0x4a7484aa,
        0x5cb0a9dc,
        0x76f988da,
        0x983e5152,
        0xa831c66d,
        0xb00327c8,
        0xbf597fc7,
        0xc6e00bf3,
        0xd5a79147,
        0x06ca6351,
        0x14292967,
        0x27b70a85,
        0x2e1b2138,
        0x4d2c6dfc,
        0x53380d13,
        0x650a7354,
        0x766a0abb,
        0x81c2c92e,
        0x92722c85,
        0xa2bfe8a1,
        0xa81a664b,
        0xc24b8b70,
        0xc76c51a3,
        0xd192e819,
        0xd6990624,
        0xf40e3585,
        0x106aa070,
        0x19a4c116,
        0x1e376c08,
        0x2748774c,
        0x34b0bcb5,
        0x391c0cb3,
        0x4ed8aa4a,
        0x5b9cca4f,
        0x682e6ff3,
        0x748f82ee,
        0x78a5636f,
        0x84c87814,
        0x8cc70208,
        0x90befffa,
        0xa4506ceb,
        0xbef9a3f7,
        0xc67178f2,
    };

    uint32_t w[0x40], t0, t1;
    uint32_t s[sizeof(ctx->state) / sizeof(*ctx->state)];

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        s[i] = ctx->state[i];
    }

    /* copy the state into 512-bits into w[0..15] */
    for (unsigned int i = 0x00; i != 0x10; ++i)
    {
        LOAD32H(w[i], buf + (i << 2));
    }

    /* fill w[16..63] */
    for (unsigned int i = 0x10; i != 0x40; ++i)
    {
        w[i] = Gamma1(w[i - 2]) + w[i - 7] + Gamma0(w[i - 15]) + w[i - 16];
    }

    /* compress */

#define RND(a, b, c, d, e, f, g, h, i)              \
    t0 = h + Sigma1(e) + Ch(e, f, g) + k[i] + w[i]; \
    t1 = Sigma0(a) + Maj(a, b, c);                  \
    d += t0;                                        \
    h = t0 + t1;

    for (unsigned int i = 0; i != 0x40; i += 8)
    {
        RND(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], i + 0);
        RND(s[7], s[0], s[1], s[2], s[3], s[4], s[5], s[6], i + 1);
        RND(s[6], s[7], s[0], s[1], s[2], s[3], s[4], s[5], i + 2);
        RND(s[5], s[6], s[7], s[0], s[1], s[2], s[3], s[4], i + 3);
        RND(s[4], s[5], s[6], s[7], s[0], s[1], s[2], s[3], i + 4);
        RND(s[3], s[4], s[5], s[6], s[7], s[0], s[1], s[2], i + 5);
        RND(s[2], s[3], s[4], s[5], s[6], s[7], s[0], s[1], i + 6);
        RND(s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[0], i + 7);
    }

#undef RND

    /* feedback */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        ctx->state[i] += s[i];
    }
}

#undef S
#undef R
#undef Ch
#undef Maj
#undef Sigma0
#undef Sigma1
#undef Gamma0
#undef Gamma1

void a_sha256_init(a_sha256_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0x6A09E667;
    ctx->state[1] = 0xBB67AE85;
    ctx->state[2] = 0x3C6EF372;
    ctx->state[3] = 0xA54FF53A;
    ctx->state[4] = 0x510E527F;
    ctx->state[5] = 0x9B05688C;
    ctx->state[6] = 0x1F83D9AB;
    ctx->state[7] = 0x5BE0CD19;
}

void a_sha224_init(a_sha256_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0xc1059ed8;
    ctx->state[1] = 0x367cd507;
    ctx->state[2] = 0x3070dd17;
    ctx->state[3] = 0xf70e5939;
    ctx->state[4] = 0xffc00b31;
    ctx->state[5] = 0x68581511;
    ctx->state[6] = 0x64f98fa7;
    ctx->state[7] = 0xbefa4fa4;
}

__A_HASH_PROCESS(a_sha256_t, a_sha256_process, a_sha256_compress)

unsigned char *a_sha256_done(a_sha256_t *ctx, unsigned char *out)
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
        a_sha256_compress(ctx, ctx->buf);
        ctx->curlen = 0;
    }

    /* pad up to 56 bytes of zeroes */
    while (ctx->curlen < 0x38)
    {
        ctx->buf[ctx->curlen++] = 0;
    }

    /* store length */
    STORE64H(ctx->length, ctx->buf + 0x38);
    a_sha256_compress(ctx, ctx->buf);

    /* copy output */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        STORE32H(ctx->state[i], ctx->out + (i << 2));
    }
    if (out && out != ctx->out)
    {
        (void)memcpy(out, ctx->out, sizeof(ctx->state));
    }

    return ctx->out;
}

unsigned char *a_sha224_done(a_sha256_t *ctx, unsigned char *out)
{
    a_sha256_done(ctx, ctx->out);

    if (out && out != ctx->out)
    {
        (void)memcpy(out, ctx->out, A_SHA224_DIGESTSIZE);
    }

    return ctx->out;
}

#define __A_SHA256(func, size)                                       \
    unsigned char *func(const void *p, size_t n, unsigned char *out) \
    {                                                                \
        a_sha256_t ctx[1];                                           \
                                                                     \
        func##_init(ctx);                                            \
        a_sha256_process(ctx, p, n);                                 \
        func##_done(ctx, out);                                       \
                                                                     \
        if (0 == out && (out = (unsigned char *)a_alloc(size)))      \
        {                                                            \
            (void)memcpy(out, ctx->out, size);                       \
        }                                                            \
                                                                     \
        return out;                                                  \
    }
__A_SHA256(a_sha256, sizeof(ctx->state))
__A_SHA256(a_sha224, A_SHA224_DIGESTSIZE)

/* END OF FILE */
