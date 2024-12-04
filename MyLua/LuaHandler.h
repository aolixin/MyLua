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
** Lua������
*/
class LuaHandler
{
public:
	// ���캯��
	LuaHandler()
	{
		// ��lua�����
		L = luaL_newstate();

		luaL_openlibs(L);

		//// ��lua�����Ŀ�
		//luaopen_base(L);

		//luaopen_table(L);

		//// ��lua����ѧ��
		//luaopen_math(L);

		//// ��lua�ַ�����
		//luaopen_string(L);

		////luaopen_debug(L);

		//luaopen_package(L);

		//luaopen_io(L);
	}

	// ��������
	~LuaHandler()
	{
		// �ر�lua�����
		lua_close(L);
	}

	// ����lua�ļ�
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

	// ��ȡȫ���ַ���
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

	// ����lua��ջ����
	void SetTop(int v)
	{
		lua_settop(L, v);
	}

	// ��ȡȫ����ֵ�ͱ���
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
