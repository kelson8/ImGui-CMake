print("Test from LUA code.")

-- I have disabled the debug, io, and os modules in my fork of 
-- Lua for a bit of security with this

-- Printing values from the C++ code.
-- print("Value printed in LUA from C++: " .. newtest.foo())
-- print("Value printed in LUA from C++: " .. newtest.var1)
-- print("Value printed in LUA from C++: " .. newtest.var2)

-- newtest.var2 = 200.2

-- Since this is disabled, it won't work.
-- file = io.open("test.txt", "w")
-- file:write("Testing from LUA")
-- file:close()

-- print("New value for var2: " .. newtest.var2)