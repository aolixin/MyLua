#if 1

#include "LuaHandler.h"

int main(int argc, char* argv[])
{
    LuaHandler luaHandler;
    luaHandler.LoadFile("lua_file/lua_call_c_dll.lua");

    system("pause");

    return 0;
}

#endif
