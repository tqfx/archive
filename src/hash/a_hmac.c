/*!
 @file a_hmac.c
 @brief RFC 2104 compliant HMAC implementation
 @details https://www.ietf.org/rfc/rfc2104.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_hmac.h"

#include <string.h>

#undef A_HMAC_IPAD
#undef A_HMAC_OPAD
#define A_HMAC_IPAD 0x36
#define A_HMAC_OPAD 0x5c

int a_hmac_init(a_hmac_s *ctx, const a_hash_s *hash, const void *pdata, size_t nbyte)
{
    AASSERT(ctx);
    AASSERT(hash);
    AASSERT(!nbyte || pdata);

    if (sizeof(ctx->buf) < hash->bufsiz)
    {
        return A_HMAC_OVERFLOW;
    }

    ctx->hash = hash;
    ctx->outsiz = ctx->hash->outsiz;

    if (ctx->hash->bufsiz < nbyte)
    {
        ctx->hash->init(ctx->state);
        if (ctx->hash->process(ctx->state, pdata, nbyte) != A_HASH_SUCCESS)
        {
            return A_HMAC_FAILURE;
        }
        if (ctx->hash->done(ctx->state, ctx->buf) == 0)
        {
            return A_HMAC_FAILURE;
        }
        nbyte = ctx->hash->outsiz;
    }
    else if (nbyte)
    {
        memcpy(ctx->buf, pdata, nbyte);
    }

    if (nbyte < ctx->hash->bufsiz)
    {
        memset(ctx->buf + nbyte, 0, sizeof(ctx->buf) - nbyte);
    }

    unsigned char buf[sizeof(ctx->buf)];
    for (unsigned int i = 0; i != ctx->hash->bufsiz; ++i)
    {
        buf[i] = ctx->buf[i] ^ A_HMAC_IPAD;
    }

    ctx->hash->init(ctx->state);
    return ctx->hash->process(ctx->state, buf, ctx->hash->bufsiz);
}

int a_hmac_process(a_hmac_s *ctx, const void *pdata, size_t nbyte)
{
    AASSERT(ctx);
    AASSERT(!nbyte || pdata);

    return ctx->hash->process(ctx->state, pdata, nbyte);
}

unsigned char *a_hmac_done(a_hmac_s *ctx, void *out)
{
    AASSERT(ctx);

    unsigned char buf[sizeof(ctx->buf)];

    if (ctx->hash->done(ctx->state, buf) == 0)
    {
        return 0;
    }

    for (unsigned int i = 0; i != ctx->hash->bufsiz; ++i)
    {
        ctx->buf[i] ^= A_HMAC_OPAD;
    }

    ctx->hash->init(ctx->state);
    if (ctx->hash->process(ctx->state, ctx->buf, ctx->hash->bufsiz) != A_HASH_SUCCESS)
    {
        return 0;
    }
    if (ctx->hash->process(ctx->state, buf, ctx->hash->outsiz) != A_HASH_SUCCESS)
    {
        return 0;
    }
    if (ctx->hash->done(ctx->state, ctx->buf) == 0)
    {
        return 0;
    }

    if (out && out != ctx->buf)
    {
        memcpy(out, ctx->buf, ctx->hash->outsiz);
    }

    return ctx->buf;
}

#undef A_HMAC_IPAD
#undef A_HMAC_OPAD
