#ifndef __LIB_H__
#define __LIB_H__

#include "jni.h"
#include "a/a.h"

#define ARRAY_SIZE(A) (sizeof(A) / sizeof(*A))

#define CLASSPATH "liba/a$"

A_INTERN jsize GetArrayLengthN(JNIEnv *jenv, jarray jobj, jsize jmax)
{
    jsize length = (*jenv)->GetArrayLength(jenv, jobj);
    return length < jmax ? length : jmax;
}

#endif /* __LIB_H__ */
