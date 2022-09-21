#include "polytrack5.h"

j_polytrack5_s *j_polytrack5_new(JNIEnv *jenv, jobject jobj, j_polytrack5_s *jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "polytrack5");
    jctx->t = (*jenv)->GetFieldID(jenv, jcls, "t", "[D");
    jctx->jt = (*jenv)->GetObjectField(jenv, jobj, jctx->t);
    jctx->q = (*jenv)->GetFieldID(jenv, jcls, "q", "[D");
    jctx->jq = (*jenv)->GetObjectField(jenv, jobj, jctx->q);
    jctx->v = (*jenv)->GetFieldID(jenv, jcls, "v", "[D");
    jctx->jv = (*jenv)->GetObjectField(jenv, jobj, jctx->v);
    jctx->a = (*jenv)->GetFieldID(jenv, jcls, "a", "[D");
    jctx->ja = (*jenv)->GetObjectField(jenv, jobj, jctx->a);
    jctx->k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
    jctx->jk = (*jenv)->GetObjectField(jenv, jobj, jctx->k);
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

jobject j_polytrack5_get(const j_polytrack5_s *jctx, a_polytrack5_s *ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jt, 0, ARRAY_SIZE(ctx->t), ctx->t);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jq, 0, ARRAY_SIZE(ctx->q), ctx->q);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jv, 0, ARRAY_SIZE(ctx->v), ctx->v);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->ja, 0, ARRAY_SIZE(ctx->a), ctx->a);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jk, 0, ARRAY_SIZE(ctx->k), ctx->k);
    return jctx->jobj;
}

jobject j_polytrack5_set(const j_polytrack5_s *jctx, const a_polytrack5_s *ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jt, 0, ARRAY_SIZE(ctx->t), ctx->t);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jq, 0, ARRAY_SIZE(ctx->q), ctx->q);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jv, 0, ARRAY_SIZE(ctx->v), ctx->v);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->ja, 0, ARRAY_SIZE(ctx->a), ctx->a);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jk, 0, ARRAY_SIZE(ctx->k), ctx->k);
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
