#include "../ThirdParty/glew-2.2.0/include/GL/glew.h"

#include "../Graphics/Camera.h"
#include "../UI/imgui.h"
#include "../UI/imgui_impl_glfw.h"
#include "../UI/imgui_impl_opengl3.h"
#include <stdio.h>
#include "GLFW/glfw3.h"

#include "../UI/Matrix2dView.h"
#include "../UI/Panel.h"
#include "../UI/ColorMapView.h"

//#include "Crystal/ThirdParty/glew-2.1.0/include/GL/glew.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

int main() {
	if (!glfwInit()) {
		return false;
	}

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	auto window = glfwCreateWindow(1280, 720, "Hello", NULL, NULL);
	glfwMakeContextCurrent(window);
	//	gl3wInit();

	const auto e = glewInit();
	if (e != GLEW_OK) {
		return false;
	}


	// Setup ImGui binding
	//ImGui_ImplGlfwGL3_Init(window, true);

	const char* glsl_version = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);


	// glfwSetScrollCallback(window, onWheel);
 //	glfwSetMouseButtonCallback(window, onMouse);
 //	glfwSetCursorPosCallback(window, onMouseMove);

	// glfwSetWindowCloseCallback(window, onClose);


	 // Setup window
	 //glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		return 1;
	}

	Crystal::UI::Panel panel("Panel");
	Crystal::UI::ColorMapView colorMap("ColorMap");
	Crystal::UI::Matrix2dView matrix2d("Matrix2d");

	// onInit();

	while (!glfwWindowShouldClose(window)) {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Sample")) {
				if (ImGui::MenuItem("Point")) {
				}
				if (ImGui::MenuItem("Line")) {
				}
				if (ImGui::MenuItem("Triangle")) {
				}
				if (ImGui::MenuItem("Tex")) {
				}
				if (ImGui::MenuItem("ColorMap")) {
					panel.clear();
					panel.add(&colorMap);
				}
				if (ImGui::MenuItem("Matrix2d")) {
					panel.clear();
					panel.add(&matrix2d);
				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		panel.show();

		//renderer.render(width, height);

		//onRender(width, height);

		glFlush();

		ImGui::Render();

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	panel.clear();

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();
	glfwTerminate();
}