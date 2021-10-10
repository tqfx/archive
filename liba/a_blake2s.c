/*!
 @file           a_blake2s.c
 @brief          RFC 7693 compliant BLAKE implementation
 @details        https://www.ietf.org/rfc/rfc7693.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_blake2s.h"

#include <string.h> /* memset, memcpy */

static const uint32_t blake2s_IV[8] = {
    /* clang-format off */
    0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
    0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19,
    /* clang-format on */
};

static const unsigned char blake2s_sigma[10][0x10] = {
    /* clang-format off */
    {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF},
    {0xE, 0xA, 0x4, 0x8, 0x9, 0xF, 0xD, 0x6, 0x1, 0xC, 0x0, 0x2, 0xB, 0x7, 0x5, 0x3},
    {0xB, 0x8, 0xC, 0x0, 0x5, 0x2, 0xF, 0xD, 0xA, 0xE, 0x3, 0x6, 0x7, 0x1, 0x9, 0x4},
    {0x7, 0x9, 0x3, 0x1, 0xD, 0xC, 0xB, 0xE, 0x2, 0x6, 0x5, 0xA, 0x4, 0x0, 0xF, 0x8},
    {0x9, 0x0, 0x5, 0x7, 0x2, 0x4, 0xA, 0xF, 0xE, 0x1, 0xB, 0xC, 0x6, 0x8, 0x3, 0xD},
    {0x2, 0xC, 0x6, 0xA, 0x0, 0xB, 0x8, 0x3, 0x4, 0xD, 0x7, 0x5, 0xF, 0xE, 0x1, 0x9},
    {0xC, 0x5, 0x1, 0xF, 0xE, 0xD, 0x4, 0xA, 0x0, 0x7, 0x6, 0x3, 0x9, 0x2, 0x8, 0xB},
    {0xD, 0xB, 0x7, 0xE, 0xC, 0x1, 0x3, 0x9, 0x5, 0x0, 0xF, 0x4, 0x8, 0x6, 0x2, 0xA},
    {0x6, 0xF, 0xE, 0x9, 0xB, 0x3, 0x0, 0x8, 0xC, 0x2, 0xD, 0x7, 0x1, 0x4, 0xA, 0x5},
    {0xA, 0x2, 0x8, 0x4, 0x7, 0x6, 0x1, 0x5, 0xF, 0xB, 0x9, 0xE, 0x3, 0xC, 0xD, 0x0},
    /* clang-format on */
};

/* param offsets */
enum
{
    O_DIGEST_LENGTH = 0,
    O_KEY_LENGTH = 1,
    O_FANOUT = 2,
    O_DEPTH = 3,
    O_LEAF_LENGTH = 4,
    O_NODE_OFFSET = 8,
    O_XOF_LENGTH = 12,
    O_NODE_DEPTH = 14,
    O_INNER_LENGTH = 15,
    O_SALT = 16,
    O_PERSONAL = 24,
    A_PARAM_SIZE = 32,
};

static __inline void a_blake2s_set_lastnode(a_blake2s_t *ctx)
{
    ctx->f[1] = 0xFFFFFFFF;
}

static __inline int a_blake2s_is_lastblock(const a_blake2s_t *ctx)
{
    return (0 != ctx->f[0]);
}

static __inline void a_blake2s_set_lastblock(a_blake2s_t *ctx)
{
    if (ctx->lastnode)
    {
        a_blake2s_set_lastnode(ctx);
    }
    ctx->f[0] = 0xFFFFFFFF;
}

static __inline void a_blake2s_increment_counter(a_blake2s_t *ctx, uint32_t inc)
{
    ctx->t[0] += inc;
    if (ctx->t[0] < inc)
    {
        ++ctx->t[1];
    }
}

#undef G
#undef ROUND

void a_blake2s_compress(a_blake2s_t *ctx, const unsigned char *buf)
{
    uint32_t v[0x10];

    /* (unsigned char *) -> (uint32_t *) */
    union
    {
        uint32_t *m;
        unsigned char *buf;
    } up[1];
    up->buf = ctx->buf;
    if (ctx->buf != buf)
    {
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD32L(up->m[i], buf + sizeof(*ctx->state) * i);
        }
    }

    /* copy state into v */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        v[i] = ctx->state[i];
    }

    v[8] = blake2s_IV[0];
    v[9] = blake2s_IV[1];
    v[10] = blake2s_IV[2];
    v[11] = blake2s_IV[3];
    v[12] = ctx->t[0] ^ blake2s_IV[4];
    v[13] = ctx->t[1] ^ blake2s_IV[5];
    v[14] = ctx->f[0] ^ blake2s_IV[6];
    v[15] = ctx->f[1] ^ blake2s_IV[7];

#define G(r, i, a, b, c, d)                                \
    do                                                     \
    {                                                      \
        a = a + b + up->m[blake2s_sigma[r][(i << 1) + 0]]; \
        d = ROR(d ^ a, 0x10);                              \
        c = c + d;                                         \
        b = ROR(b ^ c, 0x0C);                              \
        a = a + b + up->m[blake2s_sigma[r][(i << 1) + 1]]; \
        d = ROR(d ^ a, 0x08);                              \
        c = c + d;                                         \
        b = ROR(b ^ c, 0x07);                              \
    } while (0)
