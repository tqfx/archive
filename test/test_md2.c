/*!
 @file           test_md2.c
 @brief          test md2
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_md2.h"

#include "test_hash.h"

int main(void)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_MD2_DIGESTSIZE];
    } tests[] = {
        /* clang-format off */
        {
            "",
            {
                0x83, 0x50, 0xE5, 0xA3, 0xE2, 0x4C, 0x15, 0x3D,
                0xF2, 0x27, 0x5C, 0x9F, 0x80, 0x69, 0x27, 0x73,
            },
        },
        {
            "a",
            {
                0x32, 0xEC, 0x01, 0xEC, 0x4A, 0x6D, 0xAC, 0x72,
                0xC0, 0xAB, 0x96, 0xFB, 0x34, 0xC0, 0xB5, 0xD1,
            },
        },
        {
            "message digest",
            {
                0xAB, 0x4F, 0x49, 0x6B, 0xFB, 0x2A, 0x53, 0x0B,
                0x21, 0x9F, 0xF3, 0x30, 0x31, 0xFE, 0x06, 0xB0,
            },
        },
        {
            "abcdefghijklmnopqrstuvwxyz",
            {
                0x4E, 0x8D, 0xDF, 0xF3, 0x65, 0x02, 0x92, 0xAB,
                0x5A, 0x41, 0x08, 0xC3, 0xAA, 0x47, 0x94, 0x0B,
            },
        },
        {
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
            {
                0xDA, 0x33, 0xDE, 0xF2, 0xA4, 0x2D, 0xF1, 0x39,
                0x75, 0x35, 0x28, 0x46, 0xC3, 0x03, 0x38, 0xCD,
            },
        },
        {
            "1234567890123456789012345678901234567890"
            "1234567890123456789012345678901234567890",
            {
                0xD5, 0x97, 0x6F, 0x79, 0xD8, 0x3D, 0x3A, 0x0D,
                0xC9, 0x80, 0x6C, 0x3C, 0x66, 0xF3, 0xEF, 0xD8,
            },
        },
        /* clang-format on */
    };

    unsigned char out[A_MD2_DIGESTSIZE];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_md2(tests[i].msg, strlen(tests[i].msg), out);
        __HASH_DIFF(out, tests[i].hash, A_MD2_DIGESTSIZE);
    }

    return 0;
}

/* END OF FILE */
