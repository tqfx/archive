/*!
 @file           a_blake2b.c
 @brief          RFC 7693 compliant BLAKE implementation
 @details        https://www.ietf.org/rfc/rfc7693.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_blake2b.h"

#include "a_hash.h"

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

static __INLINE void a_blake2b_set_lastnode(a_blake2b_t *_ctx)
{
    _ctx->f[1] = 0xFFFFFFFFFFFFFFFF;
}

static __INLINE int a_blake2b_is_lastblock(const a_blake2b_t *_ctx)
{
    return (0 != _ctx->f[0]);
}

static __INLINE void a_blake2b_set_lastblock(a_blake2b_t *_ctx)
{
    if (_ctx->lastnode)
    {
        a_blake2b_set_lastnode(_ctx);
    }
    _ctx->f[0] = 0xFFFFFFFFFFFFFFFF;
}

static __INLINE void a_blake2b_increment_counter(a_blake2b_t *_ctx, uint64_t _inc)
{
    _ctx->t[0] += _inc;
    if (_ctx->t[0] < _inc)
    {
        ++_ctx->t[1];
    }
}

#undef G
#undef ROUND

static void a_blake2b_compress(a_blake2b_t *_ctx, const unsigned char *_buf)
{
    uint64_t v[0x10];

    /* (unsigned char *) -> (uint64_t *) */
    union
    {
        uint64_t *m;
        unsigned char *buf;
    } up[1];
    up->buf = _ctx->buf;
    if (_ctx->buf != _buf)
    {
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD64L(up->m[i], _buf + sizeof(*_ctx->state) * i);
        }
    }

    /* copy state into v */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        v[i] = _ctx->state[i];
    }

    v[8] = blake2b_IV[0];
    v[9] = blake2b_IV[1];
    v[10] = blake2b_IV[2];
    v[11] = blake2b_IV[3];
    v[12] = _ctx->t[0] ^ blake2b_IV[4];
    v[13] = _ctx->t[1] ^ blake2b_IV[5];
    v[14] = _ctx->f[0] ^ blake2b_IV[6];
    v[15] = _ctx->f[1] ^ blake2b_IV[7];

#define G(_r, _i, _a, _b, _c, _d)                               \
    do                                                          \
    {                                                           \
        _a = _a + _b + up->m[blake2b_sigma[_r][(_i << 1) + 0]]; \
        _d = ROR64(_d ^ _a, 0x20);                              \
        _c = _c + _d;                                           \
        _b = ROR64(_b ^ _c, 0x18);                              \
        _a = _a + _b + up->m[blake2b_sigma[_r][(_i << 1) + 1]]; \
        _d = ROR64(_d ^ _a, 0x10);                              \
        _c = _c + _d;                                           \
        _b = ROR64(_b ^ _c, 0x3F);                              \
    } while (0)
#define ROUND(_r)                                 \
    do                                            \
    {                                             \
        G(_r, 0, v[0x0], v[0x4], v[0x8], v[0xC]); \
        G(_r, 1, v[0x1], v[0x5], v[0x9], v[0xD]); \
        G(_r, 2, v[0x2], v[0x6], v[0xA], v[0xE]); \
        G(_r, 3, v[0x3], v[0x7], v[0xB], v[0xF]); \
        G(_r, 4, v[0x0], v[0x5], v[0xA], v[0xF]); \
        G(_r, 5, v[0x1], v[0x6], v[0xB], v[0xC]); \
        G(_r, 6, v[0x2], v[0x7], v[0x8], v[0xD]); \
        G(_r, 7, v[0x3], v[0x4], v[0x9], v[0xE]); \
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

    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        _ctx->state[i] = _ctx->state[i] ^ v[i] ^ v[i + 8];
    }
}

#undef G
#undef ROUND

