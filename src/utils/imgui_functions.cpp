#include "imgui_functions.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// https://stackoverflow.com/questions/22744262/cant-call-stdmax-because-minwindef-h-defines-max
// Fix for std::min and std::max
#define NOMINMAX

#include "imgui_functions.h"

#include <algorithm> // For std::min

// ImGui
#include "imgui.h"

#if defined(_WIN32) && defined(RW_D3D9)
#include "imgui_impl_win32.h"
#endif // _WIN32 && RW_D3D9

#include <string>
#include <iostream>

#include "defines.h"

#include <vector>
#include <sstream>

// #include "log_functions.h"

#ifdef _WIN32
#include <direct.h>
#endif // _WIN32

#include <limits.h>

#include "file_functions.h"

ImGuiFunctions::ImGuiFunctions() {

}

/// <summary>
/// Setup the imgui fonts
/// </summary>
/// <param name="io"></param>
void ImGuiFunctions::SetupFonts(ImGuiIO &io)
{
    FileFunctions &fileFunctions = FileFunctions::getInstance();

    // No wonder this wasn't working.. It's not even in the ImGui-CMake folder....
    // Why is it one level above it anyways?
    // std::cout << "Current program working directory: " << fileFunctions.GetWorkingDirectory() << std::endl;

#ifdef _WIN32
	std::string fontsPath = "fonts\\";
#else
    std::string fontsPath = "fonts/";
#endif

	Defines defines = Defines();

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display
	// an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(),
	// which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !

	io.Fonts->AddFontDefault();

    std::string fontFilePath = fontsPath + defines.fontFile;

    // Check if the font exists, if not fallback to the default fonts.
    if(fileFunctions.FileExists(fontFilePath)) {
        std::cout << fontFilePath << " exists, loading cheat_menu font." << std::endl;
        io.Fonts->AddFontFromFileTTF(fontFilePath.c_str(), 1.15f);
    } else {
        std::cout << fontFilePath << " doesn't exist! Loading default fonts." << std::endl;
    }

	// 
	// 
}


// Credit to user-grinch on github for the style code here.
// https://github.com/user-grinch/Cheat-Menu/blob/master/src/cheatmenu.cpp#L271-L335
void ImGuiFunctions::ApplyStyle()
{
     ImGuiStyle* style = &ImGui::GetStyle();
     ImVec4* colors = style->Colors;

     style->WindowPadding = ImVec2(8, 8);
     style->WindowRounding = 5.0f;
     style->FramePadding = ImVec2(8, 8);
     style->FrameRounding = 5.0f;
     style->PopupRounding = 5.0f;
     style->ItemSpacing = ImVec2(7, 7);
     style->ItemInnerSpacing = ImVec2(7, 7);
     style->IndentSpacing = 25.0f;
     style->ScrollbarSize = 12.0f;
     style->ScrollbarRounding = 10.0f;
     style->GrabMinSize = 5.0f;
     style->GrabRounding = 3.0f;

     style->ChildBorderSize = 0;
     style->WindowBorderSize = 0;
     style->FrameBorderSize = 0;
     style->TabBorderSize = 0;
     style->PopupBorderSize = 0;

     style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
     style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.35f, 0.33f, 0.3f, 1.00f);
     style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.06f, 0.95f);
     style->Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
     style->Colors[ImGuiCol_PopupBg] = ImVec4(0.06f, 0.05f, 0.06f, 0.95f);
     style->Colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
     style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
     style->Colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
     style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
     style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
     style->Colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.94f);
     style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
     style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
     style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
     style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
     style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.5f, 0.5f, 0.5f, 0.3f);
     style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.7f, 0.7f, 0.7f, 0.3f);
     style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.9f, 0.9f, 0.9f, 0.3f);
     style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
     style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
     style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
     style->Colors[ImGuiCol_Separator] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
     style->Colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
     style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
     style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
     style->Colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
     style->Colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    //  style->Colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
     style->Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
     style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
     style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
     style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.12f, 0.12f, 0.12f, 0.00f);
     style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
     style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
     style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
     style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
     style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
     style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
     style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.06f, 0.05f, 0.06f, 0.95f);
     style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.6f);
 }


/// <summary>
/// Setup the ImGui context
/// </summary>
void
ImGuiFunctions::SetupContext()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

	ImGuiFunctions::SetupFonts(io);
}

/**
 * Cleanup ImGui for OpenGL, shutdown the ImGui system.
 */
void ImGuiFunctions::Shutdown(GLFWwindow* window) {

#ifdef OPENGL
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
#elif D3D9
    // TODO Set this up.

#endif // OPENGL
}
