# Example of usage from real project
# Please DO NOT copy this file. It is just the example

cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME "ImGui-CMake")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif ()

# Find SDL2
# find_package(SDL2 CONFIG REQUIRED)

# if(WIN32)
#    find_package(Freetype CONFIG REQUIRED)
# endif ()



# include_directories(${SDL2_INCLUDE_DIRS})

# OpenGL

find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )


MESSAGE(Current dir: ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(lib)
add_subdirectory(lib/imgui)
# include_directories(modules)

if (WIN32)
    add_executable(${PROJECT_NAME} WIN32
            src/main.cpp
            # libs
#            libs/include/json.hpp
    )
endif ()

if (UNIX)
add_executable(${PROJECT_NAME}
        src/main.cpp

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



# target_link_libraries(${PROJECT_NAME} PUBLIC imgui imgui-sdl2 imgui-sdlrenderer2 imgui-opengl2 ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC imgui imgui-glfw imgui-opengl3 ${OPENGL_LIBRARIES} glfw)

if(WIN32)
#    target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
endif()


