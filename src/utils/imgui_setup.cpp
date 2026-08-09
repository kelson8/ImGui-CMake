#include "imgui_setup.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>
#include <string>

#include "defines.h"
#include "imgui_functions.h"
#include "imgui_menu.h"

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

// TODO Move into here
// GLFWwindow *window = nullptr;

ImGuiSetup::ImGuiSetup()
{
	// main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
}

//---------- Begin ImGui setup/shutdown functions ----------//

/// <summary>
/// Run my imgui OpenGL init
/// </summary>
/// <param name="window">The GLFW window for the program.</param>
///
const char *glsl_version = nullptr;

// void ImGuiSetup::InitImGui()
void ImGuiSetup::InitImGui(GLFWwindow* window)
{
	ImGuiMenu &imGuiMenu = ImGuiMenu::getInstance();
	ImGuiFunctions &imGuiFunctions = ImGuiFunctions::getInstance();
	ImGuiSetup &imGuiSetup = ImGuiSetup::getInstance();

	Defines defines = Defines();

	float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only

#ifdef OPENGL

	if (glsl_version == nullptr)
	{
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

	if (!glfwInit())
		return;

	// Init Glfw for ImGui
	ImGui_ImplGlfw_InitForOpenGL(window, true);

#endif // OPENGL

	// Setup Platform/Renderer backends
#if defined(_WIN32) && defined(D3D9)
	// Windows only, untested and not setup.
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);

#endif // _WIN32

#ifdef OPENGL
	// Init OpenGL for ImGui
	ImGui_ImplOpenGL3_Init(glsl_version);
#endif // OPENGL

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup the style from the Cheat Menu
	// https://github.com/user-grinch/Cheat-Menu
	ImGuiFunctions::ApplyStyle();

	// Setup scaling
	ImGuiStyle &style = ImGui::GetStyle();
	if (main_scale != 0)
	{
		style.ScaleAllSizes(main_scale); // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
		style.FontScaleDpi = main_scale; // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)
	}
	else
	{
		log_output("The main_scale variable was not set properly.");
	}

	// TODO Move this into here, it keeps crashing with no current context.
	// window = glfwCreateWindow(
	// 	(int)(1280 * main_scale),
	// 	(int)(800 * main_scale),
	// 	Defines::programName.c_str(),
	// 	nullptr,
	// 	nullptr);

	// if (window == nullptr)
	// 	return;
	// glfwMakeContextCurrent(window);

	// glfwSwapInterval(1); // Enable vsync

	// Setup ImGui Context, and setup fonts.
	// imGuiFunctions.SetupContext();

	// Setup Platform/Renderer backends
	// imGuiSetup.InitImGui(window);

	// Our state
	// bool show_demo_window = true;
	// bool show_another_window = false;
	// ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// // Main loop
	// while (!glfwWindowShouldClose(window))
	// {
	// 	// Poll and handle events (inputs, window resize, etc.)
	// 	// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
	// 	// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
	// 	// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
	// 	// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
	// 	glfwPollEvents();
	// 	if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
	// 	{
	// 		ImGui_ImplGlfw_Sleep(10);
	// 		continue;
	// 	}

	// 	// Start the Dear ImGui frame
	// 	ImGui_ImplOpenGL3_NewFrame();
	// 	ImGui_ImplGlfw_NewFrame();
	// 	ImGui::NewFrame();

	// 	imGuiMenu.MainMenu(show_demo_window, clear_color);

	// 	// Rendering
	// 	ImGui::Render();
	// 	int display_w, display_h;
	// 	glfwGetFramebufferSize(window, &display_w, &display_h);
	// 	glViewport(0, 0, display_w, display_h);
	// 	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// 	glfwSwapBuffers(window);
	// }

	// // Cleanup
    // imGuiFunctions.Shutdown(window);
}
