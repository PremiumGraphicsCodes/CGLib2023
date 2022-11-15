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

	void init();

	void render(const Graphics::Camera& camera, const int width, const int height) override
	{
	}

private:
	World* world;
	Crystal::Renderer::PointRenderer point;
};

	}
}