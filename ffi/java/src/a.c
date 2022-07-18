#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#endif /* __clang__ */
#include "liba_a.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#include "a/def.h"

JNIEXPORT jstring JNICALL Java_liba_a_version(JNIEnv *env, jobject obj)
{
    return (void)(obj), (*env)->NewStringUTF(env, a_version());
}
