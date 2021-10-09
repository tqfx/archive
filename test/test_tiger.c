/*!
 @file           test_tiger.c
 @brief          test tiger
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_tiger.h"

#include "test_hash.h"

#include <string.h>

int main(void)
{
    static const struct
    {
        const char *msg;
        unsigned char hash[A_TIGER_DIGESTSIZE];
    } tests[] = {
        /* clang-format off */
        {
            "",
            {
                0x32, 0x93, 0xAC, 0x63, 0x0C, 0x13, 0xF0, 0x24,
                0x5F, 0x92, 0xBB, 0xB1, 0x76, 0x6E, 0x16, 0x16,
                0x7A, 0x4E, 0x58, 0x49, 0x2D, 0xDE, 0x73, 0xF3,
            },
        },
        {
            "abc",
            {
                0x2A, 0xAB, 0x14, 0x84, 0xE8, 0xC1, 0x58, 0xF2,
                0xBF, 0xB8, 0xC5, 0xFF, 0x41, 0xB5, 0x7A, 0x52,
                0x51, 0x29, 0x13, 0x1C, 0x95, 0x7B, 0x5F, 0x93,
            },
        },
        {
            "Tiger",
            {
                0xDD, 0x00, 0x23, 0x07, 0x99, 0xF5, 0x00, 0x9F,
                0xEC, 0x6D, 0xEB, 0xC8, 0x38, 0xBB, 0x6A, 0x27,
                0xDF, 0x2B, 0x9D, 0x6F, 0x11, 0x0C, 0x79, 0x37,
            },
        },
        {
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-",
            {
                0xF7, 0x1C, 0x85, 0x83, 0x90, 0x2A, 0xFB, 0x87,
                0x9E, 0xDF, 0xE6, 0x10, 0xF8, 0x2C, 0x0D, 0x47,
                0x86, 0xA3, 0xA5, 0x34, 0x50, 0x44, 0x86, 0xB5,
            },
        },
        {
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-",
            {
                0xC5, 0x40, 0x34, 0xE5, 0xB4, 0x3E, 0xB8, 0x00,
                0x58, 0x48, 0xA7, 0xE0, 0xAE, 0x6A, 0xAC, 0x76,
                0xE4, 0xFF, 0x59, 0x0A, 0xE7, 0x15, 0xFD, 0x25,
            },
        },
        /* clang-format on */
    };

    a_tiger_t ctx[1];

    for (unsigned int i = 0; i != sizeof(tests) / sizeof(*tests); ++i)
    {
        a_tiger(tests[i].msg, strlen(tests[i].msg), ctx->out);
        __HASH_DIFF(ctx->out, tests[i].hash, A_TIGER_DIGESTSIZE);
    }

    return 0;
}

/* END OF FILE */
