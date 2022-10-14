/***
 proportional integral derivative controller
 @module liba.pid
*/

#include "pid.h"

int pid_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, PID_META_);
    return 1;
}

int pid_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, PID_FUNC_);
    return 1;
}

static int pid_init_(lua_State *L, a_pid_s *ctx)
{
    ctx->dt = luaL_checknumber(L, 1);
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 7: /* dt, kp, ki, kd, outmin, outmax, summax */
    {
        ctx->summax = luaL_checknumber(L, 7);
        a_pid_set_mode(ctx, A_PID_POS);
        A_FALLTHROUGH;
    }
    case 6: /* dt, kp, ki, kd, outmin, outmax */
    {
        ctx->outmax = luaL_checknumber(L, 6);
        ctx->outmin = luaL_checknumber(L, 5);
        a_real_t kd = luaL_checknumber(L, 4);
        a_real_t ki = luaL_checknumber(L, 3);
        a_real_t kp = luaL_checknumber(L, 2);
        a_pid_kpid(ctx, kp, ki, kd);
        if (a_pid_mode(ctx) != A_PID_POS)
        {
            a_pid_set_mode(ctx, A_PID_INC);
        }
    }
    break;
    case 4: /* dt, outmin, outmax, summax */
    {
        ctx->summax = luaL_checknumber(L, 4);
        a_pid_set_mode(ctx, A_PID_POS);
        A_FALLTHROUGH;
    }
    case 3: /* dt, outmin, outmax */
    {
        ctx->outmax = luaL_checknumber(L, 3);
        ctx->outmin = luaL_checknumber(L, 2);
        if (a_pid_mode(ctx) != A_PID_POS)
        {
            a_pid_set_mode(ctx, A_PID_INC);
        }
    }
    break;
    default:
        break;
    }
    return 1;
}

/***
 constructor for PID controller
 @tparam number dt sampling time unit(s)
 @tparam[opt] number kp proportional constant
 @tparam[opt] number ki integral constant
 @tparam[opt] number kd derivative constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid PID controller userdata
 @function new
*/
int pid_new(lua_State *L)
{
    if (lua_gettop(L) > 2)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        a_pid_s *ctx = (a_pid_s *)lua_newuserdata(L, sizeof(a_pid_s));
        memset(ctx, 0, sizeof(a_pid_s));
        pid_meta_(L);
        lua_setmetatable(L, -2);
        return pid_init_(L, ctx);
    }
    return 0;
}

/***
 calculate function for PID controller
 @param ctx PID controller userdata
 @tparam number dt sampling time unit(s)
 @tparam[opt] number kp proportional constant
 @tparam[opt] number ki integral constant
 @tparam[opt] number kd derivative constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid PID controller userdata
 @function init
*/
int pid_init(lua_State *L)
{
    if (lua_gettop(L) > 3)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        lua_remove(L, 1);
        return pid_init_(L, ctx);
    }
    return 0;
}

/***
 calculate function for PID controller
 @param ctx PID controller userdata
 @tparam number set setpoint
 @tparam number fdb feedback
 @treturn number output
 @function proc
*/
int pid_proc(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_real_t set = luaL_checknumber(L, -2);
        a_real_t fdb = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_pid_outv(ctx, set, fdb));
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

/***
 zero function for PID controller
 @param ctx PID controller userdata
 @treturn pid PID controller userdata
 @function zero
*/
int pid_zero(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_pid_zero(ctx);
        return 1;
    }
    return 0;
}

/***
 set proportional integral derivative constant for PID controller
 @param ctx PID controller userdata
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn pid PID controller userdata
 @function kpid
*/
int pid_kpid(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -4);
    if (ctx)
    {
        a_real_t kp = luaL_checknumber(L, -3);
        a_real_t ki = luaL_checknumber(L, -2);
        a_real_t kd = luaL_checknumber(L, -1);
        a_pid_kpid(ctx, kp, ki, kd);
        lua_pop(L, 3);
        return 1;
    }
    return 0;
}

/***
 positional PID controller
 @param ctx PID controller userdata
 @tparam number max maximum intergral output
 @treturn pid PID controller userdata
 @function pos
*/
int pid_pos(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_pid_pos(ctx, luaL_checknumber(L, -1));
        lua_pop(L, 1);
        return 1;
    }
    return 0;
}

/***
 incremental PID controller
 @param ctx PID controller userdata
 @treturn pid PID controller userdata
 @function inc
*/
int pid_inc(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_pid_inc(ctx);
        return 1;
    }
    return 0;
}

