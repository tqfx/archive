/*!
 @file hash.c
 @brief hash library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/cksum/hash.h"

#include <assert.h>

#undef A_HASH_INIT
#define A_HASH_INIT(stat, init, func) \
    A_INLINE void func(a_hash_u *ctx) { init(ctx->stat); }
#if defined(__A_MD2_H__)
A_HASH_INIT(md2, a_md2_init, a_hash_init_md2)
#endif /* __A_MD2_H__ */
#if defined(__A_MD4_H__)
A_HASH_INIT(md4, a_md4_init, a_hash_init_md4)
#endif /* __A_MD4_H__ */
#if defined(__A_MD5_H__)
A_HASH_INIT(md5, a_md5_init, a_hash_init_md5)
#endif /* __A_MD5_H__ */
#if defined(__A_RMD128_H__)
A_HASH_INIT(rmd128, a_rmd128_init, a_hash_init_rmd128)
#endif /* __A_RMD128_H__ */
#if defined(__A_RMD160_H__)
A_HASH_INIT(rmd160, a_rmd160_init, a_hash_init_rmd160)
#endif /* __A_RMD160_H__ */
#if defined(__A_RMD256_H__)
A_HASH_INIT(rmd256, a_rmd256_init, a_hash_init_rmd256)
#endif /* __A_RMD256_H__ */
#if defined(__A_RMD320_H__)
A_HASH_INIT(rmd320, a_rmd320_init, a_hash_init_rmd320)
#endif /* __A_RMD320_H__ */
#if defined(__A_SHA1_H__)
A_HASH_INIT(sha1, a_sha1_init, a_hash_init_sha1)
#endif /* __A_SHA1_H__ */
#if defined(__A_SHA256_H__)
A_HASH_INIT(sha256, a_sha256_init, a_hash_init_sha256)
A_HASH_INIT(sha256, a_sha224_init, a_hash_init_sha224)
#endif /* __A_SHA256_H__ */
#if defined(__A_SHA512_H__)
A_HASH_INIT(sha512, a_sha512_init, a_hash_init_sha512)
A_HASH_INIT(sha512, a_sha384_init, a_hash_init_sha384)
A_HASH_INIT(sha512, a_sha512_224_init, a_hash_init_sha512_224)
A_HASH_INIT(sha512, a_sha512_256_init, a_hash_init_sha512_256)
#endif /* __A_SHA512_H__ */
#if defined(__A_SHA3_H__)
A_HASH_INIT(sha3, a_sha3_224_init, a_hash_init_sha3_224)
A_HASH_INIT(sha3, a_sha3_256_init, a_hash_init_sha3_256)
A_HASH_INIT(sha3, a_sha3_384_init, a_hash_init_sha3_384)
A_HASH_INIT(sha3, a_sha3_512_init, a_hash_init_sha3_512)
A_HASH_INIT(sha3, a_shake128_init, a_hash_init_shake128)
A_HASH_INIT(sha3, a_shake256_init, a_hash_init_shake256)
A_HASH_INIT(sha3, a_sha3_224_init, a_hash_init_keccak224)
A_HASH_INIT(sha3, a_sha3_256_init, a_hash_init_keccak256)
A_HASH_INIT(sha3, a_sha3_384_init, a_hash_init_keccak384)
A_HASH_INIT(sha3, a_sha3_512_init, a_hash_init_keccak512)
#endif /* __A_SHA3_H__ */
#if defined(__A_TIGER_H__)
A_HASH_INIT(tiger, a_tiger_init, a_hash_init_siger)
#endif /* __A_TIGER_H__ */
#if defined(__A_BLAKE2S_H__)
A_HASH_INIT(blake2s, a_blake2s_128_init, a_hash_init_blake2s_128)
A_HASH_INIT(blake2s, a_blake2s_160_init, a_hash_init_blake2s_160)
A_HASH_INIT(blake2s, a_blake2s_224_init, a_hash_init_blake2s_224)
A_HASH_INIT(blake2s, a_blake2s_256_init, a_hash_init_blake2s_256)
#endif /* __A_BLAKE2S_H__ */
#if defined(__A_BLAKE2B_H__)
A_HASH_INIT(blake2b, a_blake2b_160_init, a_hash_init_blake2b_160)
A_HASH_INIT(blake2b, a_blake2b_256_init, a_hash_init_blake2b_256)
A_HASH_INIT(blake2b, a_blake2b_384_init, a_hash_init_blake2b_384)
A_HASH_INIT(blake2b, a_blake2b_512_init, a_hash_init_blake2b_512)
#endif /* __A_BLAKE2B_H__ */
#if defined(__A_WHIRL_H__)
A_HASH_INIT(whirlpool, a_whirlpool_init, a_hash_init_whirlpool)
#endif /* __A_WHIRL_H__ */
#undef A_HASH_INIT

