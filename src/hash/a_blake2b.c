/*!
 @file a_blake2b.c
 @brief RFC 7693 compliant BLAKE implementation
 @details https://www.ietf.org/rfc/rfc7693.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_blake2b.h"

#include "a_hash.h"
#include "a_hash_private.h"

static const uint64_t blake2b_IV[8] = {
    /* clang-format off */
    0x6A09E667F3BCC908, 0xBB67AE8584CAA73B, 0x3C6EF372FE94F82B, 0xA54FF53A5F1D36F1,
    0x510E527FADE682D1, 0x9B05688C2B3E6C1F, 0x1F83D9ABFB41BD6B, 0x5BE0CD19137E2179,
    /* clang-format on */
};

static const unsigned char blake2b_sigma[12][0x10] = {
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
    {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF},
    {0xE, 0xA, 0x4, 0x8, 0x9, 0xF, 0xD, 0x6, 0x1, 0xC, 0x0, 0x2, 0xB, 0x7, 0x5, 0x3},
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
    O_NODE_DEPTH = 16,
    O_INNER_LENGTH = 17,
    O_RESERVED = 18,
    O_SALT = 32,
    O_PERSONAL = 48,
    A_PARAM_SIZE = 64,
};

__STATIC_INLINE
void a_blake2b_set_lastnode(a_blake2b_s *ctx)
{
    ctx->f[1] = 0xFFFFFFFFFFFFFFFF;
}

__STATIC_INLINE
int a_blake2b_is_lastblock(const a_blake2b_s *ctx)
{
    return (ctx->f[0] != 0);
}

__STATIC_INLINE
void a_blake2b_set_lastblock(a_blake2b_s *ctx)
{
    if (ctx->lastnode)
    {
        a_blake2b_set_lastnode(ctx);
    }
    ctx->f[0] = 0xFFFFFFFFFFFFFFFF;
}

__STATIC_INLINE
void a_blake2b_increment_counter(a_blake2b_s *ctx, uint64_t inc)
{
    ctx->t[0] += inc;
    if (ctx->t[0] < inc)
    {
        ++ctx->t[1];
    }
}

#undef G
#undef ROUND
#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-align"
#endif /* _MSC_VER */

static void a_blake2b_compress(a_blake2b_s *ctx, const unsigned char *buf)
{
    uint64_t v[0x10];
    uint64_t *m = (uint64_t *)ctx->buf;
    if (ctx->buf != buf)
    {
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD64L(m[i], buf + sizeof(*ctx->state) * i);
        }
    }

    /* copy state into v */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        v[i] = ctx->state[i];
    }

    v[8] = blake2b_IV[0];
    v[9] = blake2b_IV[1];
    v[10] = blake2b_IV[2];
    v[11] = blake2b_IV[3];
    v[12] = ctx->t[0] ^ blake2b_IV[4];
    v[13] = ctx->t[1] ^ blake2b_IV[5];
    v[14] = ctx->f[0] ^ blake2b_IV[6];
    v[15] = ctx->f[1] ^ blake2b_IV[7];

#define G(r, i, a, b, c, d)                            \
    do                                                 \
    {                                                  \
        a = a + b + m[blake2b_sigma[r][(i << 1) + 0]]; \
        d = ROR64(d ^ a, 0x20);                        \
        c = c + d;                                     \
        b = ROR64(b ^ c, 0x18);                        \
        a = a + b + m[blake2b_sigma[r][(i << 1) + 1]]; \
        d = ROR64(d ^ a, 0x10);                        \
        c = c + d;                                     \
        b = ROR64(b ^ c, 0x3F);                        \
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

    ROUND(0x0);
    ROUND(0x1);
    ROUND(0x2);
    ROUND(0x3);
    ROUND(0x4);
    ROUND(0x5);
    ROUND(0x6);
    ROUND(0x7);
    ROUND(0x8);
    ROUND(0x9);
    ROUND(0xA);
    ROUND(0xB);

    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        ctx->state[i] = ctx->state[i] ^ v[i] ^ v[i + 8];
    }
}

