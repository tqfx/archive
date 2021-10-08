/*!
 @file           test_sha512_224.c
 @brief          sha512_224 test
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha512_224.h"

#include "test_hash.h"

#include <string.h>

__HASH_FPROCESS(a_sha512_224_t, a_sha512_224_fprocess, a_sha512_224_compress)

int main(int argc, char **argv)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_SHA512_224_DIGESTSIZE];
    } tests[] = {
        {
            "abc",
            {0x46, 0x34, 0x27, 0x0F, 0x70, 0x7B, 0x6A, 0x54, 0xDA, 0xAE, 0x75, 0x30, 0x46, 0x08, 0x42, 0xE2, 0x0E, 0x37, 0xED, 0x26, 0x5C, 0xEE, 0xE9, 0xA4, 0x3E, 0x89, 0x24, 0xAA},
        },
        {
            "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
            {0x23, 0xFE, 0xC5, 0xBB, 0x94, 0xD6, 0x0B, 0x23, 0x30, 0x81, 0x92, 0x64, 0x0B, 0x0C, 0x45, 0x33, 0x35, 0xD6, 0x64, 0x73, 0x4F, 0xE4, 0x0E, 0x72, 0x68, 0x67, 0x4A, 0xF9},
        },
    };

    a_sha512_224_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_sha512_224(tests[i].msg, strlen(tests[i].msg), ctx->out);
        if (memcmp(ctx->out, tests[i].hash, A_SHA512_224_DIGESTSIZE))
        {
            __HASH_DIFF(ctx->out, tests[i].hash, A_SHA512_224_DIGESTSIZE);
        }
    }

    char buf[(A_SHA512_224_DIGESTSIZE << 1) + 1];

    for (int i = 1; i != argc; ++i)
    {
        FILE *fp = fopen(argv[i], "rb");
        if (fp)
        {
            a_sha512_224_init(ctx);

            a_sha512_224_fprocess(ctx, fp);
            if (fclose(fp))
            {
                clearerr(fp);
            }

            a_sha512_224_done(ctx, ctx->out);

            a_digest(ctx->out, A_SHA512_224_DIGESTSIZE, buf);
            printf("%s %s\n", buf, argv[i]);
        }
    }

    return 0;
}

/* END OF FILE */
