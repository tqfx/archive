/*!
 @file           test_sha1.c
 @brief          test sha1
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha1.h"

#include "test_hash.h"

int main(void)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_SHA1_DIGESTSIZE];
    } tests[] = {
        /* clang-format off */
        {
            "abc",
            {
                0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E,
                0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D,
            },
        },
        {
            "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
            {
                0x84, 0x98, 0x3E, 0x44, 0x1C, 0x3B, 0xD2, 0x6E, 0xBA, 0xAE,
                0x4A, 0xA1, 0xF9, 0x51, 0x29, 0xE5, 0xE5, 0x46, 0x70, 0xF1,
            },
        },
        /* clang-format on */
    };

    a_sha1_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_sha1(tests[i].msg, strlen(tests[i].msg), ctx->out);
        __HASH_DIFF(ctx->out, tests[i].hash, A_SHA1_DIGESTSIZE);
    }

    return 0;
}

/* END OF FILE */
