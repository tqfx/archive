/*!
 @file           test_sha1.c
 @brief          test sha1
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha1.h"

#include "test_hash.h"

#include <string.h>

int main(void)
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
            __HASH_DIFF(ctx->out, tests[i].hash, A_SHA1_DIGESTSIZE);
        }
    }

    return 0;
}

/* END OF FILE */
