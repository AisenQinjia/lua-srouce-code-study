// buld steps:
//     gcc c_module.test.cpp -shared -fPIC -L ../lua53/ -llua
#ifdef __cplusplus
extern "C"{
#endif
#include "../lua53/lua.h"
#include "../lua53/lualib.h"
#include "../lua53/lauxlib.h"
#include "../lua53/lbaselib.c"
#ifdef __cplusplus
}
#endif

int test_summation(lua_State *L){
    int arg_count = lua_gettop(L);
    double sum = 0;
    for(int i = 1; i <= arg_count; i++){
        sum += luaL_checknumber(L,i);
    }
    lua_pushnumber(L, sum);
    return 1;
}
int test_pack(lua_State *L){
    int arg_count = lua_gettop(L);
    lua_newtable(L);
    for(int i = 1; i <=arg_count; i++){
        lua_pushinteger(L, i);
        lua_rotate(L,1, -1);
        lua_settable(L,-3);
    }
    return 1;
}

int test_reverse(lua_State *L){
    int arg_count = lua_gettop(L);
    for(int i=1; i<arg_count; i++){
        lua_insert(L, i);
    }
    return arg_count;
}

int test_foreach(lua_State *L){
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TFUNCTION);
    lua_pushnil(L);
    while (lua_next(L, 1) != 0) {
       /* uses 'key' (at index -2) and 'value' (at index -1) */
       lua_pushvalue(L,2);
       lua_pushvalue(L,3);
       lua_pushvalue(L,4);
       lua_pcall(L,2,0,0);
       /* removes 'value'; keeps 'key' for next iteration */
       lua_pop(L, 1);
    }
    lua_settop(L, 0);
    return 0;
}

static int finishpcall2 (lua_State *L, int status, lua_KContext extra) {
    printf("finishpcall2 %d", status);
    if (status != LUA_OK && status != LUA_YIELD) {  /* error? */
      lua_pushboolean(L, 0);  /* first result (false) */
      lua_pushvalue(L, -2);  /* error message */
      return 2;  /* return false, msg */
    }
    else
      return lua_gettop(L) - (int)extra;  /* return all results */
}
int test_foreach_co(lua_State *L){
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TFUNCTION);
    lua_pushnil(L);
    while (lua_next(L, 1) != 0) {
       /* uses 'key' (at index -2) and 'value' (at index -1) */
        lua_pushvalue(L,2);
        lua_pushvalue(L,3);
        lua_pushvalue(L,4);
        // lua_pcall(L,2,0,0);

        // lua_callk(L, 2, 0, 0, NULL);
        // lua_State *NL = lua_newthread(L);
        // lua_pushvalue(L, 2);  /* move function to top */
        // lua_xmove(L, NL, 1);  /* move function from L to NL */
        // int state = luaB_pcall(L);
        // int state = lua_pcall(NL,0,0,0);

        int state = lua_pcallk(L,2,0,0,0,finishpcall2);
        printf("state: %d: \n", state);
        lua_pop(L, 1);
    }
    lua_settop(L, 0);
    return 0;
}

static const struct luaL_Reg testLib []{
    {"sum", test_summation},
    {"pack", test_pack},
    {"reverse", test_reverse},
    {"foreach", test_foreach},
    {"coforeach", test_foreach_co},
    {NULL, NULL}
};

extern "C"
int luaopen_test(lua_State *L){
    luaL_newlib(L, testLib);
    return 1;
}