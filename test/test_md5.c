/*!
 @file           test_md5.c
 @brief          test md5
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_md5.h"

#include "test_hash.h"

#include <string.h>

int main(void)
{
    /* clang-format off */
    static const struct
    {
        const char *msg;
        unsigned char hash[A_MD5_DIGESTSIZE];
    } tests[] = {
        {
            "",
            {
                0xD4, 0x1D, 0x8C, 0xD9, 0x8F, 0x00, 0xB2, 0x04,
                0xE9, 0x80, 0x09, 0x98, 0xEC, 0xF8, 0x42, 0x7E,
            },
        },
        {
            "a",
            {
                0x0C, 0xC1, 0x75, 0xB9, 0xC0, 0xF1, 0xB6, 0xA8,
                0x31, 0xC3, 0x99, 0xE2, 0x69, 0x77, 0x26, 0x61,

            },
        },
        {
            "abc",
            {
                0x90, 0x01, 0x50, 0x98, 0x3C, 0xD2, 0x4F, 0xB0,
                0xD6, 0x96, 0x3F, 0x7D, 0x28, 0xE1, 0x7F, 0x72,
            },
        },
        {
            "message digest",
            {
                0xF9, 0x6B, 0x69, 0x7D, 0x7C, 0xB7, 0x93, 0x8D,
                0x52, 0x5A, 0x2F, 0x31, 0xAA, 0xF1, 0x61, 0xD0,
            },
        },
        {
            "abcdefghijklmnopqrstuvwxyz",
            {
                0xC3, 0xFC, 0xD3, 0xD7, 0x61, 0x92, 0xE4, 0x00,
                0x7D, 0xFB, 0x49, 0x6C, 0xCA, 0x67, 0xE1, 0x3B,
            },
        },
        {
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
            {
                0xD1, 0x74, 0xAB, 0x98, 0xD2, 0x77, 0xD9, 0xF5,
                0xA5, 0x61, 0x1C, 0x2C, 0x9F, 0x41, 0x9D, 0x9F,
            },
        },
        {
            "1234567890123456789012345678901234567890"
            "1234567890123456789012345678901234567890",
            {
                0x57, 0xED, 0xF4, 0xA2, 0x2B, 0xE3, 0xC9, 0x55,
                0xAC, 0x49, 0xDA, 0x2E, 0x21, 0x07, 0xB6, 0x7A,
            },
        },
    };
    /* clang-format on */

    a_md5_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_md5(tests[i].msg, strlen(tests[i].msg), ctx->out);
        if (memcmp(ctx->out, tests[i].hash, A_MD5_DIGESTSIZE))
        {
            __HASH_DIFF(ctx->out, tests[i].hash, A_MD5_DIGESTSIZE);
        }
    }

    return 0;
}

/* END OF FILE */
