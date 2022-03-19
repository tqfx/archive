/*!
 @file a_object.h
 @brief object macros
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_OBJECT_H__
#define __A_OBJECT_H__

#include <stdlib.h>

#ifndef A_OBJECT_CREATE
#define A_OBJECT_CREATE(type, func, ctor)         \
    type *func(void)                              \
    {                                             \
        type *ctx = (type *)malloc(sizeof(type)); \
        if (ctx)                                  \
        {                                         \
            ctor(ctx);                            \
        }                                         \
        return ctx;                               \
    }
#endif /* A_OBJECT_CREATE */

#ifndef A_OBJECT_CREATE_VA
#define A_OBJECT_CREATE_VA(type, func, ctor, args, ...) \
    type *func(args)                                    \
    {                                                   \
        type *ctx = (type *)malloc(sizeof(type));       \
        if (ctx)                                        \
        {                                               \
            ctor(ctx, __VA_ARGS__);                     \
        }                                               \
        return ctx;                                     \
    }
#endif /* A_OBJECT_CREATE_VA */

#ifndef A_OBJECT_DELETE
#define A_OBJECT_DELETE(type, func, dtor) \
    void func(type *ctx)                  \
    {                                     \
        if (ctx)                          \
        {                                 \
            dtor(ctx);                    \
            free(ctx);                    \
        }                                 \
    }
#endif /* A_OBJECT_DELETE */

#ifndef A_OBJECT_DELETE_VA
#define A_OBJECT_DELETE_VA(type, func, dtor, args, ...) \
    void func(type *ctx, args)                          \
    {                                                   \
        if (ctx)                                        \
        {                                               \
            dtor(ctx, __VA_ARGS__);                     \
            free(ctx);                                  \
        }                                               \
    }
#endif /* A_OBJECT_DELETE_VA */

/* Enddef to prevent recursive inclusion */
#endif /* __A_OBJECT_H__ */
