#pragma once
#include<Windows.h>
#include "lua.hpp"
#include<iostream>
#include<ctime>
#pragma comment(lib, "luaDll.lib")	// ������Ҫlua�ľ�̬�⣬����lua api �޷�������

static int getRand(lua_State* L) {
    int n = lua_gettop(L);
    double a, b, temp;
    srand(time(NULL));
    if (n == 0) {
        a = 0;
        b = time(NULL);
    }
    else if (n == 1) {
        a = 0;
        b = lua_tonumber(L, -1);
        lua_pop(L, -1);
    }
    else {
        a = lua_tonumber(L, -1);
        b = lua_tonumber(L, -1);
        lua_pop(L, -1);
        lua_pop(L, -1);
        if (a > b) {
            temp = a;
            a = b;
            b = temp;
        }
    }
    int randValue = rand() % int(b - a + 1) + a;
    lua_pushnumber(L, randValue);	// ���ؽ����Ҫ��ջ
    return 1;	// ִ�гɹ�������һ
}
// ע��ṹ
static const luaL_Reg m_funcs[]{
    {"getRand", getRand},
    {NULL, NULL}
};
// ע�ắ����luaopen_xxx ������ dll�����ƣ��� xxx.dll��
extern "C" int __declspec(dllexport) luaopen_CppDll(lua_State* L) {
    luaL_newlib(L, m_funcs);	// ����һ���±�����������ջ
    return 1;
}
