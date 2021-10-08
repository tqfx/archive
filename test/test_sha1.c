/*!
 @file           test_sha1.c
 @brief          sha1 test
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha1.h"
#include "a_convert.h"

#include "test_hash.h"

#include <string.h>

__HASH_FPROCESS(a_sha1_t, a_sha1_fprocess, a_sha1_compress)

int main(int argc, char **argv)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_SHA1_DIGESTSIZE];
    } tests[] = {
        {
            "abc",
            {0xa9, 0x99, 0x3e, 0x36, 0x47, 0x06, 0x81, 0x6a, 0xba, 0x3e, 0x25, 0x71, 0x78, 0x50, 0xc2, 0x6c, 0x9c, 0xd0, 0xd8, 0x9d},
        },
        {
            "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
            {0x84, 0x98, 0x3E, 0x44, 0x1C, 0x3B, 0xD2, 0x6E, 0xBA, 0xAE, 0x4A, 0xA1, 0xF9, 0x51, 0x29, 0xE5, 0xE5, 0x46, 0x70, 0xF1},
        },
    };

    a_sha1_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_sha1(tests[i].msg, strlen(tests[i].msg), ctx->out);
        if (memcmp(ctx->out, tests[i].hash, A_SHA1_DIGESTSIZE))
        {
            for (int j = 0; j != A_SHA1_DIGESTSIZE; ++j)
            {
                printf("%02x", ctx->out[j]);
            }
            printf(" ");
            for (int j = 0; j != A_SHA1_DIGESTSIZE; ++j)
            {
                printf("%02x", tests[i].hash[j]);
            }
            printf("\n");
        }
    }

    char buf[(A_SHA1_DIGESTSIZE << 1) + 1];

    for (int i = 1; i != argc; ++i)
    {
        FILE *fp = fopen(argv[i], "rb");
        if (fp)
        {
            a_sha1_init(ctx);

            a_sha1_fprocess(ctx, fp);
            if (fclose(fp))
            {
                clearerr(fp);
            }

            a_sha1_done(ctx, ctx->out);

            a_digest(ctx->out, A_SHA1_DIGESTSIZE, buf);
            printf("%s %s\n", buf, argv[i]);
        }
    }

    return 0;
}

/* END OF FILE */
