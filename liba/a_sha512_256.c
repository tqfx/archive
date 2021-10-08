/*!
 @file           a_sha512_256.c
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha512_256.h"

#include <string.h> /* memcpy */

void a_sha512_256_init(a_sha512_256_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0x22312194FC2BF72C;
    ctx->state[1] = 0x9F555FA3C84C64C2;
    ctx->state[2] = 0x2393B86B6F53B151;
    ctx->state[3] = 0x963877195940EABD;
    ctx->state[4] = 0x96283EE2A88EFFE3;
    ctx->state[5] = 0xBE5E1E2553863992;
    ctx->state[6] = 0x2B0199FC2C85B8AA;
    ctx->state[7] = 0x0EB72DDC81C52CA2;
}

unsigned char *a_sha512_256_done(a_sha512_256_t *ctx, unsigned char *out)
{
    a_sha512_done(ctx, ctx->out);

    if (out && out != ctx->out)
    {
        (void)memcpy(out, ctx->out, A_SHA512_256_DIGESTSIZE);
    }

    return ctx->out;
}

unsigned char *a_sha512_256(const void *p, size_t n, unsigned char *out)
{
    a_sha512_256_t ctx[1];

    a_sha512_256_init(ctx);
    a_sha512_256_process(ctx, p, n);
    a_sha512_256_done(ctx, out);

    if (0 == out && (out = (unsigned char *)a_alloc(A_SHA512_256_DIGESTSIZE)))
    {
        (void)memcpy(out, ctx->out, A_SHA512_256_DIGESTSIZE);
    }

    return out;
}

/* END OF FILE */
