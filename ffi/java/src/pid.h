#ifndef __PID_H__
#define __PID_H__

#include "lib.h"
#include "liba_ac_pid.h"
#include "a/pid.h"

typedef struct
{
    JNIEnv *jenv;
    jobject jobj;
    jfieldID ts;
    jfieldID kp;
    jfieldID ki;
    jfieldID kd;
    jfieldID out;
    jfieldID outmin;
    jfieldID outmax;
    jfieldID summax;
    jfieldID sum;
    jfieldID ref;
    jfieldID ec;
    jfieldID e;
    jfieldID mode;
    jfieldID num;
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

#endif /* __PID_H__ */
