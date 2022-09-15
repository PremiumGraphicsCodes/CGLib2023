﻿#include "../../CGLib/Shader/glew.h"

#include "../Scene/ParticleSystemScene.h"
#include "../Scene/WireFrameScene.h"

#include "ParticleSystemPresenter.h"
#include "WireFramePresenter.h"
#include "Crystal/AppBase/Canvas.h"
#include "GLFW/glfw3.h"

#include "Crystal/AppBase/CameraUICtrl.h"
#include "Crystal/AppBase/Panel.h"

#include <stdio.h>

#include "../Renderer/PointRenderer.h"
#include "../Renderer/LineRenderer.h"


#include <iostream>

#include "CGLib/Math/Vector2d.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;
using namespace Crystal::UI;

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
#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/AppBase/MenuItem.h"
#include "CGLib/Shader/ShaderBuilder.h"

class World
{
public:
	void init()
	{
		psScene.add(new Particle(Vector3df(0, 0, 0)));

		wfScene.add(new Vertex(Vector3df(0, 0, 0)));
		wfScene.add(new Vertex(Vector3df(1, 0, 0)));
		wfScene.addIndex(0);
		wfScene.addIndex(1);
	}

public:
	ParticleSystemScene psScene;
	WireFrameScene wfScene;
};

class Renderer : public Crystal::UI::IRenderer
{
public:
	explicit Renderer(World* world) :
		world(world),
		camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1, 10.0)
	{}

	void init() override
	{
		Crystal::Shader::ShaderBuilder builder;
		builder.buildFromFile("../GLSL/Point.vs", "../GLSL/Point.fs");
		point.setShader(builder.getShader());
		point.link();

		builder.buildFromFile("../GLSL/Line.vs", "../GLSL/Line.fs");
		line.setShader(builder.getShader());
		line.link();

		this->presenter = std::make_unique<Crystal::UI::ParticleSystemPresenter>(&world->psScene, &point);
		presenter->build();
		presenter->send();

		this->wfPresenter = std::make_unique<Crystal::UI::WireFramePresenter>(&world->wfScene, &line);
		wfPresenter->build();
		wfPresenter->send();

	}

	void render(const int width, const int height) override
	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//presenter.render(camera);
		wfPresenter->render(camera);

	}

	Crystal::Graphics::Camera* getCamera() { return &camera; }

private:
	World* world;
	std::unique_ptr<Crystal::UI::ParticleSystemPresenter> presenter;
	std::unique_ptr<Crystal::UI::WireFramePresenter> wfPresenter;

	Crystal::Renderer::PointRenderer point;
	Crystal::Renderer::LineRenderer line;

	Crystal::Graphics::Camera camera;
};

class ParticleSystemMenu : public IMenu
{
public:
	explicit ParticleSystemMenu(const std::string& name) :
		IMenu(name)
	{
		add(new MenuItem("Sphere", []() {}));

		/*
			add(new MenuItem("SpaceHash", [world, canvas, control]() {
				control->setWindow(new SpaceHashView("SpaceHash", world, canvas));
				}));
				*/
	}
};

/*
class ControlPanel : public IWindow
{
public:
	explicit ControlPanel(const std::string& name) :
		IWindow(name)
	{
	}

	void onShow() override
	{

	}
};
*/

int main() {
	World world;
	world.init();

	auto renderer = std::make_unique<Renderer>(&world);
	auto uiCtrl = std::make_unique<Crystal::UI::CameraUICtrl>(renderer->getCamera());

	Crystal::UI::Canvas canvas(std::move(uiCtrl), std::move(renderer));
	Crystal::UI::Window app("Hello", &canvas);
	app.init();

	app.add(new ParticleSystemMenu("ParticleSystem"));
	app.add(new Panel("Control"));
	
	app.show();
}