#pragma once

#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/Scene/ParticleSystemScene.h"
#include "Crystal/Scene/WireFrameScene.h"
#include "Crystal/Renderer/PointRenderer.h"
#include "Crystal/Renderer/LineRenderer.h"

namespace Crystal {
	namespace UI {

class Renderer : public Crystal::UI::IRenderer
{
public:
	explicit Renderer();


	void init() override;

	void addWireFrame();

	void add(Scene::IScene* scene);

	void render(const int width, const int height);

	Crystal::Graphics::Camera* getCamera() { return &camera; }

	Crystal::Renderer::PointRenderer point;
	Crystal::Renderer::LineRenderer line;

private:

	Crystal::Graphics::Camera camera;

	Scene::IScene rootScene;
	//ParticleSystemScene psScene;
	Crystal::Scene::WireFrameScene wfScene;

};

	}
}