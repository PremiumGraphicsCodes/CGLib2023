#pragma once

#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/Renderer/PointRenderer.h"

namespace Crystal {
	namespace UI {
		class World;

class Renderer : public IRenderer
{
public:
	explicit Renderer(World* world) :
		world(world)
	{}

	void init() override;

	void render(const int width, const int height) override;

	Crystal::Renderer::PointRenderer* getPointRenderer() { return &point; }

private:
	World* world;
	Crystal::Renderer::PointRenderer point;
};

	}
}