int a_blake2b_init(a_blake2b_t *_ctx, size_t siz, const void *_p, size_t _n)
{
    a_assert(_ctx);

    unsigned char ap[A_PARAM_SIZE] = {0};

    if ((0 == siz) || (sizeof(_ctx->out) < siz))
    {
        return A_HASH_INVALID;
    }

    if ((_p && !_n) || (_n && !_p) || (sizeof(_ctx->buf) < _n))
    {
        return A_HASH_INVALID;
    }

    ap[O_DIGEST_LENGTH] = (unsigned char)siz;
    ap[O_KEY_LENGTH] = (unsigned char)_n;
    ap[O_FANOUT] = 1;
    ap[O_DEPTH] = 1;

    memset(_ctx, 0, sizeof(*_ctx));

    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        _ctx->state[i] = blake2b_IV[i];
    }

    /* IV XOR ParamBlock */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        uint64_t t;
        LOAD64L(t, ap + sizeof(*_ctx->state) * i);
        _ctx->state[i] ^= t;
    }

    _ctx->outsiz = ap[O_DIGEST_LENGTH];

    if (_p)
    {
        memcpy(_ctx->buf, _p, _n);
        a_blake2b_process(_ctx, _ctx->buf, sizeof(_ctx->buf));
    }

    return A_HASH_SUCCESS;
}

#undef __A_BLAKE2B_INIT
#define __A_BLAKE2B_INIT(_bit, _ctx)                \
    void a_blake2b_##_bit##_init(a_blake2b_t *_ctx) \
    {                                               \
        a_blake2b_init(_ctx, (_bit) >> 3, 0, 0);    \
    }
__A_BLAKE2B_INIT(160, _ctx)
__A_BLAKE2B_INIT(256, _ctx)
__A_BLAKE2B_INIT(384, _ctx)
__A_BLAKE2B_INIT(512, _ctx)
#undef __A_BLAKE2B_INIT

int a_blake2b_process(a_blake2b_t *_ctx, const void *_p, size_t _n)
{
    a_assert(_ctx);
    a_assert(!_n || _p);

    if (sizeof(_ctx->buf) < _ctx->cursiz)
    {
        return A_HASH_INVALID;
    }

    const unsigned char *p = (const unsigned char *)_p;
    if (_n)
    {
        uint32_t n = sizeof(_ctx->buf) - _ctx->cursiz;
        if (_n > n)
        {
            memcpy(_ctx->buf + _ctx->cursiz, p, n);
            a_blake2b_increment_counter(_ctx, sizeof(_ctx->buf));
            a_blake2b_compress(_ctx, _ctx->buf);
            _ctx->cursiz = 0;
            _n -= n;
            p += n;
            while (_n > sizeof(_ctx->buf) - 1)
            {
                a_blake2b_increment_counter(_ctx, sizeof(_ctx->buf));
                a_blake2b_compress(_ctx, p);
                _n -= sizeof(_ctx->buf);
                p += sizeof(_ctx->buf);
            }
        }
        memcpy(_ctx->buf + _ctx->cursiz, p, _n);
        _ctx->cursiz += (uint32_t)_n;
    }

    return A_HASH_SUCCESS;
}

unsigned char *a_blake2b_done(a_blake2b_t *_ctx, void *_out)
{
    a_assert(_ctx);

    if (a_blake2b_is_lastblock(_ctx))
    {
        return 0;
    }

    a_blake2b_increment_counter(_ctx, _ctx->cursiz);
    a_blake2b_set_lastblock(_ctx);

    /* padding */
    memset(_ctx->buf + _ctx->cursiz, 0, sizeof(_ctx->buf) - _ctx->cursiz);
    a_blake2b_compress(_ctx, _ctx->buf);

    /* copy output */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        STORE64L(_ctx->state[i], _ctx->out + sizeof(*_ctx->state) * i);
    }

    if (_out && (_out != _ctx->out))
    {
        memcpy(_out, _ctx->out, _ctx->outsiz);
    }

    return _ctx->out;
}

/* END OF FILE */
