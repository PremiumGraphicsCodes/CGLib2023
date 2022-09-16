#pragma once

#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/Scene/ParticleSystemScene.h"
#include "Crystal/Scene/WireFrameScene.h"
#include "Crystal/Renderer/PointRenderer.h"
#include "Crystal/Renderer/LineRenderer.h"

#include "Crystal/AppBase/IWorld.h"

namespace Crystal {
	namespace UI {

class World : public Crystal::UI::IWorld
{
public:
};

class Renderer : public Crystal::UI::IRenderer
{
public:
	explicit Renderer(World* world);


	void init() override;

	void addWireFrame();

	void add(Scene::IScene* scene);

	void render(const int width, const int height);

	Crystal::Graphics::Camera* getCamera() { return &camera; }

	Crystal::Renderer::PointRenderer point;
	Crystal::Renderer::LineRenderer line;

private:
	World* world;
	Crystal::Graphics::Camera camera;

	Scene::IScene rootScene;
	//ParticleSystemScene psScene;
	Crystal::Scene::WireFrameScene wfScene;

};

	}
}