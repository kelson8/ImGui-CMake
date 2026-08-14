cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME "ImGui-CMake")
set(APP_VERSION "1.0.0")
set(APP_VERSION_SUFFIX "a")  # Pre-release suffix

# This sets the CMake binary output directory to the root of the git repo under bin.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#--------------
# Flags
#--------------

# Toggle optimizations for the project in release
# -O0	No optimization, useful for debugging.
# -O1	Basic optimizations without a significant increase in compile time.
# -O2	Moderate optimizations, suitable for most projects. Often a good compromise between performance and compile time.
# -O3	Aggressive optimizations, may improve performance but can increase compile time and binary size.
# -Os	Optimize for code size, enabling optimizations that reduce size.
# -Ofast	Disregards strict standards compliance for more aggressive optimizations.
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")


#--------------
# Project name, C++ language, and version
#--------------

project(${PROJECT_NAME}
  LANGUAGES CXX
  VERSION ${APP_VERSION}
)

# Specify the path to the version.h.in file
set(VERSION_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in")
set(GENERATED_VERSION_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/src/version.h")

# Generate a header file with version info
configure_file(
    "${VERSION_HEADER}"
    "${GENERATED_VERSION_HEADER}"
    @ONLY
)

# set(CMAKE_CXX_STANDARD 17)

# Switched to using C++20, I may use C++23 later on.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lm")
endif ()

#--------
# OpenGL
#--------
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

# MESSAGE(Current dir: ${CMAKE_CURRENT_SOURCE_DIR})

#--------
# ImGui
#--------
include_directories(lib)
add_subdirectory(lib/imgui)

#--------
# Lua
#--------
add_subdirectory(lib/lua)
add_subdirectory(lib/LuaBridge3)

# Add the lua and LuaBridge3 headers
include_directories(lib/lua/src)
include_directories(lib/LuaBridge3/Source)

#--------
# Serial port library
# https://github.com/crayzeewulf/libserial.git
#--------
include_directories(lib/serial/lib)
add_subdirectory(lib/serial)

#---------
# Setup Fmt, spdlog, and other dependencies.
# Switched to using a dependencies folder with a separate CMake file.
#---------
add_subdirectory(dependencies)

# Add src files for includes, this can be used for nested folder includes.
include_directories(src)
include_directories(src/utils)

# By default this ImGui instance is using OpenGL to work between Linux and Windows.
add_compile_definitions(OPENGL)
# This is incomplete and I have not started on the D3D9 version of this.
# add_compile_definitions(D3D9)

# Enable lua testing, currently this disables ImGui until I integrate it.
# add_compile_definitions(LUA_TEST)

# Enable serial port testing, this can run alongside of ImGui.
# This seems to work well for my ImGui text box to print to the serial port using the ESP32.
add_compile_definitions(SERIAL_PORT_TEST)

# This will enable the logger for the project.
# Currently it gives compiler errors so I have disabled it.
# add_compile_definitions(LOGGER_ENABLED)

if (WIN32)
    add_executable(${PROJECT_NAME} WIN32
            src/main.cpp
            src/lua_test.cpp
            src/imgui_menu.cpp
            src/utils/imgui_functions.cpp
            src/utils/imgui_setup.cpp
            src/utils/file_functions.cpp
            src/utils/defines.cpp

            # Now should support Windows also
            src/utils/serial_port.cpp

            # Logger
            src/utils/logger.cpp

            # libs
#            libs/include/json.hpp
            
    )
endif ()

if (UNIX)
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/lua_test.cpp
        src/imgui_menu.cpp
        src/utils/imgui_functions.cpp
        src/utils/imgui_setup.cpp
        src/utils/file_functions.cpp
        src/utils/defines.cpp

        src/utils/linux/serial_port_linux.cpp
        src/utils/serial_port.cpp

        # libs
#        libs/include/json.hpp
)
endif ()

#if(WIN32)
#    set(CMAKE_EXE_LINKER_FLAGS " -static")
#    target_link_libraries(${PROJECT_NAME} PUBLIC ws2_32 wsock32 dwmapi)
#endif()

if (WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    add_definitions(-D_WIN32_WINNT=0x0601)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
    target_link_libraries(${PROJECT_NAME} PUBLIC ws2_32 wsock32 dwmapi)
endif()



target_link_libraries(${PROJECT_NAME} PUBLIC 
    imgui 
    imgui-glfw 
    imgui-opengl3 
    ${OPENGL_LIBRARIES} 
    glfw
    lua::lua
    fmt::fmt
    # I added a CMake file to this project and am using it for my serial communication now.
    serial-port-lib
    )
    # TODO Enable when I get logger to work.
    # spdlog::spdlog)

# if(WIN32)
#    target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
# endif()


