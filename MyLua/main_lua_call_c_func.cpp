#if 0

#include "LuaHandler.h"


static int average(lua_State* L)
{
    /* 得到参数个数 */
    int n = lua_gettop(L);
    double sum = 0;
    int i;

    /* 循环求参数之和 */
    for (i = 1; i <= n; i++)
    {
        /* 求和 */
        sum += lua_tonumber(L, i);
    }
    /* 压入平均值 */
    lua_pushnumber(L, sum / n);
    /* 压入和 */
    lua_pushnumber(L, sum);
    /* 返回返回值的个数 */
    return 2;
}


int main(int argc, char* argv[])
{
	LuaHandler luaHandler;

    luaHandler.RegisterFunc("average",average);

	luaHandler.LoadFile("lua_file/lua_call_c_func.lua");

	system("pause");

	return 0;
}

#endif
