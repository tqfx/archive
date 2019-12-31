/*!
 @file hmac_util.c
 @brief hmac library utils
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/cksum/hmac_util.h"

#include <assert.h>
#include <stdarg.h>

int a_hmac_memory(const a_hash_s *hash, const void *pkey, size_t nkey, const void *pmsg, size_t nmsg, void *out, size_t *siz)
{
    assert(out);
    assert(siz);
    assert(hash);
    assert(!nkey || pkey);
    assert(!nmsg || pmsg);

    if (*siz < hash->outsiz)
    {
        *siz = hash->outsiz;
        return A_OVERFLOW;
    }

    a_hmac_s hmac[1];

    if (a_hmac_init(hmac, hash, pkey, nkey) != A_SUCCESS)
    {
        return A_FAILURE;
    }
    if (a_hmac_proc(hmac, pmsg, nmsg) != A_SUCCESS)
    {
        return A_FAILURE;
    }
    *siz = a_hmac_done(hmac, out) ? hash->outsiz : 0;

    return A_SUCCESS;
}

int a_hmac_mmulti(const a_hash_s *hash, void *out, size_t *siz, const void *pkey, size_t nkey, const void *pmsg, size_t nmsg, ...)
{
    assert(out);
    assert(siz);
    assert(hash);
    assert(!nkey || pkey);
    assert(!nmsg || pmsg);

    if (*siz < hash->outsiz)
    {
        *siz = hash->outsiz;
        return A_OVERFLOW;
    }

    va_list arg;
    a_hmac_s hmac[1];
    int ret = A_FAILURE;
    va_start(arg, nmsg);

    if (a_hmac_init(hmac, hash, pkey, nkey) != A_SUCCESS)
    {
        goto done;
    }
    for (;;)
    {
        ret = a_hmac_proc(hmac, pmsg, nmsg);
        if (ret != A_SUCCESS)
        {
            goto done;
        }
        pmsg = va_arg(arg, const void *);
        if (pmsg == 0)
        {
            break;
        }
        nmsg = va_arg(arg, size_t);
    }
    *siz = a_hmac_done(hmac, out) ? hash->outsiz : 0;

done:
    va_end(arg);
    return ret;
}

int a_hmac_filehandle(const a_hash_s *hash, const void *pkey, size_t nkey, FILE *in, void *out, size_t *siz)
{
    assert(in);
    assert(out);
    assert(siz);
    assert(hash);
    assert(!nkey || pkey);

    if (*siz < hash->outsiz)
    {
        *siz = hash->outsiz;
        return A_OVERFLOW;
    }

    char buf[BUFSIZ];
    a_hmac_s hmac[1];

    if (a_hmac_init(hmac, hash, pkey, nkey) != A_SUCCESS)
    {
        return A_FAILURE;
    }
    do
    {
        *siz = fread(buf, 1, BUFSIZ, in);
        a_hmac_proc(hmac, buf, *siz);
    } while (*siz == BUFSIZ);
    *siz = a_hmac_done(hmac, out) ? hash->outsiz : 0;

    return A_SUCCESS;
}

int a_hmac_file(const a_hash_s *hash, const void *pkey, size_t nkey, const char *fname, void *out, size_t *siz)
{
    assert(out);
    assert(siz);
    assert(hash);
    assert(fname);
    assert(!nkey || pkey);

    if (*siz < hash->outsiz)
    {
        *siz = hash->outsiz;
        return A_OVERFLOW;
    }

    FILE *in = fopen(fname, "rb");
    if (in == 0)
    {
        return A_NOTFOUND;
    }

    int ret = a_hmac_filehandle(hash, pkey, nkey, in, out, siz);

    if (fclose(in))
    {
        return A_FAILURE;
    }

    return ret;
}
