#ifndef __TF_H__
#define __TF_H__

#include "lib.h"
#include "liba_tf.h"
#include "a/tf.h"

typedef struct
{
    JNIEnv *jenv;
    jobject jobj;
    jfieldID num;
    jobject jnum;
    jfieldID den;
    jobject jden;
    jfieldID u;
    jobject ju;
    jfieldID v;
    jobject jv;
} j_tf_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_tf_s *j_tf_new(JNIEnv *jenv, jobject jobj, j_tf_s *jctx);
jobject j_tf_set(const j_tf_s *jctx, const a_tf_s *ctx);
jobject j_tf_get(const j_tf_s *jctx, a_tf_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __TF_H__ */
