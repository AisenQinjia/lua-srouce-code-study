// #define STRCONCAT(ROOT,PATH) TEMP(ROOT,PATH)
// #define TEMP(A,B) A##B
#define STRINGFY(x) #x
#define COMBINE2(a,b) STRINGFY(a ## b)
#define COMBINE(a,b) COMBINE2(a,b)
#define LUA_ROOT_PATH ../../3rd/Lua5
#define LUA_H 3/lua.h //not the preprocessor but the  compiler do the string concatenation!!
#define LUAXLIB_H 3/lauxlib.h
#define LUALIB_H 3/lualib.h
#include<stdio.h>
#include<string.h>
#include COMBINE(LUA_ROOT_PATH,LUA_H)
#include COMBINE(LUA_ROOT_PATH,LUAXLIB_H)
#include COMBINE(LUA_ROOT_PATH,LUALIB_H )

static void stackDump(lua_State *L){
    int i;
    int top = lua_gettop(L);
    for(int i = 1;i<=top; i++){
        int t = lua_type(L,i);
        switch (t)
        {
            case LUA_TSTRING:
                {
                    printf("'%s'", lua_tostring(L, i));
                    break;
                }
            case LUA_TBOOLEAN:
                {
                    printf(lua_toboolean(L, i) ? "true" : "false");
                    break;
                }
            case LUA_TNUMBER:
                {
                    printf("'%g'", lua_tonumber(L, i));
                    break;
                }
            
            default:
            {
                printf("%s", lua_typename(L, t));
                break;
            }
        }
        printf("    ");
    }
    printf("\n");
}

int main(void){
    lua_State *L = luaL_newstate();
    lua_pushnumber(L,3.5);
    stackDump(L);

    lua_pushstring(L, "hello");
    stackDump(L);

    lua_pushnil(L);
    stackDump(L);

    lua_rotate(L, 1, -1);
    stackDump(L);

    lua_pushvalue(L, -2);
    stackDump(L);

    lua_remove(L, 1);
    stackDump(L);

    lua_insert(L, -2);

    stackDump(L);
    return 0;
}