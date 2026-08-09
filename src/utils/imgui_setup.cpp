#include "imgui_setup.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>
#include <string>

#include "defines.h"
#include "imgui_functions.h"

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

// Mostly taken from my internal ReVC code, since it uses OpenGL now
// https://git.internal.kelsoncraft.net/kelson8/re3/src/branch/miami-dev/src/extras/functions/imgui_functions.cpp

// Some code has been adapted from the ImGui examples.

ImGuiSetup::ImGuiSetup()
{
}


//---------- Begin ImGui setup/shutdown functions ----------//

/// <summary>
/// Run my imgui OpenGL init
/// </summary>
/// <param name="window">The GLFW window for the program.</param>
///
const char *glsl_version = nullptr;

void ImGuiSetup::InitImGui(GLFWwindow* window)
{
	ImGuiFunctions &imGuiFunctions = ImGuiFunctions::getInstance();

	Defines defines = Defines();
	
	// Setup ImGui Context, and setup fonts.
	imGuiFunctions.SetupContext();

	if(glsl_version == nullptr) {
#if defined(IMGUI_IMPL_OPENGL_ES2)
		glsl_version = "#version 100";
#elif defined(IMGUI_IMPL_OPENGL_ES3)
		glsl_version = "#version 300 es";
#elif defined(__APPLE__)
		glsl_version = "#version 150";
#else
		glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif
	}

	if(!glfwInit()) return;

	// Init Glfw for ImGui
    ImGui_ImplGlfw_InitForOpenGL(window, true);
	
	// Setup Platform/Renderer backends
#if defined(_WIN32) && defined(D3D9)
	// Windows only
	ImGui_ImplWin32_Init(window);
#endif // _WIN32

	// Init OpenGL for ImGui
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup the style from the Cheat Menu
	// https://github.com/user-grinch/Cheat-Menu
	ImGuiFunctions::ApplyStyle();
}
