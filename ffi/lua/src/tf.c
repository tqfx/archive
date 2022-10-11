/***
 transfer function
 @module liba.tf
*/

#include "tf.h"

int tf_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, TF_META_);
    return 1;
}

int tf_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, TF_FUNC_);
    return 1;
}

int tf_from_(lua_State *L, int idx, a_tf_s *ctx)
{
    idx = idx < 0 ? idx - 1 : idx;
    lua_pushstring(L, "num");
    lua_rawget(L, idx);
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        ctx->m = (a_uint_t)lua_rawlen(L, -1);
        a_real_t *num = (a_real_t *)l_malloc(L, sizeof(a_real_t) * ctx->m * 2);
        arraynum_get(L, -1, num, ctx->m);
        ctx->u = num + ctx->m;
        ctx->num = num;
    }
    lua_pop(L, 1);
    lua_pushstring(L, "den");
    lua_rawget(L, idx);
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        ctx->n = (a_uint_t)lua_rawlen(L, -1);
        a_real_t *den = (a_real_t *)l_malloc(L, sizeof(a_real_t) * ctx->n * 2);
        arraynum_get(L, -1, den, ctx->n);
        ctx->v = den + ctx->n;
        ctx->den = den;
    }
    lua_pop(L, 1);
    return 0;
}

int tf_into_(lua_State *L, a_tf_s *ctx)
{
    SFnums tf[] = {
        {"num", ctx->num, ctx->m},
        {"den", ctx->den, ctx->n},
        {NULL, NULL, 0},
    };
    lua_createtable(L, 0, Larray(tf) - 1);
    arraynum_sets(L, -1, tf);
    return 1;
}

/***
 convert transfer function userdata from table
 @param[opt] ctx transfer function userdata
 @tparam table tab transfer function table
 @treturn tf transfer function userdata
 @function from
*/
int tf_from(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        lua_pushvalue(L, -2);
        lua_remove(L, -3);
    }
    else
    {
        ctx = (a_tf_s *)lua_newuserdata(L, sizeof(a_tf_s));
    }
    tf_meta_(L);
    lua_setmetatable(L, -2);
    tf_from_(L, -2, ctx);
    return 1;
}

/***
 convert transfer function userdata into table
 @param ctx transfer function userdata
 @treturn table transfer function table
 @function into
*/
int tf_into(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        return tf_into_(L, ctx);
    }
    return 0;
}

/***
 constructor for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn tf transfer function userdata
 @function new
*/
int tf_new(lua_State *L)
{
    if (lua_gettop(L) > 1)
    {
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        a_uint_t m = (a_uint_t)lua_rawlen(L, -1);
        a_real_t *num = (a_real_t *)l_malloc(L, sizeof(a_real_t) * m * 2);
        a_uint_t n = (a_uint_t)lua_rawlen(L, -2);
        a_real_t *den = (a_real_t *)l_malloc(L, sizeof(a_real_t) * n * 2);
        arraynum_get(L, -1, num, m);
        arraynum_get(L, -2, den, n);
        a_tf_s *ctx = (a_tf_s *)lua_newuserdata(L, sizeof(a_tf_s));
        tf_meta_(L);
        lua_setmetatable(L, -2);
        a_tf_init(ctx, m, num, num + m, n, den, den + n);
        return 1;
    }
    return 0;
}

/***
 initialize function for transfer function
 @param ctx transfer function userdata
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn tf transfer function userdata
 @function init
*/
int tf_init(lua_State *L)
{
    if (lua_gettop(L) > 2)
    {
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -3, LUA_TUSERDATA);
        a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, -3);
        a_uint_t m = (a_uint_t)lua_rawlen(L, -1);
        a_real_t *num = (a_real_t *)l_malloc(L, sizeof(a_real_t) * m * 2);
        a_uint_t n = (a_uint_t)lua_rawlen(L, -2);
        a_real_t *den = (a_real_t *)l_malloc(L, sizeof(a_real_t) * n * 2);
        arraynum_get(L, -1, num, m);
        arraynum_get(L, -2, den, n);
        a_tf_init(ctx, m, num, num + m, n, den, den + n);
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

/***
 process function for transfer function
 @param ctx transfer function userdata
 @tparam number x controller output
 @treturn number feedback
 @function proc
*/
int tf_proc(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t x = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_tf_proc(ctx, x));
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

/***
 zero function for transfer function
 @param ctx transfer function userdata
 @treturn tf transfer function userdata
 @function zero
*/
int tf_zero(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_tf_zero(ctx);
        return 1;
    }
    return 0;
}

static int tf_newindex(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, 1);
    switch (l_hashs(lua_tostring(L, 2)))
    {
    case 0x001D0A2A: /* num */
    {
        luaL_checktype(L, 3, LUA_TTABLE);
        a_uint_t m = (a_uint_t)lua_rawlen(L, 3);
        a_real_t *num = (a_real_t *)l_malloc(L, sizeof(a_real_t) * m * 2);
        arraynum_get(L, 3, num, m);
        ctx->u = num + m;
        ctx->num = num;
        ctx->m = m;
    }
    break;
    case 0x001A63A1: /* den */
    {
        luaL_checktype(L, 3, LUA_TTABLE);
        a_uint_t n = (a_uint_t)lua_rawlen(L, 3);
        a_real_t *den = (a_real_t *)l_malloc(L, sizeof(a_real_t) * n * 2);
        arraynum_get(L, 3, den, n);
        ctx->v = den + n;
        ctx->den = den;
        ctx->n = n;
    }
    break;
    default:
        break;
    }
    return 0;
}

int luaopen_liba_tf(lua_State *L)
{
    const SFunc funcs[] = {
        {"from", tf_from},
        {"into", tf_into},
        {"init", tf_init},
        {"proc", tf_proc},
        {"zero", tf_zero},
        {"new", tf_new},
        {NULL, NULL},
    };
    const SFunc metas[] = {
        {"__call", tf_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(funcs) - 1);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, Larray(metas) - 1);
    set_funcs(L, -1, metas);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, 3);
    set_func(L, -1, "__newindex", tf_newindex);
    set_func(L, -1, "__call", tf_proc);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -3);
    lua_rawset(L, -3);

    lua_rawsetp(L, LUA_REGISTRYINDEX, TF_META_);
    lua_rawsetp(L, LUA_REGISTRYINDEX, TF_FUNC_);
    lua_rawgetp(L, LUA_REGISTRYINDEX, TF_FUNC_);

    return 1;
}
