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
#include "liba_ac.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */
#if defined(_MSC_VER)
#pragma warning(pop)
#endif /* _MSC_VER */

#include "a/version.h"

JNIEXPORT jstring JNICALL Java_liba_ac_version(JNIEnv *env, jobject obj)
{
    return (void)(obj), (*env)->NewStringUTF(env, a_version());
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1major(JNIEnv *env, jobject obj)
{
    return (void)(env), (void)(obj), (jint)a_version_major();
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1minor(JNIEnv *env, jobject obj)
{
    return (void)(env), (void)(obj), (jint)a_version_minor();
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1patch(JNIEnv *env, jobject obj)
{
    return (void)(env), (void)(obj), (jint)a_version_patch();
}

#include "a/math.h"

JNIEXPORT jfloat JNICALL Java_liba_ac_int_1sqrt(JNIEnv *env, jobject obj, jfloat x)
{
    return (void)(env), (void)(obj), a_inv_sqrt(x);
}
