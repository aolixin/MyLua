#pragma once
#pragma comment(lib, "LuaDll")
#include <string>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <exception>
};

/*
** Lua处理类
*/
class LuaHandler
{
public:
	// 构造函数
	LuaHandler()
	{
		// 打开lua虚拟机
		L = luaL_newstate();

		luaL_openlibs(L);

		//// 打开lua基础的库
		//luaopen_base(L);

		//luaopen_table(L);

		//// 打开lua字数学库
		//luaopen_math(L);

		//// 打开lua字符串库
		//luaopen_string(L);

		////luaopen_debug(L);

		//luaopen_package(L);

		//luaopen_io(L);
	}

	// 析构函数
	~LuaHandler()
	{
		// 关闭lua虚拟机
		lua_close(L);
	}

	// 加载lua文件
	void LoadFile(const char* filename)
	{
		int nRet = luaL_dofile(L, filename);
		if (nRet != 0)
		{
			throw std::exception("can not open lua file!");
		}
	}

	void OpenLibs(const luaL_Reg* libs)
	{
		for (auto& lib = libs; lib->func; lib++)
		{
			luaL_requiref(L, lib->name, lib->func, 1);
			lua_pop(L, 1); /* remove lib */
		}
	}

	void RegisterFunc(const char* name, lua_CFunction func)
	{
		lua_register(L, name, func);
	}

	// 获取全局字符串
	std::string GetGlobalString(const char* varName)
	{
		lua_getglobal(L, varName);

		int nRet = lua_isstring(L, -1);
		if (nRet == 0)
		{
			throw std::exception("there is not a string!");
			return "";
		}

		return lua_tostring(L, -1);
	}

	// 设置lua堆栈顶部
	void SetTop(int v)
	{
		lua_settop(L, v);
	}

	// 获取全局数值型变量
	double GetGlobalNum(const char* varName)
	{
		lua_getglobal(L, varName);

		int nRet = lua_isnumber(L, -1);
		if (nRet == 0)
		{
			throw std::exception("there is not a number!");
			return 0;
		}

		return lua_tonumber(L, -1);
	}

	lua_State* GetLuaState()
	{
		return L;
	}

private:
	lua_State* L;
};
