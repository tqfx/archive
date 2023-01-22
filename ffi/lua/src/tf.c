/***
 transfer function
 @module liba.tf
*/

#include "tf.h"
#include <stdlib.h>

/***
 destructor for transfer function
 @param ctx transfer function userdata
 @function die
*/
int AMODULE(tf_die)(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        ctx->num = A_REAL_P(l_alloc(L, ctx->num, 0));
        ctx->u = 0;
        ctx->m = 0;
        ctx->den = A_REAL_P(l_alloc(L, ctx->den, 0));
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
int AMODULE(tf_new)(lua_State *L)
{
    if (lua_gettop(L) > 1)
    {
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -1, LUA_TTABLE);
        a_uint_t m = (a_uint_t)lua_rawlen(L, -2);
        a_real_t *num = (a_real_t *)l_alloc(L, NULL, sizeof(a_real_t) * m * 2);
        l_array_num_get(L, -2, num, m);
        a_uint_t n = (a_uint_t)lua_rawlen(L, -1);
        a_real_t *den = (a_real_t *)l_alloc(L, NULL, sizeof(a_real_t) * n * 2);
        l_array_num_get(L, -1, den, n);
        a_tf_s *ctx = (a_tf_s *)lua_newuserdata(L, sizeof(a_tf_s));
        AMODULE2(tf_meta_, L, 1);
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
int AMODULE(tf_init)(lua_State *L)
{
    if (lua_gettop(L) > 2)
    {
        luaL_checktype(L, -3, LUA_TUSERDATA);
        a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, -3);
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -1, LUA_TTABLE);
        a_uint_t m = (a_uint_t)lua_rawlen(L, -2);
        a_real_t *num = (a_real_t *)l_alloc(L, NULL, sizeof(a_real_t) * m * 2);
        l_array_num_get(L, -2, num, m);
        a_uint_t n = (a_uint_t)lua_rawlen(L, -1);
        a_real_t *den = (a_real_t *)l_alloc(L, NULL, sizeof(a_real_t) * n * 2);
        l_array_num_get(L, -1, den, n);
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
int AMODULE(tf_proc)(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t x = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_tf_proc(ctx, x));
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
int AMODULE(tf_zero)(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_tf_zero(ctx);
        return 1;
    }
    return 0;
}

static int AMODULE(tf_set)(lua_State *L)
{
    const char *field = lua_tostring(L, 2);
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, 1);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x001D0A2A: // num
    {
        luaL_checktype(L, 3, LUA_TTABLE);
        a_uint_t m = (a_uint_t)lua_rawlen(L, 3);
        a_real_t *num = (a_real_t *)l_alloc(L, ctx->num, sizeof(a_real_t) * m * 2);
        l_array_num_get(L, 3, num, m);
        a_tf_set_num(ctx, m, num, num + m);
        break;
    }
    case 0x001A63A1: // den
    {
        luaL_checktype(L, 3, LUA_TTABLE);
        a_uint_t n = (a_uint_t)lua_rawlen(L, 3);
        a_real_t *den = (a_real_t *)l_alloc(L, ctx->den, sizeof(a_real_t) * n * 2);
        l_array_num_get(L, 3, den, n);
        a_tf_set_den(ctx, n, den, den + n);
        break;
    }
    case 0xE8859EEB: // __name
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
        break;
    default:
        lua_getmetatable(L, 1);
        lua_pushvalue(L, 3);
        lua_setfield(L, 4, field);
    }
    return 0;
}

static int AMODULE(tf_get)(lua_State *L)
{
    const char *field = lua_tostring(L, 2);
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, 1);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x001D0A2A: // num
        lua_createtable(L, (int)ctx->m, 0);
        l_array_num_set(L, -1, ctx->num, ctx->m);
        break;
    case 0x001A63A1: // den
        lua_createtable(L, (int)ctx->n, 0);
        l_array_num_set(L, -1, ctx->den, ctx->n);
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, AMODULE(tf_new));
        break;
    case 0x001A65A4: // die
        lua_pushcfunction(L, AMODULE(tf_die));
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, AMODULE(tf_init));
        break;
    case 0x0F200702: // proc
        lua_pushcfunction(L, AMODULE(tf_proc));
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, AMODULE(tf_zero));
        break;
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int AMODULE_(_tf, lua_State *L)
{
    const l_func_s funcs[] = {
        {"init", AMODULE(tf_init)},
        {"proc", AMODULE(tf_proc)},
        {"zero", AMODULE(tf_zero)},
        {"new", AMODULE(tf_new)},
        {"die", AMODULE(tf_die)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(funcs) - 1);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 2);
    l_func_set(L, -1, L_SET, AMODULE(setter));
    l_func_set(L, -1, L_NEW, AMODULE(tf_new));
    lua_setmetatable(L, -2);

    const l_func_s metas[] = {
        {L_NEW, AMODULE(tf_proc)},
        {L_DIE, AMODULE(tf_die)},
        {L_SET, AMODULE(tf_set)},
        {L_GET, AMODULE(tf_get)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(metas));
    l_str_set(L, -1, L_NAME, "tf");
    l_func_reg(L, -1, metas);

    AMODULE2(tf_meta_, L, 0);
    AMODULE2(tf_func_, L, 0);

    return AMODULE2(tf_func_, L, 1);
}

int AMODULE(tf_func_)(lua_State *L, int ret)
{
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    void *p = (void *)(intptr_t)AMODULE(tf_func_);
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, p);
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, p);
    return 0;
}

int AMODULE(tf_meta_)(lua_State *L, int ret)
{
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    void *p = (void *)(intptr_t)AMODULE(tf_meta_);
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, p);
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, p);
    return 0;
}