/***
 turn off PID controller
 @param ctx PID controller userdata
 @treturn pid PID controller userdata
 @function off
*/
int pid_off(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_pid_off(ctx);
        return 1;
    }
    return 0;
}

static int pid_set(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x000033A0: // dt
        a_pid_set_dt(ctx, luaL_checknumber(L, 3));
        break;
    case 0x00003731: // kp
        a_pid_set_kp(ctx, luaL_checknumber(L, 3));
        break;
    case 0x0000372A: // ki
        a_pid_set_ki(ctx, luaL_checknumber(L, 3));
        break;
    case 0x00003725: // kd
        a_pid_set_kd(ctx, luaL_checknumber(L, 3));
        break;
    case 0x23C8F51C: // outmin
        ctx->outmin = luaL_checknumber(L, 3);
        break;
    case 0x23C8F10E: // outmax
        ctx->outmax = luaL_checknumber(L, 3);
        break;
    case 0x10E9FF9D: // summax
        ctx->summax = luaL_checknumber(L, 3);
        break;
    case 0x0EB84F77: // mode
        a_pid_set_mode(ctx, (a_uint_t)luaL_checkinteger(L, 3));
        break;
    default:
        return l_field(L, "setter", field, hash);
    }
    return 0;
}

static int pid_get(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x000033A0: // dt
        lua_pushnumber(L, a_pid_dt(ctx));
        break;
    case 0x00003731: // kp
        lua_pushnumber(L, a_pid_kp(ctx));
        break;
    case 0x0000372A: // ki
        lua_pushnumber(L, a_pid_ki(ctx));
        break;
    case 0x00003725: // kd
        lua_pushnumber(L, a_pid_kd(ctx));
        break;
    case 0x23C8F51C: // outmin
        lua_pushnumber(L, ctx->outmin);
        break;
    case 0x23C8F10E: // outmax
        lua_pushnumber(L, ctx->outmax);
        break;
    case 0x10E9FF9D: // summax
        lua_pushnumber(L, ctx->summax);
        break;
    case 0x001D4D3A: // out
        lua_pushnumber(L, ctx->out.v);
        break;
    case 0x001AE924: // fdb
        lua_pushnumber(L, ctx->fdb.v);
        break;
    case 0x00003412: // ec
        lua_pushnumber(L, ctx->ec.v);
        break;
    case 0x00000065: // e
        lua_pushnumber(L, ctx->e.v);
        break;
    case 0x0EB84F77: // mode
        lua_pushinteger(L, a_pid_mode(ctx));
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, pid_new);
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, pid_init);
        break;
    case 0x0F200702: // proc
        lua_pushcfunction(L, pid_proc);
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, pid_zero);
        break;
    case 0x0E73F9D8: // kpid
        lua_pushcfunction(L, pid_kpid);
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, pid_pos);
        break;
    case 0x001BB75E: // inc
        lua_pushcfunction(L, pid_inc);
        break;
    case 0x001D457F: // off
        lua_pushcfunction(L, pid_off);
        break;
    default:
        return l_field(L, "getter", field, hash);
    }
    return 1;
}

/***
 instance for PID controller
 @field OFF turn off PID controller
 @field POS positional PID controller
 @field INC incremental PID controller
 @table pid
*/
int luaopen_liba_pid(lua_State *L)
{
    const SEnum enums[] = {
        {"OFF", A_PID_OFF},
        {"POS", A_PID_POS},
        {"INC", A_PID_INC},
        {NULL, 0},
    };
    const SFunc funcs[] = {
        {"init", pid_init},
        {"proc", pid_proc},
        {"zero", pid_zero},
        {"kpid", pid_kpid},
        {"pos", pid_pos},
        {"inc", pid_inc},
        {"off", pid_off},
        {"new", pid_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(enums) + Larray(funcs) - 2);
    set_enums(L, -1, enums);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, 2);
    set_func(L, -1, LSET, l_setter);
    set_func(L, -1, LNEW, pid_new);
    lua_setmetatable(L, -2);

    const SFunc metas[] = {
        {LNEW, pid_proc},
        {LSET, pid_set},
        {LGET, pid_get},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(metas));
    set_name(L, -1, LNAME, "pid");
    set_funcs(L, -1, metas);

    lua_rawsetp(L, LUA_REGISTRYINDEX, PID_META_);
    lua_rawsetp(L, LUA_REGISTRYINDEX, PID_FUNC_);
    lua_rawgetp(L, LUA_REGISTRYINDEX, PID_FUNC_);

    return 1;
}
