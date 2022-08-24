#include "../ThirdParty/glew-2.2.0/include/GL/glew.h"

#include "../Graphics/Camera.h"
#include "../UI/imgui.h"
#include "../UI/imgui_impl_glfw.h"
#include "../UI/imgui_impl_opengl3.h"
#include <stdio.h>
#include "GLFW/glfw3.h"

#include "PointRenderer.h"
#include "TexRenderer.h"

#include "../Shader/ShaderBuilder.h"

//#include "Crystal/ThirdParty/glew-2.1.0/include/GL/glew.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

namespace {
	Camera camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1, 10.0);
}

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
	if (!glfwInit())
		return 1;

	Crystal::Shader::ShaderBuilder sBuilder;
	sBuilder.buildFromFile("./Point.vs", "./Point.fs");

	Crystal::UI::PointRenderer renderer;
	renderer.setShader(sBuilder.getShader());
	renderer.build();

	sBuilder.buildFromFile("./Tex.vs", "./Tex.fs");

	Crystal::UI::TexRenderer texRenderer;
	texRenderer.setShader(sBuilder.getShader());
	texRenderer.build();

	Crystal::Shader::TextureObject tex;
	tex.create();
	Imageuc image(2, 2);
	image.setColor(0, 0, ColorRGBAuc(0, 0, 0, 0));
	image.setColor(0, 1, ColorRGBAuc(255, 0, 0, 0));
	image.setColor(0, 1, ColorRGBAuc(0, 255, 0, 0));
	image.setColor(1, 1, ColorRGBAuc(0, 0, 255, 0));

	tex.send(image);
	texRenderer.buffer.tex = &tex;

	Crystal::Shader::VertexBufferObject positionVBO;
	Crystal::Shader::VertexBufferObject colorVBO;
	Crystal::Shader::VertexBufferObject sizeVBO;

	positionVBO.create();
	colorVBO.create();
	sizeVBO.create();


	std::vector<float> positions{ 0,0,0 };
	std::vector<float> colors{ 1,1,1,1 };
	std::vector<float> size{ 100 };
	positionVBO.send(positions);
	colorVBO.send(colors);
	sizeVBO.send(size);

	assert(GL_NO_ERROR == glGetError());

	renderer.buffer.position = &positionVBO;
	renderer.buffer.color = &colorVBO;
	renderer.buffer.size = &sizeVBO;
	renderer.buffer.modelViewMatrix = camera.getModelViewMatrix();
	renderer.buffer.projectionMatrix = camera.getProjectionMatrix();
	renderer.buffer.count = 1;
	// onInit();

	while (!glfwWindowShouldClose(window)) {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("AAA")) {
				if (ImGui::MenuItem("BBB")) {
					;
				}
				if (ImGui::MenuItem("CCC")) {
					;
				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//renderer.render();
		texRenderer.render();

		//onRender(width, height);

		glFlush();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();
	glfwTerminate();
}