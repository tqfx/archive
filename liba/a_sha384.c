/*!
 @file           a_sha384.c
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha384.h"

#include <string.h> /* memcpy */

void a_sha384_init(a_sha384_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0xcbbb9d5dc1059ed8;
    ctx->state[1] = 0x629a292a367cd507;
    ctx->state[2] = 0x9159015a3070dd17;
    ctx->state[3] = 0x152fecd8f70e5939;
    ctx->state[4] = 0x67332667ffc00b31;
    ctx->state[5] = 0x8eb44a8768581511;
    ctx->state[6] = 0xdb0c2e0d64f98fa7;
    ctx->state[7] = 0x47b5481dbefa4fa4;
}

unsigned char *a_sha384_done(a_sha384_t *ctx, unsigned char *out)
{
    a_sha512_done(ctx, ctx->out);

    if (out && out != ctx->out)
    {
        (void)memcpy(out, ctx->out, A_SHA384_DIGESTSIZE);
    }

    return ctx->out;
}

unsigned char *a_sha384(const void *p, size_t n, unsigned char *out)
{
    a_sha384_t ctx[1];

    a_sha384_init(ctx);
    a_sha384_process(ctx, p, n);
    a_sha384_done(ctx, out);

    if (0 == out && (out = (unsigned char *)a_alloc(A_SHA384_DIGESTSIZE)))
    {
        (void)memcpy(out, ctx->out, A_SHA384_DIGESTSIZE);
    }

    return out;
}

/* END OF FILE */
