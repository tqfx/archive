#ifndef FFI_LIB_H
#define FFI_LIB_H

#include "jni.h"

#define ARRAY_SIZE(A) (sizeof(A) / sizeof(*A))
#define JPACKAGE(F) Java_liba_##F
#define CLASSPATH "liba/"

A_INTERN jsize GetArrayLengthN(JNIEnv *jenv, jarray jobj, jsize jmax)
{
    jsize length = (*jenv)->GetArrayLength(jenv, jobj);
    return length < jmax ? length : jmax;
}

#endif /* FFI_LIB_H */
