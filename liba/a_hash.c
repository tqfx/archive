/*!
 @file           a_hash.c
 @brief          hash library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_hash.h"

const a_hash_t a_hash_md2 = {
    .bufsiz = A_MD2_BUFSIZ,
    .outsiz = A_MD2_OUTSIZ,
    .init = a_hash_init_md2,
    .process = a_hash_process_md2,
    .done = a_hash_done_md2,
};

const a_hash_t a_hash_md4 = {
    .bufsiz = A_MD4_BUFSIZ,
    .outsiz = A_MD4_OUTSIZ,
    .init = a_hash_init_md4,
    .process = a_hash_process_md4,
    .done = a_hash_done_md4,
};

const a_hash_t a_hash_md5 = {
    .bufsiz = A_MD5_BUFSIZ,
    .outsiz = A_MD5_OUTSIZ,
    .init = a_hash_init_md5,
    .process = a_hash_process_md5,
    .done = a_hash_done_md5,
};

const a_hash_t a_hash_sha1 = {
    .bufsiz = A_SHA1_BUFSIZ,
    .outsiz = A_SHA1_OUTSIZ,
    .init = a_hash_init_sha1,
    .process = a_hash_process_sha1,
    .done = a_hash_done_sha1,
};

const a_hash_t a_hash_tiger = {
    .bufsiz = A_TIGER_BUFSIZ,
    .outsiz = A_TIGER_OUTSIZ,
    .init = a_hash_init_tiger,
    .process = a_hash_process_tiger,
    .done = a_hash_done_tiger,
};

const a_hash_t a_hash_rmd128 = {
    .bufsiz = A_RIPEMD_BUFSIZ,
    .outsiz = A_RIPEMD128_OUTSIZ,
    .init = a_hash_init_rmd128,
    .process = a_hash_process_rmd128,
    .done = a_hash_done_rmd128,
};

const a_hash_t a_hash_rmd160 = {
    .bufsiz = A_RIPEMD_BUFSIZ,
    .outsiz = A_RIPEMD160_OUTSIZ,
    .init = a_hash_init_rmd160,
    .process = a_hash_process_rmd160,
    .done = a_hash_done_rmd160,
};

const a_hash_t a_hash_rmd256 = {
    .bufsiz = A_RIPEMD_BUFSIZ,
    .outsiz = A_RIPEMD256_OUTSIZ,
    .init = a_hash_init_rmd256,
    .process = a_hash_process_rmd256,
    .done = a_hash_done_rmd256,
};

const a_hash_t a_hash_rmd320 = {
    .bufsiz = A_RIPEMD_BUFSIZ,
    .outsiz = A_RIPEMD320_OUTSIZ,
    .init = a_hash_init_rmd320,
    .process = a_hash_process_rmd320,
    .done = a_hash_done_rmd320,
};

const a_hash_t a_hash_sha224 = {
    .bufsiz = A_SHA256_BUFSIZ,
    .outsiz = A_SHA224_OUTSIZ,
    .init = a_hash_init_sha224,
    .process = a_hash_process_sha224,
    .done = a_hash_done_sha224,
};

const a_hash_t a_hash_sha256 = {
    .bufsiz = A_SHA256_BUFSIZ,
    .outsiz = A_SHA256_OUTSIZ,
    .init = a_hash_init_sha256,
    .process = a_hash_process_sha256,
    .done = a_hash_done_sha256,
};

const a_hash_t a_hash_sha384 = {
    .bufsiz = A_SHA512_BUFSIZ,
    .outsiz = A_SHA384_OUTSIZ,
    .init = a_hash_init_sha384,
    .process = a_hash_process_sha384,
    .done = a_hash_done_sha384,
};

const a_hash_t a_hash_sha512 = {
    .bufsiz = A_SHA512_BUFSIZ,
    .outsiz = A_SHA512_OUTSIZ,
    .init = a_hash_init_sha512,
    .process = a_hash_process_sha512,
    .done = a_hash_done_sha512,
};

const a_hash_t a_hash_sha512_224 = {
    .bufsiz = A_SHA512_BUFSIZ,
    .outsiz = A_SHA512_224_OUTSIZ,
    .init = a_hash_init_sha512_224,
    .process = a_hash_process_sha512_224,
    .done = a_hash_done_sha512_224,
};

const a_hash_t a_hash_sha512_256 = {
    .bufsiz = A_SHA512_BUFSIZ,
    .outsiz = A_SHA512_256_OUTSIZ,
    .init = a_hash_init_sha512_256,
    .process = a_hash_process_sha512_256,
    .done = a_hash_done_sha512_256,
};

const a_hash_t a_hash_sha3_224 = {
    .bufsiz = A_SHA3_224_BUFSIZ,
    .outsiz = A_SHA3_224_OUTSIZ,
    .init = a_hash_init_sha3_224,
    .process = a_hash_process_sha3_224,
    .done = a_hash_done_sha3_224,
};

const a_hash_t a_hash_sha3_256 = {
    .bufsiz = A_SHA3_256_BUFSIZ,
    .outsiz = A_SHA3_256_OUTSIZ,
    .init = a_hash_init_sha3_256,
    .process = a_hash_process_sha3_256,
    .done = a_hash_done_sha3_256,
};

const a_hash_t a_hash_sha3_384 = {
    .bufsiz = A_SHA3_384_BUFSIZ,
    .outsiz = A_SHA3_384_OUTSIZ,
    .init = a_hash_init_sha3_384,
    .process = a_hash_process_sha3_384,
    .done = a_hash_done_sha3_384,
};

const a_hash_t a_hash_sha3_512 = {
    .bufsiz = A_SHA3_512_BUFSIZ,
    .outsiz = A_SHA3_512_OUTSIZ,
    .init = a_hash_init_sha3_512,
    .process = a_hash_process_sha3_512,
    .done = a_hash_done_sha3_512,
};

const a_hash_t a_hash_shake128 = {
    .bufsiz = A_SHAKE128_BUFSIZ,
    .outsiz = A_SHAKE128_OUTSIZ,
    .init = a_hash_init_shake128,
    .process = a_hash_process_shake128,
    .done = a_hash_done_shake128,
};

const a_hash_t a_hash_shake256 = {
    .bufsiz = A_SHAKE256_BUFSIZ,
    .outsiz = A_SHAKE256_OUTSIZ,
    .init = a_hash_init_shake256,
    .process = a_hash_process_shake256,
    .done = a_hash_done_shake256,
};

const a_hash_t a_hash_keccak224 = {
    .bufsiz = A_KECCAK224_BUFSIZ,
    .outsiz = A_KECCAK224_OUTSIZ,
    .init = a_hash_init_keccak224,
    .process = a_hash_process_keccak224,
    .done = a_hash_done_keccak224,
};

const a_hash_t a_hash_keccak256 = {
    .bufsiz = A_KECCAK256_BUFSIZ,
    .outsiz = A_KECCAK256_OUTSIZ,
    .init = a_hash_init_keccak256,
    .process = a_hash_process_keccak256,
    .done = a_hash_done_keccak256,
};

const a_hash_t a_hash_keccak384 = {
    .bufsiz = A_KECCAK384_BUFSIZ,
    .outsiz = A_KECCAK384_OUTSIZ,
    .init = a_hash_init_keccak384,
    .process = a_hash_process_keccak384,
    .done = a_hash_done_keccak384,
};

const a_hash_t a_hash_keccak512 = {
    .bufsiz = A_KECCAK512_BUFSIZ,
    .outsiz = A_KECCAK512_OUTSIZ,
    .init = a_hash_init_keccak512,
    .process = a_hash_process_keccak512,
    .done = a_hash_done_keccak512,
};

const a_hash_t a_hash_whirlpool = {
    .bufsiz = A_WHIRLPOOL_BUFSIZ,
    .outsiz = A_WHIRLPOOL_OUTSIZ,
    .init = a_hash_init_whirlpool,
    .process = a_hash_process_whirlpool,
    .done = a_hash_done_whirlpool,
};

const a_hash_t a_hash_blake2s_128 = {
    .bufsiz = A_BLAKE2S_BUFSIZ,
    .outsiz = A_BLAKE2S_128_OUTSIZ,
    .init = a_hash_init_blake2s_128,
    .process = a_hash_process_blake2s_128,
    .done = a_hash_done_blake2s_128,
};

const a_hash_t a_hash_blake2s_160 = {
    .bufsiz = A_BLAKE2S_BUFSIZ,
    .outsiz = A_BLAKE2S_160_OUTSIZ,
    .init = a_hash_init_blake2s_160,
    .process = a_hash_process_blake2s_160,
    .done = a_hash_done_blake2s_160,
};

const a_hash_t a_hash_blake2s_224 = {
    .bufsiz = A_BLAKE2S_BUFSIZ,
    .outsiz = A_BLAKE2S_224_OUTSIZ,
    .init = a_hash_init_blake2s_224,
    .process = a_hash_process_blake2s_224,
    .done = a_hash_done_blake2s_224,
};

const a_hash_t a_hash_blake2s_256 = {
    .bufsiz = A_BLAKE2S_BUFSIZ,
    .outsiz = A_BLAKE2S_256_OUTSIZ,
    .init = a_hash_init_blake2s_256,
    .process = a_hash_process_blake2s_256,
    .done = a_hash_done_blake2s_256,
};

const a_hash_t a_hash_blake2b_160 = {
    .bufsiz = A_BLAKE2B_BUFSIZ,
    .outsiz = A_BLAKE2B_160_OUTSIZ,
    .init = a_hash_init_blake2b_160,
    .process = a_hash_process_blake2b_160,
    .done = a_hash_done_blake2b_160,
};

const a_hash_t a_hash_blake2b_256 = {
    .bufsiz = A_BLAKE2B_BUFSIZ,
    .outsiz = A_BLAKE2B_256_OUTSIZ,
    .init = a_hash_init_blake2b_256,
    .process = a_hash_process_blake2b_256,
    .done = a_hash_done_blake2b_256,
};

const a_hash_t a_hash_blake2b_384 = {
    .bufsiz = A_BLAKE2B_BUFSIZ,
    .outsiz = A_BLAKE2B_384_OUTSIZ,
    .init = a_hash_init_blake2b_384,
    .process = a_hash_process_blake2b_384,
    .done = a_hash_done_blake2b_384,
};

const a_hash_t a_hash_blake2b_512 = {
    .bufsiz = A_BLAKE2B_BUFSIZ,
    .outsiz = A_BLAKE2B_512_OUTSIZ,
    .init = a_hash_init_blake2b_512,
    .process = a_hash_process_blake2b_512,
    .done = a_hash_done_blake2b_512,
};

/* END OF FILE */
