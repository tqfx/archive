/*!
 @file           test_blake2s.c
 @brief          test blake2s 128 160 224 256
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_blake2s.h"

#include "test_hash.h"

static void test_blake2s_128(void)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_BLAKE2S_128_DIGESTSIZE];
    } tests[] = {
        /* clang-format off */
        {
            "",
            {
                0x64, 0x55, 0x0D, 0x6F, 0xFE, 0x2C, 0x0A, 0x01,
                0xA1, 0x4A, 0xBA, 0x1E, 0xAD, 0xE0, 0x20, 0x0C,
            },
        },
        {
            "abc",
            {
                0xAA, 0x49, 0x38, 0x11, 0x9B, 0x1D, 0xC7, 0xB8,
                0x7C, 0xBA, 0xD0, 0xFF, 0xD2, 0x00, 0xD0, 0xAE,
            },
        },
        /* clang-format on */
    };

    a_blake2s_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_blake2s_128(tests[i].msg, strlen(tests[i].msg), ctx->out);
        __HASH_DIFF(ctx->out, tests[i].hash, A_BLAKE2S_128_DIGESTSIZE);
    }
}

static void test_blake2s_160(void)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_BLAKE2S_160_DIGESTSIZE];
    } tests[] = {
        /* clang-format off */
        {
            "",
            {
                0x35, 0x4C, 0x9C, 0x33, 0xF7, 0x35, 0x96, 0x24,
                0x18, 0xBD, 0xAC, 0xB9, 0x47, 0x98, 0x73, 0x42,
                0x9C, 0x34, 0x91, 0x6F,
            },
        },
        {
            "abc",
            {
                0x5A, 0xE3, 0xB9, 0x9B, 0xE2, 0x9B, 0x01, 0x83,
                0x4C, 0x3B, 0x50, 0x85, 0x21, 0xED, 0xE6, 0x04,
                0x38, 0xF8, 0xDE, 0x17,
            },
        },
        /* clang-format on */
    };

    a_blake2s_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_blake2s_160(tests[i].msg, strlen(tests[i].msg), ctx->out);
        __HASH_DIFF(ctx->out, tests[i].hash, A_BLAKE2S_160_DIGESTSIZE);
    }
}

static void test_blake2s_224(void)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_BLAKE2S_224_DIGESTSIZE];
    } tests[] = {
        /* clang-format off */
        {
            "",
            {
                0x1F, 0xA1, 0x29, 0x1E, 0x65, 0x24, 0x8B, 0x37,
                0xB3, 0x43, 0x34, 0x75, 0xB2, 0xA0, 0xDD, 0x63,
                0xD5, 0x4A, 0x11, 0xEC, 0xC4, 0xE3, 0xE0, 0x34,
                0xE7, 0xBC, 0x1E, 0xF4,
            },
        },
        {
            "abc",
            {
                0x0B, 0x03, 0x3F, 0xC2, 0x26, 0xDF, 0x7A, 0xBD,
                0xE2, 0x9F, 0x67, 0xA0, 0x5D, 0x3D, 0xC6, 0x2C,
                0xF2, 0x71, 0xEF, 0x3D, 0xFE, 0xA4, 0xD3, 0x87,
                0x40, 0x7F, 0xBD, 0x55,
            },
        },
        /* clang-format on */
    };

    a_blake2s_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_blake2s_224(tests[i].msg, strlen(tests[i].msg), ctx->out);
        __HASH_DIFF(ctx->out, tests[i].hash, A_BLAKE2S_224_DIGESTSIZE);
    }
}

static void test_blake2s_256(void)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_BLAKE2S_256_DIGESTSIZE];
    } tests[] = {
        /* clang-format off */
        {
            "",
            {
                0x69, 0x21, 0x7A, 0x30, 0x79, 0x90, 0x80, 0x94,
                0xE1, 0x11, 0x21, 0xD0, 0x42, 0x35, 0x4A, 0x7C,
                0x1F, 0x55, 0xB6, 0x48, 0x2C, 0xA1, 0xA5, 0x1E,
                0x1B, 0x25, 0x0D, 0xFD, 0x1E, 0xD0, 0xEE, 0xF9,
            },
        },
        {
            "abc",
            {
                0x50, 0x8C, 0x5E, 0x8C, 0x32, 0x7C, 0x14, 0xE2,
                0xE1, 0xA7, 0x2B, 0xA3, 0x4E, 0xEB, 0x45, 0x2F,
                0x37, 0x45, 0x8B, 0x20, 0x9E, 0xD6, 0x3A, 0x29,
                0x4D, 0x99, 0x9B, 0x4C, 0x86, 0x67, 0x59, 0x82,
            },
        },
        {
            "12345678901234567890123456789012345678901234567890"
            "12345678901234567890123456789012345678901234567890"
            "12345678901234567890123456789012345678901234567890"
            "12345678901234567890123456789012345678901234567890"
            "12345678901234567890123456789012345678901234567890"
            "12345678901234567890123456789012345678901234567890",
            {
                0xA3, 0x78, 0x8B, 0x5B, 0x59, 0xEE, 0xE4, 0x41,
                0x95, 0x23, 0x58, 0x00, 0xA4, 0xF9, 0xFA, 0x41,
                0x86, 0x0C, 0x7B, 0x1C, 0x35, 0xA2, 0x42, 0x70,
                0x50, 0x80, 0x79, 0x56, 0xE3, 0xBE, 0x31, 0x74,
            },
        },
        /* clang-format on */
    };

    a_blake2s_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_blake2s_256(tests[i].msg, strlen(tests[i].msg), ctx->out);
        __HASH_DIFF(ctx->out, tests[i].hash, A_BLAKE2S_256_DIGESTSIZE);
    }
}

int main(void)
{
    test_blake2s_128();
    test_blake2s_160();
    test_blake2s_224();
    test_blake2s_256();

    return 0;
}

/* END OF FILE */
