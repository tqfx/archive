/*!
 @file a_crc.c
 @brief Cyclic Redundancy Check
 @details https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_crc.h"

#undef __A_CRC_LSB
#define __A_CRC_LSB(_bit)                              \
    void a_crc##_bit##_lsb(uint##_bit##_t _tab[0x100], \
                           uint##_bit##_t _poly)       \
    {                                                  \
        for (unsigned int i = 0; i != 0x100; ++i)      \
        {                                              \
            uint##_bit##_t crc = (uint8_t)i;           \
            for (unsigned int j = 0; j != 8; ++j)      \
            {                                          \
                crc = (crc >> 1) ^                     \
                      ((crc & 1) ? _poly : 0);         \
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
#define __A_CRC_MSB(_bit, _msk)                        \
    void a_crc##_bit##_msb(uint##_bit##_t _tab[0x100], \
                           uint##_bit##_t _poly)       \
    {                                                  \
        for (unsigned int i = 0; i != 0x100; ++i)      \
        {                                              \
            uint##_bit##_t crc = (uint8_t)i;           \
            for (unsigned int j = _bit; j; --j)        \
            {                                          \
                crc = (crc << 1) ^                     \
                      ((crc & _msk) ? _poly : 0);      \
            }                                          \
            _tab[i] = crc;                             \
        }                                              \
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

uint16_t a_crc16(const uint16_t _tab[0x100],
                 const void *_p, size_t _n,
                 uint16_t _crc)
{
    const uint8_t *p = (const uint8_t *)_p;
    const uint8_t *q = (const uint8_t *)_p + _n;
    while (p != q)
    {
#if 1
        _crc = (_crc >> 8) ^ _tab[(_crc ^ *p++) & 0xFF];
#else
        _crc = (_crc << 8) ^ _tab[((_crc >> 0x8) ^ *p++) & 0xFF];
#endif
    }
    return _crc;
}

uint32_t a_crc32(const uint32_t _tab[0x100],
                 const void *_p, size_t _n,
                 uint32_t _crc)
{
    const uint8_t *p = (const uint8_t *)_p;
    const uint8_t *q = (const uint8_t *)_p + _n;
    while (p != q)
    {
#if 1
        _crc = (_crc >> 8) ^ _tab[(_crc ^ *p++) & 0xFF];
#else
        _crc = (_crc << 8) ^ _tab[((_crc >> 0x18) ^ *p++) & 0xFF];
#endif
    }
    return _crc;
}

uint64_t a_crc64(const uint64_t _tab[0x100],
                 const void *_p, size_t _n,
                 uint64_t _crc)
{
    const uint8_t *p = (const uint8_t *)_p;
    const uint8_t *q = (const uint8_t *)_p + _n;
    while (p != q)
    {
#if 1
        _crc = (_crc >> 8) ^ _tab[(_crc ^ *p++) & 0xFF];
#else
        _crc = (_crc << 8) ^ _tab[((_crc >> 0x38) ^ *p++) & 0xFF];
#endif
    }
    return _crc;
}

/* END OF FILE */
