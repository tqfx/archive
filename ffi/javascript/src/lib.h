#ifndef __LIB_H__
#define __LIB_H__
#include "a/a.h"
#include <stdlib.h>
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#if !defined EM_PORT_API
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#if defined(__cplusplus)
#define EM_PORT_API(T) extern "C" T EMSCRIPTEN_KEEPALIVE
#else /* !__cplusplus */
#define EM_PORT_API(T) T EMSCRIPTEN_KEEPALIVE
#endif /* __cplusplus */
#else /* !__EMSCRIPTEN__ */
#if defined(__cplusplus)
#define EM_PORT_API(T) extern "C" T
#else /* !__cplusplus */
#define EM_PORT_API(T) T
#endif /* __cplusplus */
#endif /* __EMSCRIPTEN__ */
#endif /* EM_PORT_API */
#endif /* __LIB_H__ */