#define ROUND(r)                                 \
    do                                           \
    {                                            \
        G(r, 0, v[0x0], v[0x4], v[0x8], v[0xC]); \
        G(r, 1, v[0x1], v[0x5], v[0x9], v[0xD]); \
        G(r, 2, v[0x2], v[0x6], v[0xA], v[0xE]); \
        G(r, 3, v[0x3], v[0x7], v[0xB], v[0xF]); \
        G(r, 4, v[0x0], v[0x5], v[0xA], v[0xF]); \
        G(r, 5, v[0x1], v[0x6], v[0xB], v[0xC]); \
        G(r, 6, v[0x2], v[0x7], v[0x8], v[0xD]); \
        G(r, 7, v[0x3], v[0x4], v[0x9], v[0xE]); \
    } while (0)

    ROUND(0);
    ROUND(1);
    ROUND(2);
    ROUND(3);
    ROUND(4);
    ROUND(5);
    ROUND(6);
    ROUND(7);
    ROUND(8);
    ROUND(9);

    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        ctx->state[i] = ctx->state[i] ^ v[i] ^ v[i + 8];
    }
}

#undef G
#undef ROUND

int a_blake2s_init(a_blake2s_t *ctx, size_t len, const void *p, size_t n)
{
    unsigned char ap[A_PARAM_SIZE] = {0};

    if ((0 == len) || (sizeof(ctx->out) < len))
    {
        return -1;
    }

    const unsigned char *s = (const unsigned char *)p;
    if ((s && !n) || (n && !s) || (sizeof(ctx->buf) < n))
    {
        return -1;
    }

    ap[O_DIGEST_LENGTH] = (unsigned char)len;
    ap[O_KEY_LENGTH] = (unsigned char)n;
    ap[O_FANOUT] = 1;
    ap[O_DEPTH] = 1;

    memset(ctx, 0, sizeof(*ctx));

    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        ctx->state[i] = blake2s_IV[i];
    }

    /* IV XOR ParamBlock */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        uint32_t t;
        LOAD32L(t, ap + sizeof(*ctx->state) * i);
        ctx->state[i] ^= t;
    }

    ctx->outlen = ap[O_DIGEST_LENGTH];

    if (s)
    {
        memcpy(ctx->buf, s, n);
        a_blake2s_process(ctx, ctx->buf, sizeof(ctx->buf));
    }

    return 0;
}

#undef __A_BLAKE2S_INIT
#define __A_BLAKE2S_INIT(bit, ctx)                \
    void a_blake2s_##bit##_init(a_blake2s_t *ctx) \
    {                                             \
        a_blake2s_init(ctx, (bit) >> 3, 0, 0);    \
    }
__A_BLAKE2S_INIT(128, ctx)
__A_BLAKE2S_INIT(160, ctx)
__A_BLAKE2S_INIT(224, ctx)
__A_BLAKE2S_INIT(256, ctx)
#undef __A_BLAKE2S_INIT

void a_blake2s_process(a_blake2s_t *ctx, const void *p, size_t n)
{
    const unsigned char *s = (const unsigned char *)p;
    if (n)
    {
        uint32_t m = sizeof(ctx->buf) - ctx->curlen;
        if (n > m)
        {
            memcpy(ctx->buf + ctx->curlen, s, m);
            a_blake2s_increment_counter(ctx, sizeof(ctx->buf));
            a_blake2s_compress(ctx, ctx->buf);
            ctx->curlen = 0;
            s += m;
            n -= m;
            while (n > sizeof(ctx->buf) - 1)
            {
                a_blake2s_increment_counter(ctx, sizeof(ctx->buf));
                a_blake2s_compress(ctx, s);
                s += sizeof(ctx->buf);
                n -= sizeof(ctx->buf);
            }
        }
        memcpy(ctx->buf + ctx->curlen, s, n);
        ctx->curlen += (uint32_t)n;
    }
}

unsigned char *a_blake2s_done(a_blake2s_t *ctx, unsigned char *out)
{
    if (a_blake2s_is_lastblock(ctx))
    {
        return 0;
    }

    a_blake2s_increment_counter(ctx, ctx->curlen);
    a_blake2s_set_lastblock(ctx);

    /* padding */
    memset(ctx->buf + ctx->curlen, 0, sizeof(ctx->buf) - ctx->curlen);
    a_blake2s_compress(ctx, ctx->buf);

    /* copy output */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        STORE32L(ctx->state[i], ctx->out + sizeof(*ctx->state) * i);
    }
    if (out && (out != ctx->out))
    {
        memcpy(out, ctx->out, ctx->outlen);
    }

    return ctx->out;
}

#undef __A_BLAKE2S
#define __A_BLAKE2S(func, size)                                        \
    unsigned char *func(const void *p, size_t n, unsigned char *out)   \
    {                                                                  \
        a_blake2s_t ctx[1];                                            \
                                                                       \
        func##_init(ctx);                                              \
        a_blake2s_process(ctx, p, n);                                  \
        a_blake2s_done(ctx, out);                                      \
                                                                       \
        if ((0 == out) && (out = (unsigned char *)a_alloc(size), out)) \
        {                                                              \
            memcpy(out, ctx->out, size);                               \
        }                                                              \
                                                                       \
        return out;                                                    \
    }
__A_BLAKE2S(a_blake2s_128, A_BLAKE2S_128_DIGESTSIZE)
__A_BLAKE2S(a_blake2s_160, A_BLAKE2S_160_DIGESTSIZE)
__A_BLAKE2S(a_blake2s_224, A_BLAKE2S_224_DIGESTSIZE)
__A_BLAKE2S(a_blake2s_256, A_BLAKE2S_256_DIGESTSIZE)
#undef __A_BLAKE2S

/* END OF FILE */
