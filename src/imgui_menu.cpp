#include "imgui_menu.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>
#include <string>

#include "defines.h"
#include "imgui_functions.h"

#include <format>
#include <fmt/core.h>

#include "serial_port.h"


// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// Mostly taken from my internal ReVC code, since it uses OpenGL now

// Some code has been adapted from the ImGui examples.

ImGuiMenu::ImGuiMenu()
{
}

#ifdef __linux__

// I will have some Linux only testing here.

#endif

void ImGuiMenu::MainMenu(ImVec4 &clear_color)
{

	static bool show_demo_window = false;

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("ImGui-C Make");

	ImGui::Text("This is a test with ImGui.");
	// For some reason if I don't space CMake in ImGui it looks weird.
	ImGui::Text("Using C Make and C++20.");

	// TODO Make this log custom text from input to console.
	if (ImGui::Button("Log to console")) {
		fmt::println("Logged from ImGui");
	}

	// Serial port testing

#if SERIAL_PORT_TEST
    SerialPortTest &serialPortTest = SerialPortTest::getInstance();

	// Input box for serial port.
	ImGui::InputText("Serial port message", serialPortMessage, MAX_SERIAL_CHARS);

	ImGui::Text("Serial Port Test");
	if(ImGui::Button("Serial Test")) {
		// serialPortTest.SendMessage("/dev/ttyUSB0", "Test message from C++.");
#ifdef __linux__
		serialPortTest.SendMessage("/dev/ttyUSB0", serialPortMessage);
#elif _WIN32
		// TODO Fix Windows support.
		// serialPortTest.SendMessage("COM1?", serialPortMessage);
#endif // __linux__
	}

#endif // SERIAL_PORT_TEST

	// https://stackoverflow.com/questions/69046648/using-stdstring-in-imguiinputtext

	// This doesn't seem to work right.
	// std::string testText;

	// char buf[255];

	// ImGui::InputText("Test Text", buf, sizeof(buf) - 1);
	// testText = std::format("Buf: {}", buf);

	// if(ImGui::Button("Print test text")) {
	// 	log_output(testText);
	// }

	// ImGui::Text(testText.c_str());

	// Toggle the demo window, moved out of the function.
	ImGui::Checkbox("Toggle demo window", &show_demo_window);

	// if(ImGui::Button("Read ini value")) {

	// }


	// ImGui::Text("This is some useful text.");		   // Display some text (you can use a format strings too)
	// ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
	// // ImGui::Checkbox("Another Window", &show_another_window);

	// ImGui::SliderFloat("float", &f, 0.0f, 1.0f);			 // Edit 1 float using a slider from 0.0f to 1.0f
	// ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

	// if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
	// 	counter++;
	// ImGui::SameLine();
	// ImGui::Text("counter = %d", counter);

	// ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();

	// 3. Show another simple window.
	// if (show_another_window)
	// {
	// 	ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	// 	ImGui::Text("Hello from another window!");
	// 	if (ImGui::Button("Close Me"))
	// 		show_another_window = false;
	// 	ImGui::End();
	// }
}
