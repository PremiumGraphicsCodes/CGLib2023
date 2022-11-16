#pragma once
#include "World.h"
#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/Renderer/PointRenderer.h"
#include "Crystal/Renderer/LineRenderer.h"
#include "Crystal/Renderer/TriangleRenderer.h"

namespace Crystal {
	namespace UI {

class SelectionRenderer : public Crystal::UI::IRenderer
{
public:
	explicit SelectionRenderer(World* world) :
		world(world)
	{}

	void init() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	World* world;
	Crystal::Renderer::PointRenderer point;
	Crystal::Renderer::LineRenderer line;
	Crystal::Renderer::TriangleRenderer triangle;
};

	}
}
