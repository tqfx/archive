#include "lib.h"
#include "a/polytrack.h"

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
