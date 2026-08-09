#pragma once
#include <iostream>

// https://git.internal.kelsoncraft.net/kelson8/re3/src/branch/miami-dev/src/extras/utils/defines.h

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

// private:
};
