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

void set_enum(lua_State *L, int idx, const char *name, lua_Integer data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushinteger(L, data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

lua_Integer get_enum(lua_State *L, int idx, const char *name)
{
    /* data=table[name] */
    lua_pushstring(L, name);
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    lua_Integer x = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return x;
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

void set_fnum(lua_State *L, int idx, const char *name, a_real_t data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushnumber(L, (lua_Number)data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

a_real_t get_fnum(lua_State *L, int idx, const char *name)
{
    /* data=table[name] */
    lua_pushstring(L, name);
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    a_real_t x = (a_real_t)lua_tonumber(L, -1);
    lua_pop(L, 1);
    return x;
}

void set_fnums(lua_State *L, int idx, const SFnum *tab)
{
    idx = idx < 0 ? idx - 2 : idx;
    while (tab->name)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushnumber(L, (lua_Number)tab->data);
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
        *tab->data = (a_real_t)lua_tonumber(L, -1);
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
    /* data=table[name] */
    lua_pushstring(L, name);
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    const char *data = lua_tostring(L, -1);
    lua_pop(L, 1);
    return data;
}

void set_name(lua_State *L, int idx, const char *name, const char *data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushstring(L, data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

void arraynum_get(lua_State *L, int idx, a_real_t *ptr, unsigned int num)
{
    size_t len = (size_t)lua_rawlen(L, idx);
    if (num > len)
    {
        num = (unsigned int)len;
    }
    for (unsigned int i = num; i--; num = i)
    {
        lua_rawgeti(L, idx, (int)num);
        ptr[i] = (a_real_t)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
}

void arraynum_set(lua_State *L, int idx, const a_real_t *ptr, unsigned int num)
{
    idx = idx < 0 ? idx - 1 : idx;
    for (unsigned int i = num; i--; num = i)
    {
        lua_pushnumber(L, (lua_Number)ptr[i]);
        lua_rawseti(L, idx, (int)num);
    }
}

a_size_t tablenum_len(lua_State *L, int idx);
a_size_t tablenum_len(lua_State *L, int idx) // NOLINT(misc-no-recursion)
{
    a_size_t num = 0;
    a_size_t n = (a_size_t)lua_rawlen(L, idx);
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

a_real_t *tablenum_num(lua_State *L, int idx, a_real_t *ptr);
a_real_t *tablenum_num(lua_State *L, int idx, a_real_t *ptr) // NOLINT(misc-no-recursion)
{
    size_t n = (size_t)lua_rawlen(L, idx);
    for (unsigned int i = 0; i++ != n;)
    {
        lua_rawgeti(L, idx, (int)i);
        int e = lua_type(L, -1);
        if (e == LUA_TNUMBER)
        {
            *ptr++ = (a_real_t)lua_tonumber(L, -1);
        }
        else if (e == LUA_TTABLE)
        {
            ptr = tablenum_num(L, -1, ptr);
        }
        lua_pop(L, 1);
    }
    return ptr;
}

a_real_t *tablenum_get(lua_State *L, int idx, const a_real_t *ptr, a_size_t *num)
{
    a_real_t *ret = (a_real_t *)(intptr_t)ptr; // NOLINT(performance-no-int-to-ptr)
    if (lua_type(L, idx) == LUA_TTABLE)
    {
        a_size_t tmp = 0;
        num = num ? num : &tmp;
        *num = tablenum_len(L, idx);
        if (*num)
        {
            ret = (a_real_t *)l_realloc(ptr, sizeof(a_real_t) * *num);
            tablenum_num(L, idx, ret);
        }
    }
    return ret;
}

void tablenum_set(lua_State *L, int idx, const a_real_t *ptr, a_size_t num, unsigned int col)
{
    a_size_t n = num / col;
    lua_createtable(L, (int)n, 0);
    for (unsigned int i = 0; i++ != n;)
    {
        lua_createtable(L, (int)col, 0);
        arraynum_set(L, -1, ptr, col);
        lua_rawseti(L, -2, (int)i);
    }
    num %= col;
    if (num)
    {
        lua_createtable(L, (int)num, 0);
        arraynum_set(L, -1, ptr, (unsigned int)num);
        lua_rawseti(L, -2, (int)n + 1);
    }
    lua_rawset(L, idx < 0 ? idx - 1 : idx);
}