#undef A_HASH_PROC
#define A_HASH_PROC(stat, proc, func) \
    A_INLINE int func(a_hash_u *ctx, const void *pdata, size_t nbyte) { return proc(ctx->stat, pdata, nbyte); }
#if defined(__A_MD2_H__)
A_HASH_PROC(md2, a_md2_proc, a_hash_proc_md2)
#endif /* __A_MD2_H__ */
#if defined(__A_MD4_H__)
A_HASH_PROC(md4, a_md4_proc, a_hash_proc_md4)
#endif /* __A_MD4_H__ */
#if defined(__A_MD5_H__)
A_HASH_PROC(md5, a_md5_proc, a_hash_proc_md5)
#endif /* __A_MD5_H__ */
#if defined(__A_RMD128_H__)
A_HASH_PROC(rmd128, a_rmd128_proc, a_hash_proc_rmd128)
#endif /* __A_RMD128_H__ */
#if defined(__A_RMD160_H__)
A_HASH_PROC(rmd160, a_rmd160_proc, a_hash_proc_rmd160)
#endif /* __A_RMD160_H__ */
#if defined(__A_RMD256_H__)
A_HASH_PROC(rmd256, a_rmd256_proc, a_hash_proc_rmd256)
#endif /* __A_RMD256_H__ */
#if defined(__A_RMD320_H__)
A_HASH_PROC(rmd320, a_rmd320_proc, a_hash_proc_rmd320)
#endif /* __A_RMD320_H__ */
#if defined(__A_SHA1_H__)
A_HASH_PROC(sha1, a_sha1_proc, a_hash_proc_sha1)
#endif /* __A_SHA1_H__ */
#if defined(__A_SHA256_H__)
A_HASH_PROC(sha256, a_sha256_proc, a_hash_proc_sha256)
A_HASH_PROC(sha256, a_sha256_proc, a_hash_proc_sha224)
#endif /* __A_SHA256_H__ */
#if defined(__A_SHA512_H__)
A_HASH_PROC(sha512, a_sha512_proc, a_hash_proc_sha512)
A_HASH_PROC(sha512, a_sha512_proc, a_hash_proc_sha384)
A_HASH_PROC(sha512, a_sha512_proc, a_hash_proc_sha512_224)
A_HASH_PROC(sha512, a_sha512_proc, a_hash_proc_sha512_256)
#endif /* __A_SHA512_H__ */
#if defined(__A_SHA3_H__)
A_HASH_PROC(sha3, a_sha3_proc, a_hash_proc_sha3_224)
A_HASH_PROC(sha3, a_sha3_proc, a_hash_proc_sha3_256)
A_HASH_PROC(sha3, a_sha3_proc, a_hash_proc_sha3_384)
A_HASH_PROC(sha3, a_sha3_proc, a_hash_proc_sha3_512)
A_HASH_PROC(sha3, a_sha3_proc, a_hash_proc_shake128)
A_HASH_PROC(sha3, a_sha3_proc, a_hash_proc_shake256)
A_HASH_PROC(sha3, a_sha3_proc, a_hash_proc_keccak224)
A_HASH_PROC(sha3, a_sha3_proc, a_hash_proc_keccak256)
A_HASH_PROC(sha3, a_sha3_proc, a_hash_proc_keccak384)
A_HASH_PROC(sha3, a_sha3_proc, a_hash_proc_keccak512)
#endif /* __A_SHA3_H__ */
#if defined(__A_TIGER_H__)
A_HASH_PROC(tiger, a_tiger_proc, a_hash_proc_siger)
#endif /* __A_TIGER_H__ */
#if defined(__A_BLAKE2S_H__)
A_HASH_PROC(blake2s, a_blake2s_proc, a_hash_proc_blake2s_128)
A_HASH_PROC(blake2s, a_blake2s_proc, a_hash_proc_blake2s_160)
A_HASH_PROC(blake2s, a_blake2s_proc, a_hash_proc_blake2s_224)
A_HASH_PROC(blake2s, a_blake2s_proc, a_hash_proc_blake2s_256)
#endif /* __A_BLAKE2S_H__ */
#if defined(__A_BLAKE2B_H__)
A_HASH_PROC(blake2b, a_blake2b_proc, a_hash_proc_blake2b_160)
A_HASH_PROC(blake2b, a_blake2b_proc, a_hash_proc_blake2b_256)
A_HASH_PROC(blake2b, a_blake2b_proc, a_hash_proc_blake2b_384)
A_HASH_PROC(blake2b, a_blake2b_proc, a_hash_proc_blake2b_512)
#endif /* __A_BLAKE2B_H__ */
#if defined(__A_WHIRL_H__)
A_HASH_PROC(whirlpool, a_whirlpool_proc, a_hash_proc_whirlpool)
#endif /* __A_WHIRL_H__ */
#undef A_HASH_PROC

