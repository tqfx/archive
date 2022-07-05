#include "a/def.hpp"

#include "aa.h"

JNIEXPORT jstring JNICALL Java_a_version(JNIEnv *env, jobject obj)
{
    (void)(obj);
    return (env)->NewStringUTF(a::version());
}
