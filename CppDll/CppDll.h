#pragma once
#include<Windows.h>
#include "lua.hpp"
#include<iostream>
#include<ctime>
#pragma comment(lib, "luaDll.lib")	// 这里需要lua的静态库，否则lua api 无法被调用

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
    lua_pushnumber(L, randValue);	// 返回结果需要入栈
    return 1;	// 执行成功，返回一
}
// 注册结构
static const luaL_Reg m_funcs[]{
    {"getRand", getRand},
    {NULL, NULL}
};
// 注册函数【luaopen_xxx 必须是 dll的名称，即 xxx.dll】
extern "C" int __declspec(dllexport) luaopen_CppDll(lua_State* L) {
    luaL_newlib(L, m_funcs);	// 创建一个新表，并将函数入栈
    return 1;
}