#undef A_HASH_DONE
#define A_HASH_DONE(stat, done, func) \
    A_INLINE unsigned char *func(a_hash_u *ctx, void *out) { return done(ctx->stat, out); }
#if defined(__A_MD2_H__)
A_HASH_DONE(md2, a_md2_done, a_hash_done_md2)
#endif /* __A_MD2_H__ */
#if defined(__A_MD4_H__)
A_HASH_DONE(md4, a_md4_done, a_hash_done_md4)
#endif /* __A_MD4_H__ */
#if defined(__A_MD5_H__)
A_HASH_DONE(md5, a_md5_done, a_hash_done_md5)
#endif /* __A_MD5_H__ */
#if defined(__A_RMD128_H__)
A_HASH_DONE(rmd128, a_rmd128_done, a_hash_done_rmd128)
#endif /* __A_RMD128_H__ */
#if defined(__A_RMD160_H__)
A_HASH_DONE(rmd160, a_rmd160_done, a_hash_done_rmd160)
#endif /* __A_RMD160_H__ */
#if defined(__A_RMD256_H__)
A_HASH_DONE(rmd256, a_rmd256_done, a_hash_done_rmd256)
#endif /* __A_RMD256_H__ */
#if defined(__A_RMD320_H__)
A_HASH_DONE(rmd320, a_rmd320_done, a_hash_done_rmd320)
#endif /* __A_RMD320_H__ */
#if defined(__A_SHA1_H__)
A_HASH_DONE(sha1, a_sha1_done, a_hash_done_sha1)
#endif /* __A_SHA1_H__ */
#if defined(__A_SHA256_H__)
A_HASH_DONE(sha256, a_sha256_done, a_hash_done_sha256)
A_HASH_DONE(sha256, a_sha256_done, a_hash_done_sha224)
#endif /* __A_SHA256_H__ */
#if defined(__A_SHA512_H__)
A_HASH_DONE(sha512, a_sha512_done, a_hash_done_sha512)
A_HASH_DONE(sha512, a_sha512_done, a_hash_done_sha384)
A_HASH_DONE(sha512, a_sha512_done, a_hash_done_sha512_224)
A_HASH_DONE(sha512, a_sha512_done, a_hash_done_sha512_256)
#endif /* __A_SHA512_H__ */
#if defined(__A_SHA3_H__)
A_HASH_DONE(sha3, a_sha3_done, a_hash_done_sha3_224)
A_HASH_DONE(sha3, a_sha3_done, a_hash_done_sha3_256)
A_HASH_DONE(sha3, a_sha3_done, a_hash_done_sha3_384)
A_HASH_DONE(sha3, a_sha3_done, a_hash_done_sha3_512)
A_HASH_DONE(sha3, a_shake128_done, a_hash_done_shake128)
A_HASH_DONE(sha3, a_shake256_done, a_hash_done_shake256)
A_HASH_DONE(sha3, a_keccak_done, a_hash_done_keccak224)
A_HASH_DONE(sha3, a_keccak_done, a_hash_done_keccak256)
A_HASH_DONE(sha3, a_keccak_done, a_hash_done_keccak384)
A_HASH_DONE(sha3, a_keccak_done, a_hash_done_keccak512)
#endif /* __A_SHA3_H__ */
#if defined(__A_TIGER_H__)
A_HASH_DONE(tiger, a_tiger_done, a_hash_done_siger)
#endif /* __A_TIGER_H__ */
#if defined(__A_BLAKE2S_H__)
A_HASH_DONE(blake2s, a_blake2s_done, a_hash_done_blake2s_128)
A_HASH_DONE(blake2s, a_blake2s_done, a_hash_done_blake2s_160)
A_HASH_DONE(blake2s, a_blake2s_done, a_hash_done_blake2s_224)
A_HASH_DONE(blake2s, a_blake2s_done, a_hash_done_blake2s_256)
#endif /* __A_BLAKE2S_H__ */
#if defined(__A_BLAKE2B_H__)
A_HASH_DONE(blake2b, a_blake2b_done, a_hash_done_blake2b_160)
A_HASH_DONE(blake2b, a_blake2b_done, a_hash_done_blake2b_256)
A_HASH_DONE(blake2b, a_blake2b_done, a_hash_done_blake2b_384)
A_HASH_DONE(blake2b, a_blake2b_done, a_hash_done_blake2b_512)
#endif /* __A_BLAKE2B_H__ */
#if defined(__A_WHIRL_H__)
A_HASH_DONE(whirlpool, a_whirlpool_done, a_hash_done_whirlpool)
#endif /* __A_WHIRL_H__ */
#undef A_HASH_DONE

