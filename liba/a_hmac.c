/*!
 @file           a_hmac.c
 @brief          RFC 2104 compliant HMAC implementation
 @details        https://www.ietf.org/rfc/rfc2104.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_hmac.h"

#undef A_HMAC_IPAD
#undef A_HMAC_OPAD
#define A_HMAC_IPAD 0x36
#define A_HMAC_OPAD 0x5c

int a_hmac_init(a_hmac_t *ctx, const a_hash_t *hash, const void *p, size_t n)
{
    /* assert(ctx) */
    /* assert(hash) */
    /* assert(!n || p) */
    if (sizeof(ctx->buf) < hash->bufsiz)
    {
        return A_HMAC_OVERFLOW;
    }

    ctx->hash = hash;
    ctx->outsiz = ctx->hash->outsiz;

    if (n > ctx->hash->bufsiz)
    {
        ctx->hash->init(ctx->state);
        if (ctx->hash->process(ctx->state, p, n) != A_HASH_SUCCESS)
        {
            return A_HMAC_FAILURE;
        }
        if (ctx->hash->done(ctx->state, ctx->buf) == 0)
        {
            return A_HMAC_FAILURE;
        }
        n = ctx->hash->outsiz;
    }
    else if (n)
    {
        memcpy(ctx->buf, p, n);
    }

    if (n < ctx->hash->bufsiz)
    {
        memset(ctx->buf + n, 0, sizeof(ctx->buf) - n);
    }

    unsigned char buf[sizeof(ctx->buf)];
    for (unsigned int i = 0; i != ctx->hash->bufsiz; ++i)
    {
        buf[i] = ctx->buf[i] ^ A_HMAC_IPAD;
    }

    ctx->hash->init(ctx->state);
    return ctx->hash->process(ctx->state, buf, ctx->hash->bufsiz);
}

int a_hmac_process(a_hmac_t *ctx, const void *p, size_t n)
{
    /* assert(ctx) */
    /* assert(!n || p) */
    return ctx->hash->process(ctx->state, p, n);
}

unsigned char *a_hmac_done(a_hmac_t *ctx, unsigned char *out)
{
    /* assert(ctx) */
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

/* END OF FILE */
