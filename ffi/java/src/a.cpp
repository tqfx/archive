#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#endif /* __clang__ */
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#include "liba_ax.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */
#if defined(_MSC_VER)
#pragma warning(pop)
#endif /* _MSC_VER */

#include "a/version.hpp"

JNIEXPORT jstring JNICALL Java_liba_ax_version(JNIEnv *env, jclass)
{
    return env->NewStringUTF(a::version());
}

JNIEXPORT jint JNICALL Java_liba_ax_version_1major(JNIEnv *, jclass)
{
    return static_cast<jint>(a::version_major());
}

JNIEXPORT jint JNICALL Java_liba_ax_version_1minor(JNIEnv *, jclass)
{
    return static_cast<jint>(a::version_minor());
}

JNIEXPORT jint JNICALL Java_liba_ax_version_1patch(JNIEnv *, jclass)
{
    return static_cast<jint>(a::version_patch());
}
