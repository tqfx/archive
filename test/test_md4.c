/*!
 @file           test_md4.c
 @brief          test md4
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_md4.h"

#include "test_hash.h"

#include <string.h>

int main(void)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_MD4_DIGESTSIZE];
    } tests[] = {
        /* clang-format off */
        {
            "",
            {
                0x31, 0xD6, 0xCF, 0xE0, 0xD1, 0x6A, 0xE9, 0x31,
                0xB7, 0x3C, 0x59, 0xD7, 0xE0, 0xC0, 0x89, 0xC0,
            },
        },
        {
            "a",
            {
                0xBD, 0xE5, 0x2C, 0xB3, 0x1D, 0xE3, 0x3E, 0x46,
                0x24, 0x5E, 0x05, 0xFB, 0xDB, 0xD6, 0xFB, 0x24,
            },
        },
        {
            "abc",
            {
                0xA4, 0x48, 0x01, 0x7A, 0xAF, 0x21, 0xD8, 0x52,
                0x5F, 0xC1, 0x0A, 0xE8, 0x7A, 0xA6, 0x72, 0x9D,
            },
        },
        {
            "message digest",
            {
                0xD9, 0x13, 0x0A, 0x81, 0x64, 0x54, 0x9F, 0xE8,
                0x18, 0x87, 0x48, 0x06, 0xE1, 0xC7, 0x01, 0x4B,
            },
        },
        {
            "abcdefghijklmnopqrstuvwxyz",
            {
                0xD7, 0x9E, 0x1C, 0x30, 0x8A, 0xA5, 0xBB, 0xCD,
                0xEE, 0xA8, 0xED, 0x63, 0xDF, 0x41, 0x2D, 0xA9,
            },
        },
        {
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
            {
                0x04, 0x3F, 0x85, 0x82, 0xF2, 0x41, 0xDB, 0x35,
                0x1C, 0xE6, 0x27, 0xE1, 0x53, 0xE7, 0xF0, 0xE4,
            },
        },
        {
            "1234567890123456789012345678901234567890"
            "1234567890123456789012345678901234567890",
            {
                0xE3, 0x3B, 0x4D, 0xDC, 0x9C, 0x38, 0xF2, 0x19,
                0x9C, 0x3E, 0x7B, 0x16, 0x4F, 0xCC, 0x05, 0x36,
            },
        },
        /* clang-format on */
    };

    a_md4_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_md4(tests[i].msg, strlen(tests[i].msg), ctx->out);
        if (memcmp(ctx->out, tests[i].hash, A_MD4_DIGESTSIZE))
        {
            __HASH_DIFF(ctx->out, tests[i].hash, A_MD4_DIGESTSIZE);
        }
    }

    return 0;
}

/* END OF FILE */
