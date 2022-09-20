#include "lua.h"
#include "a/pid.h"

int pid_from_(lua_State *L, int idx, a_pid_s *ctx);
int pid_into_(lua_State *L, int idx, a_pid_s *ctx);

int pid_from_(lua_State *L, int idx, a_pid_s *ctx)
{
    GFnum pid[] = {
        {"ts", &ctx->ts},
        {"kp", &ctx->kp},
        {"ki", &ctx->ki},
        {"kd", &ctx->kd},
        {"out", &ctx->out},
        {"outmin", &ctx->outmin},
        {"outmax", &ctx->outmax},
        {"summax", &ctx->summax},
        {"sum", &ctx->sum},
        {"ref", &ctx->ref},
        {"ec", &ctx->ec},
        {"e", &ctx->e},
        {NULL, NULL},
    };
    get_fnums(L, idx, pid);
    ctx->mode = (a_uint_t)get_enum(L, idx, "mode");
    ctx->num = (a_uint_t)get_enum(L, idx, "num");
    return 1;
}

int pid_into_(lua_State *L, int idx, a_pid_s *ctx)
{
    SFnum pid[] = {
        {"ts", ctx->ts},
        {"kp", ctx->kp},
        {"ki", ctx->ki},
        {"kd", ctx->kd},
        {"out", ctx->out},
        {"outmin", ctx->outmin},
        {"outmax", ctx->outmax},
        {"summax", ctx->summax},
        {"sum", ctx->sum},
        {"ref", ctx->ref},
        {"ec", ctx->ec},
        {"e", ctx->e},
        {NULL, 0},
    };
    lua_createtable(L, 0, Larray(pid) + 1);
    set_fnums(L, idx, pid);
    set_enum(L, idx, "mode", ctx->mode);
    set_enum(L, idx, "num", ctx->num);
    return 1;
}

static int pid_from(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)userdata_new(L, sizeof(a_pid_s), 1);
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        userdata_setp(L, 1, ctx); /* :from() */
    }
    return pid_from_(L, -1, ctx);
}

static int pid_into(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)userdata_get(L);
    if (ctx)
    {
        return pid_into_(L, -1, ctx);
    }
    return 0;
}

static int pid_init(lua_State *L)
{
    int n = lua_gettop(L) - lua_istable(L, 1);
    if (n > 2)
    {
        a_pid_s *ctx = (a_pid_s *)userdata_new(L, sizeof(a_pid_s), 3);
        ctx->ts = luaL_checknumber(L, 1);
        switch (n)
        {
        case 7: /* ts, kp, ki, kd, outmin, outmax, summax */
        {
            ctx->summax = luaL_checknumber(L, 7);
            ctx->mode = A_PID_POS;
            A_FALLTHROUGH;
        }
        case 6: /* ts, kp, ki, kd, outmin, outmax */
        {
            ctx->outmax = luaL_checknumber(L, 6);
            ctx->outmin = luaL_checknumber(L, 5);
            a_real_t kd = luaL_checknumber(L, 4);
            a_real_t ki = luaL_checknumber(L, 3);
            a_real_t kp = luaL_checknumber(L, 2);
            a_pid_kpid(ctx, kp, ki, kd);
            if (ctx->mode != A_PID_POS)
            {
                ctx->mode = A_PID_INC;
            }
        }
        break;
        case 4: /* ts, outmin, outmax, summax */
        {
            ctx->summax = luaL_checknumber(L, 4);
            ctx->mode = A_PID_POS;
            A_FALLTHROUGH;
        }
        case 3: /* ts, outmin, outmax */
        {
            ctx->outmax = luaL_checknumber(L, 3);
            ctx->outmin = luaL_checknumber(L, 2);
            if (ctx->mode != A_PID_POS)
            {
                ctx->mode = A_PID_INC;
            }
        }
        break;
        default:
            break;
        }
        return 1;
    }
    return 0;
}

static int pid_proc(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t set = luaL_checknumber(L, 2);
        a_real_t ref = luaL_checknumber(L, 3);
        lua_pushnumber(L, a_pid_proc(ctx, set, ref));
        return 1;
    }
    return 0;
}

