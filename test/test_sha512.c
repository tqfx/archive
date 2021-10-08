/*!
 @file           test_sha512.c
 @brief          sha512 test
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha512.h"
#include "a_convert.h"

#include <stdio.h>
#include <string.h>

static void a_sha512_fprocess(a_sha512_t *ctx, FILE *fp)
{
    long idx = ftell(fp);

    for (;;)
    {
        size_t m = A_SHA512_BLOCKSIZE - ctx->curlen;
        size_t n = fread(ctx->buf + ctx->curlen, 1, m, fp);
        if (A_SHA512_BLOCKSIZE == ctx->curlen + n)
        {
            a_sha512_compress(ctx, ctx->buf);
            ctx->length += (A_SHA512_BLOCKSIZE << 3);
            ctx->curlen = 0;
        }
        else
        {
            ctx->curlen += (uint32_t)n;
            break;
        }
    }

    fseek(fp, idx, SEEK_SET);
}

int main(int argc, char **argv)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_SHA512_DIGESTSIZE];
    } tests[] = {
        {
            "abc",
            {0xdd, 0xaf, 0x35, 0xa1, 0x93, 0x61, 0x7a, 0xba, 0xcc, 0x41, 0x73, 0x49, 0xae, 0x20, 0x41, 0x31, 0x12, 0xe6, 0xfa, 0x4e, 0x89, 0xa9, 0x7e, 0xa2, 0x0a, 0x9e, 0xee, 0xe6, 0x4b, 0x55, 0xd3, 0x9a, 0x21, 0x92, 0x99, 0x2a, 0x27, 0x4f, 0xc1, 0xa8, 0x36, 0xba, 0x3c, 0x23, 0xa3, 0xfe, 0xeb, 0xbd, 0x45, 0x4d, 0x44, 0x23, 0x64, 0x3c, 0xe8, 0x0e, 0x2a, 0x9a, 0xc9, 0x4f, 0xa5, 0x4c, 0xa4, 0x9f},
        },
        {
            "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
            {0x8e, 0x95, 0x9b, 0x75, 0xda, 0xe3, 0x13, 0xda, 0x8c, 0xf4, 0xf7, 0x28, 0x14, 0xfc, 0x14, 0x3f, 0x8f, 0x77, 0x79, 0xc6, 0xeb, 0x9f, 0x7f, 0xa1, 0x72, 0x99, 0xae, 0xad, 0xb6, 0x88, 0x90, 0x18, 0x50, 0x1d, 0x28, 0x9e, 0x49, 0x00, 0xf7, 0xe4, 0x33, 0x1b, 0x99, 0xde, 0xc4, 0xb5, 0x43, 0x3a, 0xc7, 0xd3, 0x29, 0xee, 0xb6, 0xdd, 0x26, 0x54, 0x5e, 0x96, 0xe5, 0x5b, 0x87, 0x4b, 0xe9, 0x09},
        },
    };

    a_sha512_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_sha512(tests[i].msg, strlen(tests[i].msg), ctx->out);
        if (memcmp(ctx->out, tests[i].hash, A_SHA512_DIGESTSIZE))
        {
            for (int j = 0; j != A_SHA512_DIGESTSIZE; ++j)
            {
                printf("%02x", ctx->out[j]);
            }
            printf(" ");
            for (int j = 0; j != A_SHA512_DIGESTSIZE; ++j)
            {
                printf("%02x", tests[i].hash[j]);
            }
            printf("\n");
        }
    }

    char buf[(A_SHA512_DIGESTSIZE << 1) + 1];

    for (int i = 1; i != argc; ++i)
    {
        FILE *fp = fopen(argv[i], "rb");
        if (fp)
        {
            a_sha512_init(ctx);

            a_sha512_fprocess(ctx, fp);
            if (fclose(fp))
            {
                clearerr(fp);
            }

            a_sha512_done(ctx, ctx->out);

            a_digest(ctx->out, A_SHA512_DIGESTSIZE, buf);
            printf("%s %s\n", buf, argv[i]);
        }
    }

    return 0;
}

/* END OF FILE */
