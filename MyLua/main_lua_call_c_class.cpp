#if 0

#include "LuaHandler.h"

#include "Student.h"
#include "StudentRegFunc.h"

static const luaL_Reg lua_reg_libs[] = {
	{ "Student", luaopen_student_libs}, //Ä£¿éÃû×ÖStudent£¬×¢²áº¯Êýluaopen_student_libs
	{ NULL, NULL }
};

int main(int argc, char* argv[])
{
	LuaHandler luaHandler;

	luaHandler.OpenLibs(lua_reg_libs);

	luaHandler.LoadFile("lua_file/lua_call_c_class.lua");

	system("pause");

	return 0;
}

#endif
