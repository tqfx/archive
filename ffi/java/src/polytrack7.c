#include "polytrack7.h"

j_polytrack7_s *j_polytrack7_new(JNIEnv *jenv, jobject jobj, j_polytrack7_s *jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "polytrack7");
    jctx->t = (*jenv)->GetFieldID(jenv, jcls, "t", "[D");
    jctx->jt = (*jenv)->GetObjectField(jenv, jobj, jctx->t);
    jctx->q = (*jenv)->GetFieldID(jenv, jcls, "q", "[D");
    jctx->jq = (*jenv)->GetObjectField(jenv, jobj, jctx->q);
    jctx->v = (*jenv)->GetFieldID(jenv, jcls, "v", "[D");
    jctx->jv = (*jenv)->GetObjectField(jenv, jobj, jctx->v);
    jctx->a = (*jenv)->GetFieldID(jenv, jcls, "a", "[D");
    jctx->ja = (*jenv)->GetObjectField(jenv, jobj, jctx->a);
    jctx->j = (*jenv)->GetFieldID(jenv, jcls, "j", "[D");
    jctx->jj = (*jenv)->GetObjectField(jenv, jobj, jctx->j);
    jctx->k = (*jenv)->GetFieldID(jenv, jcls, "k", "[D");
    jctx->jk = (*jenv)->GetObjectField(jenv, jobj, jctx->k);
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

jobject j_polytrack7_get(const j_polytrack7_s *jctx, a_polytrack7_s *ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jt, 0, ARRAY_SIZE(ctx->t), ctx->t);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jq, 0, ARRAY_SIZE(ctx->q), ctx->q);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jv, 0, ARRAY_SIZE(ctx->v), ctx->v);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->ja, 0, ARRAY_SIZE(ctx->a), ctx->a);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jj, 0, ARRAY_SIZE(ctx->j), ctx->j);
    (*jenv)->GetDoubleArrayRegion(jenv, jctx->jk, 0, ARRAY_SIZE(ctx->k), ctx->k);
    return jctx->jobj;
}

jobject j_polytrack7_set(const j_polytrack7_s *jctx, const a_polytrack7_s *ctx)
{
    JNIEnv *jenv = jctx->jenv;
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jt, 0, ARRAY_SIZE(ctx->t), ctx->t);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jq, 0, ARRAY_SIZE(ctx->q), ctx->q);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jv, 0, ARRAY_SIZE(ctx->v), ctx->v);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->ja, 0, ARRAY_SIZE(ctx->a), ctx->a);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jj, 0, ARRAY_SIZE(ctx->j), ctx->j);
    (*jenv)->SetDoubleArrayRegion(jenv, jctx->jk, 0, ARRAY_SIZE(ctx->k), ctx->k);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL Java_liba_a_00024polytrack7_init(JNIEnv *jenv, jobject jobj, jdoubleArray jsource, jdoubleArray jtarget)
{
    jdouble source[5], target[5];
    (*jenv)->GetDoubleArrayRegion(jenv, jsource, 0, ARRAY_SIZE(source), source);
    (*jenv)->GetDoubleArrayRegion(jenv, jtarget, 0, ARRAY_SIZE(target), target);
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_new(jenv, jobj, jctx);
    a_polytrack7_init(ctx, source, target);
    return j_polytrack7_set(jctx, ctx);
}

JNIEXPORT jdoubleArray JNICALL Java_liba_a_00024polytrack7_all(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    jdouble out[4];
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, jctx), ctx);
    a_polytrack7_all(ctx, jts, out);
    jdoubleArray jresult = (*jenv)->NewDoubleArray(jenv, ARRAY_SIZE(out));
    (*jenv)->SetDoubleArrayRegion(jenv, jresult, 0, ARRAY_SIZE(out), out);
    return jresult;
}

JNIEXPORT jdouble JNICALL Java_liba_a_00024polytrack7_pos(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, jctx), ctx);
    return a_polytrack7_pos(ctx, jts);
}

JNIEXPORT jdouble JNICALL Java_liba_a_00024polytrack7_vec(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, jctx), ctx);
    return a_polytrack7_vec(ctx, jts);
}

JNIEXPORT jdouble JNICALL Java_liba_a_00024polytrack7_acc(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, jctx), ctx);
    return a_polytrack7_acc(ctx, jts);
}

JNIEXPORT jdouble JNICALL Java_liba_a_00024polytrack7_jer(JNIEnv *jenv, jobject jobj, jdouble jts)
{
    a_polytrack7_s ctx[1];
    j_polytrack7_s jctx[1];
    j_polytrack7_get(j_polytrack7_new(jenv, jobj, jctx), ctx);
    return a_polytrack7_jer(ctx, jts);
}
