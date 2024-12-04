#if 0

#include "LuaHandler.h"
#include <iostream>

using namespace std;

int main()
{
	LuaHandler luaHandler;
	luaHandler.LoadFile("lua_file/config.lua");
	auto name = luaHandler.GetGlobalString("PlayerName");
	auto speed = luaHandler.GetGlobalNum("PlayerSpeed");

	cout << "PlayerName: " << name << endl;
	cout << "PlayerSpeed: " << speed << endl;
	system("Pause");

	return 0;
}

#endif
