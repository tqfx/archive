/*!
 @file           test_md5.c
 @brief          md5 test
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_md5.h"

#include <stdio.h>
#include <string.h>

static void md5_fprocess(md5_t *ctx, FILE *fp)
{
    long idx = ftell(fp);

    for (;;)
    {
        size_t m = MD5_BLOCKSIZE - ctx->curlen;
        size_t n = fread(ctx->buf + ctx->curlen, 1, m, fp);
        if (MD5_BLOCKSIZE == ctx->curlen + n)
        {
            md5_compress(ctx, ctx->buf);
            ctx->length += (MD5_BLOCKSIZE << 3);
            ctx->curlen = 0;
        }
        else
        {
            ctx->curlen += (md5_u32_t)n;
            break;
        }
    }

    (void)fseek(fp, idx, SEEK_SET);
}

int main(int argc, char **argv)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[16];
    } tests[] = {
        {
            "",
            {0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04, 0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e},
        },
        {
            "a",
            {0x0c, 0xc1, 0x75, 0xb9, 0xc0, 0xf1, 0xb6, 0xa8, 0x31, 0xc3, 0x99, 0xe2, 0x69, 0x77, 0x26, 0x61},
        },
        {
            "abc",
            {0x90, 0x01, 0x50, 0x98, 0x3c, 0xd2, 0x4f, 0xb0, 0xd6, 0x96, 0x3f, 0x7d, 0x28, 0xe1, 0x7f, 0x72},
        },
        {
            "message digest",
            {0xf9, 0x6b, 0x69, 0x7d, 0x7c, 0xb7, 0x93, 0x8d, 0x52, 0x5a, 0x2f, 0x31, 0xaa, 0xf1, 0x61, 0xd0},
        },
        {
            "abcdefghijklmnopqrstuvwxyz",
            {0xc3, 0xfc, 0xd3, 0xd7, 0x61, 0x92, 0xe4, 0x00, 0x7d, 0xfb, 0x49, 0x6c, 0xca, 0x67, 0xe1, 0x3b},
        },
        {
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
            {0xd1, 0x74, 0xab, 0x98, 0xd2, 0x77, 0xd9, 0xf5, 0xa5, 0x61, 0x1c, 0x2c, 0x9f, 0x41, 0x9d, 0x9f},
        },
        {
            "12345678901234567890123456789012345678901234567890123456789012345678901234567890",
            {0x57, 0xed, 0xf4, 0xa2, 0x2b, 0xe3, 0xc9, 0x55, 0xac, 0x49, 0xda, 0x2e, 0x21, 0x07, 0xb6, 0x7a},
        },
        {
            0,
            {0},
        },
    };

    md5_t ctx[1];

    for (int i = 0; 0 != tests[i].msg; ++i)
    {
        md5_init(ctx);
        md5_process(ctx, tests[i].msg, strlen(tests[i].msg));
        md5_done(ctx, ctx->out);
        if (memcmp(ctx->out, tests[i].hash, MD5_DIGESTSIZE))
        {
            for (int j = 0; j != MD5_DIGESTSIZE; ++j)
            {
                printf("%02x", ctx->out[j]);
            }
            printf(" ");
            for (int j = 0; j != MD5_DIGESTSIZE; ++j)
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
            md5_init(ctx);
            md5_fprocess(ctx, fp);
            md5_done(ctx, ctx->out);
            if (fclose(fp))
            {
                clearerr(fp);
            }
            for (int j = 0; j != MD5_DIGESTSIZE; ++j)
            {
                printf("%02x", ctx->out[j]);
            }
            printf(" %s\n", argv[i]);
        }
    }

    return 0;
}

/* END OF FILE */
