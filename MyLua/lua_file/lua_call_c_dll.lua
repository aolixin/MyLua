print('do somthing')
local cppdll = require "CppDll"
print(cppdll.getRand())
print(cppdll.getRand(10))
print(cppdll.getRand(10, 100))
