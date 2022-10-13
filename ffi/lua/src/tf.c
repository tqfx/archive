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

/***
 destructor for transfer function
 @param ctx transfer function userdata
 @function die
*/
int tf_die(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        l_dealloc(&ctx->num);
        l_dealloc(&ctx->den);
        ctx->u = 0;
        ctx->m = 0;
        ctx->v = 0;
        ctx->n = 0;
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
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -1, LUA_TTABLE);
        a_uint_t m = (a_uint_t)lua_rawlen(L, -2);
        a_real_t *num = (a_real_t *)l_cmalloc(sizeof(a_real_t) * m * 2);
        arraynum_get(L, -2, num, m);
        a_uint_t n = (a_uint_t)lua_rawlen(L, -1);
        a_real_t *den = (a_real_t *)l_cmalloc(sizeof(a_real_t) * n * 2);
        arraynum_get(L, -1, den, n);
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
        luaL_checktype(L, -3, LUA_TUSERDATA);
        a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, -3);
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -1, LUA_TTABLE);
        a_uint_t m = (a_uint_t)lua_rawlen(L, -2);
        a_real_t *num = (a_real_t *)l_cmalloc(sizeof(a_real_t) * m * 2);
        arraynum_get(L, -2, num, m);
        a_uint_t n = (a_uint_t)lua_rawlen(L, -1);
        a_real_t *den = (a_real_t *)l_cmalloc(sizeof(a_real_t) * n * 2);
        arraynum_get(L, -1, den, n);
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

static int tf_set(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x001D0A2A: // num
        luaL_checktype(L, 3, LUA_TTABLE);
        a_uint_t m = (a_uint_t)lua_rawlen(L, 3);
        a_real_t *num = (a_real_t *)l_realloc(ctx->num, sizeof(a_real_t) * m * 2);
        arraynum_get(L, 3, num, m);
        a_tf_set_num(ctx, m, num, num + m);
        break;
    case 0x001A63A1: // den
        luaL_checktype(L, 3, LUA_TTABLE);
        a_uint_t n = (a_uint_t)lua_rawlen(L, 3);
        a_real_t *den = (a_real_t *)l_realloc(ctx->den, sizeof(a_real_t) * n * 2);
        arraynum_get(L, 3, den, n);
        a_tf_set_den(ctx, n, den, den + n);
        break;
    default:
        return l_field(L, "setter", field, hash);
    }
    return 0;
}

static int tf_get(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x001D0A2A: // num
        lua_createtable(L, (int)ctx->m, 0);
        arraynum_set(L, -1, ctx->num, ctx->m);
        break;
    case 0x001A63A1: // den
        lua_createtable(L, (int)ctx->n, 0);
        arraynum_set(L, -1, ctx->den, ctx->n);
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, tf_new);
        break;
    case 0x001A65A4: // die
        lua_pushcfunction(L, tf_die);
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, tf_init);
        break;
    case 0x0F200702: // proc
        lua_pushcfunction(L, tf_proc);
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, tf_zero);
        break;
    default:
        return l_field(L, "getter", field, hash);
    }
    return 1;
}

int luaopen_liba_tf(lua_State *L)
{
    const SFunc funcs[] = {
        {"init", tf_init},
        {"proc", tf_proc},
        {"zero", tf_zero},
        {"new", tf_new},
        {"die", tf_die},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(funcs) - 1);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, 2);
    set_func(L, -1, LSET, l_setter);
    set_func(L, -1, LNEW, tf_new);
    lua_setmetatable(L, -2);

    const SFunc metas[] = {
        {LNEW, tf_proc},
        {LDIE, tf_die},
        {LSET, tf_set},
        {LGET, tf_get},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(metas) - 1);
    set_funcs(L, -1, metas);

    lua_rawsetp(L, LUA_REGISTRYINDEX, TF_META_);
    lua_rawsetp(L, LUA_REGISTRYINDEX, TF_FUNC_);
    lua_rawgetp(L, LUA_REGISTRYINDEX, TF_FUNC_);

    return 1;
}
