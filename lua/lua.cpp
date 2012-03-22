#include "lua.hpp"
#include "valkyrie.h"
#include <iostream>

extern "C"
{

static int l_major_version (lua_State *L)
{
    lua_pushnumber(L, VKApiMajorVersion());
    return 1;
}

static int l_minor_version (lua_State *L)
{
    lua_pushnumber(L, VKApiMinorVersion());
    return 1;
}

static int l_patch_version (lua_State *L)
{
    lua_pushnumber(L, VKApiPatchVersion());
    return 1;
}

static int l_is_at_least_version (lua_State *L)
{
    int major = luaL_checkinteger(L, 1);
    int minor = luaL_checkinteger(L, 2);
    int patch = luaL_checkinteger(L, 3);
    lua_pushboolean(L, VKApiVersionIsAtLeast(major, minor, patch));
    return 1;
}

static int l_version(lua_State *L)
{
    const char *version = VKApiVersion();
    lua_pushstring(L, version);
    return 1;
}

static const struct luaL_reg luavalkyrie [] = {
    {"major_version", l_major_version},
    {"minor_version", l_minor_version},
    {"patch_version", l_patch_version},
    {"version_is_at_least", l_is_at_least_version},
    {"version", l_version},
    {NULL, NULL}
};

int luaopen_luavalkyrie(lua_State *L)
{
    luaL_register(L, "luavalkyrie", luavalkyrie);
    return 0;
}

}
