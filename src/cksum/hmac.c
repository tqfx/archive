/*!
 @file hmac.c
 @brief RFC 2104 compliant HMAC implementation
 @details https://www.ietf.org/rfc/rfc2104.txt
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/cksum/hmac.h"

#include <assert.h>
#include <string.h>

#undef A_HMAC_IPAD
#undef A_HMAC_OPAD
#define A_HMAC_IPAD 0x36
#define A_HMAC_OPAD 0x5C

int a_hmac_init(a_hmac_s *ctx, const a_hash_s *hash, const void *pdata, size_t nbyte)
{
    assert(ctx);
    assert(hash);
    assert(!nbyte || pdata);

    if (sizeof(ctx->buf) < hash->bufsiz)
    {
        return A_OVERFLOW;
    }

    ctx->__hash = hash;
    ctx->outsiz = ctx->__hash->outsiz;

    if (ctx->__hash->bufsiz < nbyte)
    {
        ctx->__hash->init(ctx->__state);
        if (ctx->__hash->proc(ctx->__state, pdata, nbyte) != A_SUCCESS)
        {
            return A_FAILURE;
        }
        if (ctx->__hash->done(ctx->__state, ctx->buf) == 0)
        {
            return A_FAILURE;
        }
        nbyte = ctx->__hash->outsiz;
    }
    else if (nbyte)
    {
        memcpy(ctx->buf, pdata, nbyte);
    }

    if (nbyte < ctx->__hash->bufsiz)
    {
        memset(ctx->buf + nbyte, 0, sizeof(ctx->buf) - nbyte);
    }

    unsigned char buf[sizeof(ctx->buf)];
    for (unsigned int i = 0; i != ctx->__hash->bufsiz; ++i)
    {
        buf[i] = ctx->buf[i] ^ A_HMAC_IPAD;
    }

    ctx->__hash->init(ctx->__state);
    return ctx->__hash->proc(ctx->__state, buf, ctx->__hash->bufsiz);
}

int a_hmac_proc(a_hmac_s *ctx, const void *pdata, size_t nbyte)
{
    assert(ctx);
    assert(!nbyte || pdata);

    return ctx->__hash->proc(ctx->__state, pdata, nbyte);
}

unsigned char *a_hmac_done(a_hmac_s *ctx, void *out)
{
    assert(ctx);

    unsigned char buf[sizeof(ctx->buf)];

    if (ctx->__hash->done(ctx->__state, buf) == 0)
    {
        return 0;
    }

    for (unsigned int i = 0; i != ctx->__hash->bufsiz; ++i)
    {
        ctx->buf[i] ^= A_HMAC_OPAD;
    }

    ctx->__hash->init(ctx->__state);
    if (ctx->__hash->proc(ctx->__state, ctx->buf, ctx->__hash->bufsiz) != A_SUCCESS)
    {
        return 0;
    }
    if (ctx->__hash->proc(ctx->__state, buf, ctx->__hash->outsiz) != A_SUCCESS)
    {
        return 0;
    }
    if (ctx->__hash->done(ctx->__state, ctx->buf) == 0)
    {
        return 0;
    }

    if (out && out != ctx->buf)
    {
        memcpy(out, ctx->buf, ctx->__hash->outsiz);
    }

    return ctx->buf;
}

#undef A_HMAC_IPAD
#undef A_HMAC_OPAD
