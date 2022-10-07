#ifndef __POLYTRACK5_H__
#define __POLYTRACK5_H__

#include "lib.h"
#include "liba_a_polytrack5.h"
#include "a/polytrack.h"

typedef struct
{
    JNIEnv *jenv;
    jobject jobj;
    jfieldID t;
    jobject jt;
    jfieldID q;
    jobject jq;
    jfieldID v;
    jobject jv;
    jfieldID a;
    jobject ja;
    jfieldID k;
    jobject jk;
} j_polytrack5_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_polytrack5_s *j_polytrack5_new(JNIEnv *jenv, jobject jobj, j_polytrack5_s *jctx);
jobject j_polytrack5_set(const j_polytrack5_s *jctx, const a_polytrack5_s *ctx);
jobject j_polytrack5_get(const j_polytrack5_s *jctx, a_polytrack5_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __POLYTRACK5_H__ */
