/*!
 @file test_crctab.c
 @brief Create Cyclic Redundancy Check Table
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_crc.h"

#include <stdio.h>
#include <stdlib.h>

#undef __WRITE_TAB
#define __WRITE_TAB(_bit, _)                                                                \
    void write_tab##_bit(FILE *_out, uint##_bit##_t _tab[A_CRC_TABSIZ], const char *_label) \
    {                                                                                       \
        fprintf(_out, "const uint%u_t %s[0x%X] = {\n", _bit, _label, A_CRC_TABSIZ);         \
        fprintf(_out, "    /* clang-format off */\n");                                      \
        for (size_t i = 0; i != A_CRC_TABSIZ / 8; ++i)                                      \
        {                                                                                   \
            fprintf(_out, "    ");                                                          \
            for (size_t j = 0; j != 8; ++j)                                                 \
            {                                                                               \
                fprintf(_out, "0x%0" #_ "X,", _tab[8 * i + j]);                             \
                if (j != 7)                                                                 \
                {                                                                           \
                    fprintf(_out, " ");                                                     \
                }                                                                           \
            }                                                                               \
            fprintf(_out, "\n");                                                            \
        }                                                                                   \
        fprintf(_out, "    /* clang-format on */\n");                                       \
        fprintf(_out, "};\n\n");                                                            \
    }
__WRITE_TAB(8, 2)
__WRITE_TAB(16, 4)
__WRITE_TAB(32, 8)
#undef __WRITE_TAB

void write_tab64(FILE *_out, uint64_t _tab[A_CRC_TABSIZ], const char *_label)
{
    fprintf(_out, "const uint%u_t %s[0x%X] = {\n", 64, _label, A_CRC_TABSIZ);
    fprintf(_out, "    /* clang-format off */\n");
    for (size_t i = 0; i != A_CRC_TABSIZ / 4; ++i)
    {
        fprintf(_out, "    ");
        for (size_t j = 0; j != 4; ++j)
        {
            fprintf(_out, "0x%016zX,", _tab[4 * i + j]);
            if (j != 3)
            {
                fprintf(_out, " ");
            }
        }
        fprintf(_out, "\n");
    }
    fprintf(_out, "    /* clang-format on */\n");
    fprintf(_out, "};\n\n");
}

void create_table(const char *_fname)
{
    FILE *fp = stdout;

    if (_fname)
    {
        fp = fopen(_fname, "wb");
        if (fp == 0)
        {
            perror(_fname);
            exit(EXIT_FAILURE);
        }
    }

    fprintf(fp, "/*!\n");
    fprintf(fp, " @file %s\n", _fname);
    fprintf(fp, " @brief Table for Cyclic Redundancy Check\n");
    fprintf(fp, " @copyright Copyright (C) 2020 tqfx. All rights reserved.\n");
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

    fprintf(fp, "/* END OF FILE */\n");
    fclose(fp);
}

int main(int argc, char *argv[])
{
    const char *fname = 0;

    if (argc > 1)
    {
        fname = argv[argc - 1];
    }

    create_table(fname);

    return 0;
}

/* END OF FILE */
