#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
#include "lauxlib.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#include <string.h>

#undef NAME
#undef CALL
#define NAME "__name"
#define CALL "__call"

typedef struct
{
    const char *name;
    lua_CFunction func;
} RegFunc;

typedef struct
{
    const char *name;
    lua_Number data;
} RegFnum;

typedef struct
{
    const char *name;
    lua_Integer data;
} RegEnum;

#undef USERDATA
#define USERDATA "userdata"

#if 0
static void show(lua_State *L, int id)
{
    int n = lua_gettop(L);
    printf("%i:", id);
    for (int i = 0; i++ != n;)
    {
        printf(" %i", lua_type(L, i));
    }
    putchar('\n');
}
#endif

static void *touserdata(lua_State *L)
{
    void *userdata = NULL;
    if (lua_istable(L, 1))
    {
        lua_pushstring(L, USERDATA);
        if (lua_rawget(L, 1) == LUA_TUSERDATA)
        {
            userdata = lua_touserdata(L, -1);
        }
        lua_pop(L, 1);
        if (lua_type(L, 2) == LUA_TUSERDATA)
        {
            lua_rotate(L, 1, -1);
        }
    }
    if (userdata == NULL)
    {
        userdata = lua_touserdata(L, 1);
    }
    return userdata;
}

static void *newuserdata(lua_State *L, size_t sz)
{
    void *userdata = NULL; /* :func() */
    if (lua_istable(L, 1) && lua_gettop(L) > 1)
    {
        lua_pushstring(L, USERDATA);
        if (lua_rawget(L, 1) == LUA_TUSERDATA)
        {
            userdata = lua_touserdata(L, -1);
        }
        lua_pop(L, 1);
        lua_rotate(L, 1, -1);
    }
    if (userdata == NULL)
    {
        userdata = lua_newuserdata(L, sz);
        memset(userdata, 0, sz);
    }
    return userdata;
}

#include "a/math.h"

static int inv_sqrt(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }
    int n = lua_gettop(L);
    for (int i = 0; i++ != n;)
    {
        a_f32_t x = (a_f32_t)luaL_checknumber(L, i);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* __GNUC__ || __clang__ */
        lua_Number y = a_inv_sqrt(x);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */
        lua_pushnumber(L, y);
    }
    return n;
}

static const RegFunc funcs[] = {
    {"inv_sqrt", inv_sqrt},
    {NULL, NULL},
};

static void open_liba(lua_State *L)
{
    lua_createtable(L, 0, sizeof(funcs) / sizeof(funcs[0]) - 1);
    for (const RegFunc *p = funcs; p->name; ++p)
    {
        /* table[name]=func */
        lua_pushstring(L, p->name);
        lua_pushcclosure(L, p->func, 0);
        lua_rawset(L, -3);
    }
}

#include "a/version.h"

static int version(lua_State *L)
{
    lua_pushstring(L, a_version());
    return 1;
}

static const RegEnum versionet[] = {
    {"major", A_VERSION_MAJOR},
    {"minor", A_VERSION_MINOR},
    {"patch", A_VERSION_PATCH},
    {NULL, 0},
};

static const RegFunc versionmt[] = {
    {CALL, version},
    {NULL, NULL},
};

static void open_version(lua_State *L)
{
    /* table[name] = {} */
    const char *name = "version";
    lua_pushstring(L, name);

    lua_createtable(L, 0, sizeof(versionet) / sizeof(versionet[0]) - 1);
    for (const RegEnum *p = versionet; p->name; ++p)
    {
        /* table[name]=data */
        lua_pushstring(L, p->name);
        lua_pushinteger(L, p->data);
        lua_rawset(L, -3);
    }

    lua_createtable(L, 0, sizeof(versionmt) / sizeof(versionmt[0]));
    /* registry[name]=name */
    lua_pushstring(L, name);
    lua_pushvalue(L, -1);
    lua_rawset(L, LUA_REGISTRYINDEX);
    /* metatable[NAME]=name */
    lua_pushstring(L, NAME);
    lua_pushstring(L, name);
    lua_rawset(L, -3);
    for (const RegFunc *p = versionmt; p->name; ++p)
    {
        /* table[name]=func */
        lua_pushstring(L, p->name);
        lua_pushcclosure(L, p->func, 0);
        lua_rawset(L, -3);
    }
    lua_setmetatable(L, -2);

    lua_rawset(L, -3);
}

#include "a/pid.h"

static int pid_from(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)newuserdata(L, sizeof(a_pid_s));
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        lua_pushstring(L, USERDATA);
        lua_pushlightuserdata(L, ctx);
        lua_rawset(L, 1); /* :from() */
    }
    lua_pushstring(L, "mode");
    if (lua_rawget(L, -3) == LUA_TNUMBER)
    {
        ctx->mode = (a_uint_t)lua_tointeger(L, -1);
    }
    lua_pop(L, 1);
