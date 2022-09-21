#include "lib.h"
#include "liba_ac.h"
#include "a/math.h"
#include "a/version.h"

JNIEXPORT jstring JNICALL Java_liba_ac_version(JNIEnv *jenv, jclass jcls)
{
    return (void)(jcls), (*jenv)->NewStringUTF(jenv, a_version());
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1major(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_major();
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1minor(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_minor();
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1patch(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_patch();
}

JNIEXPORT jfloat JNICALL Java_liba_ac_int_1sqrt(JNIEnv *jenv, jclass jcls, jfloat jx)
{
    return (void)(jenv), (void)(jcls), a_inv_sqrt(jx);
}
