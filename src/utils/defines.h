#pragma once
#include <iostream>

// This works for logging with a message
template <typename T>
inline void
log_output(const T &message)
{
	std::cout << message << std::endl;
}


class Defines {
public:
    static std::string programName;
    static std::string programAuthor;
    static std::string programVersion;

    static std::string fontFile;

    static const std::string& GetLogFile();
    static const std::string& GetLogPrefix();

private:
    static const std::string LogFile;
    static const std::string LogPrefix;
};
