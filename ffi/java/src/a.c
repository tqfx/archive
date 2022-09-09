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
#include "liba_ac_polytrack3.h"
#include "liba_ac_polytrack5.h"
#include "liba_ac_polytrack7.h"
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

#include "a/polytrack.h"

typedef struct
{
    jfieldID t;
    jfieldID q;
    jfieldID v;
    jfieldID k;
    jobject ot;
    jobject oq;
    jobject ov;
    jobject ok;
} j_polytrack3_s;

static void j_polytrack3_new(JNIEnv *env, jobject obj, j_polytrack3_s *dat)
{
    jclass cls = (*env)->FindClass(env, CLASSPATH "polytrack3");
    dat->t = (*env)->GetFieldID(env, cls, "t", "[D");
    dat->ot = (*env)->GetObjectField(env, obj, dat->t);
    dat->q = (*env)->GetFieldID(env, cls, "q", "[D");
    dat->oq = (*env)->GetObjectField(env, obj, dat->q);
    dat->v = (*env)->GetFieldID(env, cls, "v", "[D");
    dat->ov = (*env)->GetObjectField(env, obj, dat->v);
    dat->k = (*env)->GetFieldID(env, cls, "k", "[D");
    dat->ok = (*env)->GetObjectField(env, obj, dat->k);
}

static void j_polytrack3_get(JNIEnv *env, const j_polytrack3_s *dat, a_polytrack3_s *ctx)
{
    (*env)->GetDoubleArrayRegion(env, dat->ot, 0, 2, ctx->t);
    (*env)->GetDoubleArrayRegion(env, dat->oq, 0, 2, ctx->q);
    (*env)->GetDoubleArrayRegion(env, dat->ov, 0, 2, ctx->v);
    (*env)->GetDoubleArrayRegion(env, dat->ok, 0, 4, ctx->k);
}

static void j_polytrack3_set(JNIEnv *env, const j_polytrack3_s *dat, const a_polytrack3_s *ctx)
{
    (*env)->SetDoubleArrayRegion(env, dat->ot, 0, 2, ctx->t);
    (*env)->SetDoubleArrayRegion(env, dat->oq, 0, 2, ctx->q);
    (*env)->SetDoubleArrayRegion(env, dat->ov, 0, 2, ctx->v);
    (*env)->SetDoubleArrayRegion(env, dat->ok, 0, 4, ctx->k);
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024polytrack3_init(JNIEnv *env, jobject obj, jdoubleArray jsource, jdoubleArray jtarget)
{
    jdouble source[3], target[3];
    (*env)->GetDoubleArrayRegion(env, jsource, 0, 3, source);
    (*env)->GetDoubleArrayRegion(env, jtarget, 0, 3, target);
    a_polytrack3_s ctx[1];
    j_polytrack3_s dat[1];
    j_polytrack3_new(env, obj, dat);
    a_polytrack3_init(ctx, source, target);
    j_polytrack3_set(env, dat, ctx);
    return obj;
}

JNIEXPORT jdoubleArray JNICALL Java_liba_ac_00024polytrack3_all(JNIEnv *env, jobject obj, jdouble ts)
{
    jdouble out[3];
    a_polytrack3_s ctx[1];
    j_polytrack3_s dat[1];
    j_polytrack3_new(env, obj, dat);
    j_polytrack3_get(env, dat, ctx);
    a_polytrack3_all(ctx, ts, out);
    jdoubleArray jresult = (*env)->NewDoubleArray(env, 3);
    (*env)->SetDoubleArrayRegion(env, jresult, 0, 3, out);
    return jresult;
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack3_pos(JNIEnv *env, jobject obj, jdouble ts)
{
    a_polytrack3_s ctx[1];
    j_polytrack3_s dat[1];
    j_polytrack3_new(env, obj, dat);
    j_polytrack3_get(env, dat, ctx);
    return a_polytrack3_pos(ctx, ts);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack3_vec(JNIEnv *env, jobject obj, jdouble ts)
{
    a_polytrack3_s ctx[1];
    j_polytrack3_s dat[1];
    j_polytrack3_new(env, obj, dat);
    j_polytrack3_get(env, dat, ctx);
    return a_polytrack3_vec(ctx, ts);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack3_acc(JNIEnv *env, jobject obj, jdouble ts)
{
    a_polytrack3_s ctx[1];
    j_polytrack3_s dat[1];
    j_polytrack3_new(env, obj, dat);
    j_polytrack3_get(env, dat, ctx);
    return a_polytrack3_acc(ctx, ts);
}

typedef struct
{
    jfieldID t;
    jfieldID q;
    jfieldID v;
    jfieldID a;
    jfieldID k;
    jobject ot;
    jobject oq;
    jobject ov;
    jobject oa;
    jobject ok;
} j_polytrack5_s;

static void j_polytrack5_new(JNIEnv *env, jobject obj, j_polytrack5_s *dat)
{
    jclass cls = (*env)->FindClass(env, CLASSPATH "polytrack5");
    dat->t = (*env)->GetFieldID(env, cls, "t", "[D");
    dat->ot = (*env)->GetObjectField(env, obj, dat->t);
    dat->q = (*env)->GetFieldID(env, cls, "q", "[D");
    dat->oq = (*env)->GetObjectField(env, obj, dat->q);
    dat->v = (*env)->GetFieldID(env, cls, "v", "[D");
    dat->ov = (*env)->GetObjectField(env, obj, dat->v);
    dat->a = (*env)->GetFieldID(env, cls, "a", "[D");
    dat->oa = (*env)->GetObjectField(env, obj, dat->a);
    dat->k = (*env)->GetFieldID(env, cls, "k", "[D");
    dat->ok = (*env)->GetObjectField(env, obj, dat->k);
}

static void j_polytrack5_get(JNIEnv *env, const j_polytrack5_s *dat, a_polytrack5_s *ctx)
{
    (*env)->GetDoubleArrayRegion(env, dat->ot, 0, 2, ctx->t);
    (*env)->GetDoubleArrayRegion(env, dat->oq, 0, 2, ctx->q);
    (*env)->GetDoubleArrayRegion(env, dat->ov, 0, 2, ctx->v);
    (*env)->GetDoubleArrayRegion(env, dat->oa, 0, 2, ctx->a);
    (*env)->GetDoubleArrayRegion(env, dat->ok, 0, 6, ctx->k);
}

static void j_polytrack5_set(JNIEnv *env, const j_polytrack5_s *dat, const a_polytrack5_s *ctx)
{
    (*env)->SetDoubleArrayRegion(env, dat->ot, 0, 2, ctx->t);
    (*env)->SetDoubleArrayRegion(env, dat->oq, 0, 2, ctx->q);
    (*env)->SetDoubleArrayRegion(env, dat->ov, 0, 2, ctx->v);
    (*env)->SetDoubleArrayRegion(env, dat->oa, 0, 2, ctx->a);
    (*env)->SetDoubleArrayRegion(env, dat->ok, 0, 6, ctx->k);
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024polytrack5_init(JNIEnv *env, jobject obj, jdoubleArray jsource, jdoubleArray jtarget)
{
    jdouble source[4], target[4];
    (*env)->GetDoubleArrayRegion(env, jsource, 0, 4, source);
    (*env)->GetDoubleArrayRegion(env, jtarget, 0, 4, target);
    a_polytrack5_s ctx[1];
    j_polytrack5_s dat[1];
    j_polytrack5_new(env, obj, dat);
    a_polytrack5_init(ctx, source, target);
    j_polytrack5_set(env, dat, ctx);
    return obj;
}

JNIEXPORT jdoubleArray JNICALL Java_liba_ac_00024polytrack5_all(JNIEnv *env, jobject obj, jdouble ts)
{
    jdouble out[3];
    a_polytrack5_s ctx[1];
    j_polytrack5_s dat[1];
    j_polytrack5_new(env, obj, dat);
    j_polytrack5_get(env, dat, ctx);
    a_polytrack5_all(ctx, ts, out);
    jdoubleArray jresult = (*env)->NewDoubleArray(env, 3);
    (*env)->SetDoubleArrayRegion(env, jresult, 0, 3, out);
    return jresult;
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack5_pos(JNIEnv *env, jobject obj, jdouble ts)
{
    a_polytrack5_s ctx[1];
    j_polytrack5_s dat[1];
    j_polytrack5_new(env, obj, dat);
    j_polytrack5_get(env, dat, ctx);
    return a_polytrack5_pos(ctx, ts);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack5_vec(JNIEnv *env, jobject obj, jdouble ts)
{
    a_polytrack5_s ctx[1];
    j_polytrack5_s dat[1];
    j_polytrack5_new(env, obj, dat);
    j_polytrack5_get(env, dat, ctx);
    return a_polytrack5_vec(ctx, ts);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack5_acc(JNIEnv *env, jobject obj, jdouble ts)
{
    a_polytrack5_s ctx[1];
    j_polytrack5_s dat[1];
    j_polytrack5_new(env, obj, dat);
    j_polytrack5_get(env, dat, ctx);
    return a_polytrack5_acc(ctx, ts);
}

typedef struct
{
    jfieldID t;
    jfieldID q;
    jfieldID v;
    jfieldID a;
    jfieldID j;
    jfieldID k;
    jobject ot;
    jobject oq;
    jobject ov;
    jobject oa;
    jobject oj;
    jobject ok;
} j_polytrack7_s;

static void j_polytrack7_new(JNIEnv *env, jobject obj, j_polytrack7_s *dat)
{
    jclass cls = (*env)->FindClass(env, CLASSPATH "polytrack7");
    dat->t = (*env)->GetFieldID(env, cls, "t", "[D");
    dat->ot = (*env)->GetObjectField(env, obj, dat->t);
    dat->q = (*env)->GetFieldID(env, cls, "q", "[D");
    dat->oq = (*env)->GetObjectField(env, obj, dat->q);
    dat->v = (*env)->GetFieldID(env, cls, "v", "[D");
    dat->ov = (*env)->GetObjectField(env, obj, dat->v);
    dat->a = (*env)->GetFieldID(env, cls, "a", "[D");
    dat->oa = (*env)->GetObjectField(env, obj, dat->a);
    dat->j = (*env)->GetFieldID(env, cls, "j", "[D");
    dat->oj = (*env)->GetObjectField(env, obj, dat->j);
    dat->k = (*env)->GetFieldID(env, cls, "k", "[D");
    dat->ok = (*env)->GetObjectField(env, obj, dat->k);
}

static void j_polytrack7_get(JNIEnv *env, const j_polytrack7_s *dat, a_polytrack7_s *ctx)
{
    (*env)->GetDoubleArrayRegion(env, dat->ot, 0, 2, ctx->t);
    (*env)->GetDoubleArrayRegion(env, dat->oq, 0, 2, ctx->q);
    (*env)->GetDoubleArrayRegion(env, dat->ov, 0, 2, ctx->v);
    (*env)->GetDoubleArrayRegion(env, dat->oa, 0, 2, ctx->a);
    (*env)->GetDoubleArrayRegion(env, dat->oj, 0, 2, ctx->j);
    (*env)->GetDoubleArrayRegion(env, dat->ok, 0, 8, ctx->k);
}

static void j_polytrack7_set(JNIEnv *env, const j_polytrack7_s *dat, const a_polytrack7_s *ctx)
{
    (*env)->SetDoubleArrayRegion(env, dat->ot, 0, 2, ctx->t);
    (*env)->SetDoubleArrayRegion(env, dat->oq, 0, 2, ctx->q);
    (*env)->SetDoubleArrayRegion(env, dat->ov, 0, 2, ctx->v);
    (*env)->SetDoubleArrayRegion(env, dat->oa, 0, 2, ctx->a);
    (*env)->SetDoubleArrayRegion(env, dat->oj, 0, 2, ctx->j);
    (*env)->SetDoubleArrayRegion(env, dat->ok, 0, 8, ctx->k);
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024polytrack7_init(JNIEnv *env, jobject obj, jdoubleArray jsource, jdoubleArray jtarget)
{
    jdouble source[5], target[5];
    (*env)->GetDoubleArrayRegion(env, jsource, 0, 5, source);
    (*env)->GetDoubleArrayRegion(env, jtarget, 0, 5, target);
    a_polytrack7_s ctx[1];
    j_polytrack7_s dat[1];
    j_polytrack7_new(env, obj, dat);
    a_polytrack7_init(ctx, source, target);
    j_polytrack7_set(env, dat, ctx);
    return obj;
}

JNIEXPORT jdoubleArray JNICALL Java_liba_ac_00024polytrack7_all(JNIEnv *env, jobject obj, jdouble ts)
{
    jdouble out[4];
    a_polytrack7_s ctx[1];
    j_polytrack7_s dat[1];
    j_polytrack7_new(env, obj, dat);
    j_polytrack7_get(env, dat, ctx);
    a_polytrack7_all(ctx, ts, out);
    jdoubleArray jresult = (*env)->NewDoubleArray(env, 4);
    (*env)->SetDoubleArrayRegion(env, jresult, 0, 4, out);
    return jresult;
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack7_pos(JNIEnv *env, jobject obj, jdouble ts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s dat[1];
    j_polytrack7_new(env, obj, dat);
    j_polytrack7_get(env, dat, ctx);
    return a_polytrack7_pos(ctx, ts);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack7_vec(JNIEnv *env, jobject obj, jdouble ts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s dat[1];
    j_polytrack7_new(env, obj, dat);
    j_polytrack7_get(env, dat, ctx);
    return a_polytrack7_vec(ctx, ts);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack7_acc(JNIEnv *env, jobject obj, jdouble ts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s dat[1];
    j_polytrack7_new(env, obj, dat);
    j_polytrack7_get(env, dat, ctx);
    return a_polytrack7_acc(ctx, ts);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack7_jer(JNIEnv *env, jobject obj, jdouble ts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s dat[1];
    j_polytrack7_new(env, obj, dat);
    j_polytrack7_get(env, dat, ctx);
    return a_polytrack7_jer(ctx, ts);
}
