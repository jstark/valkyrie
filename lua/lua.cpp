#include "lua.hpp"
#include "valkyrie.h"

extern "C"
{

#define FIRST_ARGUMENT  1
#define SECOND_ARGUMENT 2
#define THIRD_ARGUMENT  3

static int l_major_version(lua_State *L)
{
    lua_pushinteger(L, VKApiMajorVersion());
    return 1;
}

static int l_minor_version(lua_State *L)
{
    lua_pushinteger(L, VKApiMinorVersion());
    return 1;
}

static int l_patch_version(lua_State *L)
{
    lua_pushinteger(L, VKApiPatchVersion());
    return 1;
}

static int l_is_at_least_version(lua_State *L)
{
    int M = luaL_checkinteger(L, FIRST_ARGUMENT);
    int m = luaL_checkinteger(L, SECOND_ARGUMENT);
    int p = luaL_checkinteger(L, THIRD_ARGUMENT);
    lua_pushboolean(L, VKApiVersionIsAtLeast(M, m, p));
    return 1;
}

static int l_version(lua_State *L)
{
    lua_pushstring(L, VKApiVersion());
    return 1;
}

static int return_value(lua_State *L, int code)
{
    const char *errmsg = VKErrorMessage(code);
    if (errmsg)
    {
        return luaL_error(L, errmsg);
    }
    return 1;
}

/* VKModelCreate => create_model */
static int l_model_create(lua_State *L)
{
    int mid = luaL_checkinteger(L, FIRST_ARGUMENT);

    /* second argument is not mandatory */
    const char *name = NULL;
    if (lua_isstring(L, SECOND_ARGUMENT))
    {
        name= lua_tostring(L, SECOND_ARGUMENT);
    }
    int ret = VKModelCreate(mid, name);
    return return_value(L, ret);
}

static int l_model_create_node(lua_State *L)
{
    int mid = luaL_checkinteger(L, 1);
    int nid = luaL_checkinteger(L, 2);
    double x= luaL_checknumber(L, 3); // x
    double y= luaL_checknumber(L, 4); // y
    double z= luaL_checknumber(L, 5); // z
    return return_value(L, VKModelCreateNode(mid, nid, x, y, z));
}

static int l_model_create_material(lua_State *L)
{
    int mid = luaL_checkinteger(L, 1);
    int matid = luaL_checkinteger(L, 2);
    double E= luaL_checknumber(L, 3); // E
    double rho= luaL_checknumber(L, 4); // rho
    const char *name = NULL;
    if (lua_isstring(L, 5))
    {
        name= lua_tostring(L, 5);
    }
    return return_value(L, VKModelCreateMaterial(mid, matid, E, rho, name));
}

static int l_model_create_property(lua_State *L)
{
    int mid = luaL_checkinteger(L, 1);
    int pid = luaL_checkinteger(L, 2);
    int matid = luaL_checkinteger(L, 3);
    double A= luaL_checknumber(L, 4); // A
    const char *name = NULL;
    if (lua_isstring(L, 5))
    {
        name= lua_tostring(L, 5);
    }
    return return_value(L, VKModelCreateProperty(mid, pid, matid, A, name));
}

static int l_model_create_element(lua_State *L)
{
    int mid = luaL_checkinteger(L, 1);
    int rid = luaL_checkinteger(L, 2);
    int pid = luaL_checkinteger(L, 3);
    int nd1 = luaL_checkinteger(L, 4);
    int nd2 = luaL_checkinteger(L, 5);
    return return_value(L, VKModelCreateRod(mid, rid, pid, nd1, nd2));
}

static int l_model_create_spc(lua_State *L)
{
    int mid = luaL_checkinteger(L, 1);
    int sid = luaL_checkinteger(L, 2);
    int dofs = luaL_checkinteger(L, 3);
    int nid = luaL_checkinteger(L, 4);
    return return_value(L, VKModelCreateSpc(mid, sid, dofs, nid));
}

static int l_model_create_force(lua_State *L)
{
    int mid = luaL_checkinteger(L, 1);
    int fid = luaL_checkinteger(L, 2);
    int nid = luaL_checkinteger(L, 3);
    double M  = luaL_checknumber(L, 4);
    double nx = luaL_checknumber(L, 5);
    double ny = luaL_checknumber(L, 6);
    double nz = luaL_checknumber(L, 7);
    return return_value(L, VKModelCreateForce(mid, fid, nid, M, nx, ny, nz));
}

static int l_model_get_constraint_code(lua_State *L)
{
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int z = luaL_checkinteger(L, 3);
    lua_pushinteger(L, VKDofCode(x, y, z));
    return 1;
}

static int l_model_perform_static_analysis(lua_State *L)
{
    int mid = luaL_checkinteger(L, 1);
    return return_value(L, VKModelPerformStaticAnalysis(mid));
}

static int l_model_print_results(lua_State *L)
{
    int mid = luaL_checkinteger(L, 1);
    return return_value(L, VKStaticAnalysisPrintResults(mid));
}

static const struct luaL_Reg valkyrie [] = {
    {"major_version", l_major_version},
    {"minor_version", l_minor_version},
    {"patch_version", l_patch_version},
    {"is_at_least_version", l_is_at_least_version},
    {"version", l_version},
    {"create_model" , l_model_create},
    {"create_node", l_model_create_node},
    {"create_material", l_model_create_material},
    {"create_property", l_model_create_property},
    {"create_element", l_model_create_element},
    {"constraint_code", l_model_get_constraint_code},
    {"create_spc", l_model_create_spc},
    {"create_force", l_model_create_force},
    {"perform_static_analysis", l_model_perform_static_analysis},
    {"print_results", l_model_print_results},
    {NULL, NULL}
};

int luaopen_valkyrie (lua_State *L)
{
    luaL_register(L, "valkyrie", valkyrie);
    return 1;
}

}//~extern "C"
