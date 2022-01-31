/*!
 @file a_hmac_util.c
 @brief hmac library utils
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_hmac_util.h"

#include <stdarg.h>

int a_hmac_memory(const a_hash_s *hash,
                  const void *pkey, size_t nkey,
                  const void *pmsg, size_t nmsg,
                  void *out, size_t *siz)
{
    AASSERT(out);
    AASSERT(siz);
    AASSERT(hash);
    AASSERT(!nkey || pkey);
    AASSERT(!nmsg || pmsg);

    if (*siz < hash->outsiz)
    {
        *siz = hash->outsiz;
        return A_HMAC_OVERFLOW;
    }

    a_hmac_s hmac[1];

    if (a_hmac_init(hmac, hash, pkey, nkey) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    if (a_hmac_process(hmac, pmsg, nmsg) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    *siz = a_hmac_done(hmac, out) ? hash->outsiz : 0;

    return A_HMAC_SUCCESS;
}

int a_hmac_mmulti(const a_hash_s *hash,
                  void *out, size_t *siz,
                  const void *pkey, size_t nkey,
                  const void *pmsg, size_t nmsg, ...)
{
    AASSERT(out);
    AASSERT(siz);
    AASSERT(hash);
    AASSERT(!nkey || pkey);
    AASSERT(!nmsg || pmsg);

    if (*siz < hash->outsiz)
    {
        *siz = hash->outsiz;
        return A_HMAC_OVERFLOW;
    }

    va_list arg;
    a_hmac_s hmac[1];
    va_start(arg, nmsg);

    if (a_hmac_init(hmac, hash, pkey, nkey) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    for (;;)
    {
        if (a_hmac_process(hmac, pmsg, nmsg) != A_HMAC_SUCCESS)
        {
            va_end(arg);
            return A_HMAC_FAILURE;
        }
        pmsg = va_arg(arg, const void *);
        if (pmsg == 0)
        {
            va_end(arg);
            break;
        }
        nmsg = va_arg(arg, size_t);
    };
    *siz = a_hmac_done(hmac, out) ? hash->outsiz : 0;

    return A_HMAC_SUCCESS;
}

int a_hmac_filehandle(const a_hash_s *hash,
                      const void *pkey, size_t nkey, FILE *in,
                      void *out, size_t *siz)
{
    AASSERT(in);
    AASSERT(out);
    AASSERT(siz);
    AASSERT(hash);
    AASSERT(!nkey || pkey);

    if (*siz < hash->outsiz)
    {
        *siz = hash->outsiz;
        return A_HMAC_OVERFLOW;
    }

    a_hmac_s hmac[1];

    if (a_hmac_init(hmac, hash, pkey, nkey) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    do
    {
        char buf[BUFSIZ];
        *siz = fread(buf, 1, BUFSIZ, in);
        if (a_hmac_process(hmac, buf, *siz) != A_HMAC_SUCCESS)
        {
            return A_HMAC_FAILURE;
        }
    } while (*siz == BUFSIZ);
    *siz = a_hmac_done(hmac, out) ? hash->outsiz : 0;

    return A_HMAC_SUCCESS;
}

int a_hmac_file(const a_hash_s *hash,
                const void *pkey, size_t nkey, const char *fname,
                void *out, size_t *siz)
{
    AASSERT(out);
    AASSERT(siz);
    AASSERT(hash);
    AASSERT(fname);
    AASSERT(!nkey || pkey);

    if (*siz < hash->outsiz)
    {
        *siz = hash->outsiz;
        return A_HMAC_OVERFLOW;
    }

    FILE *in = fopen(fname, "rb");
    if (in == 0)
    {
        return A_HMAC_NOTFOUND;
    }

    int ret = a_hmac_filehandle(hash, pkey, nkey, in, out, siz);

    if (fclose(in))
    {
        return A_HMAC_FAILURE;
    }

    return ret;
}
