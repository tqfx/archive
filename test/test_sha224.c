/*!
 @file           test_sha224.c
 @brief          sha224 test
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha224.h"

#include "test_hash.h"

#include <string.h>

__HASH_FPROCESS(a_sha224_t, a_sha224_fprocess, a_sha224_compress)

int main(int argc, char **argv)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_SHA224_DIGESTSIZE];
    } tests[] = {
        {
            "abc",
            {0x23, 0x09, 0x7d, 0x22, 0x34, 0x05, 0xd8, 0x22, 0x86, 0x42, 0xa4, 0x77, 0xbd, 0xa2, 0x55, 0xb3, 0x2a, 0xad, 0xbc, 0xe4, 0xbd, 0xa0, 0xb3, 0xf7, 0xe3, 0x6c, 0x9d, 0xa7},
        },
        {
            "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
            {0x75, 0x38, 0x8b, 0x16, 0x51, 0x27, 0x76, 0xcc, 0x5d, 0xba, 0x5d, 0xa1, 0xfd, 0x89, 0x01, 0x50, 0xb0, 0xc6, 0x45, 0x5c, 0xb4, 0xf5, 0x8b, 0x19, 0x52, 0x52, 0x25, 0x25},
        },
    };

    a_sha224_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_sha224(tests[i].msg, strlen(tests[i].msg), ctx->out);
        if (memcmp(ctx->out, tests[i].hash, A_SHA224_DIGESTSIZE))
        {
            __HASH_DIFF(ctx->out, tests[i].hash, A_SHA224_DIGESTSIZE);
        }
    }

    char buf[(A_SHA224_DIGESTSIZE << 1) + 1];

    for (int i = 1; i != argc; ++i)
    {
        FILE *fp = fopen(argv[i], "rb");
        if (fp)
        {
            a_sha224_init(ctx);

            a_sha224_fprocess(ctx, fp);
            if (fclose(fp))
            {
                clearerr(fp);
            }

            a_sha224_done(ctx, ctx->out);

            a_digest(ctx->out, A_SHA224_DIGESTSIZE, buf);
            printf("%s %s\n", buf, argv[i]);
        }
    }

    return 0;
}

/* END OF FILE */
