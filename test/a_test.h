/*!
 @file a_test.h
 @brief test header file
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __ATEST__
#define __ATEST__

#include "a_convert.h"

#include <stdio.h>
#include <string.h>

#define __HASH_DIFF(src, dst, size, info)             \
    do                                                \
    {                                                 \
        if (memcmp(src, dst, size))                   \
        {                                             \
            char bsrc_[((size) << 1) + 1];            \
            char bdst_[((size) << 1) + 1];            \
            a_digest_upper(src, size, bsrc_);         \
            a_digest_upper(dst, size, bdst_);         \
            printf("%s %s %s\n", bsrc_, bdst_, info); \
        }                                             \
    } while (0)

/* Enddef to prevent recursive inclusion */
#endif /* __ATEST__ */
