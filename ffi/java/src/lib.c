#include "lib.h"
#include "a/math.h"
#include "a/version.h"

JNIEXPORT jstring JNICALL Java_liba_ac_version(JNIEnv *env, jclass cls)
{
    return (void)(cls), (*env)->NewStringUTF(env, a_version());
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1major(JNIEnv *env, jclass cls)
{
    return (void)(env), (void)(cls), (jint)a_version_major();
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1minor(JNIEnv *env, jclass cls)
{
    return (void)(env), (void)(cls), (jint)a_version_minor();
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1patch(JNIEnv *env, jclass cls)
{
    return (void)(env), (void)(cls), (jint)a_version_patch();
}

JNIEXPORT jfloat JNICALL Java_liba_ac_int_1sqrt(JNIEnv *env, jclass cls, jfloat x)
{
    return (void)(env), (void)(cls), a_inv_sqrt(x);
}
