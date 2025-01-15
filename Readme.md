# MyLua

这个库旨在学习 lua 和 cpp 的交互

## 关键词:

+ lua
+ c++
+ lua 编译
+ lua 和 c++ 交互



## lua 编译



关于 lua 的编译 --> https://cloud.tencent.com/developer/article/2449942

这里采用的是把 lua 编译成动态库的方案, 在 mian.cpp 编译之前链接

```
#pragma comment(lib, "LuaDll")
```



## 项目结构

项目结构如下

其中 LuaDll 负责编译出 lua 的动态库 LuaDll

CppDll 也引用 LuaDll, 编译出 CppDll, 给 MyLua 调用

MyLua 里有 main 函数, 链接时链接 LuaDll & CppDll



<img src="img\项目结构.png" alt="cpp read lua config" style="zoom:67%;" />

## c++ 读取 lua 配置

这里直接用 **lua_getglobal** 获取 lua 文件的参数

<img src="img\cpp read lua config.jpg" alt="cpp read lua config" style="zoom:67%;" />







## lua 面向对象

直接贴代码了

```
local function class(className, super)
    -- build class
    local clazz = { __cname = className, super = super }
    if (super) then
        setmetatable(clazz, { __index = super })
    end

    clazz.new = function(...)
        local instance = {}
        setmetatable(instance, { __index = clazz })

        if (clazz.ctor) then
            clazz.ctor(instance, ...)
        end

        return instance
    end

    return clazz
end


-- test
local printf = function(str, ...)
    -- print(str,...)
    return print(string.format(str, ...))
end

-- claim calss A
local ClassA = class("ClassA")
ClassA.static = 'Static A'
function ClassA:ctor(a, b)
    self.a = a or 0
    self.b = b or 0
end

function ClassA:print()
    printf("%s, a = %d, b = %d, static = %s", self.__cname, self.a, self.b, self.static)
end

function ClassA:getSum()
    return self.a + self.b
end

-- claim class B derived from A
local ClassB = class("ClassB", ClassA)
function ClassB:ctor(...)
    ClassA.ctor(self, ...)
end

-- overwrite
function ClassB:print()
    print("class B overwrite supr print")
end

local ClassC = class("ClassC", ClassA)
ClassC.static = 'Static C'

local obj_a1 = ClassA.new(1, 2);
local obj_a2 = ClassA.new(10, 20);
local obj_b1 = ClassB.new(3, 4);
local obj_b2 = ClassB.new(30, 40);
local obj_c = ClassC.new(5, 6);

obj_a1:print();
obj_a2:print();
obj_b1:print();
obj_b2:print();
obj_c:print();

printf("5 + 6 = %s",obj_c:getSum())

```

<img src="img\cpp read lua config.jpg" alt="cpp read lua config" style="zoom:67%;" />







## lua 使用 cpp 类

这里稍微有点复杂, 要把 Student 类封装成 lua userdata, 并提供对应的 create, get, set 函数, 之后把这些函数封装成一个 lib, 最后把这个 lib 注册到 lua 虚拟机

```
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
	Student();
	~Student();
	
	string get_name();
	void set_name(string name);
	unsigned get_age();
	void set_age(unsigned age);

	void print();

private:
	string _name;
	unsigned _age;
};
```



```
static const luaL_Reg lua_reg_student_funcs[] = {
	{ "create", lua_create_new_student },
	{ "get_name", lua_get_name },
	{ "set_name", lua_set_name },
	{ "get_age", lua_get_age },
	{ "set_age", lua_set_age },
	{ "print", lua_print },
	{ NULL, NULL },
};
```



```
int luaopen_student_libs(lua_State* L)
{
	luaL_newlib(L, lua_reg_student_funcs);
	return 1;
}
```



```
static const luaL_Reg lua_reg_libs[] = {
	{ "Student", luaopen_student_libs},
	{ NULL, NULL }
};
```



```
void OpenLibs(const luaL_Reg* libs)
{
    for (auto& lib = libs; lib->func; lib++)
    {
        luaL_requiref(L, lib->name, lib->func, 1);
        lua_pop(L, 1); /* remove lib */
    }
}
```



<img src="img\cpp read lua config.jpg" alt="cpp read lua config" style="zoom:67%;" />







## lua 调用 cpp 函数

lua 调用 cpp 函数主要有两种方式:

1. 直接把函数注册到 lua 虚拟机
2. 把 cpp 编译成 dll, 然后在 lua 中 require, 在这里的体现就是上面提到的 CppDll

这里我两种方式都做了一下

效果如下

<img src="img\cpp read lua config.jpg" alt="cpp read lua config" style="zoom:67%;" />





