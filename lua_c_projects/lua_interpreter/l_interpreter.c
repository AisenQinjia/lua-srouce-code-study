// shell:  gcc l_interpreter.c -L../../3rd/Lua53/ -llua -lm -Wl,--no-as-needed -ldl 
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

int main(void){

    char buff[256];
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    while(fgets(buff, sizeof(buff),stdin) != NULL){
        error= luaL_loadstring(L,buff) || lua_pcall(L,0,0,0);
        if(error){
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            lua_pop(L,1);
        }
    }
    lua_close(L);
    return 0;
}
