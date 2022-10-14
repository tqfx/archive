#include "lib.h"
#include "a/math.h"
#include "a/version.h"
#if defined(__clang__)
#pragma clang diagnostic push
#if __has_warning("-Wreserved-identifier")
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif /* -Wreserved-identifier */
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif /* __clang__ */
#include "liba_a.h"
#if defined(__clang__)
#pragma clang diagnostic pop
#endif /* __clang__ */

JNIEXPORT jstring JNICALL JPACKAGE(a_version)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jcls), (*jenv)->NewStringUTF(jenv, a_version());
}

JNIEXPORT jint JNICALL JPACKAGE(a_version_1major)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_major();
}

JNIEXPORT jint JNICALL JPACKAGE(a_version_1minor)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_minor();
}

JNIEXPORT jint JNICALL JPACKAGE(a_version_1patch)(JNIEnv *jenv, jclass jcls)
{
    return (void)(jenv), (void)(jcls), (jint)a_version_patch();
}

JNIEXPORT jfloat JNICALL JPACKAGE(a_sqrt_1inv)(JNIEnv *jenv, jclass jcls, jfloat jx)
{
    return (void)(jenv), (void)(jcls), a_sqrt_inv(jx);
}
