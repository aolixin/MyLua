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
