/*!
 @file crc.c
 @brief test Cyclic Redundancy Check
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/cksum/crc.h"

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

#undef WRITE_TAB
#define WRITE_TAB(bit, row, fmt)                                                              \
    static void write_tab##bit(FILE *out, uint##bit##_t tab[A_CRC_TABSIZ], const char *label) \
    {                                                                                         \
        fprintf(out, "const uint%i_t %s[0x%X] = {\n", bit, label, A_CRC_TABSIZ);              \
        fprintf(out, "    /* clang-format off */\n");                                         \
        for (size_t i = 0; i != A_CRC_TABSIZ / row; ++i)                                      \
        {                                                                                     \
            fprintf(out, "    ");                                                             \
            for (size_t j = 0; j != row; ++j)                                                 \
            {                                                                                 \
                fprintf(out, "0x%0" #fmt PRIx##bit ",", tab[row * i + j]);                    \
                if (j != row - 1)                                                             \
                {                                                                             \
                    fprintf(out, " ");                                                        \
                }                                                                             \
            }                                                                                 \
            fprintf(out, "\n");                                                               \
        }                                                                                     \
        fprintf(out, "    /* clang-format on */\n");                                          \
        fprintf(out, "};\n");                                                                 \
    }
WRITE_TAB(8, 8, 2)
WRITE_TAB(16, 8, 4)
WRITE_TAB(32, 8, 8)
WRITE_TAB(64, 4, 16)
#undef WRITE_TAB

static void create_table(const char *fname)
{
    FILE *fp = stdout;

    if (fname)
    {
        fp = fopen(fname, "wb");
        if (fp == 0)
        {
            perror(fname);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fname = "crc_tab.c";
    }

    fprintf(fp, "/*!\n");
    fprintf(fp, " @file %s\n", fname);
    fprintf(fp, " @brief Table for Cyclic Redundancy Check\n");
    fprintf(fp, " @copyright Copyright (C) 2020 tqfx, All rights reserved.\n");
    fprintf(fp, "*/\n\n");

    fprintf(fp, "#include <stdint.h>\n\n");

    uint8_t tab8[A_CRC_TABSIZ];
    a_crc8_lsb(tab8, A_CRC8_POLY);
    write_tab8(fp, tab8, "crc8_tabl");
    a_crc8_msb(tab8, A_CRC8_POLY);
    write_tab8(fp, tab8, "crc8_tabh");

    uint16_t tab16[A_CRC_TABSIZ];
    a_crc16_lsb(tab16, A_CRC16_POLY);
    write_tab16(fp, tab16, "crc16_tabl");
    a_crc16_msb(tab16, A_CRC16_POLY);
    write_tab16(fp, tab16, "crc16_tabh");

    uint32_t tab32[A_CRC_TABSIZ];
    a_crc32_lsb(tab32, A_CRC32_POLY);
    write_tab32(fp, tab32, "crc32_tabl");
    a_crc32_msb(tab32, A_CRC32_POLY);
    write_tab32(fp, tab32, "crc32_tabh");

    uint64_t tab64[A_CRC_TABSIZ];
    a_crc64_lsb(tab64, A_CRC64_POLY);
    write_tab64(fp, tab64, "crc64_tabl");
    a_crc64_msb(tab64, A_CRC64_POLY);
    write_tab64(fp, tab64, "crc64_tabh");

    fclose(fp);
}

static void test(void)
{
    const char *text = "123456789";
    unsigned int size = sizeof("123456789") - 1;

    uint8_t tab8[A_CRC_TABSIZ];
    printf("POLY: 0x%02u\n", A_CRC8_POLY);
    printf("INIT: 0x%02u\n", A_CRC8_INIT);
    a_crc8_lsb(tab8, A_CRC8_POLY);
    printf("LSB: 0x%02" PRIX8 "\n", a_crc8(tab8, text, size, A_CRC8_INIT));
    a_crc8_msb(tab8, A_CRC8_POLY);
    printf("MSB: 0x%02" PRIX8 "\n", a_crc8(tab8, text, size, A_CRC8_INIT));

    uint16_t tab16[A_CRC_TABSIZ];
    printf("POLY: 0x%04u\n", A_CRC16_POLY);
    printf("INIT: 0x%04u\n", A_CRC16_INIT);
    a_crc16_lsb(tab16, A_CRC16_POLY);
    printf("LSB: 0x%04" PRIX16 "(L) 0x%04" PRIX16 "(H)\n",
           a_crc16l(tab16, text, size, A_CRC16_INIT),
           a_crc16h(tab16, text, size, A_CRC16_INIT));
    a_crc16_msb(tab16, A_CRC16_POLY);
    printf("MSB: 0x%04" PRIX16 "(L) 0x%04" PRIX16 "(H)\n",
           a_crc16l(tab16, text, size, A_CRC16_INIT),
           a_crc16h(tab16, text, size, A_CRC16_INIT));

    uint32_t tab32[A_CRC_TABSIZ];
    printf("POLY: 0x%08" PRIX32 "\n", A_CRC32_POLY);
    printf("INIT: 0x%08" PRIX32 "\n", A_CRC32_INIT);
    a_crc32_lsb(tab32, A_CRC32_POLY);
    printf("LSB: 0x%08" PRIX32 "(L) 0x%08" PRIX32 "(H)\n",
           a_crc32l(tab32, text, size, A_CRC32_INIT),
           a_crc32h(tab32, text, size, A_CRC32_INIT));
    a_crc32_msb(tab32, A_CRC32_POLY);
    printf("MSB: 0x%08" PRIX32 "(L) 0x%08" PRIX32 "(H)\n",
           a_crc32l(tab32, text, size, A_CRC32_INIT),
           a_crc32h(tab32, text, size, A_CRC32_INIT));

    uint64_t tab64[A_CRC_TABSIZ];
    printf("POLY: 0x%016" PRIX64 "\n", A_CRC64_POLY);
    printf("INIT: 0x%016" PRIX64 "\n", A_CRC64_INIT);
    a_crc64_lsb(tab64, A_CRC64_POLY);
    printf("LSB: 0x%016" PRIX64 "(L) 0x%016" PRIX64 "(H)\n",
           a_crc64l(tab64, text, size, A_CRC64_INIT),
           a_crc64h(tab64, text, size, A_CRC64_INIT));
    a_crc64_msb(tab64, A_CRC64_POLY);
    printf("LSB: 0x%016" PRIX64 "(L) 0x%016" PRIX64 "(H)\n",
           a_crc64l(tab64, text, size, A_CRC64_INIT),
           a_crc64h(tab64, text, size, A_CRC64_INIT));
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        create_table(argv[argc - 1]);
    }

    test();

    return 0;
}
