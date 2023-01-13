#ifndef FFI_POLYTRACK3_H
#define FFI_POLYTRACK3_H

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
} j_polytrack3_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_polytrack3_s *j_polytrack3_new(JNIEnv *jenv, jobject jobj, j_polytrack3_s *jctx);
jobject j_polytrack3_set(const j_polytrack3_s *jctx, const a_polytrack3_s *ctx);
jobject j_polytrack3_get(const j_polytrack3_s *jctx, a_polytrack3_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FFI_POLYTRACK3_H */
