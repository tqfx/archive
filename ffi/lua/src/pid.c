/***
 proportional integral derivative controller
 @module liba.pid
*/

#include "pid.h"
#include <string.h>

static int LMODULE(pid_init_)(lua_State *L, a_pid_s *ctx)
{
    ctx->dt = (a_real_t)luaL_checknumber(L, 1);
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 7: /* dt, kp, ki, kd, outmin, outmax, summax */
    {
        ctx->summax = (a_real_t)luaL_checknumber(L, 7);
        a_pid_set_mode(ctx, A_PID_POS);
        A_FALLTHROUGH;
    }
    case 6: /* dt, kp, ki, kd, outmin, outmax */
    {
        ctx->outmax = (a_real_t)luaL_checknumber(L, 6);
        ctx->outmin = (a_real_t)luaL_checknumber(L, 5);
        a_real_t kd = (a_real_t)luaL_checknumber(L, 4);
        a_real_t ki = (a_real_t)luaL_checknumber(L, 3);
        a_real_t kp = (a_real_t)luaL_checknumber(L, 2);
        a_pid_kpid(ctx, kp, ki, kd);
        if (a_pid_mode(ctx) != A_PID_POS)
        {
            a_pid_set_mode(ctx, A_PID_INC);
        }
        break;
    }
    case 4: /* dt, outmin, outmax, summax */
    {
        ctx->summax = (a_real_t)luaL_checknumber(L, 4);
        a_pid_set_mode(ctx, A_PID_POS);
        A_FALLTHROUGH;
    }
    case 3: /* dt, outmin, outmax */
    {
        ctx->outmax = (a_real_t)luaL_checknumber(L, 3);
        ctx->outmin = (a_real_t)luaL_checknumber(L, 2);
        if (a_pid_mode(ctx) != A_PID_POS)
        {
            a_pid_set_mode(ctx, A_PID_INC);
        }
        break;
    }
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
int LMODULE(pid_new)(lua_State *L)
{
    if (lua_gettop(L) > 2)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        a_pid_s *ctx = (a_pid_s *)lua_newuserdata(L, sizeof(a_pid_s));
        memset(ctx, 0, sizeof(a_pid_s));
        LMODULE2(pid_meta_, L, 1);
        lua_setmetatable(L, -2);
        return LMODULE2(pid_init_, L, ctx);
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
int LMODULE(pid_init)(lua_State *L)
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
        return LMODULE2(pid_init_, L, ctx);
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
int LMODULE(pid_proc)(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_real_t set = (a_real_t)luaL_checknumber(L, -2);
        a_real_t fdb = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_pid_outv(ctx, set, fdb));
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
int LMODULE(pid_zero)(lua_State *L)
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
int LMODULE(pid_kpid)(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -4);
    if (ctx)
    {
        a_real_t kp = (a_real_t)luaL_checknumber(L, -3);
        a_real_t ki = (a_real_t)luaL_checknumber(L, -2);
        a_real_t kd = (a_real_t)luaL_checknumber(L, -1);
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
int LMODULE(pid_pos)(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_pid_pos(ctx, (a_real_t)luaL_checknumber(L, -1));
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
int LMODULE(pid_inc)(lua_State *L)
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
int LMODULE(pid_off)(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_pid_off(ctx);
        return 1;
    }
    return 0;
}

static int LMODULE(pid_set)(lua_State *L)
{
    const char *field = lua_tostring(L, 2);
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, 1);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x000033A0: // dt
        a_pid_set_dt(ctx, (a_real_t)luaL_checknumber(L, 3));
        break;
    case 0x00003731: // kp
        a_pid_set_kp(ctx, (a_real_t)luaL_checknumber(L, 3));
        break;
    case 0x0000372A: // ki
        a_pid_set_ki(ctx, (a_real_t)luaL_checknumber(L, 3));
        break;
    case 0x00003725: // kd
        a_pid_set_kd(ctx, (a_real_t)luaL_checknumber(L, 3));
        break;
    case 0x23C8F51C: // outmin
        ctx->outmin = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x23C8F10E: // outmax
        ctx->outmax = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x10E9FF9D: // summax
        ctx->summax = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x0EB84F77: // mode
        a_pid_set_mode(ctx, (a_uint_t)luaL_checkinteger(L, 3));
        break;
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

static int LMODULE(pid_get)(lua_State *L)
{
    const char *field = lua_tostring(L, 2);
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, 1);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x000033A0: // dt
        lua_pushnumber(L, (lua_Number)a_pid_dt(ctx));
        break;
    case 0x00003731: // kp
        lua_pushnumber(L, (lua_Number)a_pid_kp(ctx));
        break;
    case 0x0000372A: // ki
        lua_pushnumber(L, (lua_Number)a_pid_ki(ctx));
        break;
    case 0x00003725: // kd
        lua_pushnumber(L, (lua_Number)a_pid_kd(ctx));
        break;
    case 0x23C8F51C: // outmin
        lua_pushnumber(L, (lua_Number)ctx->outmin);
        break;
    case 0x23C8F10E: // outmax
        lua_pushnumber(L, (lua_Number)ctx->outmax);
        break;
    case 0x10E9FF9D: // summax
        lua_pushnumber(L, (lua_Number)ctx->summax);
        break;
    case 0x001D4D3A: // out
        lua_pushnumber(L, (lua_Number)ctx->out.v);
        break;
    case 0x001AE924: // fdb
        lua_pushnumber(L, (lua_Number)ctx->fdb.v);
        break;
    case 0x00003412: // ec
        lua_pushnumber(L, (lua_Number)ctx->ec.v);
        break;
    case 0x00000065: // e
        lua_pushnumber(L, (lua_Number)ctx->e.v);
        break;
    case 0x0EB84F77: // mode
        lua_pushinteger(L, (lua_Integer)a_pid_mode(ctx));
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, LMODULE(pid_new));
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, LMODULE(pid_init));
        break;
    case 0x0F200702: // proc
        lua_pushcfunction(L, LMODULE(pid_proc));
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, LMODULE(pid_zero));
        break;
    case 0x0E73F9D8: // kpid
        lua_pushcfunction(L, LMODULE(pid_kpid));
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, LMODULE(pid_pos));
        break;
    case 0x001BB75E: // inc
        lua_pushcfunction(L, LMODULE(pid_inc));
        break;
    case 0x001D457F: // off
        lua_pushcfunction(L, LMODULE(pid_off));
        break;
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
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
int LMODULE_(pid, lua_State *L)
{
    const l_int_s enums[] = {
        {"OFF", A_PID_OFF},
        {"POS", A_PID_POS},
        {"INC", A_PID_INC},
        {NULL, 0},
    };
    const l_func_s funcs[] = {
        {"init", LMODULE(pid_init)},
        {"proc", LMODULE(pid_proc)},
        {"zero", LMODULE(pid_zero)},
        {"kpid", LMODULE(pid_kpid)},
        {"pos", LMODULE(pid_pos)},
        {"inc", LMODULE(pid_inc)},
        {"off", LMODULE(pid_off)},
        {"new", LMODULE(pid_new)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(enums) + L_ARRAY(funcs) - 2);
    l_int_reg(L, -1, enums);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 2);
    l_func_set(L, -1, L_SET, LMODULE(setter));
    l_func_set(L, -1, L_NEW, LMODULE(pid_new));
    lua_setmetatable(L, -2);

    const l_func_s metas[] = {
        {L_NEW, LMODULE(pid_proc)},
        {L_SET, LMODULE(pid_set)},
        {L_GET, LMODULE(pid_get)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(metas));
    l_str_set(L, -1, L_NAME, "pid");
    l_func_reg(L, -1, metas);

    LMODULE2(pid_meta_, L, 0);
    LMODULE2(pid_func_, L, 0);

    return LMODULE2(pid_func_, L, 1);
}

int LMODULE(pid_func_)(lua_State *L, int ret)
{
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    void *p = (void *)(intptr_t)LMODULE(pid_func_);
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, p);
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, p);
    return 0;
}

int LMODULE(pid_meta_)(lua_State *L, int ret)
{
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    void *p = (void *)(intptr_t)LMODULE(pid_meta_);
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, p);
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, p);
    return 0;
}
