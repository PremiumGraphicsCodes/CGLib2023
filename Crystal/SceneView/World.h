#pragma once

#include "Crystal/AppBase/WorldBase.h"

#include "ParticleSystem.h"

namespace Crystal {
	namespace UI {
		class Renderer;

class World : public Crystal::UI::WorldBase
{
public:
	void setRenderer(Renderer* renderer) { this->renderer = renderer; }

	void addParticleSystem(std::unique_ptr<Shape::ParticleSystem>&& particleSystem);

private:
	 Renderer* renderer;
};

	}
}
