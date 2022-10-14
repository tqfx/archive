/***
 cubic polynomial trajectory
 @module liba.polytrack3
*/

#include "polytrack3.h"

static int polytrack3_init_(lua_State *L, a_polytrack3_s *ctx)
{
    a_real_t t0 = 0, q0 = 0, v0 = 0;
    a_real_t t1 = 0, q1 = 0, v1 = 0;
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 6:
    {
        v1 = luaL_checknumber(L, 6);
        A_FALLTHROUGH;
    }
    case 5:
    {
        v0 = luaL_checknumber(L, 5);
        A_FALLTHROUGH;
    }
    case 4:
    {
        q1 = luaL_checknumber(L, 4);
        q0 = luaL_checknumber(L, 3);
        t1 = luaL_checknumber(L, 2);
        t0 = luaL_checknumber(L, 1);
    }
    break;
    default:
        break;
    }
    a_polytrack3_init(ctx, t0, t1, q0, q1, v0, v1);
    return 1;
}

/***
 constructor for cubic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn polytrack3 cubic polynomial trajectory userdata
 @function new
*/
int polytrack3_new(lua_State *L)
{
    int top = lua_gettop(L);
    int type = lua_type(L, -1);
    if (top > 3 && type == LUA_TNUMBER)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        a_polytrack3_s *ctx = (a_polytrack3_s *)lua_newuserdata(L, sizeof(a_polytrack3_s));
        polytrack3_meta_(L);
        lua_setmetatable(L, -2);
        return polytrack3_init_(L, ctx);
    }
    if (top > 1 && type == LUA_TTABLE)
    {
        a_real_t target[3] = {0};
        a_real_t source[3] = {0};
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        arraynum_get(L, -1, target, Larray(target));
        arraynum_get(L, -2, source, Larray(source));
        a_polytrack3_s *ctx = (a_polytrack3_s *)lua_newuserdata(L, sizeof(a_polytrack3_s));
        polytrack3_meta_(L);
        lua_setmetatable(L, -2);
        a_polytrack3_init2(ctx, source, target);
        return 1;
    }
    return 0;
}

/***
 initialize function for cubic polynomial trajectory
 @param ctx cubic polynomial trajectory userdata
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn polytrack3 cubic polynomial trajectory userdata
 @function init
*/
int polytrack3_init(lua_State *L)
{
    int top = lua_gettop(L);
    int type = lua_type(L, -1);
    if (top > 4 && type == LUA_TNUMBER)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        lua_remove(L, 1);
        return polytrack3_init_(L, ctx);
    }
    if (top > 2 && type == LUA_TTABLE)
    {
        a_real_t target[3] = {0};
        a_real_t source[3] = {0};
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -3, LUA_TUSERDATA);
        a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -3);
        arraynum_get(L, -1, target, Larray(target));
        arraynum_get(L, -2, source, Larray(source));
        a_polytrack3_init2(ctx, source, target);
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

/***
 generation function for cubic polynomial trajectory
 @param ctx cubic polynomial trajectory userdata
 @treturn polytrack3 cubic polynomial trajectory userdata
 @function gen
*/
int polytrack3_gen(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_polytrack3_gen(ctx);
        return 1;
    }
    return 0;
}

/***
 process function for cubic polynomial trajectory
 @param ctx cubic polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn table {position,velocity,acceleration}
 @function out
*/
int polytrack3_out(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t out[3];
        a_real_t ts = luaL_checknumber(L, -1);
        a_polytrack3_out(ctx, ts, out);
        lua_createtable(L, Larray(out), 0);
        arraynum_set(L, -1, out, Larray(out));
        return 1;
    }
    return 0;
}

/***
 process function for cubic polynomial trajectory position
 @param ctx cubic polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn number position output
 @function pos
*/
int polytrack3_pos(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack3_pos(ctx, ts));
        return 1;
    }
    return 0;
}

/***
 process function for cubic polynomial trajectory velocity
 @param ctx cubic polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn number velocity output
 @function vec
*/
int polytrack3_vec(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack3_vec(ctx, ts));
        return 1;
    }
    return 0;
}

