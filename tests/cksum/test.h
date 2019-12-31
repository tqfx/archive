/*!
 @file test.h
 @brief Header file for testing
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __TEST_H__
#define __TEST_H__

#include "a/misc/convert.h"

#include <string.h>
#include <stdio.h>

#define HASH_DIFF(src, dst, size, info)               \
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

#endif /* __TEST_H__ */
