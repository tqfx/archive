/*!
 @file           test_sha256.c
 @brief          test sha256 sha224
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha256.h"

#include "test_hash.h"

#include <string.h>

static void test_sha256(void)
{
    /* clang-format off */
    static const struct
    {
        const char *msg;
        unsigned char hash[A_SHA256_DIGESTSIZE];
    } tests[] = {
        {
            "abc",
            {
                0xBA, 0x78, 0x16, 0xBF, 0x8F, 0x01, 0xCF, 0xEA,
                0x41, 0x41, 0x40, 0xDE, 0x5D, 0xAE, 0x22, 0x23,
                0xB0, 0x03, 0x61, 0xA3, 0x96, 0x17, 0x7A, 0x9C,
                0xB4, 0x10, 0xFF, 0x61, 0xF2, 0x00, 0x15, 0xAD,
            },
        },
        {
            "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
            {
                0x24, 0x8D, 0x6A, 0x61, 0xD2, 0x06, 0x38, 0xB8,
                0xE5, 0xC0, 0x26, 0x93, 0x0C, 0x3E, 0x60, 0x39,
                0xA3, 0x3C, 0xE4, 0x59, 0x64, 0xFF, 0x21, 0x67,
                0xF6, 0xEC, 0xED, 0xD4, 0x19, 0xDB, 0x06, 0xC1,
            },
        },
    };
    /* clang-format on */

    a_sha256_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_sha256(tests[i].msg, strlen(tests[i].msg), ctx->out);
        if (memcmp(ctx->out, tests[i].hash, A_SHA256_DIGESTSIZE))
        {
            __HASH_DIFF(ctx->out, tests[i].hash, A_SHA256_DIGESTSIZE);
        }
    }
}

static void test_sha224(void)
{
    /* clang-format off */
    static const struct
    {
        const char *msg;
        unsigned char hash[A_SHA224_DIGESTSIZE];
    } tests[] = {
        {
            "abc",
            {
                0x23, 0x09, 0x7D, 0x22, 0x34, 0x05, 0xD8, 0x22,
                0x86, 0x42, 0xA4, 0x77, 0xBD, 0xA2, 0x55, 0xB3,
                0x2A, 0xAD, 0xBC, 0xE4, 0xBD, 0xA0, 0xB3, 0xF7,
                0xE3, 0x6C, 0x9D, 0xA7,
            },
        },
        {
            "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
            {
                0x75, 0x38, 0x8B, 0x16, 0x51, 0x27, 0x76, 0xCC,
                0x5D, 0xBA, 0x5D, 0xA1, 0xFD, 0x89, 0x01, 0x50,
                0xB0, 0xC6, 0x45, 0x5C, 0xB4, 0xF5, 0x8B, 0x19,
                0x52, 0x52, 0x25, 0x25,
            },
        },
    };
    /* clang-format on */

    a_sha224_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_sha224(tests[i].msg, strlen(tests[i].msg), ctx->out);
        if (memcmp(ctx->out, tests[i].hash, A_SHA224_DIGESTSIZE))
        {
            __HASH_DIFF(ctx->out, tests[i].hash, A_SHA224_DIGESTSIZE);
        }
    }
}

int main(void)
{
    test_sha256();
    test_sha224();

    return 0;
}

/* END OF FILE */
