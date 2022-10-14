#ifndef FFI_POLYTRACK7_H
#define FFI_POLYTRACK7_H

#include "lib.h"
#include "a/polytrack.h"

typedef struct
{
    JNIEnv *jenv;
    jobject jobj;
    jfieldID k;
    jobject jk;
    jfieldID t;
    jobject jt;
    jfieldID q;
    jobject jq;
    jfieldID v;
    jobject jv;
    jfieldID a;
    jobject ja;
    jfieldID j;
    jobject jj;
} j_polytrack7_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_polytrack7_s *j_polytrack7_new(JNIEnv *jenv, jobject jobj, j_polytrack7_s *jctx);
jobject j_polytrack7_set(const j_polytrack7_s *jctx, const a_polytrack7_s *ctx);
jobject j_polytrack7_get(const j_polytrack7_s *jctx, a_polytrack7_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FFI_POLYTRACK7_H */