#undef get
#define get(field)                        \
    lua_pushstring(L, #field);            \
    if (lua_rawget(L, -3) == LUA_TNUMBER) \
    {                                     \
        ctx->field = lua_tonumber(L, -1); \
    }                                     \
    lua_pop(L, 1)
    get(ts);
    get(kp);
    get(ki);
    get(kd);
    get(out);
    get(outmin);
    get(outmax);
    get(summax);
    get(sum);
    get(ref);
    get(ec);
    get(e);
#undef get
    return 1;
}

static int pid_into(lua_State *L)
{
    a_pid_s *ctx = (a_pid_s *)touserdata(L);
    if (ctx)
    {
        RegFnum pid[] = {
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
        lua_createtable(L, 0, sizeof(pid) / sizeof(pid[0]) - 1);
        for (const RegFnum *p = pid; p->name; ++p)
        {
            /* table[name]=data */
            lua_pushstring(L, p->name);
            lua_pushnumber(L, p->data);
            lua_rawset(L, -3);
        }
        lua_pushstring(L, "mode");
        lua_pushinteger(L, ctx->mode);
        lua_rawset(L, -3);
        return 1;
    }
    return 0;
}

static int pid_init(lua_State *L)
{
    int n = lua_gettop(L) - lua_istable(L, 1);
    if (n > 2)
    {
        a_pid_s *ctx = (a_pid_s *)newuserdata(L, sizeof(a_pid_s));
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
    a_pid_s *ctx = (a_pid_s *)touserdata(L);
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
    a_pid_s *ctx = (a_pid_s *)touserdata(L);
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
    a_pid_s *ctx = (a_pid_s *)touserdata(L);
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
    a_pid_s *ctx = (a_pid_s *)touserdata(L);
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
    a_pid_s *ctx = (a_pid_s *)touserdata(L);
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
    a_pid_s *ctx = (a_pid_s *)touserdata(L);
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
    a_pid_s *ctx = (a_pid_s *)touserdata(L);
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

static const RegFunc pid[] = {
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

static const RegEnum pidet[] = {
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

    lua_createtable(L, 0, sizeof(pid) / sizeof(pid[0]) + sizeof(pidet) / sizeof(pidet[0]) - 2);
    lua_pushstring(L, USERDATA);
    lua_pushvalue(L, -3);
    lua_rawset(L, -3);
    for (const RegFunc *p = pid; p->name; ++p)
    {
        /* table[name]=func */
        lua_pushstring(L, p->name);
        lua_pushcclosure(L, p->func, 0);
        lua_rawset(L, -3);
    }
    for (const RegEnum *p = pidet; p->name; ++p)
    {
        /* table[name]=data */
        lua_pushstring(L, p->name);
        lua_pushinteger(L, p->data);
        lua_rawset(L, -3);
    }

    lua_createtable(L, 0, 1);
    lua_pushstring(L, CALL);
    lua_pushcclosure(L, pid_proc, 0);
    lua_rawset(L, -3);
    lua_setmetatable(L, -2);

    return ok;
}

static const RegFunc pidmt[] = {
    {CALL, pid_new},
    {NULL, NULL},
};

static void open_pid(lua_State *L)
{
    /* table[name] = {} */
    const char *name = "pid";
    lua_pushstring(L, name);

    lua_createtable(L, 0, sizeof(pid) / sizeof(pid[0]) + sizeof(pidet) / sizeof(pidet[0]) - 2);
    for (const RegFunc *p = pid; p->name; ++p)
    {
        /* table[name]=func */
        lua_pushstring(L, p->name);
        lua_pushcclosure(L, p->func, 0);
        lua_rawset(L, -3);
    }
    for (const RegEnum *p = pidet; p->name; ++p)
    {
        /* table[name]=data */
        lua_pushstring(L, p->name);
        lua_pushinteger(L, p->data);
        lua_rawset(L, -3);
    }

    lua_createtable(L, 0, sizeof(pidmt) / sizeof(pidmt[0]));
    /* metatable[NAME]=name */
    lua_pushstring(L, NAME);
    lua_pushstring(L, name);
    lua_rawset(L, -3);
    for (const RegFunc *p = pidmt; p->name; ++p)
    {
        /* table[name]=func */
        lua_pushstring(L, p->name);
        lua_pushcclosure(L, p->func, 0);
        lua_rawset(L, -3);
    }
    lua_setmetatable(L, -2);

    lua_rawset(L, -3);
}

A_PUBLIC LUA_API int luaopen_liba(lua_State *L);

int luaopen_liba(lua_State *L)
{
    luaL_checkversion(L);
    open_liba(L);
    open_version(L);
    open_pid(L);
    return 1;
}
