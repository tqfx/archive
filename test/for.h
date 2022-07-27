/*!
 @file for.h
 @brief Test algorithm library foreach
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_FOR_H__
#define __TEST_FOR_H__

#include "a/a.h"

/*!
 @brief iterate over an array
 @param I index type of this array
 @param i index variable of this array
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param num number of elements in this array
*/
#define a_forboth(I, i, T, it, ptr, num) \
    for (I i = 0; (void)((it) = a_cast(T *, ptr) + i), i != (num); ++i)

/*!
 @brief iterate over an array in reverse
 @param I index type of this array
 @param i index variable of this array
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param num number of elements in this array
*/
#define a_forboth_reverse(I, i, T, it, ptr, num) \
    for (I i = (num); i ? ((void)((it) = a_cast(T *, ptr) + --i), 1) : 0;)

#endif /* __TEST_FOR_H__ */
