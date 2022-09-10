#include "lib.h"
#include "a/pid.h"

typedef struct
{
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
} j_pid_s;

static void j_pid_new(JNIEnv *env, j_pid_s *dat)
{
    jclass cls = (*env)->FindClass(env, CLASSPATH "pid");
    dat->mode = (*env)->GetFieldID(env, cls, "mode", "I");
    dat->ts = (*env)->GetFieldID(env, cls, "ts", "D");
    dat->kp = (*env)->GetFieldID(env, cls, "kp", "D");
    dat->ki = (*env)->GetFieldID(env, cls, "ki", "D");
    dat->kd = (*env)->GetFieldID(env, cls, "kd", "D");
    dat->out = (*env)->GetFieldID(env, cls, "out", "D");
    dat->outmin = (*env)->GetFieldID(env, cls, "outmin", "D");
    dat->outmax = (*env)->GetFieldID(env, cls, "outmax", "D");
    dat->summax = (*env)->GetFieldID(env, cls, "summax", "D");
    dat->sum = (*env)->GetFieldID(env, cls, "sum", "D");
    dat->ref = (*env)->GetFieldID(env, cls, "ref", "D");
    dat->ec = (*env)->GetFieldID(env, cls, "ec", "D");
    dat->e = (*env)->GetFieldID(env, cls, "e", "D");
}

static void j_pid_get(JNIEnv *env, jobject obj, const j_pid_s *dat, a_pid_s *ctx)
{
    ctx->mode = (a_uint_t)(*env)->GetIntField(env, obj, dat->mode);
    ctx->ts = (*env)->GetDoubleField(env, obj, dat->ts);
    ctx->kp = (*env)->GetDoubleField(env, obj, dat->kp);
    ctx->ki = (*env)->GetDoubleField(env, obj, dat->ki);
    ctx->kd = (*env)->GetDoubleField(env, obj, dat->kd);
    ctx->out = (*env)->GetDoubleField(env, obj, dat->out);
    ctx->outmin = (*env)->GetDoubleField(env, obj, dat->outmin);
    ctx->outmax = (*env)->GetDoubleField(env, obj, dat->outmax);
    ctx->summax = (*env)->GetDoubleField(env, obj, dat->summax);
    ctx->sum = (*env)->GetDoubleField(env, obj, dat->sum);
    ctx->ref = (*env)->GetDoubleField(env, obj, dat->ref);
    ctx->ec = (*env)->GetDoubleField(env, obj, dat->ec);
    ctx->e = (*env)->GetDoubleField(env, obj, dat->e);
}

static void j_pid_set(JNIEnv *env, jobject obj, const j_pid_s *dat, const a_pid_s *ctx)
{
    (*env)->SetIntField(env, obj, dat->mode, (jint)ctx->mode);
    (*env)->SetDoubleField(env, obj, dat->ts, ctx->ts);
    (*env)->SetDoubleField(env, obj, dat->kp, ctx->kp);
    (*env)->SetDoubleField(env, obj, dat->ki, ctx->ki);
    (*env)->SetDoubleField(env, obj, dat->kd, ctx->kd);
    (*env)->SetDoubleField(env, obj, dat->out, ctx->out);
    (*env)->SetDoubleField(env, obj, dat->outmin, ctx->outmin);
    (*env)->SetDoubleField(env, obj, dat->outmax, ctx->outmax);
    (*env)->SetDoubleField(env, obj, dat->summax, ctx->summax);
    (*env)->SetDoubleField(env, obj, dat->sum, ctx->sum);
    (*env)->SetDoubleField(env, obj, dat->ref, ctx->ref);
    (*env)->SetDoubleField(env, obj, dat->ec, ctx->ec);
    (*env)->SetDoubleField(env, obj, dat->e, ctx->e);
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_off(JNIEnv *env, jobject obj)
{
    a_pid_s ctx[1];
    j_pid_s dat[1];
    j_pid_new(env, dat);
    j_pid_get(env, obj, dat, ctx);
    a_pid_off(ctx);
    j_pid_set(env, obj, dat, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_inc(JNIEnv *env, jobject obj)
{
    a_pid_s ctx[1];
    j_pid_s dat[1];
    j_pid_new(env, dat);
    j_pid_get(env, obj, dat, ctx);
    a_pid_inc(ctx);
    j_pid_set(env, obj, dat, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_pos(JNIEnv *env, jobject obj, jdouble max)
{
    a_pid_s ctx[1];
    j_pid_s dat[1];
    j_pid_new(env, dat);
    j_pid_get(env, obj, dat, ctx);
    a_pid_pos(ctx, max);
    j_pid_set(env, obj, dat, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_mode(JNIEnv *env, jobject obj, jint mode)
{
    a_pid_s ctx[1];
    j_pid_s dat[1];
    j_pid_new(env, dat);
    j_pid_get(env, obj, dat, ctx);
    a_pid_mode(ctx, (a_uint_t)mode);
    j_pid_set(env, obj, dat, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_time(JNIEnv *env, jobject obj, jdouble ts)
{
    a_pid_s ctx[1];
    j_pid_s dat[1];
    j_pid_new(env, dat);
    j_pid_get(env, obj, dat, ctx);
    a_pid_time(ctx, ts);
    j_pid_set(env, obj, dat, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_kpid(JNIEnv *env, jobject obj, jdouble kp, jdouble ki, jdouble kd)
{
    a_pid_s ctx[1];
    j_pid_s dat[1];
    j_pid_new(env, dat);
    j_pid_get(env, obj, dat, ctx);
    a_pid_kpid(ctx, kp, ki, kd);
    j_pid_set(env, obj, dat, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_init(JNIEnv *env, jobject obj, jdouble ts, jdouble min, jdouble max)
{
    a_pid_s ctx[1];
    j_pid_s dat[1];
    j_pid_new(env, dat);
    a_pid_init(ctx, ts, min, max);
    j_pid_set(env, obj, dat, ctx);
    return obj;
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024pid_proc(JNIEnv *env, jobject obj, jdouble set, jdouble ref)
{
    a_pid_s ctx[1];
    j_pid_s dat[1];
    j_pid_new(env, dat);
    j_pid_get(env, obj, dat, ctx);
    jdouble jresult = a_pid_proc(ctx, set, ref);
    j_pid_set(env, obj, dat, ctx);
    return (void)(obj), jresult;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_done(JNIEnv *env, jobject obj)
{
    a_pid_s ctx[1];
    j_pid_s dat[1];
    j_pid_new(env, dat);
    j_pid_get(env, obj, dat, ctx);
    a_pid_done(ctx);
    j_pid_set(env, obj, dat, ctx);
    return obj;
}
