/*!
 @file           a_sha512_224.c
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha512_224.h"

#include <string.h> /* memcpy */

void a_sha512_224_init(a_sha512_224_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0x8C3D37C819544DA2;
    ctx->state[1] = 0x73E1996689DCD4D6;
    ctx->state[2] = 0x1DFAB7AE32FF9C82;
    ctx->state[3] = 0x679DD514582F9FCF;
    ctx->state[4] = 0x0F6D2B697BD44DA8;
    ctx->state[5] = 0x77E36F7304C48942;
    ctx->state[6] = 0x3F9D85A86A1D36C8;
    ctx->state[7] = 0x1112E6AD91D692A1;
}

unsigned char *a_sha512_224_done(a_sha512_224_t *ctx, unsigned char *out)
{
    a_sha512_done(ctx, ctx->out);

    if (out && out != ctx->out)
    {
        (void)memcpy(out, ctx->out, A_SHA512_224_DIGESTSIZE);
    }

    return ctx->out;
}

unsigned char *a_sha512_224(const void *p, size_t n, unsigned char *out)
{
    a_sha512_224_t ctx[1];

    a_sha512_224_init(ctx);
    a_sha512_224_process(ctx, p, n);
    a_sha512_224_done(ctx, out);

    if (0 == out && (out = (unsigned char *)a_alloc(A_SHA512_224_DIGESTSIZE)))
    {
        (void)memcpy(out, ctx->out, A_SHA512_224_DIGESTSIZE);
    }

    return out;
}

/* END OF FILE */
