#include "lib.h"
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

static j_pid_s *j_pid_new(JNIEnv *jenv, jobject jobj, j_pid_s *jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "pid");
    jctx->num = (*jenv)->GetFieldID(jenv, jcls, "num", "I");
    jctx->mode = (*jenv)->GetFieldID(jenv, jcls, "mode", "I");
    jctx->ts = (*jenv)->GetFieldID(jenv, jcls, "ts", "D");
    jctx->kp = (*jenv)->GetFieldID(jenv, jcls, "kp", "D");
    jctx->ki = (*jenv)->GetFieldID(jenv, jcls, "ki", "D");
    jctx->kd = (*jenv)->GetFieldID(jenv, jcls, "kd", "D");
    jctx->out = (*jenv)->GetFieldID(jenv, jcls, "out", "D");
    jctx->outmin = (*jenv)->GetFieldID(jenv, jcls, "outmin", "D");
    jctx->outmax = (*jenv)->GetFieldID(jenv, jcls, "outmax", "D");
    jctx->summax = (*jenv)->GetFieldID(jenv, jcls, "summax", "D");
    jctx->sum = (*jenv)->GetFieldID(jenv, jcls, "sum", "D");
    jctx->ref = (*jenv)->GetFieldID(jenv, jcls, "ref", "D");
    jctx->ec = (*jenv)->GetFieldID(jenv, jcls, "ec", "D");
    jctx->e = (*jenv)->GetFieldID(jenv, jcls, "e", "D");
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

static jobject j_pid_get(const j_pid_s *jctx, a_pid_s *ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    ctx->num = (a_uint_t)(*jenv)->GetIntField(jenv, jobj, jctx->num);
    ctx->mode = (a_uint_t)(*jenv)->GetIntField(jenv, jobj, jctx->mode);
    ctx->ts = (*jenv)->GetDoubleField(jenv, jobj, jctx->ts);
    ctx->kp = (*jenv)->GetDoubleField(jenv, jobj, jctx->kp);
    ctx->ki = (*jenv)->GetDoubleField(jenv, jobj, jctx->ki);
    ctx->kd = (*jenv)->GetDoubleField(jenv, jobj, jctx->kd);
    ctx->out = (*jenv)->GetDoubleField(jenv, jobj, jctx->out);
    ctx->outmin = (*jenv)->GetDoubleField(jenv, jobj, jctx->outmin);
    ctx->outmax = (*jenv)->GetDoubleField(jenv, jobj, jctx->outmax);
    ctx->summax = (*jenv)->GetDoubleField(jenv, jobj, jctx->summax);
    ctx->sum = (*jenv)->GetDoubleField(jenv, jobj, jctx->sum);
    ctx->ref = (*jenv)->GetDoubleField(jenv, jobj, jctx->ref);
    ctx->ec = (*jenv)->GetDoubleField(jenv, jobj, jctx->ec);
    ctx->e = (*jenv)->GetDoubleField(jenv, jobj, jctx->e);
    return jctx->jobj;
}

static jobject j_pid_set(const j_pid_s *jctx, const a_pid_s *ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    (*jenv)->SetIntField(jenv, jobj, jctx->num, (jint)ctx->num);
    (*jenv)->SetIntField(jenv, jobj, jctx->mode, (jint)ctx->mode);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->ts, ctx->ts);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->kp, ctx->kp);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->ki, ctx->ki);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->kd, ctx->kd);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->out, ctx->out);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->outmin, ctx->outmin);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->outmax, ctx->outmax);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->summax, ctx->summax);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->sum, ctx->sum);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->ref, ctx->ref);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->ec, ctx->ec);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->e, ctx->e);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_off(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx[1];
    j_pid_s jctx[1];
    j_pid_get(j_pid_new(jenv, jobj, jctx), ctx);
    a_pid_off(ctx);
    return j_pid_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_inc(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx[1];
    j_pid_s jctx[1];
    j_pid_get(j_pid_new(jenv, jobj, jctx), ctx);
    a_pid_inc(ctx);
    return j_pid_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_pos(JNIEnv *jenv, jobject jobj, jdouble jmax)
{
    a_pid_s ctx[1];
    j_pid_s jctx[1];
    j_pid_get(j_pid_new(jenv, jobj, jctx), ctx);
    a_pid_pos(ctx, jmax);
    return j_pid_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_mode(JNIEnv *jenv, jobject jobj, jint jmode)
{
    a_pid_s ctx[1];
    j_pid_s jctx[1];
    j_pid_get(j_pid_new(jenv, jobj, jctx), ctx);
    a_pid_mode(ctx, (a_uint_t)jmode);
    return j_pid_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_time(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_pid_s ctx[1];
    j_pid_s jctx[1];
    j_pid_get(j_pid_new(jenv, jobj, jctx), ctx);
    a_pid_time(ctx, jts);
    return j_pid_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_kpid(JNIEnv *jenv, jobject jobj, jdouble jkp, jdouble jki, jdouble jkd)
{
    a_pid_s ctx[1];
    j_pid_s jctx[1];
    j_pid_get(j_pid_new(jenv, jobj, jctx), ctx);
    a_pid_kpid(ctx, jkp, jki, jkd);
    return j_pid_set(jctx, ctx);
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_init(JNIEnv *jenv, jobject jobj, jdouble jts, jdouble jmin, jdouble jmax)
{
    a_pid_s ctx[1];
    j_pid_s jctx[1];
    j_pid_new(jenv, jobj, jctx);
    a_pid_init(ctx, jts, jmin, jmax);
    return j_pid_set(jctx, ctx);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024pid_proc(JNIEnv *jenv, jobject jobj, jdouble jset, jdouble jref)
{
    a_pid_s ctx[1];
    j_pid_s jctx[1];
    j_pid_get(j_pid_new(jenv, jobj, jctx), ctx);
    jdouble jresult = a_pid_proc(ctx, jset, jref);
    j_pid_set(jctx, ctx);
    return (void)(jobj), jresult;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_done(JNIEnv *jenv, jobject jobj)
{
    a_pid_s ctx[1];
    j_pid_s jctx[1];
    j_pid_get(j_pid_new(jenv, jobj, jctx), ctx);
    a_pid_done(ctx);
    return j_pid_set(jctx, ctx);
}
