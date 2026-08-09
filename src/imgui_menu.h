#pragma once

#include "imgui.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

class ImGuiMenu {
public:
    static ImGuiMenu &getInstance()
    {
        static ImGuiMenu instance; // Guaranteed to be destroyed.
        return instance;
    }

    void MainMenu(bool &show_demo_window, ImVec4 &clear_color);


    // void InitImGui(GLFWwindow* window);

private:
    ImGuiMenu();
    // ~Commands(); // Optional deconstructor
    ImGuiMenu(const ImGuiMenu &) = delete;            // Prevent copy-construction
    ImGuiMenu &operator=(const ImGuiMenu &) = delete; // Prevent assignment
};