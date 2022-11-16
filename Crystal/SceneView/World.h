#pragma once

#include "Crystal/AppBase/WorldBase.h"

#include "ParticleSystem.h"
#include "WireFrame.h"
#include <memory>

namespace Crystal {
	namespace UI {
		class Renderer;

class World : public Crystal::UI::WorldBase
{
public:
	void setRenderer(Renderer* renderer) { this->renderer = renderer; }

	void addParticleSystem(std::unique_ptr<Shape::ParticleSystem>&& particleSystem);

	void addWireFrame(std::unique_ptr<Shape::WireFrame>&& wireFrame);

	const std::vector<std::unique_ptr<Scene::IPresenter>>& getPresenters() { return presenters; }

private:
	 Renderer* renderer;
	 std::vector<std::unique_ptr<Scene::IPresenter>> presenters;
};

	}
}
