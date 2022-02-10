/*!
 @file a_blake2s.c
 @brief RFC 7693 compliant BLAKE implementation
 @details https://www.ietf.org/rfc/rfc7693.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_blake2s.h"

#include "a_hash.h"
#include "a_hash_private.h"

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

__STATIC_INLINE
void a_blake2s_set_lastnode(a_blake2s_s *ctx)
{
    ctx->f[1] = 0xFFFFFFFF;
}

__STATIC_INLINE
int a_blake2s_is_lastblock(const a_blake2s_s *ctx)
{
    return (ctx->f[0] != 0);
}

__STATIC_INLINE
void a_blake2s_set_lastblock(a_blake2s_s *ctx)
{
    if (ctx->lastnode)
    {
        a_blake2s_set_lastnode(ctx);
    }
    ctx->f[0] = 0xFFFFFFFF;
}

__STATIC_INLINE
void a_blake2s_increment_counter(a_blake2s_s *ctx, uint32_t inc)
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

static void a_blake2s_compress(a_blake2s_s *ctx, const unsigned char *buf)
{
    uint32_t v[0x10];
    uint32_t *m = (uint32_t *)ctx->buf;
    if (ctx->buf != buf)
    {
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD32L(m[i], buf + sizeof(*ctx->state) * i);
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

#define G(r, i, a, b, c, d)                            \
    do                                                 \
    {                                                  \
        a = a + b + m[blake2s_sigma[r][(i << 1) + 0]]; \
        d = ROR(d ^ a, 0x10);                          \
        c = c + d;                                     \
        b = ROR(b ^ c, 0x0C);                          \
        a = a + b + m[blake2s_sigma[r][(i << 1) + 1]]; \
        d = ROR(d ^ a, 0x08);                          \
        c = c + d;                                     \
        b = ROR(b ^ c, 0x07);                          \
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
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

int a_blake2s_init(a_blake2s_s *ctx, size_t siz, const void *pdata, size_t nbyte)
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
        ctx->state[i] = blake2s_IV[i];
    }

    /* IV XOR ParamBlock */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        uint32_t t;
        LOAD32L(t, ap + sizeof(*ctx->state) * i);
        ctx->state[i] ^= t;
    }

    ctx->outsiz = ap[O_DIGEST_LENGTH];

    if (pdata)
    {
        memcpy(ctx->buf, pdata, nbyte);
        a_blake2s_process(ctx, ctx->buf, sizeof(ctx->buf));
    }

    return A_HASH_SUCCESS;
}

#undef __A_BLAKE2S_INIT
#define __A_BLAKE2S_INIT(bit)                     \
    void a_blake2s_##bit##_init(a_blake2s_s *ctx) \
    {                                             \
        a_blake2s_init(ctx, (bit) >> 3, 0, 0);    \
    }
__A_BLAKE2S_INIT(128)
__A_BLAKE2S_INIT(160)
__A_BLAKE2S_INIT(224)
__A_BLAKE2S_INIT(256)
#undef __A_BLAKE2S_INIT

int a_blake2s_process(a_blake2s_s *ctx, const void *pdata, size_t nbyte)
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
        a_blake2s_increment_counter(ctx, sizeof(ctx->buf));
        a_blake2s_compress(ctx, ctx->buf);
        ctx->cursiz = 0;
        nbyte -= n;
        p += n;
        while (nbyte > sizeof(ctx->buf) - 1)
        {
            a_blake2s_increment_counter(ctx, sizeof(ctx->buf));
            a_blake2s_compress(ctx, p);
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

unsigned char *a_blake2s_done(a_blake2s_s *ctx, void *out)
{
    AASSERT(ctx);

    if (a_blake2s_is_lastblock(ctx))
    {
        return 0;
    }

    a_blake2s_increment_counter(ctx, ctx->cursiz);
    a_blake2s_set_lastblock(ctx);

    /* padding */
    memset(ctx->buf + ctx->cursiz, 0, sizeof(ctx->buf) - ctx->cursiz);
    a_blake2s_compress(ctx, ctx->buf);

    /* copy output */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        STORE32L(ctx->state[i], ctx->out + sizeof(*ctx->state) * i);
    }

    if (out && (out != ctx->out))
    {
        memcpy(out, ctx->out, ctx->outsiz);
    }

    return ctx->out;
}
