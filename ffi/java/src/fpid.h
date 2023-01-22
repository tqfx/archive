#ifndef J_FPID_H
#define J_FPID_H

#include "pid.h"
#include "a/fpid.h"

typedef struct
{
    j_pid_s pid[1];
    JNIEnv *jenv;
    jobject jobj;
    jfieldID mmp;
    jobject jmmp;
    jfieldID mkp;
    jobject jmkp;
    jfieldID mki;
    jobject jmki;
    jfieldID mkd;
    jobject jmkd;
    jfieldID mat;
    jobject jmat;
    jfieldID mms;
    jobject jmms;
    jfieldID idx;
    jobject jidx;
    jfieldID sigma;
    jfieldID alpha;
    jfieldID kp;
    jfieldID ki;
    jfieldID kd;
    jfieldID op;
} j_fpid_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_fpid_s *j_fpid_new(JNIEnv *jenv, jobject jobj, j_fpid_s *jctx);
jobject j_fpid_set(const j_fpid_s *jctx, const a_fpid_s *ctx);
jobject j_fpid_get(const j_fpid_s *jctx, a_fpid_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* J_FPID_H */
