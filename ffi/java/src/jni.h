#ifndef FFI_JNI_H
#define FFI_JNI_H
#include "a/a.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#if a_prereq_gnuc(6, 0) || __has_warning("-Wignored-attributes")
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif /* -Wignored-attributes */
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* diagnostic */
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wlanguage-extension-token"
#if __has_warning("-Wreserved-identifier")
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif /* -Wreserved-identifier */
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif /* __clang__ */
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#include <jni.h>
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */
#if defined(_MSC_VER)
#pragma warning(pop)
#endif /* _MSC_VER */
#endif /* FFI_JNI_H */
