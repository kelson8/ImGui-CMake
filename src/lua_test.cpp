#include "lua_test.h"
// Lua
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include <iostream>

#include "defines.h"

LuaTest::LuaTest() 
{

}

// Check lua globals, made this into a function
bool CheckLua(lua_State* L, int r)
{
	// Check if the value is valid
	if (r != LUA_OK)
	{
		std::string errorMsg = lua_tostring(L, -1);
		std::cout << errorMsg << std::endl;
		return false;
	}

	return true;
}


// Lua testing
// https://luabridge3.readthedocs.io/en/latest/cpp-from-lua/properties-and-functions.html
int globalVar = 2;
static float staticVar = 2.222;

std::string stringProperty;
std::string getString() { return stringProperty; }
void setString(std::string s) { stringProperty = s; }

std::tuple<int, std::string> tuple;

int foo() { return 42; }
void bar(char const *) {}
int cFunc(lua_State *L) { return 0; }

void LuaTest::MainTest() {
    log_output("----------------------");
    log_output("Running Lua testing");
    log_output("----------------------");

    //-------
    // Lua
    //-------
    
    // Lua states is needed, to do anything in lua
    lua_State *L = luaL_newstate();

    // Open the libraries, without this, stuff like math won't work
    luaL_openlibs(L);

    // luabridge::getGlobalNamespace(L)
        // .beginNamespace("test")
        // .beginNamespace("println")
        // .endNamespace();
    // .beginNamespace("test");


    luabridge::getGlobalNamespace(L)
        .beginNamespace("newtest")
        .addProperty("var1", &globalVar)             // read-only
        .addProperty("var2", &staticVar, &staticVar) // read-write
        .addProperty("prop1", getString)             // read-only
        .addProperty("prop2", getString, setString)  // read-write
        .addProperty("tup1", &tuple)                 // read-only
        .addProperty("tup2", &tuple, &tuple)         // read-write
        .addFunction("foo", foo)
        .addFunction("bar", bar)
        .addFunction("cfunc", cFunc)
        .endNamespace();

    // Make sure lua file exist, and run the script if it does.
    if (!CheckLua(L, luaL_dofile(L, "scripts/test.lua"))) {
        log_output("ERROR loading of lua file scripts/test.lua failed");
        return;
    }




    //-------
}