#include "lib.hpp"
#include "a/version.hpp"

JNIEXPORT jstring JNICALL Java_liba_ax_version(JNIEnv *jenv, jclass)
{
    return jenv->NewStringUTF(a::version());
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
