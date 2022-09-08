#include "../../CGLib/Shader/glew.h"

#include "../Scene/ParticleSystemScene.h"
#include "../Scene/WireFrameScene.h"

#include "ParticleSystemPresenter.h"
#include "WireFramePresenter.h"

#include "../../CGLib/UI/imgui.h"
#include "../../CGLib/UI/imgui_impl_glfw.h"
#include "../../CGLib/UI/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

#include <stdio.h>

#include "Renderer.h"

#include <iostream>

#include "CGLib/Math/Vector2d.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;

namespace {

	void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

	bool isLeftDown;
	bool isRightDown;

	Camera camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1, 10.0);

	IScene scene;


	Vector2df toScreenCoord(GLFWwindow* window, const double x, const double y) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		const auto xx = x / (float)width;
		const auto yy = 1.0 - y / (float)height;
		return Vector2df(xx, yy);
	}

	Vector2df prevCoord(0, 0);

	void onMouse(GLFWwindow* window, int button, int action, int mods) {
		if (ImGui::IsMouseHoveringAnyWindow()) {
			return;
		}

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		const auto& coord = toScreenCoord(window, x, y);
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (action == GLFW_PRESS) {
				prevCoord = coord;
				//canvas->onLeftButtonDown(coord);
				isLeftDown = true;
			}
			else if (action == GLFW_RELEASE) {
				//canvas->onLeftButtonUp(coord);
				isLeftDown = false;
			}
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			if (action == GLFW_PRESS) {
				prevCoord = coord;
				//canvas->onRightButtonDown(coord);
				isRightDown = true;
			}
			else if (action == GLFW_RELEASE) {
				//canvas->onRightButtonUp(coord);
				isRightDown = false;
			}
		}
	}


	void onMouseMove(GLFWwindow* window, double xpos, double ypos)
	{
		const auto& coord = toScreenCoord(window, xpos, ypos);
		if (isLeftDown) {
			const auto diff = (coord - prevCoord) * 1.0f;
			camera.setEye(camera.getEye() + Vector3df(diff, 0.0));
			camera.setTarget(camera.getTarget() + Vector3df(diff, 0.0));
			prevCoord = coord;
			//canvas->onLeftDragging(coord);
		}
		else if (isRightDown) {
			const auto diff = prevCoord - coord;
			//const auto bb = world->getBoundingBox();
			const auto scale = 1.0;//glm::distance(bb.getMin(), bb.getMax()) * 0.1;

			const auto& matrix = camera.getRotationMatrix();
			const auto v = glm::transpose(Matrix3dd(matrix)) * Vector3dd(diff, 0.0);

			{
				const Vector3df t = v;
				const auto& eye = camera.getEye();
				const auto& target = camera.getTarget();
				const auto& up = camera.getUp();
				camera.lookAt(eye + t, target, up);
			}

			prevCoord = coord;
		}
	}

	struct Particle : public IParticle
	{
	public:
		Particle(const Vector3df& p) {
			this->pos = p;
		}

		Vector3df getPosition() const override {
			return pos;
		}

	private:
		Vector3df pos;
	};

	struct Vertex : public IVertex
	{
	public:
		explicit Vertex(const Vector3df& p) : pos(p) {
		}

		Vector3df getPosition() const override {
			return pos;
		}

	private:
		Vector3df pos;
	};
}

#include "CGLib/UI/Window.h"

class App : public Crystal::UI::Window
{
public:
	App() :
		Crystal::UI::Window("Hello")
	{
	}

	void onInit() override
	{
		renderer.build();

		psScene.add(new Particle(Vector3df(0, 0, 0)));

		this->presenter = std::make_unique<Crystal::UI::ParticleSystemPresenter>(&psScene, &renderer.point);
		presenter->build();
		presenter->send();

		wfScene.add(new Vertex(Vector3df(0, 0, 0)));
		wfScene.add(new Vertex(Vector3df(1, 0, 0)));
		wfScene.addIndex(0);
		wfScene.addIndex(1);

		this->wfPresenter = std::make_unique<Crystal::UI::WireFramePresenter>(&wfScene, &renderer.line);
		wfPresenter->build();
		wfPresenter->send();

		auto window = getGLFWWindow();
		glfwSetMouseButtonCallback(window, onMouse);
		glfwSetCursorPosCallback(window, onMouseMove);

	}

	void onRender()
	{
		int width, height;
		auto window = getGLFWWindow();
		glfwGetWindowSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//presenter.render(camera);
		wfPresenter->render(camera);

	}

private:
	Crystal::UI::Renderer renderer;
	ParticleSystemScene psScene;
	WireFrameScene wfScene;

	std::unique_ptr<Crystal::UI::ParticleSystemPresenter> presenter;
	std::unique_ptr<Crystal::UI::WireFramePresenter> wfPresenter;
};

int main() {
	App app;
	app.init();

	app.show();
}