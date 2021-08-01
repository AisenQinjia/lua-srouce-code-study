#include "./setlimit.h"
#include <stdio.h>
extern "C"{
    #include "../../3rd/Lua53/lua.h"
    #include "../../3rd/Lua53/lauxlib.h"
    #include "../../3rd/Lua53/lualib.h"
}
int main()
{
    lua_State *L = luaL_newstate();
    int limit  = 30;
    setlimit(L, &limit);
    printf("push 5 bytes of string\n");
    lua_pushstring(L, "12345");
    printf("push 7 bytes of string\n");
    lua_pushstring(L, "1234567");
    return 0;
}