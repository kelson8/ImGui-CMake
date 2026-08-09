#pragma once

// #ifdef _WIN32
// #include <Windows.h>
// #endif

#include "imgui.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include <string>

// Oops, I was missing this header.
#include <cstdint>

#include <map>
#include <functional> // For std::function

//#include "common.h"


class ImGuiFunctions
{
public:
    static ImGuiFunctions &getInstance()
    {
        static ImGuiFunctions instance; // Guaranteed to be destroyed.
        return instance;
    }


	// Setup ImGui context.
	static void SetupContext();

	// Shutdown ImGui
	static void Shutdown(GLFWwindow* window);

	static void ImGuiLoop();

	static void ApplyStyle();

	void IV4toRGBA(ImVec4 color);
	
	// Windows directory opening and buttons
	// std::string GetCurrentWorkingDirectory();
	// void OpenCurrentDirectoryButton(const char *buttonLabel);
	// void OpenDirectoryButton(std::string folder, const char *buttonLabel);
	//

	//
	static bool ImGuiActive;

	// This prints to a VS 2022 debug output window.
	// TODO Move this somewhere else
	static void PrintToOutput(const char *text);

	// For setting a min/max value on ImGui::InputInt
	// Set it to just have a maximum value
	static void InputIntMax(const char *label, int *v, int step = 1, int step_fast = 10, int max_value = 100);
	// Set it to have a minimum and maximum value
	static void InputIntClamp(const char *label, int *v, int step = 1, int step_fast = 10, int min_value = 0, int max_value = 100);

private:
	// Setup ImGui fonts, this isn't used outside of this class
	static void SetupFonts(ImGuiIO &io);

    ImGuiFunctions();
    // ~Commands(); // Optional deconstructor
    ImGuiFunctions(const ImGuiFunctions &) = delete;            // Prevent copy-construction
    ImGuiFunctions &operator=(const ImGuiFunctions &) = delete; // Prevent assignment
	
};

