/*!
 @file oop.h
 @brief Object Oriented Programming Macros
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_OOP_H__
#define __A_OOP_H__

#include <stdlib.h>

#define A_OOP_NEW(type, func, ctor)               \
    type *func(void)                              \
    {                                             \
        type *ctx = (type *)malloc(sizeof(type)); \
        if (ctx)                                  \
        {                                         \
            ctor(ctx);                            \
        }                                         \
        return ctx;                               \
    }
#define A_OOP_NEW_VA(type, func, ctor, args, ...) \
    type *func(args)                              \
    {                                             \
        type *ctx = (type *)malloc(sizeof(type)); \
        if (ctx)                                  \
        {                                         \
            ctor(ctx, __VA_ARGS__);               \
        }                                         \
        return ctx;                               \
    }
#define A_OOP_DIE(type, func, dtor) \
    void func(type *ctx)            \
    {                               \
        if (ctx)                    \
        {                           \
            dtor(ctx);              \
            free(ctx);              \
        }                           \
    }
#define A_OOP_DIE_VA(type, func, dtor, args, ...) \
    void func(type *ctx, args)                    \
    {                                             \
        if (ctx)                                  \
        {                                         \
            dtor(ctx, __VA_ARGS__);               \
            free(ctx);                            \
        }                                         \
    }

#define A_OOP_CREATE    A_OOP_NEW
#define A_OOP_DELETE    A_OOP_DIE
#define A_OOP_CREATE_VA A_OOP_NEW_VA
#define A_OOP_DELETE_VA A_OOP_DIE_VA

#endif /* __A_OOP_H__ */
