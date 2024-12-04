#pragma once

#include "Student.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//------������ص�ȫ�ֺ���------
//��������
int lua_create_new_student(lua_State* L);

//get/set����
int lua_get_name(lua_State* L);
int lua_set_name(lua_State* L);
int lua_get_age(lua_State* L);
int lua_set_age(lua_State* L);

//��ӡ����
int lua_print(lua_State* L);

//------ע��ȫ�ֺ�����Luaʹ��------
static const luaL_Reg lua_reg_student_funcs[] = {
	{ "create", lua_create_new_student },
	{ "get_name", lua_get_name },
	{ "set_name", lua_set_name },
	{ "get_age", lua_get_age },
	{ "set_age", lua_set_age },
	{ "print", lua_print },
	{ NULL, NULL },
};

int luaopen_student_libs(lua_State* L);