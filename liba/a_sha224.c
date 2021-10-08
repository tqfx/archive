/*!
 @file           a_sha224.c
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha224.h"

#include <string.h> /* memcpy */

void a_sha224_init(a_sha224_t *ctx)
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

unsigned char *a_sha224_done(a_sha224_t *ctx, unsigned char *out)
{
    a_sha256_done(ctx, ctx->out);

    if (out && out != ctx->out)
    {
        (void)memcpy(out, ctx->out, A_SHA224_DIGESTSIZE);
    }

    return ctx->out;
}

unsigned char *a_sha224(const void *p, size_t n, unsigned char *out)
{
    a_sha224_t ctx[1];

    a_sha224_init(ctx);
    a_sha224_process(ctx, p, n);
    a_sha224_done(ctx, out);

    if (0 == out && (out = (unsigned char *)a_alloc(A_SHA224_DIGESTSIZE)))
    {
        (void)memcpy(out, ctx->out, A_SHA224_DIGESTSIZE);
    }

    return out;
}

/* END OF FILE */