/***
 process function for cubic polynomial trajectory acceleration
 @param ctx cubic polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn number acceleration output
 @function acc
*/
int polytrack3_acc(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack3_acc(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack3_set(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x00000074: // t
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, Larray(ctx->t), 0);
        arraynum_get(L, 3, ctx->t, Larray(ctx->t));
        break;
    case 0x00000071: // q
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, Larray(ctx->q), 0);
        arraynum_get(L, 3, ctx->q, Larray(ctx->q));
        break;
    case 0x00000076: // v
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, Larray(ctx->v), 0);
        arraynum_get(L, 3, ctx->v, Larray(ctx->v));
        break;
    case 0x00003B8C: // t0
        ctx->t[0] = luaL_checknumber(L, 3);
        break;
    case 0x00003A03: // q0
        ctx->q[0] = luaL_checknumber(L, 3);
        break;
    case 0x00003C92: // v0
        ctx->v[0] = luaL_checknumber(L, 3);
        break;
    case 0x00003B8D: // t1
        ctx->t[1] = luaL_checknumber(L, 3);
        break;
    case 0x00003A04: // q1
        ctx->q[1] = luaL_checknumber(L, 3);
        break;
    case 0x00003C93: // v1
        ctx->v[1] = luaL_checknumber(L, 3);
        break;
    default:
        return l_field(L, "setter", field, hash);
    }
    a_polytrack3_gen(ctx);
    return 0;
}

static int polytrack3_get(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x0000006B: // k
        lua_createtable(L, Larray(ctx->k), 0);
        arraynum_set(L, -1, ctx->k, Larray(ctx->k));
        break;
    case 0x00000074: // t
        lua_createtable(L, Larray(ctx->t), 0);
        arraynum_set(L, -1, ctx->t, Larray(ctx->t));
        break;
    case 0x00000071: // q
        lua_createtable(L, Larray(ctx->q), 0);
        arraynum_set(L, -1, ctx->q, Larray(ctx->q));
        break;
    case 0x00000076: // v
        lua_createtable(L, Larray(ctx->v), 0);
        arraynum_set(L, -1, ctx->v, Larray(ctx->v));
        break;
    case 0x00003B8C: // t0
        lua_pushnumber(L, ctx->t[0]);
        break;
    case 0x00003A03: // q0
        lua_pushnumber(L, ctx->q[0]);
        break;
    case 0x00003C92: // v0
        lua_pushnumber(L, ctx->v[0]);
        break;
    case 0x00003B8D: // t1
        lua_pushnumber(L, ctx->t[1]);
        break;
    case 0x00003A04: // q1
        lua_pushnumber(L, ctx->q[1]);
        break;
    case 0x00003C93: // v1
        lua_pushnumber(L, ctx->v[1]);
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, polytrack3_new);
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, polytrack3_init);
        break;
    case 0x001B2CBC: // gen
        lua_pushcfunction(L, polytrack3_gen);
        break;
    case 0x001D4D3A: // out
        lua_pushcfunction(L, polytrack3_out);
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, polytrack3_pos);
        break;
    case 0x001F1A38: // vec
        lua_pushcfunction(L, polytrack3_vec);
        break;
    case 0x00199975: // acc
        lua_pushcfunction(L, polytrack3_acc);
        break;
    default:
        return l_field(L, "getter", field, hash);
    }
    return 1;
}

int luaopen_liba_polytrack3(lua_State *L)
{
    const SFunc funcs[] = {
        {"init", polytrack3_init},
        {"gen", polytrack3_gen},
        {"out", polytrack3_out},
        {"pos", polytrack3_pos},
        {"vec", polytrack3_vec},
        {"acc", polytrack3_acc},
        {"new", polytrack3_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(funcs) - 1);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, 2);
    set_func(L, -1, LSET, l_setter);
    set_func(L, -1, LNEW, polytrack3_new);
    lua_setmetatable(L, -2);

    const SFunc metas[] = {
        {LNEW, polytrack3_out},
        {LSET, polytrack3_set},
        {LGET, polytrack3_get},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(metas));
    set_name(L, -1, LNAME, "polytrack3");
    set_funcs(L, -1, metas);

    lua_rawsetp(L, LUA_REGISTRYINDEX, POLYTRACK3_META_); // NOLINT(performance-no-int-to-ptr)
    lua_rawsetp(L, LUA_REGISTRYINDEX, POLYTRACK3_FUNC_); // NOLINT(performance-no-int-to-ptr)

    return polytrack3_func_(L);
}

int polytrack3_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, POLYTRACK3_FUNC_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}

int polytrack3_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, POLYTRACK3_META_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}
