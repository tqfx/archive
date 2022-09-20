#include "lua.h"

A_ATTRIBUTE(unused)
void lua_show(lua_State *L, int line)
{
    char map[] = {'0', 'B', 'P', 'N', 'S', 'T', 'F', 'U', 'M'};
    int n = lua_gettop(L);
    printf("%i: ", line);
    for (int i = 0; i++ != n;)
    {
        putchar(map[lua_type(L, i) % (int)sizeof(map)]);
        putchar(i != n ? ' ' : '\n');
    }
}

lua_Number get_fnum(lua_State *L, int idx, const char *name)
{
    lua_Number x = 0;
    /* data=table[name] */
    lua_pushstring(L, name);
    if (lua_rawget(L, idx < 0 ? idx - 2 : idx) == LUA_TNUMBER)
    {
        x = lua_tonumber(L, -1);
    }
    lua_pop(L, 1);
    return x;
}

void set_enum(lua_State *L, int idx, const char *name, lua_Integer data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushinteger(L, data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

void set_enums(lua_State *L, int idx, const SEnum *tab)
{
    idx = idx < 0 ? idx - 2 : idx;
    while (tab->name)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushinteger(L, tab->data);
        lua_rawset(L, idx);
        ++tab;
    }
}

lua_Integer get_enum(lua_State *L, int idx, const char *name)
{
    lua_Number x = 0;
    /* data=table[name] */
    lua_pushstring(L, name);
    if (lua_rawget(L, idx < 0 ? idx - 2 : idx) == LUA_TNUMBER)
    {
        x = lua_tonumber(L, -1);
    }
    lua_pop(L, 1);
    return (lua_Integer)x;
}

void set_fnum(lua_State *L, int idx, const char *name, lua_Number data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushnumber(L, data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

void set_fnums(lua_State *L, int idx, const SFnum *tab)
{
    idx = idx < 0 ? idx - 2 : idx;
    while (tab->name)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushnumber(L, tab->data);
        lua_rawset(L, idx);
        ++tab;
    }
}

void get_fnums(lua_State *L, int idx, const GFnum *tab)
{
    idx = idx < 0 ? idx - 2 : idx;
    while (tab->name)
    {
        /* data=table[name] */
        lua_pushstring(L, tab->name);
        if (lua_rawget(L, idx) == LUA_TNUMBER)
        {
            *tab->data = lua_tonumber(L, -1);
        }
        lua_pop(L, 1);
        ++tab;
    }
}

void set_func(lua_State *L, int idx, const char *name, lua_CFunction func)
{
    /* table[name]=func */
    lua_pushstring(L, name);
    lua_pushcclosure(L, func, 0);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

void set_funcs(lua_State *L, int idx, const SFunc *tab)
{
    idx = idx < 0 ? idx - 2 : idx;
    while (tab->name)
    {
        /* table[name]=func */
        lua_pushstring(L, tab->name);
        lua_pushcclosure(L, tab->func, 0);
        lua_rawset(L, idx);
        ++tab;
    }
}

void set_name(lua_State *L, int idx, const char *name)
{
    /* table["__name"]=name */
    lua_pushstring(L, "__name");
    lua_pushstring(L, name);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

void arraynum_get(lua_State *L, int idx, lua_Number *ptr, unsigned int num)
{
    for (unsigned int i = num; i--; num = i)
    {
        if (lua_rawgeti(L, idx, num) == LUA_TNUMBER)
        {
            ptr[i] = lua_tonumber(L, -1);
        }
        lua_pop(L, 1);
    }
}

void arraynum_set(lua_State *L, int idx, const lua_Number *ptr, unsigned int num)
{
    idx = idx < 0 ? idx - 1 : idx;
    for (unsigned int i = num; i--; num = i)
    {
        lua_pushnumber(L, ptr[i]);
        lua_rawseti(L, idx, num);
    }
}

void arraynum_gets(lua_State *L, int idx, const GFnums *tab)
{
    idx = idx < 0 ? idx - 2 : idx;
    while (tab->name)
    {
        lua_pushstring(L, tab->name);
        if (lua_rawget(L, idx) == LUA_TTABLE)
        {
            arraynum_get(L, -1, tab->ptr, (unsigned int)tab->num);
        }
        lua_pop(L, 1);
        ++tab;
    }
}

void arraynum_sets(lua_State *L, int idx, const SFnums *tab)
{
    idx = idx < 0 ? idx - 2 : idx;
    while (tab->name)
    {
        lua_pushstring(L, tab->name);
        lua_createtable(L, (int)tab->num, 0);
        arraynum_set(L, -1, tab->ptr, (unsigned int)tab->num);
        lua_rawset(L, idx);
        ++tab;
    }
}

#undef USERDATA
#define USERDATA "USERDATA"

void *userdata_get(lua_State *L)
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

void *userdata_new(lua_State *L, size_t sz, int op)
{
    void *userdata = NULL; /* :func() */
    if (lua_istable(L, 1) && lua_gettop(L) > op)
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

void userdata_seti(lua_State *L, int idx, int dat)
{
    lua_pushstring(L, USERDATA);
    lua_pushvalue(L, dat < 0 ? dat - 1 : dat);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

void userdata_setp(lua_State *L, int idx, void *ptr)
{
    lua_pushstring(L, USERDATA);
    lua_pushlightuserdata(L, ptr);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

#undef USERDATA
