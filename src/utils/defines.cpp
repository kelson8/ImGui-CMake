#include "defines.h"



#include "../version.h"

//------------
// Private values
//------------

const std::string Defines::LogPrefix = "ImGui-Test";

const std::string Defines::LogFile = "kcnet-console-test.log";

// const std::string Defines::IniFile = "example.ini";

//------------
// Public values
//------------

std::string Defines::programName = "ImGui-Test";
std::string Defines::programAuthor = "kelson8";
std::string Defines::programVersion = "1.0.0a";

std::string Defines::fontFile = "cheat_menu.ttf";

/**
 * 
 * @return The Log prefix of the application
 */
const std::string& Defines::GetLogPrefix()
{
    return Defines::LogPrefix;
}

/**
 * 
 * @return The config file name
 */
const std::string& Defines::GetLogFile()
{
    return Defines::LogFile;
}

/**
 * 
 * @return The ini file name
 */
// const std::string& Config::GetIniFile()
// {
//     return Config::IniFile;
// }