#ifndef __POLYTRACK3_H__
#define __POLYTRACK3_H__

#include "lib.h"
#include "liba_a_polytrack3.h"
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

#endif /* __POLYTRACK3_H__ */
