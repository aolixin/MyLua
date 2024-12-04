#include "StudentRegFunc.h"

int lua_create_new_student(lua_State* L)
{
	//����һ������ָ��ŵ�stack����ظ�Lua��ʹ��
	Student** s = (Student**)lua_newuserdata(L, sizeof(Student*));
	*s = new Student();
	return 1;
}

int lua_get_name(lua_State* L)
{
	//�õ���һ������Ķ����������stack��ײ���
	Student** s = (Student**)lua_touserdata(L, 1);
	luaL_argcheck(L, s != NULL, 1, "invalid user data");

	//���stack
	lua_settop(L, 0);

	//�����ݷ���stack�У���Luaʹ��
	lua_pushstring(L, (*s)->get_name().c_str());

	return 1;
}

int lua_set_name(lua_State* L)
{
	//�õ���һ������Ķ������
	Student** s = (Student**)lua_touserdata(L, 1);
	luaL_argcheck(L, s != NULL, 1, "invalid user data");

	luaL_checktype(L, -1, LUA_TSTRING);

	std::string name = lua_tostring(L, -1);
	(*s)->set_name(name);

	return 0;
}

int lua_get_age(lua_State* L)
{
	Student** s = (Student**)lua_touserdata(L, 1);
	luaL_argcheck(L, s != NULL, 1, "invalid user data");

	lua_pushinteger(L, (*s)->get_age());

	return 1;
}

int lua_set_age(lua_State* L)
{
	Student** s = (Student**)lua_touserdata(L, 1);
	luaL_argcheck(L, s != NULL, 1, "invalid user data");

	luaL_checktype(L, -1, LUA_TNUMBER);

	(*s)->set_age((unsigned)lua_tointeger(L, -1));

	return 0;
}

int lua_print(lua_State* L)
{
	Student** s = (Student**)lua_touserdata(L, 1);
	luaL_argcheck(L, s != NULL, 1, "invalid user data");

	(*s)->print();

	return 0;
}

int luaopen_student_libs(lua_State* L)
{
	// ����һ���µı������б�ĺ���ע���ȥ
	luaL_newlib(L, lua_reg_student_funcs);
	return 1;
}