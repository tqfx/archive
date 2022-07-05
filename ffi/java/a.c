#include "a/def.h"

#include "a.h"

JNIEXPORT jstring JNICALL Java_a_version(JNIEnv *env, jobject obj)
{
    (void)(obj);
    return (*env)->NewStringUTF(env, a_version());
}
