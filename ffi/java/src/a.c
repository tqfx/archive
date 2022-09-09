#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#endif /* __clang__ */
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#include "liba_ac.h"
#include "liba_ac_pid.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */
#if defined(_MSC_VER)
#pragma warning(pop)
#endif /* _MSC_VER */

#define CLASSPATH "liba/ac$"

#include "a/version.h"

JNIEXPORT jstring JNICALL Java_liba_ac_version(JNIEnv *env, jclass cls)
{
    return (void)(cls), (*env)->NewStringUTF(env, a_version());
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1major(JNIEnv *env, jclass cls)
{
    return (void)(env), (void)(cls), (jint)a_version_major();
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1minor(JNIEnv *env, jclass cls)
{
    return (void)(env), (void)(cls), (jint)a_version_minor();
}

JNIEXPORT jint JNICALL Java_liba_ac_version_1patch(JNIEnv *env, jclass cls)
{
    return (void)(env), (void)(cls), (jint)a_version_patch();
}

#include "a/math.h"

JNIEXPORT jfloat JNICALL Java_liba_ac_int_1sqrt(JNIEnv *env, jclass cls, jfloat x)
{
    return (void)(env), (void)(cls), a_inv_sqrt(x);
}

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

static void j_pid_new(JNIEnv *env, j_pid_s *jid)
{
    jclass cls = (*env)->FindClass(env, CLASSPATH "pid");
    jid->mode = (*env)->GetFieldID(env, cls, "mode", "I");
    jid->ts = (*env)->GetFieldID(env, cls, "ts", "D");
    jid->kp = (*env)->GetFieldID(env, cls, "kp", "D");
    jid->ki = (*env)->GetFieldID(env, cls, "ki", "D");
    jid->kd = (*env)->GetFieldID(env, cls, "kd", "D");
    jid->out = (*env)->GetFieldID(env, cls, "out", "D");
    jid->outmin = (*env)->GetFieldID(env, cls, "outmin", "D");
    jid->outmax = (*env)->GetFieldID(env, cls, "outmax", "D");
    jid->summax = (*env)->GetFieldID(env, cls, "summax", "D");
    jid->sum = (*env)->GetFieldID(env, cls, "sum", "D");
    jid->ref = (*env)->GetFieldID(env, cls, "ref", "D");
    jid->ec = (*env)->GetFieldID(env, cls, "ec", "D");
    jid->e = (*env)->GetFieldID(env, cls, "e", "D");
}

static void j_pid_get(JNIEnv *env, jobject obj, const j_pid_s *jid, a_pid_s *ctx)
{
    ctx->mode = (a_uint_t)(*env)->GetIntField(env, obj, jid->mode);
    ctx->ts = (*env)->GetDoubleField(env, obj, jid->ts);
    ctx->kp = (*env)->GetDoubleField(env, obj, jid->kp);
    ctx->ki = (*env)->GetDoubleField(env, obj, jid->ki);
    ctx->kd = (*env)->GetDoubleField(env, obj, jid->kd);
    ctx->out = (*env)->GetDoubleField(env, obj, jid->out);
    ctx->outmin = (*env)->GetDoubleField(env, obj, jid->outmin);
    ctx->outmax = (*env)->GetDoubleField(env, obj, jid->outmax);
    ctx->summax = (*env)->GetDoubleField(env, obj, jid->summax);
    ctx->sum = (*env)->GetDoubleField(env, obj, jid->sum);
    ctx->ref = (*env)->GetDoubleField(env, obj, jid->ref);
    ctx->ec = (*env)->GetDoubleField(env, obj, jid->ec);
    ctx->e = (*env)->GetDoubleField(env, obj, jid->e);
}

static void j_pid_set(JNIEnv *env, jobject obj, const j_pid_s *jid, const a_pid_s *ctx)
{
    (*env)->SetIntField(env, obj, jid->mode, (jint)ctx->mode);
    (*env)->SetDoubleField(env, obj, jid->ts, ctx->ts);
    (*env)->SetDoubleField(env, obj, jid->kp, ctx->kp);
    (*env)->SetDoubleField(env, obj, jid->ki, ctx->ki);
    (*env)->SetDoubleField(env, obj, jid->kd, ctx->kd);
    (*env)->SetDoubleField(env, obj, jid->out, ctx->out);
    (*env)->SetDoubleField(env, obj, jid->outmin, ctx->outmin);
    (*env)->SetDoubleField(env, obj, jid->outmax, ctx->outmax);
    (*env)->SetDoubleField(env, obj, jid->summax, ctx->summax);
    (*env)->SetDoubleField(env, obj, jid->sum, ctx->sum);
    (*env)->SetDoubleField(env, obj, jid->ref, ctx->ref);
    (*env)->SetDoubleField(env, obj, jid->ec, ctx->ec);
    (*env)->SetDoubleField(env, obj, jid->e, ctx->e);
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_off(JNIEnv *env, jobject obj)
{
    a_pid_s ctx[1];
    j_pid_s jid[1];
    j_pid_new(env, jid);
    j_pid_get(env, obj, jid, ctx);
    a_pid_off(ctx);
    j_pid_set(env, obj, jid, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_inc(JNIEnv *env, jobject obj)
{
    a_pid_s ctx[1];
    j_pid_s jid[1];
    j_pid_new(env, jid);
    j_pid_get(env, obj, jid, ctx);
    a_pid_inc(ctx);
    j_pid_set(env, obj, jid, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_pos(JNIEnv *env, jobject obj, jdouble max)
{
    a_pid_s ctx[1];
    j_pid_s jid[1];
    j_pid_new(env, jid);
    j_pid_get(env, obj, jid, ctx);
    a_pid_pos(ctx, max);
    j_pid_set(env, obj, jid, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_mode(JNIEnv *env, jobject obj, jint mode)
{
    a_pid_s ctx[1];
    j_pid_s jid[1];
    j_pid_new(env, jid);
    j_pid_get(env, obj, jid, ctx);
    a_pid_mode(ctx, (a_uint_t)mode);
    j_pid_set(env, obj, jid, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_time(JNIEnv *env, jobject obj, jdouble ts)
{
    a_pid_s ctx[1];
    j_pid_s jid[1];
    j_pid_new(env, jid);
    j_pid_get(env, obj, jid, ctx);
    a_pid_time(ctx, ts);
    j_pid_set(env, obj, jid, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_kpid(JNIEnv *env, jobject obj, jdouble kp, jdouble ki, jdouble kd)
{
    a_pid_s ctx[1];
    j_pid_s jid[1];
    j_pid_new(env, jid);
    j_pid_get(env, obj, jid, ctx);
    a_pid_kpid(ctx, kp, ki, kd);
    j_pid_set(env, obj, jid, ctx);
    return obj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_init(JNIEnv *env, jobject obj, jdouble ts, jdouble min, jdouble max)
{
    a_pid_s ctx[1];
    j_pid_s jid[1];
    j_pid_new(env, jid);
    a_pid_init(ctx, ts, min, max);
    j_pid_set(env, obj, jid, ctx);
    return obj;
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024pid_proc(JNIEnv *env, jobject obj, jdouble set, jdouble ref)
{
    a_pid_s ctx[1];
    j_pid_s jid[1];
    j_pid_new(env, jid);
    j_pid_get(env, obj, jid, ctx);
    jdouble jresult = a_pid_proc(ctx, set, ref);
    j_pid_set(env, obj, jid, ctx);
    return (void)(obj), jresult;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024pid_done(JNIEnv *env, jobject obj)
{
    a_pid_s ctx[1];
    j_pid_s jid[1];
    j_pid_new(env, jid);
    j_pid_get(env, obj, jid, ctx);
    a_pid_done(ctx);
    j_pid_set(env, obj, jid, ctx);
    return obj;
}
