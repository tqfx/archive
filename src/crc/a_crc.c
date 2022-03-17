/*!
 @file a_crc.c
 @brief Cyclic Redundancy Check
 @details https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_crc.h"

#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif /* _MSC_VER */

#undef A_CRC_LSB
#define A_CRC_LSB(bit)                              \
    void a_crc##bit##_lsb(uint##bit##_t tab[0x100], \
                          uint##bit##_t poly)       \
    {                                               \
        for (unsigned int i = 0; i != 0x100; ++i)   \
        {                                           \
            uint##bit##_t crc = (uint##bit##_t)i;   \
            for (unsigned int j = 8; j; --j)        \
            {                                       \
                if (crc & 1)                        \
                {                                   \
                    crc >>= 1;                      \
                    crc ^= poly;                    \
                }                                   \
                else                                \
                {                                   \
                    crc >>= 1;                      \
                }                                   \
            }                                       \
            tab[i] = crc;                           \
        }                                           \
    }
A_CRC_LSB(8)
A_CRC_LSB(16)
A_CRC_LSB(32)
A_CRC_LSB(64)
#undef A_CRC_LSB

#undef A_CRC_MSB
#define A_CRC_MSB(bit, _msk)                                   \
    void a_crc##bit##_msb(uint##bit##_t tab[0x100],            \
                          uint##bit##_t poly)                  \
    {                                                          \
        for (unsigned int i = 0; i != 0x100; ++i)              \
        {                                                      \
            uint##bit##_t crc = (uint##bit##_t)i << (bit - 8); \
            for (unsigned int j = 8; j; --j)                   \
            {                                                  \
                if (crc & _msk)                                \
                {                                              \
                    crc <<= 1;                                 \
                    crc ^= poly;                               \
                }                                              \
                else                                           \
                {                                              \
                    crc <<= 1;                                 \
                }                                              \
            }                                                  \
            tab[i] = crc;                                      \
        }                                                      \
    }
A_CRC_MSB(8, 0x80)
A_CRC_MSB(16, 0x8000)
A_CRC_MSB(32, 0x80000000)
A_CRC_MSB(64, 0x8000000000000000)
#undef A_CRC_MSB

uint8_t a_crc8(const uint8_t tab[0x100],
               const void *pdata, size_t nbyte,
               uint8_t crc)
{
    const uint8_t *p = (const uint8_t *)pdata;
    const uint8_t *q = (const uint8_t *)pdata + nbyte;
    while (p != q)
    {
        crc = tab[crc ^ *p++];
    }
    return crc;
}

#undef A_CRCL
#define A_CRCL(bit)                                              \
    uint##bit##_t a_crc##bit##l(const uint##bit##_t tab[0x100],  \
                                const void *pdata, size_t nbyte, \
                                uint##bit##_t crc)               \
    {                                                            \
        const uint8_t *p = (const uint8_t *)pdata;               \
        const uint8_t *q = (const uint8_t *)pdata + nbyte;       \
        while (p != q)                                           \
        {                                                        \
            crc = (crc >> 8) ^ tab[(crc ^ *p++) & 0xFF];         \
        }                                                        \
        return crc;                                              \
    }
A_CRCL(16)
A_CRCL(32)
A_CRCL(64)
#undef A_CRCL

#undef A_CRCH
#define A_CRCH(bit)                                                     \
    uint##bit##_t a_crc##bit##h(const uint##bit##_t tab[0x100],         \
                                const void *pdata, size_t nbyte,        \
                                uint##bit##_t crc)                      \
    {                                                                   \
        const uint8_t *p = (const uint8_t *)pdata;                      \
        const uint8_t *q = (const uint8_t *)pdata + nbyte;              \
        while (p != q)                                                  \
        {                                                               \
            crc = (crc << 8) ^ tab[((crc >> (bit - 8)) ^ *p++) & 0xFF]; \
        }                                                               \
        return crc;                                                     \
    }
A_CRCH(16)
A_CRCH(32)
A_CRCH(64)
#undef A_CRCH

#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */
