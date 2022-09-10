#include "lib.h"
#include "a/polytrack.h"

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