static int pid_done(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)userdata_get(L);
    if (ctx)
    {
        a_pid_done(ctx);
        if (lua_type(L, 1) != LUA_TTABLE)
        {
            lua_pushlightuserdata(L, ctx);
        }
        else
        {
            lua_pushvalue(L, 1);
        }
        return 1;
    }
    return 0;
}

static int pid_kpid(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t kp = luaL_checknumber(L, 2);
        a_real_t ki = luaL_checknumber(L, 3);
        a_real_t kd = luaL_checknumber(L, 4);
        a_pid_kpid(ctx, kp, ki, kd);
        if (lua_type(L, 1) != LUA_TTABLE)
        {
            lua_pushlightuserdata(L, ctx);
        }
        else
        {
            lua_pushvalue(L, 1);
        }
        return 1;
    }
    return 0;
}

static int pid_time(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)userdata_get(L);
    if (ctx)
    {
        a_pid_time(ctx, luaL_checknumber(L, 2));
        if (lua_type(L, 1) != LUA_TTABLE)
        {
            lua_pushlightuserdata(L, ctx);
        }
        else
        {
            lua_pushvalue(L, 1);
        }
        return 1;
    }
    return 0;
}

static int pid_pos(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)userdata_get(L);
    if (ctx)
    {
        a_pid_pos(ctx, luaL_checknumber(L, 2));
        if (lua_type(L, 1) != LUA_TTABLE)
        {
            lua_pushlightuserdata(L, ctx);
        }
        else
        {
            lua_pushvalue(L, 1);
        }
        return 1;
    }
    return 0;
}

static int pid_inc(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)userdata_get(L);
    if (ctx)
    {
        a_pid_inc(ctx);
        if (lua_type(L, 1) != LUA_TTABLE)
        {
            lua_pushlightuserdata(L, ctx);
        }
        else
        {
            lua_pushvalue(L, 1);
        }
        return 1;
    }
    return 0;
}

static int pid_off(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)userdata_get(L);
    if (ctx)
    {
        a_pid_off(ctx);
        if (lua_type(L, 1) != LUA_TTABLE)
        {
            lua_pushlightuserdata(L, ctx);
        }
        else
        {
            lua_pushvalue(L, 1);
        }
        return 1;
    }
    return 0;
}

static const SFunc pidTF[] = {
    {"from", pid_from},
    {"into", pid_into},
    {"init", pid_init},
    {"proc", pid_proc},
    {"done", pid_done},
    {"kpid", pid_kpid},
    {"time", pid_time},
    {"pos", pid_pos},
    {"inc", pid_inc},
    {"off", pid_off},
    {NULL, NULL},
};

static const SEnum pidTE[] = {
    {"OFF", A_PID_OFF},
    {"POS", A_PID_POS},
    {"INC", A_PID_INC},
    {NULL, 0},
};

static int pid_new(lua_State *L)
{
    if (lua_istable(L, 1) && lua_istable(L, 2) && lua_gettop(L) > 2)
    {
        lua_rotate(L, 1, -1);
        lua_pop(L, 1); /* :pid() */
    }

    int ok = pid_init(L);

    lua_createtable(L, 0, Larray(pidTF) + Larray(pidTE) - 1);
    userdata_seti(L, -1, -2);
    set_enums(L, -1, pidTE);
    set_funcs(L, -1, pidTF);

    lua_createtable(L, 0, 1);
    set_func(L, -1, "__call", pid_proc);
    lua_setmetatable(L, -2);

    return ok;
}

static const SFunc pidTM[] = {
    {"__call", pid_new},
    {NULL, NULL},
};

int luaopen_liba_pid(lua_State *L)
{
    lua_createtable(L, 0, Larray(pidTF) + Larray(pidTE) - 2);
    set_enums(L, -1, pidTE);
    set_funcs(L, -1, pidTF);
    lua_createtable(L, 0, Larray(pidTM));
    set_funcs(L, -1, pidTM);
    set_name(L, -1, "pid");
    lua_setmetatable(L, -2);
    return 1;
}
