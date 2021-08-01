#include<stdio.h>
#include<stdlib.h>
// #include "setlimit.h"
extern "C"{
    #include "../../3rd/Lua53/lua.h"
    #include "../../3rd/Lua53/lauxlib.h"
    #include "../../3rd/Lua53/lualib.h"
}

static void *alloc(void *ud, void *ptr, size_t osize, size_t nsize){
    if (nsize == 0){
        free(ptr);
        return NULL;
    }
    else{
        int *limit = (int *)ud;
        if(limit != NULL && nsize > (*limit)){
            printf("failed, out of memory!\n nsize: %zu, limit: %d", nsize, *limit);
            return NULL;
        }
        else{
            return realloc(ptr, nsize);
        }
    }
}
void setlimit(lua_State * L, int *memsize){
    lua_setallocf(L, alloc, memsize);
}
// int main()
// {
//     lua_State *L = luaL_newstate();
//     int limit  = 30;
//     setlimit(L, &limit);
//     printf("push 5 bytes of string\n");
//     lua_pushstring(L, "12345");
//     printf("push 7 bytes of string\n");
//     lua_pushstring(L, "1234567");
//     return 0;
// }