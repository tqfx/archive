#ifndef J_PID_H
#define J_PID_H

#include "a.h"
#include "a/pid.h"

typedef struct
{
    JNIEnv *jenv;
    jobject jobj;
    jfieldID dt;
    jfieldID kp;
    jfieldID ki;
    jfieldID kd;
    jfieldID outmin;
    jfieldID outmax;
    jfieldID summax;
    jfieldID sum;
    jfieldID out;
    jfieldID fdb;
    jfieldID ec;
    jfieldID e;
    jfieldID num;
    jfieldID reg;
} j_pid_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

j_pid_s *j_pid_new(JNIEnv *jenv, jobject jobj, j_pid_s *jctx);
jobject j_pid_set(const j_pid_s *jctx, const a_pid_s *ctx);
jobject j_pid_get(const j_pid_s *jctx, a_pid_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* J_PID_H */
