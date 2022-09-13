#include "../../CGLib/Shader/glew.h"

#include "../Scene/ParticleSystemScene.h"
#include "../Scene/WireFrameScene.h"

#include "ParticleSystemPresenter.h"
#include "WireFramePresenter.h"

#include "../../CGLib/UI/imgui.h"
#include "../../CGLib/UI/imgui_impl_glfw.h"
#include "../../CGLib/UI/imgui_impl_opengl3.h"
#include "Crystal/AppBase/Canvas.h"
#include "GLFW/glfw3.h"

#include "Crystal/AppBase/CameraUICtrl.h"

#include <stdio.h>

#include "Renderer.h"

#include <iostream>

#include "CGLib/Math/Vector2d.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;

namespace {
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

#include "Crystal/AppBase/Window.h"

class App : public Crystal::UI::Window
{
public:
	App() :
		Crystal::UI::Window("Hello", &canvas),
		camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1, 10.0),
		cameraUICtrl(&camera)
	{

	}

	void onInit() override
	{
		canvas.setUICtrl(&cameraUICtrl);

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
	Crystal::UI::Canvas canvas;
	Crystal::UI::CameraUICtrl cameraUICtrl;
	Crystal::Graphics::Camera camera;
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