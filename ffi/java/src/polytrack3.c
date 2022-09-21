#include "polytrack3.h"

j_polytrack3_s *j_polytrack3_new(JNIEnv *jenv, jobject jobj, j_polytrack3_s *jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "polytrack3");
    jctx->t = (*jenv)->GetFieldID(jenv, jcls, "t", "[D");
    jctx->jt = (*jenv)->GetObjectField(jenv, jobj, jctx->t);
    jctx->q = (*jenv)->GetFieldID(jenv, jcls, "q", "[D");
    jctx->jq = (*jenv)->GetObjectField(jenv, jobj, jctx->q);
    jctx->v = (*jenv)->GetFieldID(jenv, jcls, "v", "[D");
    jctx->jv = (*jenv)->GetObjectField(jenv, jobj, jctx->v);
    jctx->k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
    jctx->jk = (*jenv)->GetObjectField(jenv, jobj, jctx->k);
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

jobject j_polytrack3_get(const j_polytrack3_s *jctx, a_polytrack3_s *ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jt, 0, ARRAY_SIZE(ctx->t), ctx->t);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jq, 0, ARRAY_SIZE(ctx->q), ctx->q);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jv, 0, ARRAY_SIZE(ctx->v), ctx->v);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jk, 0, ARRAY_SIZE(ctx->k), ctx->k);
    return jctx->jobj;
}

jobject j_polytrack3_set(const j_polytrack3_s *jctx, const a_polytrack3_s *ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jt, 0, ARRAY_SIZE(ctx->t), ctx->t);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jq, 0, ARRAY_SIZE(ctx->q), ctx->q);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jv, 0, ARRAY_SIZE(ctx->v), ctx->v);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jk, 0, ARRAY_SIZE(ctx->k), ctx->k);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL Java_liba_ac_00024polytrack3_init(JNIEnv *jenv, jobject jobj, jdoubleArray jsource, jdoubleArray jtarget)
{
    jdouble source[3], target[3];
    (*jenv)->GetDoubleArrayRegion(jenv, jsource, 0, ARRAY_SIZE(source), source);
    (*jenv)->GetDoubleArrayRegion(jenv, jtarget, 0, ARRAY_SIZE(target), target);
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_new(jenv, jobj, jctx);
    a_polytrack3_init(ctx, source, target);
    return j_polytrack3_set(jctx, ctx);
}

JNIEXPORT jdoubleArray JNICALL Java_liba_ac_00024polytrack3_all(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    jdouble out[3];
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, jctx), ctx);
    a_polytrack3_all(ctx, jts, out);
    jdoubleArray jresult = (*jenv)->NewDoubleArray(jenv, ARRAY_SIZE(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jresult, 0, ARRAY_SIZE(out), out);
    return jresult;
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack3_pos(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, jctx), ctx);
    return a_polytrack3_pos(ctx, jts);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack3_vec(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, jctx), ctx);
    return a_polytrack3_vec(ctx, jts);
}

JNIEXPORT jdouble JNICALL Java_liba_ac_00024polytrack3_acc(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack3_s ctx[1];
    j_polytrack3_s jctx[1];
    j_polytrack3_get(j_polytrack3_new(jenv, jobj, jctx), ctx);
    return a_polytrack3_acc(ctx, jts);
}
