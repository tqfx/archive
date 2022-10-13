/*!
 @file crc.cpp
 @brief Test Cyclic Redundancy Check
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/crc.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define WRITE_TABLE(bit, row, fmt)                                                           \
    static a_void_t write_table##bit(FILE *out, a_u##bit##_t ctx[A_CRC_SIZ], a_cstr_t label) \
    {                                                                                        \
        fprintf(out, "const uint%i_t %s[0x%X] = {\n", bit, label, A_CRC_SIZ);                \
        fprintf(out, "    /* clang-format off */\n");                                        \
        for (a_size_t i = 0; i != A_CRC_SIZ / row; ++i)                                      \
        {                                                                                    \
            fprintf(out, "    ");                                                            \
            for (a_size_t j = 0; j != row; ++j)                                              \
            {                                                                                \
                fprintf(out, "0x%0" #fmt PRIX##bit ",", ctx[row * i + j]);                   \
                if (j != row - 1)                                                            \
                {                                                                            \
                    fputc(' ', out);                                                         \
                }                                                                            \
            }                                                                                \
            fputc('\n', out);                                                                \
        }                                                                                    \
        fprintf(out, "    /* clang-format on */\n");                                         \
        fprintf(out, "};\n");                                                                \
    }
WRITE_TABLE(8, 8, 2)
WRITE_TABLE(16, 8, 4)
WRITE_TABLE(32, 8, 8)
WRITE_TABLE(64, 4, 16)
#undef WRITE_TABLE

static a_void_t create_table(a_cstr_t name)
{
    FILE *out = stdout;

    if (name)
    {
        out = fopen(name, "wb");
        if (!out)
        {
            perror(name);
            exit(EXIT_FAILURE);
        }
    }

    fprintf(out, "#include <stdint.h>\n");

    a_u8_t table8[A_CRC_SIZ];
    a_crc8l_init(table8, A_CRC8_POLY);
    write_table8(out, table8, "CRC8L");
    a_crc8h_init(table8, A_CRC8_POLY);
    write_table8(out, table8, "CRC8H");

    a_u16_t table16[A_CRC_SIZ];
    a_crc16l_init(table16, A_CRC16_POLY);
    write_table16(out, table16, "CRC16L");
    a_crc16h_init(table16, A_CRC16_POLY);
    write_table16(out, table16, "CRC16H");

    a_u32_t table32[A_CRC_SIZ];
    a_crc32l_init(table32, A_CRC32_POLY);
    write_table32(out, table32, "CRC32L");
    a_crc32h_init(table32, A_CRC32_POLY);
    write_table32(out, table32, "CRC32H");

    a_u64_t table64[A_CRC_SIZ];
    a_crc64l_init(table64, A_CRC64_POLY);
    write_table64(out, table64, "CRC64L");
    a_crc64h_init(table64, A_CRC64_POLY);
    write_table64(out, table64, "CRC64H");

    fclose(out);
}

static void test(void)
{
    a_cstr_t text = "123456789";
    a_uint_t size = sizeof("123456789") - 1;

    a_u8_t table8[A_CRC_SIZ];
    printf("POLY: 0x%02u\n", A_CRC8_POLY);
    printf("INIT: 0x%02u\n", A_CRC8_INIT);
    a_crc8l_init(table8, A_CRC8_POLY);
    printf("LSB: 0x%02" PRIX8 "\n", a_crc8(table8, text, size, A_CRC8_INIT));
    a_crc8h_init(table8, A_CRC8_POLY);
    printf("MSB: 0x%02" PRIX8 "\n", a_crc8(table8, text, size, A_CRC8_INIT));

    a_u16_t table16[A_CRC_SIZ];
    printf("POLY: 0x%04u\n", A_CRC16_POLY);
    printf("INIT: 0x%04u\n", A_CRC16_INIT);
    a_crc16l_init(table16, A_CRC16_POLY);
    printf("LSB: 0x%04" PRIX16 "(L) 0x%04" PRIX16 "(H)\n",
           a_crc16l(table16, text, size, A_CRC16_INIT),
           a_crc16h(table16, text, size, A_CRC16_INIT));
    a_crc16h_init(table16, A_CRC16_POLY);
    printf("MSB: 0x%04" PRIX16 "(L) 0x%04" PRIX16 "(H)\n",
           a_crc16l(table16, text, size, A_CRC16_INIT),
           a_crc16h(table16, text, size, A_CRC16_INIT));

    a_u32_t table32[A_CRC_SIZ];
    printf("POLY: 0x%08" PRIX32 "\n", A_CRC32_POLY);
    printf("INIT: 0x%08" PRIX32 "\n", A_CRC32_INIT);
    a_crc32l_init(table32, A_CRC32_POLY);
    printf("LSB: 0x%08" PRIX32 "(L) 0x%08" PRIX32 "(H)\n",
           a_crc32l(table32, text, size, A_CRC32_INIT),
           a_crc32h(table32, text, size, A_CRC32_INIT));
    a_crc32h_init(table32, A_CRC32_POLY);
    printf("MSB: 0x%08" PRIX32 "(L) 0x%08" PRIX32 "(H)\n",
           a_crc32l(table32, text, size, A_CRC32_INIT),
           a_crc32h(table32, text, size, A_CRC32_INIT));

    a_u64_t table64[A_CRC_SIZ];
    printf("POLY: 0x%016" PRIX64 "\n", A_CRC64_POLY);
    printf("INIT: 0x%016" PRIX64 "\n", A_CRC64_INIT);
    a_crc64l_init(table64, A_CRC64_POLY);
    printf("LSB: 0x%016" PRIX64 "(L) 0x%016" PRIX64 "(H)\n",
           a_crc64l(table64, text, size, A_CRC64_INIT),
           a_crc64h(table64, text, size, A_CRC64_INIT));
    a_crc64h_init(table64, A_CRC64_POLY);
    printf("MSB: 0x%016" PRIX64 "(L) 0x%016" PRIX64 "(H)\n",
           a_crc64l(table64, text, size, A_CRC64_INIT),
           a_crc64h(table64, text, size, A_CRC64_INIT));
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        create_table(argv[argc - 1]);
    }
    test();
    return A_SUCCESS;
}
