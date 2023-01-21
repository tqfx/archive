/***
 transfer function
 @module liba.tf
*/

#define LUA_LIB
#include "tf.h"
#include <stdlib.h>

/***
 destructor for transfer function
 @param ctx transfer function userdata
 @function die
*/
int l_tf_die(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        void *ud;
        lua_Alloc alloc = lua_getallocf(L, &ud);
        ctx->num = (const a_real_t *)alloc(ud, (void *)(intptr_t)ctx->num, // NOLINT(performance-no-int-to-ptr)
                                           sizeof(a_real_t) * ctx->m * 2, 0);
        ctx->u = 0;
        ctx->m = 0;
        ctx->den = (const a_real_t *)alloc(ud, (void *)(intptr_t)ctx->den, // NOLINT(performance-no-int-to-ptr)
                                           sizeof(a_real_t) * ctx->n * 2, 0);
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
int l_tf_new(lua_State *L)
{
    if (lua_gettop(L) > 1)
    {
        void *ud;
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -1, LUA_TTABLE);
        lua_Alloc alloc = lua_getallocf(L, &ud);
        a_uint_t m = (a_uint_t)lua_rawlen(L, -2);
        a_real_t *num = (a_real_t *)alloc(ud, NULL, LUA_TUSERDATA, sizeof(a_real_t) * m * 2);
        l_array_num_get(L, -2, num, m);
        a_uint_t n = (a_uint_t)lua_rawlen(L, -1);
        a_real_t *den = (a_real_t *)alloc(ud, NULL, LUA_TUSERDATA, sizeof(a_real_t) * n * 2);
        l_array_num_get(L, -1, den, n);
        a_tf_s *ctx = (a_tf_s *)lua_newuserdata(L, sizeof(a_tf_s));
        l_tf_meta_(L);
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
int l_tf_init(lua_State *L)
{
    if (lua_gettop(L) > 2)
    {
        void *ud;
        luaL_checktype(L, -3, LUA_TUSERDATA);
        a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, -3);
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -1, LUA_TTABLE);
        lua_Alloc alloc = lua_getallocf(L, &ud);
        a_uint_t m = (a_uint_t)lua_rawlen(L, -2);
        a_real_t *num = (a_real_t *)alloc(ud, NULL, LUA_TUSERDATA, sizeof(a_real_t) * m * 2);
        l_array_num_get(L, -2, num, m);
        a_uint_t n = (a_uint_t)lua_rawlen(L, -1);
        a_real_t *den = (a_real_t *)alloc(ud, NULL, LUA_TUSERDATA, sizeof(a_real_t) * n * 2);
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
int l_tf_proc(lua_State *L)
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
int l_tf_zero(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_tf_zero(ctx);
        return 1;
    }
    return 0;
}

static int l_tf_set(lua_State *L)
{
    void *ud;
    lua_Alloc alloc = lua_getallocf(L, &ud);
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x001D0A2A: // num
    {
        luaL_checktype(L, 3, LUA_TTABLE);
        a_uint_t m = (a_uint_t)lua_rawlen(L, 3);
        a_real_t *num = (a_real_t *)alloc(ud, (void *)(intptr_t)ctx->num, // NOLINT(performance-no-int-to-ptr)
                                          sizeof(a_real_t) * ctx->m * 2,
                                          sizeof(a_real_t) * m * 2);
        l_array_num_get(L, 3, num, m);
        a_tf_set_num(ctx, m, num, num + m);
        break;
    }
    case 0x001A63A1: // den
    {
        luaL_checktype(L, 3, LUA_TTABLE);
        a_uint_t n = (a_uint_t)lua_rawlen(L, 3);
        a_real_t *den = (a_real_t *)alloc(ud, (void *)(intptr_t)ctx->den, // NOLINT(performance-no-int-to-ptr)
                                          sizeof(a_real_t) * ctx->n * 2,
                                          sizeof(a_real_t) * n * 2);
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

static int l_tf_get(lua_State *L)
{
    a_tf_s *ctx = (a_tf_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
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
        lua_pushcfunction(L, l_tf_new);
        break;
    case 0x001A65A4: // die
        lua_pushcfunction(L, l_tf_die);
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, l_tf_init);
        break;
    case 0x0F200702: // proc
        lua_pushcfunction(L, l_tf_proc);
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, l_tf_zero);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int luaopen_liba_tf(lua_State *L)
{
    const l_func_s funcs[] = {
        {"init", l_tf_init},
        {"proc", l_tf_proc},
        {"zero", l_tf_zero},
        {"new", l_tf_new},
        {"die", l_tf_die},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(funcs) - 1);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 2);
    l_func_set(L, -1, L_SET, l_setter);
    l_func_set(L, -1, L_NEW, l_tf_new);
    lua_setmetatable(L, -2);

    const l_func_s metas[] = {
        {L_NEW, l_tf_proc},
        {L_DIE, l_tf_die},
        {L_SET, l_tf_set},
        {L_GET, l_tf_get},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(metas));
    l_str_set(L, -1, L_NAME, "tf");
    l_func_reg(L, -1, metas);

    lua_rawsetp(L, LUA_REGISTRYINDEX, L_TF_META_); // NOLINT(performance-no-int-to-ptr)
    lua_rawsetp(L, LUA_REGISTRYINDEX, L_TF_FUNC_); // NOLINT(performance-no-int-to-ptr)

    return l_tf_func_(L);
}

int l_tf_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, L_TF_FUNC_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}

int l_tf_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, L_TF_META_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}
