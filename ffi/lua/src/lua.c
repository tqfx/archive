#include "lua.h"

int l_setter(lua_State *L)
{
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    return l_field(L, "setter", field, hash);
}

int l_field(lua_State *L, const char *i, const char *s, uint32_t v)
{
    char h[11];
    (void)sprintf(h, "0x%08" PRIX32, v);
    return luaL_error(L, "field(%s) '%s' missing in %s", h, s, i);
}

void l_stack(lua_State *L, int line)
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

void *l_cmalloc(size_t siz)
{
    return calloc(sizeof(char), siz);
}

void *l_realloc(const void *ptr, size_t siz)
{
    return realloc((void *)(intptr_t)ptr, siz); // NOLINT(performance-no-int-to-ptr)
}

void l_dealloc(const void *var)
{
    void **ptr = (void **)(intptr_t)var; // NOLINT(performance-no-int-to-ptr)
    free(*ptr);
    *ptr = 0;
}

lua_Number get_fnum(lua_State *L, int idx, const char *name)
{
    lua_Number x = 0;
    /* data=table[name] */
    lua_pushstring(L, name);
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    if (lua_type(L, -1) == LUA_TNUMBER)
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
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    if (lua_type(L, -1) == LUA_TNUMBER)
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
    idx = idx < 0 ? idx - 1 : idx;
    while (tab->name)
    {
        /* data=table[name] */
        lua_pushstring(L, tab->name);
        lua_rawget(L, idx);
        if (lua_type(L, -1) == LUA_TNUMBER)
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

const char *get_name(lua_State *L, int idx, const char *name)
{
    const char *data = 0;
    /* data=table[name] */
    lua_pushstring(L, name);
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    if (lua_type(L, -1) == LUA_TSTRING)
    {
        data = lua_tostring(L, -1);
    }
    return data;
}

void set_name(lua_State *L, int idx, const char *name, const char *data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushstring(L, data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

void arraynum_get(lua_State *L, int idx, lua_Number *ptr, unsigned int num)
{
    size_t len = (size_t)lua_rawlen(L, idx);
    if (num > len)
    {
        num = (unsigned int)len;
    }
    for (unsigned int i = num; i--; num = i)
    {
        lua_rawgeti(L, idx, (int)num);
        if (lua_type(L, -1) == LUA_TNUMBER)
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
        lua_rawseti(L, idx, (int)num);
    }
}

void arraynum_gets(lua_State *L, int idx, const GFnums *tab)
{
    idx = idx < 0 ? idx - 1 : idx;
    while (tab->name)
    {
        lua_pushstring(L, tab->name);
        lua_rawget(L, idx);
        if (lua_type(L, -1) == LUA_TTABLE)
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

size_t tablenum_len(lua_State *L, int idx) // NOLINT(misc-no-recursion)
{
    size_t num = 0;
    size_t n = (size_t)lua_rawlen(L, idx);
    for (unsigned int i = 0; i++ != n;)
    {
        lua_rawgeti(L, idx, (int)i);
        int e = lua_type(L, -1);
        if (e == LUA_TNUMBER)
        {
            ++num;
        }
        else if (e == LUA_TTABLE)
        {
            num += tablenum_len(L, -1);
        }
        lua_pop(L, 1);
    }
    return num;
}

lua_Number *tablenum_num(lua_State *L, int idx, lua_Number *ptr) // NOLINT(misc-no-recursion)
{
    size_t n = (size_t)lua_rawlen(L, idx);
    for (unsigned int i = 0; i++ != n;)
    {
        lua_rawgeti(L, idx, (int)i);
        int e = lua_type(L, -1);
        if (e == LUA_TNUMBER)
        {
            *ptr++ = lua_tonumber(L, -1);
        }
        else if (e == LUA_TTABLE)
        {
            ptr = tablenum_num(L, -1, ptr);
        }
        lua_pop(L, 1);
    }
    return ptr;
}

lua_Number *tablenum_get(lua_State *L, int idx, const lua_Number *ptr, size_t *num)
{
    if (lua_type(L, idx) == LUA_TTABLE)
    {
        size_t buf = 0;
        num = num ? num : &buf;
        *num = tablenum_len(L, idx);
        if (*num)
        {
            ptr = (lua_Number *)l_realloc(ptr, sizeof(lua_Number) * *num);
            tablenum_num(L, idx, (lua_Number *)(intptr_t)ptr); // NOLINT(performance-no-int-to-ptr)
        }
    }
    return (lua_Number *)(intptr_t)ptr; // NOLINT(performance-no-int-to-ptr)
}

void tablenum_set(lua_State *L, int idx, const lua_Number *ptr, size_t num, unsigned int col)
{
    size_t n = num / col;
    lua_createtable(L, 0, 0);
    for (unsigned int i = 0; i++ != n;)
    {
        lua_createtable(L, 0, 0);
        arraynum_set(L, -1, ptr, col);
        lua_rawseti(L, -2, (int)i);
    }
    num %= col;
    if (num)
    {
        lua_createtable(L, 0, 0);
        arraynum_set(L, -1, ptr, (unsigned int)num);
        lua_rawseti(L, -2, (int)n + 1);
    }
    lua_rawset(L, idx < 0 ? idx - 1 : idx);
}