#if defined(__A_MD2_H__)
const a_hash_s a_hash_md2 = {
    .bufsiz = A_MD2_BUFSIZ,
    .outsiz = A_MD2_OUTSIZ,
    .init = a_hash_init_md2,
    .proc = a_hash_proc_md2,
    .done = a_hash_done_md2,
};
#endif /* __A_MD2_H__ */
#if defined(__A_MD4_H__)
const a_hash_s a_hash_md4 = {
    .bufsiz = A_MD4_BUFSIZ,
    .outsiz = A_MD4_OUTSIZ,
    .init = a_hash_init_md4,
    .proc = a_hash_proc_md4,
    .done = a_hash_done_md4,
};
#endif /* __A_MD4_H__ */
#if defined(__A_MD5_H__)
const a_hash_s a_hash_md5 = {
    .bufsiz = A_MD5_BUFSIZ,
    .outsiz = A_MD5_OUTSIZ,
    .init = a_hash_init_md5,
    .proc = a_hash_proc_md5,
    .done = a_hash_done_md5,
};
#endif /* __A_MD5_H__ */
#if defined(__A_RMD128_H__)
const a_hash_s a_hash_rmd128 = {
    .bufsiz = A_RIPEMD128_BUFSIZ,
    .outsiz = A_RIPEMD128_OUTSIZ,
    .init = a_hash_init_rmd128,
    .proc = a_hash_proc_rmd128,
    .done = a_hash_done_rmd128,
};
#endif /* __A_RMD128_H__ */
#if defined(__A_RMD160_H__)
const a_hash_s a_hash_rmd160 = {
    .bufsiz = A_RIPEMD160_BUFSIZ,
    .outsiz = A_RIPEMD160_OUTSIZ,
    .init = a_hash_init_rmd160,
    .proc = a_hash_proc_rmd160,
    .done = a_hash_done_rmd160,
};
#endif /* __A_RMD160_H__ */
#if defined(__A_RMD256_H__)
const a_hash_s a_hash_rmd256 = {
    .bufsiz = A_RIPEMD256_BUFSIZ,
    .outsiz = A_RIPEMD256_OUTSIZ,
    .init = a_hash_init_rmd256,
    .proc = a_hash_proc_rmd256,
    .done = a_hash_done_rmd256,
};
#endif /* __A_RMD256_H__ */
#if defined(__A_RMD320_H__)
const a_hash_s a_hash_rmd320 = {
    .bufsiz = A_RIPEMD320_BUFSIZ,
    .outsiz = A_RIPEMD320_OUTSIZ,
    .init = a_hash_init_rmd320,
    .proc = a_hash_proc_rmd320,
    .done = a_hash_done_rmd320,
};
#endif /* __A_RMD320_H__ */
#if defined(__A_SHA1_H__)
const a_hash_s a_hash_sha1 = {
    .bufsiz = A_SHA1_BUFSIZ,
    .outsiz = A_SHA1_OUTSIZ,
    .init = a_hash_init_sha1,
    .proc = a_hash_proc_sha1,
    .done = a_hash_done_sha1,
};
#endif /* __A_SHA1_H__ */
#if defined(__A_SHA256_H__)
const a_hash_s a_hash_sha224 = {
    .bufsiz = A_SHA256_BUFSIZ,
    .outsiz = A_SHA224_OUTSIZ,
    .init = a_hash_init_sha224,
    .proc = a_hash_proc_sha224,
    .done = a_hash_done_sha224,
};
const a_hash_s a_hash_sha256 = {
    .bufsiz = A_SHA256_BUFSIZ,
    .outsiz = A_SHA256_OUTSIZ,
    .init = a_hash_init_sha256,
    .proc = a_hash_proc_sha256,
    .done = a_hash_done_sha256,
};
#endif /* __A_SHA256_H__ */
#if defined(__A_SHA512_H__)
const a_hash_s a_hash_sha384 = {
    .bufsiz = A_SHA512_BUFSIZ,
    .outsiz = A_SHA384_OUTSIZ,
    .init = a_hash_init_sha384,
    .proc = a_hash_proc_sha384,
    .done = a_hash_done_sha384,
};
const a_hash_s a_hash_sha512 = {
    .bufsiz = A_SHA512_BUFSIZ,
    .outsiz = A_SHA512_OUTSIZ,
    .init = a_hash_init_sha512,
    .proc = a_hash_proc_sha512,
    .done = a_hash_done_sha512,
};
const a_hash_s a_hash_sha512_224 = {
    .bufsiz = A_SHA512_BUFSIZ,
    .outsiz = A_SHA512_224_OUTSIZ,
    .init = a_hash_init_sha512_224,
    .proc = a_hash_proc_sha512_224,
    .done = a_hash_done_sha512_224,
};
const a_hash_s a_hash_sha512_256 = {
    .bufsiz = A_SHA512_BUFSIZ,
    .outsiz = A_SHA512_256_OUTSIZ,
    .init = a_hash_init_sha512_256,
    .proc = a_hash_proc_sha512_256,
    .done = a_hash_done_sha512_256,
};
#endif /* __A_SHA512_H__ */
#if defined(__A_SHA3_H__)
const a_hash_s a_hash_sha3_224 = {
    .bufsiz = A_SHA3_224_BUFSIZ,
    .outsiz = A_SHA3_224_OUTSIZ,
    .init = a_hash_init_sha3_224,
    .proc = a_hash_proc_sha3_224,
    .done = a_hash_done_sha3_224,
};
const a_hash_s a_hash_sha3_256 = {
    .bufsiz = A_SHA3_256_BUFSIZ,
    .outsiz = A_SHA3_256_OUTSIZ,
    .init = a_hash_init_sha3_256,
    .proc = a_hash_proc_sha3_256,
    .done = a_hash_done_sha3_256,
};
const a_hash_s a_hash_sha3_384 = {
    .bufsiz = A_SHA3_384_BUFSIZ,
    .outsiz = A_SHA3_384_OUTSIZ,
    .init = a_hash_init_sha3_384,
    .proc = a_hash_proc_sha3_384,
    .done = a_hash_done_sha3_384,
};
const a_hash_s a_hash_sha3_512 = {
    .bufsiz = A_SHA3_512_BUFSIZ,
    .outsiz = A_SHA3_512_OUTSIZ,
    .init = a_hash_init_sha3_512,
    .proc = a_hash_proc_sha3_512,
    .done = a_hash_done_sha3_512,
};
const a_hash_s a_hash_shake128 = {
    .bufsiz = A_SHAKE128_BUFSIZ,
    .outsiz = A_SHAKE128_OUTSIZ,
    .init = a_hash_init_shake128,
    .proc = a_hash_proc_shake128,
    .done = a_hash_done_shake128,
};
const a_hash_s a_hash_shake256 = {
    .bufsiz = A_SHAKE256_BUFSIZ,
    .outsiz = A_SHAKE256_OUTSIZ,
    .init = a_hash_init_shake256,
    .proc = a_hash_proc_shake256,
    .done = a_hash_done_shake256,
};
const a_hash_s a_hash_keccak224 = {
    .bufsiz = A_KECCAK224_BUFSIZ,
    .outsiz = A_KECCAK224_OUTSIZ,
    .init = a_hash_init_keccak224,
    .proc = a_hash_proc_keccak224,
    .done = a_hash_done_keccak224,
};
const a_hash_s a_hash_keccak256 = {
    .bufsiz = A_KECCAK256_BUFSIZ,
    .outsiz = A_KECCAK256_OUTSIZ,
    .init = a_hash_init_keccak256,
    .proc = a_hash_proc_keccak256,
    .done = a_hash_done_keccak256,
};
const a_hash_s a_hash_keccak384 = {
    .bufsiz = A_KECCAK384_BUFSIZ,
    .outsiz = A_KECCAK384_OUTSIZ,
    .init = a_hash_init_keccak384,
    .proc = a_hash_proc_keccak384,
    .done = a_hash_done_keccak384,
};
const a_hash_s a_hash_keccak512 = {
    .bufsiz = A_KECCAK512_BUFSIZ,
    .outsiz = A_KECCAK512_OUTSIZ,
    .init = a_hash_init_keccak512,
    .proc = a_hash_proc_keccak512,
    .done = a_hash_done_keccak512,
};
#endif /* __A_SHA3_H__ */
#if defined(__A_TIGER_H__)
const a_hash_s a_hash_siger = {
    .bufsiz = A_TIGER_BUFSIZ,
    .outsiz = A_TIGER_OUTSIZ,
    .init = a_hash_init_siger,
    .proc = a_hash_proc_siger,
    .done = a_hash_done_siger,
};
#endif /* __A_TIGER_H__ */
#if defined(__A_BLAKE2S_H__)
const a_hash_s a_hash_blake2s_128 = {
    .bufsiz = A_BLAKE2S_BUFSIZ,
    .outsiz = A_BLAKE2S_128_OUTSIZ,
    .init = a_hash_init_blake2s_128,
    .proc = a_hash_proc_blake2s_128,
    .done = a_hash_done_blake2s_128,
};
const a_hash_s a_hash_blake2s_160 = {
    .bufsiz = A_BLAKE2S_BUFSIZ,
    .outsiz = A_BLAKE2S_160_OUTSIZ,
    .init = a_hash_init_blake2s_160,
    .proc = a_hash_proc_blake2s_160,
    .done = a_hash_done_blake2s_160,
};
const a_hash_s a_hash_blake2s_224 = {
    .bufsiz = A_BLAKE2S_BUFSIZ,
    .outsiz = A_BLAKE2S_224_OUTSIZ,
    .init = a_hash_init_blake2s_224,
    .proc = a_hash_proc_blake2s_224,
    .done = a_hash_done_blake2s_224,
};
const a_hash_s a_hash_blake2s_256 = {
    .bufsiz = A_BLAKE2S_BUFSIZ,
    .outsiz = A_BLAKE2S_256_OUTSIZ,
    .init = a_hash_init_blake2s_256,
    .proc = a_hash_proc_blake2s_256,
    .done = a_hash_done_blake2s_256,
};
#endif /* __A_BLAKE2S_H__ */
#if defined(__A_BLAKE2B_H__)
const a_hash_s a_hash_blake2b_160 = {
    .bufsiz = A_BLAKE2B_BUFSIZ,
    .outsiz = A_BLAKE2B_160_OUTSIZ,
    .init = a_hash_init_blake2b_160,
    .proc = a_hash_proc_blake2b_160,
    .done = a_hash_done_blake2b_160,
};
const a_hash_s a_hash_blake2b_256 = {
    .bufsiz = A_BLAKE2B_BUFSIZ,
    .outsiz = A_BLAKE2B_256_OUTSIZ,
    .init = a_hash_init_blake2b_256,
    .proc = a_hash_proc_blake2b_256,
    .done = a_hash_done_blake2b_256,
};
const a_hash_s a_hash_blake2b_384 = {
    .bufsiz = A_BLAKE2B_BUFSIZ,
    .outsiz = A_BLAKE2B_384_OUTSIZ,
    .init = a_hash_init_blake2b_384,
    .proc = a_hash_proc_blake2b_384,
    .done = a_hash_done_blake2b_384,
};
const a_hash_s a_hash_blake2b_512 = {
    .bufsiz = A_BLAKE2B_BUFSIZ,
    .outsiz = A_BLAKE2B_512_OUTSIZ,
    .init = a_hash_init_blake2b_512,
    .proc = a_hash_proc_blake2b_512,
    .done = a_hash_done_blake2b_512,
};
#endif /* __A_BLAKE2B_H__ */
#if defined(__A_WHIRL_H__)
const a_hash_s a_hash_whirlpool = {
    .bufsiz = A_WHIRLPOOL_BUFSIZ,
    .outsiz = A_WHIRLPOOL_OUTSIZ,
    .init = a_hash_init_whirlpool,
    .proc = a_hash_proc_whirlpool,
    .done = a_hash_done_whirlpool,
};
#endif /* __A_WHIRL_H__ */
