#include "lib.h"
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
