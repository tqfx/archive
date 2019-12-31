/*!
 @file hash.h
 @brief hash library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_HASH_H__
#define __A_HASH_H__

#include "../def.h"

#include "md2.h"
#include "md4.h"
#include "md5.h"

#include "rmd128.h"
#include "rmd160.h"
#include "rmd256.h"
#include "rmd320.h"

#include "sha1.h"
#include "sha256.h"
#include "sha512.h"
#include "sha3.h"

#include "tiger.h"
#include "whirl.h"

#include "blake2s.h"
#include "blake2b.h"

/*!
    shake128    0xA8    168
    sha3-224    0x90    144
*/
#define A_HASH_BUFSIZ 0xA8

typedef union a_hash_u
{
#if defined(__A_MD2_H__)
    a_md2_s md2[1];
#endif /* __A_MD2_H__ */
#if defined(__A_MD4_H__)
    a_md4_s md4[1];
#endif /* __A_MD4_H__ */
#if defined(__A_MD5_H__)
    a_md5_s md5[1];
#endif /* __A_MD5_H__ */
#if defined(__A_RMD128_H__)
    a_rmd128_s rmd128[1];
#endif /* __A_RMD128_H__ */
#if defined(__A_RMD160_H__)
    a_rmd160_s rmd160[1];
#endif /* __A_RMD160_H__ */
#if defined(__A_RMD256_H__)
    a_rmd256_s rmd256[1];
#endif /* __A_RMD256_H__ */
#if defined(__A_RMD320_H__)
    a_rmd320_s rmd320[1];
#endif /* __A_RMD320_H__ */
#if defined(__A_SHA1_H__)
    a_sha1_s sha1[1];
#endif /* __A_SHA1_H__ */
#if defined(__A_SHA256_H__)
    a_sha256_s sha256[1];
#endif /* __A_SHA256_H__ */
#if defined(__A_SHA512_H__)
    a_sha512_s sha512[1];
#endif /* __A_SHA512_H__ */
#if defined(__A_SHA3_H__)
    a_sha3_s sha3[1];
#endif /* __A_SHA3_H__ */
#if defined(__A_TIGER_H__)
    a_tiger_s tiger[1];
#endif /* __A_TIGER_H__ */
#if defined(__A_BLAKE2S_H__)
    a_blake2s_s blake2s[1];
#endif /* __A_BLAKE2S_H__ */
#if defined(__A_BLAKE2B_H__)
    a_blake2b_s blake2b[1];
#endif /* __A_BLAKE2B_H__ */
#if defined(__A_WHIRL_H__)
    a_whirlpool_s whirlpool[1];
#endif /* __A_WHIRL_H__ */
} a_hash_u;

typedef struct a_hash_s
{
    unsigned int bufsiz; /*!< size of block */
    unsigned int outsiz; /*!< size of digest */
    /*!
     @brief Initialize function for hash.
     @param[in,out] ctx points to an instance of hash state.
    */
    void (*init)(a_hash_u *ctx);
    /*!
     @brief Process function for hash.
     @param[in,out] ctx points to an instance of hash state.
     @param[in] pdata points to data to hash.
     @param[in] nbyte length of data to hash.
     @return the execution state of the function.
      @retval 0 success
    */
    int (*proc)(a_hash_u *ctx, const void *pdata, size_t nbyte);
    /*!
     @brief Terminate function for hash.
     @param[in,out] ctx points to an instance of hash state.
     @param[in,out] out points to buffer that holds the digest.
     @return the digest internal buffer.
      @retval 0 generic invalid argument.
    */
    unsigned char *(*done)(a_hash_u *ctx, void *out);
} a_hash_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#if defined(__A_MD2_H__)
A_PUBLIC extern const a_hash_s a_hash_md2;
#endif /* __A_MD2_H__ */
#if defined(__A_MD4_H__)
A_PUBLIC extern const a_hash_s a_hash_md4;
#endif /* __A_MD4_H__ */
#if defined(__A_MD5_H__)
A_PUBLIC extern const a_hash_s a_hash_md5;
#endif /* __A_MD5_H__ */
#if defined(__A_RMD128_H__)
A_PUBLIC extern const a_hash_s a_hash_rmd128;
#endif /* __A_RMD128_H__ */
#if defined(__A_RMD160_H__)
A_PUBLIC extern const a_hash_s a_hash_rmd160;
#endif /* __A_RMD160_H__ */
#if defined(__A_RMD256_H__)
A_PUBLIC extern const a_hash_s a_hash_rmd256;
#endif /* __A_RMD256_H__ */
#if defined(__A_RMD320_H__)
A_PUBLIC extern const a_hash_s a_hash_rmd320;
#endif /* __A_RMD320_H__ */
#if defined(__A_SHA1_H__)
A_PUBLIC extern const a_hash_s a_hash_sha1;
#endif /* __A_SHA1_H__ */
#if defined(__A_SHA256_H__)
A_PUBLIC extern const a_hash_s a_hash_sha224;
A_PUBLIC extern const a_hash_s a_hash_sha256;
#endif /* __A_SHA256_H__ */
#if defined(__A_SHA512_H__)
A_PUBLIC extern const a_hash_s a_hash_sha384;
A_PUBLIC extern const a_hash_s a_hash_sha512;
A_PUBLIC extern const a_hash_s a_hash_sha512_224;
A_PUBLIC extern const a_hash_s a_hash_sha512_256;
#endif /* __A_SHA512_H__ */
#if defined(__A_SHA3_H__)
A_PUBLIC extern const a_hash_s a_hash_sha3_224;
A_PUBLIC extern const a_hash_s a_hash_sha3_256;
A_PUBLIC extern const a_hash_s a_hash_sha3_384;
A_PUBLIC extern const a_hash_s a_hash_sha3_512;
A_PUBLIC extern const a_hash_s a_hash_shake128;
A_PUBLIC extern const a_hash_s a_hash_shake256;
A_PUBLIC extern const a_hash_s a_hash_keccak224;
A_PUBLIC extern const a_hash_s a_hash_keccak256;
A_PUBLIC extern const a_hash_s a_hash_keccak384;
A_PUBLIC extern const a_hash_s a_hash_keccak512;
#endif /* __A_SHA3_H__ */
#if defined(__A_TIGER_H__)
A_PUBLIC extern const a_hash_s a_hash_siger;
#endif /* __A_TIGER_H__ */
#if defined(__A_BLAKE2S_H__)
A_PUBLIC extern const a_hash_s a_hash_blake2s_128;
A_PUBLIC extern const a_hash_s a_hash_blake2s_160;
A_PUBLIC extern const a_hash_s a_hash_blake2s_224;
A_PUBLIC extern const a_hash_s a_hash_blake2s_256;
#endif /* __A_BLAKE2S_H__ */
#if defined(__A_BLAKE2B_H__)
A_PUBLIC extern const a_hash_s a_hash_blake2b_160;
A_PUBLIC extern const a_hash_s a_hash_blake2b_256;
A_PUBLIC extern const a_hash_s a_hash_blake2b_384;
A_PUBLIC extern const a_hash_s a_hash_blake2b_512;
#endif /* __A_BLAKE2B_H__ */
#if defined(__A_WHIRL_H__)
A_PUBLIC extern const a_hash_s a_hash_whirlpool;
#endif /* __A_WHIRL_H__ */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_HASH_H__ */
