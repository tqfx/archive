/*!
 @file           test_polynomial.c
 @brief          polynomial trajectory test
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-05-22
 @copyright      Copyright (C) 2021 tqfx
 \n \n
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 \n \n
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 \n \n
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include <stdio.h>

#include "ca.h"

int main(void)
{
    float source[5] = {0, 0, 0, 0, 0};
    float target[5] = {10, 10, 0, 0, 0};

    polynomial3_t poly3;
    polynomial3_init(&poly3, source, target);
    for (float i = 0; i < 10; i += 1)
    {
        printf("%g:%g\n", (double)i, (double)polynomial3_vec(&poly3, i));
    }

    polynomial5_t poly5;
    polynomial5_init(&poly5, source, target);
    for (float i = 0; i < 10; i += 1)
    {
        printf("%g:%g\n", (double)i, (double)polynomial5_vec(&poly5, i));
    }

    polynomial7_t poly7;
    polynomial7_init(&poly7, source, target);
    for (float i = 0; i < 10; i += 1)
    {
        printf("%g:%g\n", (double)i, (double)polynomial7_vec(&poly7, i));
    }

    return 0;
}

/* END OF FILE */
