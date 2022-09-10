#include "lib.h"
#include "a/polytrack.h"

typedef struct
{
    JNIEnv *jenv;
    jobject jobj;
    jfieldID t;
    jobject lt;
    jfieldID q;
    jobject lq;
    jfieldID v;
    jobject lv;
    jfieldID a;
    jobject la;
    jfieldID k;
    jobject lk;
} j_polytrack5_s;

static j_polytrack5_s *j_polytrack5_new(JNIEnv *jenv, jobject jobj, j_polytrack5_s *jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "polytrack5");
    jctx->t = (*jenv)->GetFieldID(jenv, jcls, "t", "[D");
    jctx->lt = (*jenv)->GetObjectField(jenv, jobj, jctx->t);
    jctx->q = (*jenv)->GetFieldID(jenv, jcls, "q", "[D");
    jctx->lq = (*jenv)->GetObjectField(jenv, jobj, jctx->q);
    jctx->v = (*jenv)->GetFieldID(jenv, jcls, "v", "[D");
    jctx->lv = (*jenv)->GetObjectField(jenv, jobj, jctx->v);
    jctx->a = (*jenv)->GetFieldID(jenv, jcls, "a", "[D");
    jctx->la = (*jenv)->GetObjectField(jenv, jobj, jctx->a);
    jctx->k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
    jctx->lk = (*jenv)->GetObjectField(jenv, jobj, jctx->k);
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

static jobject j_polytrack5_get(const j_polytrack5_s *jctx, a_polytrack5_s *ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->lt, 0, ARRAY_SIZE(ctx->t), ctx->t);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->lq, 0, ARRAY_SIZE(ctx->q), ctx->q);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->lv, 0, ARRAY_SIZE(ctx->v), ctx->v);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->la, 0, ARRAY_SIZE(ctx->a), ctx->a);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->lk, 0, ARRAY_SIZE(ctx->k), ctx->k);
    return jctx->jobj;
}

static jobject j_polytrack5_set(const j_polytrack5_s *jctx, const a_polytrack5_s *ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->lt, 0, ARRAY_SIZE(ctx->t), ctx->t);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->lq, 0, ARRAY_SIZE(ctx->q), ctx->q);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->lv, 0, ARRAY_SIZE(ctx->v), ctx->v);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->la, 0, ARRAY_SIZE(ctx->a), ctx->a);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->lk, 0, ARRAY_SIZE(ctx->k), ctx->k);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024polytrack5_init(JNIEnv *jenv, jobject jobj, jdoubleArray jsource, jdoubleArray jtarget)
{
    jdouble source[4], target[4];
    (*jenv)->GetDoubleArrayRegion(jenv, jsource, 0, ARRAY_SIZE(source), source);
    (*jenv)->GetDoubleArrayRegion(jenv, jtarget, 0, ARRAY_SIZE(target), target);
    a_polytrack5_s ctx[1];
    j_polytrack5_s jctx[1];
    j_polytrack5_new(jenv, jobj, jctx);
    a_polytrack5_init(ctx, source, target);
    return j_polytrack5_set(jctx, ctx);
}

JNIEXPORT jdoubleArray JNICALL Java_liba_ac_00024polytrack5_all(JNIEnv *jenv, jobject jobj, jdouble ts)
{
    jdouble out[3];
    a_polytrack5_s ctx[1];
    j_polytrack5_s jctx[1];
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, jctx), ctx);
    a_polytrack5_all(ctx, ts, out);
    jdoubleArray jresult = (*jenv)->NewDoubleArray(jenv, ARRAY_SIZE(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jresult, 0, ARRAY_SIZE(out), out);
    return jresult;
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack5_pos(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack5_s ctx[1];
    j_polytrack5_s jctx[1];
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, jctx), ctx);
    return a_polytrack5_pos(ctx, jts);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack5_vec(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack5_s ctx[1];
    j_polytrack5_s jctx[1];
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, jctx), ctx);
    return a_polytrack5_vec(ctx, jts);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack5_acc(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack5_s ctx[1];
    j_polytrack5_s jctx[1];
    j_polytrack5_get(j_polytrack5_new(jenv, jobj, jctx), ctx);
    return a_polytrack5_acc(ctx, jts);
}
