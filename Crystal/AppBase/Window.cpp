#include "Window.h"

#include "CGLib/Math/Vector2d.h"
#include "CGLib/ThirdParty/glew-2.2.0/include/GL/glew.h"
#include "GLFW/glfw3.h"
#include "Canvas.h"
#include "RendererBase.h"

#include "CGLib/UI/imgui.h"
#include "CGLib/UI/imgui_impl_glfw.h"
#include "CGLib/UI/imgui_impl_opengl3.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

namespace {
	Canvas* canvas;

	void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

	bool isLeftDown;
	bool isRightDown;

	Vector2df toScreenCoord(GLFWwindow* window, const double x, const double y) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		const auto xx = x / (float)width;
		const auto yy = 1.0 - y / (float)height;
		return Vector2df(xx, yy);
	}

	void onMouse(GLFWwindow* window, int button, int action, int mods) {
		if (ImGui::IsMouseHoveringAnyWindow()) {
			return;
		}

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		const auto& coord = toScreenCoord(window, x, y);
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (action == GLFW_PRESS) {
				canvas->onLeftButtonDown(coord);
				isLeftDown = true;
			}
			else if (action == GLFW_RELEASE) {
				canvas->onLeftButtonUp(coord);
				isLeftDown = false;
			}
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			if (action == GLFW_PRESS) {
				canvas->onRightButtonDown(coord);
				isRightDown = true;
			}
			else if (action == GLFW_RELEASE) {
				canvas->onRightButtonUp(coord);
				isRightDown = false;
			}
		}
	}


	void onMouseMove(GLFWwindow* window, double xpos, double ypos)
	{
		const auto& coord = toScreenCoord(window, xpos, ypos);
		if (isLeftDown) {
			canvas->onLeftDragging(coord);
		}
		else if (isRightDown) {
			canvas->onRightDragging(coord);
		}
	}

	void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
	{
		canvas->onWheel(yoffset);
	}
}

Window::Window(const std::string& title, Canvas* canvas, IRenderer* renderer) :
	title(title),
	renderer(renderer)
{
	::canvas = canvas;
}

bool Window::init()
{
	if (!glfwInit()) {
		return false;
	}


	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1280, 720, title.c_str(), NULL, NULL);
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

	glfwSetMouseButtonCallback(window, onMouse);
	glfwSetCursorPosCallback(window, onMouseMove);
	glfwSetScrollCallback(window, onMouseWheel);

	renderer->init();

	return true;
}

void Window::show()
{
	while (!glfwWindowShouldClose(window)) {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar()) {
			for (auto& m : menus) {
				m->show();
			}
			ImGui::EndMainMenuBar();
		}

		for (auto& p : panels) {
			p->show();
		}

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		renderer->render(width, height);
		//world->getRenderer()->render(*world->getCamera()->getCamera(), width, height);

		//const auto animations = world->getAnimations();
		//for (auto& a : animations) {
		//	a->step();
		//}

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