#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#endif /* __clang__ */
#include "liba_aa.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#include "a/def.hpp"

JNIEXPORT jstring JNICALL Java_liba_aa_version(JNIEnv *env, jobject)
{
    return env->NewStringUTF(a::version());
}
