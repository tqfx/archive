/*!
 @file           test_sha256.c
 @brief          sha256 test
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha256.h"
#include "a_convert.h"

#include <stdio.h>
#include <string.h>

static void a_sha256_fprocess(a_sha256_t *ctx, FILE *fp)
{
    long idx = ftell(fp);

    for (;;)
    {
        size_t m = A_SHA256_BLOCKSIZE - ctx->curlen;
        size_t n = fread(ctx->buf + ctx->curlen, 1, m, fp);
        if (A_SHA256_BLOCKSIZE == ctx->curlen + n)
        {
            a_sha256_compress(ctx, ctx->buf);
            ctx->length += (A_SHA256_BLOCKSIZE << 3);
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
        unsigned char hash[32];
    } tests[] = {
        {
            "abc",
            {0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea, 0x41, 0x41, 0x40, 0xde, 0x5d, 0xae, 0x22, 0x23, 0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17, 0x7a, 0x9c, 0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad},
        },
        {
            "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
            {0x24, 0x8d, 0x6a, 0x61, 0xd2, 0x06, 0x38, 0xb8, 0xe5, 0xc0, 0x26, 0x93, 0x0c, 0x3e, 0x60, 0x39, 0xa3, 0x3c, 0xe4, 0x59, 0x64, 0xff, 0x21, 0x67, 0xf6, 0xec, 0xed, 0xd4, 0x19, 0xdb, 0x06, 0xc1},
        },
    };

    a_sha256_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_sha256(tests[i].msg, strlen(tests[i].msg), ctx->out);
        if (memcmp(ctx->out, tests[i].hash, A_SHA256_DIGESTSIZE))
        {
            for (int j = 0; j != A_SHA256_DIGESTSIZE; ++j)
            {
                printf("%02x", ctx->out[j]);
            }
            printf(" ");
            for (int j = 0; j != A_SHA256_DIGESTSIZE; ++j)
            {
                printf("%02x", tests[i].hash[j]);
            }
            printf("\n");
        }
    }

    for (int i = 1; i != argc; ++i)
    {
        FILE *fp = fopen(argv[i], "rb");
        if (fp)
        {
            a_sha256_init(ctx);

            a_sha256_fprocess(ctx, fp);
            if (fclose(fp))
            {
                clearerr(fp);
            }

            a_sha256_done(ctx, ctx->out);

            a_digest(ctx->out, A_SHA256_DIGESTSIZE, (char *)ctx->buf);
            printf("%s %s\n", ctx->buf, argv[i]);
        }
    }

    return 0;
}

/* END OF FILE */
