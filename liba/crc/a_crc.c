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

#undef __A_CRC_LSB
#define __A_CRC_LSB(_bit)                              \
    void a_crc##_bit##_lsb(uint##_bit##_t _tab[0x100], \
                           uint##_bit##_t _poly)       \
    {                                                  \
        for (unsigned int i = 0; i != 0x100; ++i)      \
        {                                              \
            uint##_bit##_t crc = (uint##_bit##_t)i;    \
            for (unsigned int j = 8; j; --j)           \
            {                                          \
                if (crc & 1)                           \
                {                                      \
                    crc >>= 1;                         \
                    crc ^= _poly;                      \
                }                                      \
                else                                   \
                {                                      \
                    crc >>= 1;                         \
                }                                      \
            }                                          \
            _tab[i] = crc;                             \
        }                                              \
    }
__A_CRC_LSB(8)
__A_CRC_LSB(16)
__A_CRC_LSB(32)
__A_CRC_LSB(64)
#undef __A_CRC_LSB

#undef __A_CRC_MSB
#define __A_CRC_MSB(_bit, _msk)                                   \
    void a_crc##_bit##_msb(uint##_bit##_t _tab[0x100],            \
                           uint##_bit##_t _poly)                  \
    {                                                             \
        for (unsigned int i = 0; i != 0x100; ++i)                 \
        {                                                         \
            uint##_bit##_t crc = (uint##_bit##_t)i << (_bit - 8); \
            for (unsigned int j = 8; j; --j)                      \
            {                                                     \
                if (crc & _msk)                                   \
                {                                                 \
                    crc <<= 1;                                    \
                    crc ^= _poly;                                 \
                }                                                 \
                else                                              \
                {                                                 \
                    crc <<= 1;                                    \
                }                                                 \
            }                                                     \
            _tab[i] = crc;                                        \
        }                                                         \
    }
__A_CRC_MSB(8, 0x80)
__A_CRC_MSB(16, 0x8000)
__A_CRC_MSB(32, 0x80000000)
__A_CRC_MSB(64, 0x8000000000000000)
#undef __A_CRC_MSB

uint8_t a_crc8(const uint8_t _tab[0x100],
               const void *_p, size_t _n,
               uint8_t _crc)
{
    const uint8_t *p = (const uint8_t *)_p;
    const uint8_t *q = (const uint8_t *)_p + _n;
    while (p != q)
    {
        _crc = _tab[_crc ^ *p++];
    }
    return _crc;
}

#undef __A_CRCL
#define __A_CRCL(_bit)                                              \
    uint##_bit##_t a_crc##_bit##l(const uint##_bit##_t _tab[0x100], \
                                  const void *_p, size_t _n,        \
                                  uint##_bit##_t _crc)              \
    {                                                               \
        const uint8_t *p = (const uint8_t *)_p;                     \
        const uint8_t *q = (const uint8_t *)_p + _n;                \
        while (p != q)                                              \
        {                                                           \
            _crc = (_crc >> 8) ^ _tab[(_crc ^ *p++) & 0xFF];        \
        }                                                           \
        return _crc;                                                \
    }
__A_CRCL(16)
__A_CRCL(32)
__A_CRCL(64)
#undef __A_CRCL

#undef __A_CRCH
#define __A_CRCH(_bit)                                                       \
    uint##_bit##_t a_crc##_bit##h(const uint##_bit##_t _tab[0x100],          \
                                  const void *_p, size_t _n,                 \
                                  uint##_bit##_t _crc)                       \
    {                                                                        \
        const uint8_t *p = (const uint8_t *)_p;                              \
        const uint8_t *q = (const uint8_t *)_p + _n;                         \
        while (p != q)                                                       \
        {                                                                    \
            _crc = (_crc << 8) ^ _tab[((_crc >> (_bit - 8)) ^ *p++) & 0xFF]; \
        }                                                                    \
        return _crc;                                                         \
    }
__A_CRCH(16)
__A_CRCH(32)
__A_CRCH(64)
#undef __A_CRCH

#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

/* END OF FILE */
