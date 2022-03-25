/*!
 @file base.c
 @brief test base library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_base.h"

#include <stdio.h>
#include <string.h>

char buf[BUFSIZ];
char out[BUFSIZ];

const char text[] = "1234567890abcdef";

static void test_base16(void)
{
    size_t siz[1];

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base16_encode(text, strlen(text), buf, siz, A_BASE16_LOWER);
    a_base16_decode(buf, *siz, out, siz);
    if (memcmp(text, out, *siz))
    {
        printf("%zu	%s\n", *siz, out);
    }

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base16_encode(text, strlen(text), buf, siz, A_BASE16_UPPER);
    a_base16_decode(buf, *siz, out, siz);
    if (memcmp(text, out, *siz))
    {
        printf("%zu	%s\n", *siz, out);
    }
}

static void test_base32(void)
{
    size_t siz[1];

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base32_encode(text, strlen(text), buf, siz, A_BASE32_RFC4648);
    a_base32_decode(buf, *siz, out, siz, A_BASE32_RFC4648);
    if (memcmp(text, out, *siz))
    {
        printf("%zu\t%s\n", *siz, out);
    }

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base32_encode(text, strlen(text), buf, siz, A_BASE32_BASE32HEX);
    a_base32_decode(buf, *siz, out, siz, A_BASE32_BASE32HEX);
    if (memcmp(text, out, *siz))
    {
        printf("%zu	%s\n", *siz, out);
    }

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base32_encode(text, strlen(text), buf, siz, A_BASE32_ZBASE32);
    a_base32_decode(buf, *siz, out, siz, A_BASE32_ZBASE32);
    if (memcmp(text, out, *siz))
    {
        printf("%zu	%s\n", *siz, out);
    }

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base32_encode(text, strlen(text), buf, siz, A_BASE32_CROCKFORD);
    a_base32_decode(buf, *siz, out, siz, A_BASE32_CROCKFORD);
    if (memcmp(text, out, *siz))
    {
        printf("%zu	%s\n", *siz, out);
    }
}

static void test_base64(void)
{
    size_t siz[1];

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base64_encode(text, strlen(text), buf, siz);

    a_base64_decode(buf, *siz, out, siz);
    if (memcmp(text, out, *siz))
    {
        printf("%zu	%s\n", *siz, out);
    }

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base64_encode(text, strlen(text), buf, siz);
    a_base64_decode_strict(buf, *siz, out, siz);
    if (memcmp(text, out, *siz))
    {
        printf("%zu	%s\n", *siz, out);
    }

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base64_encode(text, strlen(text), buf, siz);
    a_base64_decode_sane(buf, *siz, out, siz);
    if (memcmp(text, out, *siz))
    {
        printf("%zu	%s\n", *siz, out);
    }

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base64url_encode(text, strlen(text), buf, siz);
    a_base64url_decode(buf, *siz, out, siz);
    if (memcmp(text, out, *siz))
    {
        printf("%zu	%s\n", *siz, out);
    }

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base64url_encode_strict(text, strlen(text), buf, siz);
    a_base64url_decode_strict(buf, *siz, out, siz);
    if (memcmp(text, out, *siz))
    {
        printf("%zu	%s\n", *siz, out);
    }

    *siz = BUFSIZ;
    memset(buf, 0, sizeof(buf));
    memset(out, 0, sizeof(buf));
    a_base64url_encode(text, strlen(text), buf, siz);
    a_base64url_decode_sane(buf, *siz, out, siz);
    if (memcmp(text, out, *siz))
    {
        printf("%zu	%s\n", *siz, out);
    }
}

int main(void)
{
    test_base16();
    test_base32();
    test_base64();

    return 0;
}
