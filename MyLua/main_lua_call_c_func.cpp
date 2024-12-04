#if 0

#include "LuaHandler.h"


static int average(lua_State* L)
{
    /* �õ��������� */
    int n = lua_gettop(L);
    double sum = 0;
    int i;

    /* ѭ�������֮�� */
    for (i = 1; i <= n; i++)
    {
        /* ��� */
        sum += lua_tonumber(L, i);
    }
    /* ѹ��ƽ��ֵ */
    lua_pushnumber(L, sum / n);
    /* ѹ��� */
    lua_pushnumber(L, sum);
    /* ���ط���ֵ�ĸ��� */
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
