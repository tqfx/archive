/*!
 @file a_crc.h
 @brief Cyclic Redundancy Check
 @details https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_CRC_H__
#define __A_CRC_H__

#include "liba.h"

#define A_CRC_TABSIZ 0x100

#define A_CRC8_POLY 0x31
#define A_CRC8_INIT 0x00

#define A_CRC16_POLY 0xA001
#define A_CRC16_INIT 0x0000

#define A_CRC32_POLY 0xEDB88320
#define A_CRC32_INIT 0xFFFFFFFF

#define A_CRC64_POLY 0x42F0E1EBA9EA3693
#define A_CRC64_INIT 0xFFFFFFFFFFFFFFFF

__BEGIN_DECLS

void a_crc8_lsb(uint8_t tab[0x100], uint8_t poly);
void a_crc8_msb(uint8_t tab[0x100], uint8_t poly);
uint8_t a_crc8(const uint8_t tab[0x100], const void *pdata, size_t nbyte, uint8_t crc);

void a_crc16_lsb(uint16_t tab[0x100], uint16_t poly);
void a_crc16_msb(uint16_t tab[0x100], uint16_t poly);
uint16_t a_crc16l(const uint16_t tab[0x100], const void *pdata, size_t nbyte, uint16_t crc);
uint16_t a_crc16h(const uint16_t tab[0x100], const void *pdata, size_t nbyte, uint16_t crc);

void a_crc32_lsb(uint32_t tab[0x100], uint32_t poly);
void a_crc32_msb(uint32_t tab[0x100], uint32_t poly);
uint32_t a_crc32l(const uint32_t tab[0x100], const void *pdata, size_t nbyte, uint32_t crc);
uint32_t a_crc32h(const uint32_t tab[0x100], const void *pdata, size_t nbyte, uint32_t crc);

void a_crc64_lsb(uint64_t tab[0x100], uint64_t poly);
void a_crc64_msb(uint64_t tab[0x100], uint64_t poly);
uint64_t a_crc64l(const uint64_t tab[0x100], const void *pdata, size_t nbyte, uint64_t crc);
uint64_t a_crc64h(const uint64_t tab[0x100], const void *pdata, size_t nbyte, uint64_t crc);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_CRC_H__ */
