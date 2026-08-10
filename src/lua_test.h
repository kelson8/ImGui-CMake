#pragma once

class LuaTest {
public:
    static LuaTest &getInstance()
    {
        static LuaTest instance; // Guaranteed to be destroyed.
        return instance;
    }

    void MainTest();

private:
    LuaTest();
    // ~Commands(); // Optional deconstructor
    LuaTest(const LuaTest &) = delete;            // Prevent copy-construction
    LuaTest &operator=(const LuaTest &) = delete; // Prevent assignment

};



