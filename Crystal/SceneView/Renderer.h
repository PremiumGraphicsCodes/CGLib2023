#pragma once
#include "World.h"
#include "Crystal/AppBase/RendererBase.h"
#include "Crystal/Renderer/PointRenderer.h"
#include "Crystal/Renderer/LineRenderer.h"
#include "Crystal/Renderer/TriangleRenderer.h"

namespace Crystal{
	namespace UI {

class Renderer : public Crystal::UI::IRenderer
{
public:
	explicit Renderer(World* world) :
		world(world)
	{}

	void init() override;

	void render(const int width, const int height) override;

	Crystal::Renderer::PointRenderer* getPointRenderer() { return &point; }

	Crystal::Renderer::LineRenderer* getLineRenderer() { return &line; }

	Crystal::Renderer::TriangleRenderer* getTriangleRenderer() { return &triangle; }

private:
	World* world;
	Crystal::Renderer::PointRenderer point;
	Crystal::Renderer::LineRenderer line;
	Crystal::Renderer::TriangleRenderer triangle;
};

	}
}
