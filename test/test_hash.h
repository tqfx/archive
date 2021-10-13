/*!
 @file           test_hash.h
 @brief          hash library test
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __TEST_HASH_H__
#define __TEST_HASH_H__

#include "a_convert.h"

#include <stdio.h>
#include <string.h>

#define __HASH_DIFF(src, dst, size, info)                              \
    do                                                                 \
    {                                                                  \
        if (memcmp(src, dst, size))                                    \
        {                                                              \
            char _bsrc[((size) << 1) + 1];                             \
            char _bdst[((size) << 1) + 1];                             \
            a_digest_upper((const unsigned char *)(src), size, _bsrc); \
            a_digest_upper((const unsigned char *)(dst), size, _bdst); \
            printf("%s %s %s\n", _bsrc, _bdst, info);                  \
        }                                                              \
    } while (0)

/* Enddef to prevent recursive inclusion */
#endif /* __TEST_HASH_H__ */

/* END OF FILE */