#undef G
#undef ROUND
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

int a_blake2b_init(a_blake2b_s *ctx, size_t siz, const void *pdata, size_t nbyte)
{
    AASSERT(ctx);

    unsigned char ap[A_PARAM_SIZE] = {0};

    if ((siz == 0) || (sizeof(ctx->out) < siz))
    {
        return A_HASH_INVALID;
    }

    if ((pdata && !nbyte) || (nbyte && !pdata) || (sizeof(ctx->buf) < nbyte))
    {
        return A_HASH_INVALID;
    }

    ap[O_DIGEST_LENGTH] = (unsigned char)siz;
    ap[O_KEY_LENGTH] = (unsigned char)nbyte;
    ap[O_FANOUT] = 1;
    ap[O_DEPTH] = 1;

    memset(ctx, 0, sizeof(*ctx));

    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        ctx->state[i] = blake2b_IV[i];
    }

    /* IV XOR ParamBlock */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        uint64_t t;
        LOAD64L(t, ap + sizeof(*ctx->state) * i);
        ctx->state[i] ^= t;
    }

    ctx->outsiz = ap[O_DIGEST_LENGTH];

    if (pdata)
    {
        memcpy(ctx->buf, pdata, nbyte);
        a_blake2b_process(ctx, ctx->buf, sizeof(ctx->buf));
    }

    return A_HASH_SUCCESS;
}

#undef __A_BLAKE2B_INIT
#define __A_BLAKE2B_INIT(_bit)                     \
    void a_blake2b_##_bit##_init(a_blake2b_s *ctx) \
    {                                              \
        a_blake2b_init(ctx, (_bit) >> 3, 0, 0);    \
    }
__A_BLAKE2B_INIT(160)
__A_BLAKE2B_INIT(256)
__A_BLAKE2B_INIT(384)
__A_BLAKE2B_INIT(512)
#undef __A_BLAKE2B_INIT

int a_blake2b_process(a_blake2b_s *ctx, const void *pdata, size_t nbyte)
{
    AASSERT(ctx);
    AASSERT(!nbyte || pdata);

    if (sizeof(ctx->buf) < ctx->cursiz)
    {
        return A_HASH_INVALID;
    }

    const unsigned char *p = (const unsigned char *)pdata;
    uint32_t n = (uint32_t)sizeof(ctx->buf) - ctx->cursiz;
    if (nbyte > n)
    {
        memcpy(ctx->buf + ctx->cursiz, p, n);
        a_blake2b_increment_counter(ctx, sizeof(ctx->buf));
        a_blake2b_compress(ctx, ctx->buf);
        ctx->cursiz = 0;
        nbyte -= n;
        p += n;
        while (nbyte > sizeof(ctx->buf) - 1)
        {
            a_blake2b_increment_counter(ctx, sizeof(ctx->buf));
            a_blake2b_compress(ctx, p);
            nbyte -= sizeof(ctx->buf);
            p += sizeof(ctx->buf);
        }
    }
    if (nbyte)
    {
        memcpy(ctx->buf + ctx->cursiz, p, nbyte);
        ctx->cursiz += (uint32_t)nbyte;
    }

    return A_HASH_SUCCESS;
}

unsigned char *a_blake2b_done(a_blake2b_s *ctx, void *out)
{
    AASSERT(ctx);

    if (a_blake2b_is_lastblock(ctx))
    {
        return 0;
    }

    a_blake2b_increment_counter(ctx, ctx->cursiz);
    a_blake2b_set_lastblock(ctx);

    /* padding */
    memset(ctx->buf + ctx->cursiz, 0, sizeof(ctx->buf) - ctx->cursiz);
    a_blake2b_compress(ctx, ctx->buf);

    /* copy output */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        STORE64L(ctx->state[i], ctx->out + sizeof(*ctx->state) * i);
    }

    if (out && (out != ctx->out))
    {
        memcpy(out, ctx->out, ctx->outsiz);
    }

    return ctx->out;
}
