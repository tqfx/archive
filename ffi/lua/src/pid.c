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

int pid_from_(lua_State *L, int idx, a_pid_s *ctx)
{
    GFnum pid[] = {
        {"dt", &ctx->dt},
        {"kp", &ctx->kp},
        {"ki", &ctx->ki},
        {"kd", &ctx->kd},
        {"outmin", &ctx->outmin},
        {"outmax", &ctx->outmax},
        {"summax", &ctx->summax},
        {"out", &ctx->out.x},
        {"sum", &ctx->sum.x},
        {"fdb", &ctx->fdb.x},
        {"ec", &ctx->ec.x},
        {"e", &ctx->e.x},
        {NULL, NULL},
    };
    get_fnums(L, idx, pid);
    ctx->num = (a_uint_t)get_enum(L, idx, "num");
    ctx->reg = (a_uint_t)get_enum(L, idx, "reg");
    return 0;
}

int pid_into_(lua_State *L, a_pid_s *ctx)
{
    SFnum pid[] = {
        {"dt", ctx->dt},
        {"kp", ctx->kp},
        {"ki", ctx->ki},
        {"kd", ctx->kd},
        {"outmin", ctx->outmin},
        {"outmax", ctx->outmax},
        {"summax", ctx->summax},
        {"out", ctx->out.x},
        {"sum", ctx->sum.x},
        {"fdb", ctx->fdb.x},
        {"ec", ctx->ec.x},
        {"e", ctx->e.x},
        {NULL, 0},
    };
    lua_createtable(L, 0, Larray(pid) + 1);
    set_fnums(L, -1, pid);
    set_enum(L, -1, "num", ctx->num);
    set_enum(L, -1, "reg", ctx->reg);
    return 1;
}

static int pid_from(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        lua_pushvalue(L, -2);
        lua_remove(L, -3);
    }
    else
    {
        ctx = (a_pid_s *)lua_newuserdata(L, sizeof(a_pid_s));
        memset(ctx, 0, sizeof(a_pid_s));
    }
    pid_meta_(L);
    lua_setmetatable(L, -2);
    pid_from_(L, -2, ctx);
    return 1;
}

static int pid_into(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        return pid_into_(L, ctx);
    }
    return 0;
}

static int pid_init_(lua_State *L, a_pid_s *ctx)
{
    ctx->dt = luaL_checknumber(L, 1);
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 7: /* dt, kp, ki, kd, outmin, outmax, summax */
    {
        ctx->summax = luaL_checknumber(L, 7);
        a_pid_mode(ctx, A_PID_POS);
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
        if ((ctx->reg & ((1U << A_PID_REG) - 1)) != A_PID_POS)
        {
            a_pid_mode(ctx, A_PID_INC);
        }
    }
    break;
    case 4: /* dt, outmin, outmax, summax */
    {
        ctx->summax = luaL_checknumber(L, 4);
        a_pid_mode(ctx, A_PID_POS);
        A_FALLTHROUGH;
    }
    case 3: /* dt, outmin, outmax */
    {
        ctx->outmax = luaL_checknumber(L, 3);
        ctx->outmin = luaL_checknumber(L, 2);
        if ((ctx->reg & ((1U << A_PID_REG) - 1)) != A_PID_POS)
        {
            a_pid_mode(ctx, A_PID_INC);
        }
    }
    break;
    default:
        break;
    }
    return 1;
}

static int pid_init(lua_State *L)
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

static int pid_new(lua_State *L)
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

static int pid_proc(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_real_t set = luaL_checknumber(L, -2);
        a_real_t fdb = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_pid_cc_x(ctx, set, fdb));
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

static int pid_zero(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_pid_zero(ctx);
        return 1;
    }
    return 0;
}

static int pid_kpid(lua_State *L)
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

static int pid_time(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_pid_time(ctx, luaL_checknumber(L, -1));
        lua_pop(L, 1);
        return 1;
    }
    return 0;
}

static int pid_pos(lua_State *L)
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

static int pid_inc(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_pid_inc(ctx);
        return 1;
    }
    return 0;
}

static int pid_off(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_pid_off(ctx);
        return 1;
    }
    return 0;
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
        {"from", pid_from},
        {"into", pid_into},
        {"init", pid_init},
        {"proc", pid_proc},
        {"zero", pid_zero},
        {"kpid", pid_kpid},
        {"time", pid_time},
        {"pos", pid_pos},
        {"inc", pid_inc},
        {"off", pid_off},
        {"new", pid_new},
        {NULL, NULL},
    };
    const SFunc metas[] = {
        {"__call", pid_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(enums) + Larray(funcs) - 2);
    set_enums(L, -1, enums);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, Larray(metas) - 1);
    set_funcs(L, -1, metas);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, 2);
    set_func(L, -1, "__call", pid_proc);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -3);
    lua_rawset(L, -3);

    lua_rawsetp(L, LUA_REGISTRYINDEX, PID_META_);
    lua_rawsetp(L, LUA_REGISTRYINDEX, PID_FUNC_);
    lua_rawgetp(L, LUA_REGISTRYINDEX, PID_FUNC_);

    return 1;
}
