#pragma once

#include "imgui.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

class ImGuiSetup {
public:
    static ImGuiSetup &getInstance()
    {
        static ImGuiSetup instance; // Guaranteed to be destroyed.
        return instance;
    }


    void InitImGui(GLFWwindow* window);
    // void InitImGui();

private:
    ImGuiSetup();
    // ~Commands(); // Optional deconstructor
    ImGuiSetup(const ImGuiSetup &) = delete;            // Prevent copy-construction
    ImGuiSetup &operator=(const ImGuiSetup &) = delete; // Prevent assignment

    GLFWwindow* window;

    // float main_scale;
};