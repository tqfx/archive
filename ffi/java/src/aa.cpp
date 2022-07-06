#include "a/def.hpp"

#include "liba_aa.h"

JNIEXPORT jstring JNICALL Java_liba_aa_version(JNIEnv *env, jobject)
{
    return (env)->NewStringUTF(a::version());
}
