#pragma once

// #include "SimpleIni.h"
// #include "INIReader.h"

class IniHandler {
public:
    static IniHandler &getInstance()
    {
        static IniHandler instance; // Guaranteed to be destroyed.
        return instance;
    }

    void IniTest();

    // static int InihHandler(void* user, const char* section, const char* name, const char* value);


private:
    IniHandler();
    ~IniHandler(); // Optional deconstructor
    IniHandler(const IniHandler &) = delete;            // Prevent copy-construction
    IniHandler &operator=(const IniHandler &) = delete; // Prevent assignment

};