#ifndef FFI_JNI_H
#define FFI_JNI_H
#include "a/a.h"
#if defined(_MSC_VER)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#if a_prereq_gnuc(2, 95) || __has_warning("-Wpadded")
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* -Wpadded */
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif /* -Wreserved-id-macro */
#if __has_warning("-Wreserved-identifier")
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif /* -Wreserved-identifier */
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#endif /* diagnostic */
#if a_prereq_gnuc(6, 1) || __has_warning("-Wignored-attributes")
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif /* -Wignored-attributes */
#if __has_warning("-Wlanguage-extension-token")
#pragma clang diagnostic ignored "-Wlanguage-extension-token"
#endif /* -Wlanguage-extension-token */
#include <jni.h>
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */
#endif /* FFI_JNI_H */
