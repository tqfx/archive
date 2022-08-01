#ifndef ____A___H__
#define ____A___H__

#include <stddef.h>

#undef __inline__
#undef __export__
#undef __import__
#undef __hidden__
#undef __public__
#define __inline__ static inline
#if defined(__has_attribute)
#define __export__ __attribute__((visibility("default")))
#define __import__ __attribute__((visibility("default")))
#define __hidden__ __attribute__((visibility("hidden")))
#elif defined(_WIN32) || defined(__CYGWIN__)
#define __export__ __declspec(dllexport)
#define __import__ __declspec(dllimport)
#define __hidden__
#else /* !__has_attribute */
#define __export__
#define __import__
#define __hidden__
#endif /* __has_attribute */
#if defined(A_EXPORTS)
#define __public__ __export__
#elif defined(A_SHARED)
#define __public__ __import__
#else /* !__public__ */
#define __public__
#endif /* __public__ */

#undef __cast__
#undef __null__
#if defined(__cplusplus)
#define __null__ nullptr
#define __cast__(T, ...) static_cast<T>(__VA_ARGS__)
#else /* !__cplusplus */
#define __cast__(T, ...) (T)(__VA_ARGS__)
#define __null__ NULL
#endif /* __cplusplus */

#undef __failure__
#undef __success__
#define __failure__ 1
#define __success__ 0

typedef size_t __T__;

#endif /* ____A___H__ */
