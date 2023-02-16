#ifndef QJS_A_H
#define QJS_A_H

#include "a/a.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC system_header
#endif /* __GNUC__ */
#include "quickjs.h"

#define countof(x) (sizeof(x) / sizeof(*(x)))

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC JSModuleDef *js_init_module(JSContext *ctx, char const *module_name);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* QJS_A_H */
