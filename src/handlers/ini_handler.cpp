#include "ini_handler.h"

#include <stdio.h>
#include <assert.h>
#include <iostream>

#include <stdlib.h>
#include <string.h>

#include "file_functions.h"

// https://github.com/brofield/simpleini

// https://github.com/benhoyt/inih

// TODO Fix this to work.
// I may switch to using toml or something else.

typedef struct
{
    int version;
    const char* programName;
} configuration;


IniHandler::IniHandler()
{

}

IniHandler::~IniHandler()
{

}

// int IniHandler::InihHandler(void* user, const char* section, const char* name, const char* value)
// {
//     configuration* pconfig = (configuration*)user;

//     #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
//     if (MATCH("protocol", "version")) {
//         pconfig->version = atoi(value);
//     } else if (MATCH("user", "name")) {
//         pconfig->programName = strdup(value);
//     } else {
//         return 0;  /* unknown section/name, error */
//     }
//     return 1;
// }

/**
 * Run the test for the inihandler.
 * 
 */
void IniHandler::IniTest()
{
    // Inih testing

    //-----------
    // SimpleIni testing
    //-----------
    // CSimpleIniA ini;
    // ini.SetUnicode();

    // SI_Error rc = ini.LoadFile("test.ini");
    // // std::string iniFile = FileFunctions::getInstance().GetWorkingDirectory() + "test.ini";
    // // SI_Error rc = ini.LoadFile(iniFile.c_str());
    // if (rc < 0)
    // {
    //     // Handle error
    //     // ASSERT_EQ(rc, SI_OK);
    //     // https://www.geeksforgeeks.org/cpp/assertions-cc/
    //     // Assert can be useful to catch crashes like this before I have proper error handling.
    //     assert(rc == SI_OK);
    // }

    // const char* pv;
    // // pv = ini.GetValue("section", "key", "default");
    // pv = ini.GetValue("section", "key", "default");
    // std::cout << "Ini value: " << pv << std::endl;

    // ini.SetValue("section", "key", "newvalue");

    // pv = ini.GetValue("section", "key", "default");
    // std::cout << "New ini value: " << pv << std::endl;


}