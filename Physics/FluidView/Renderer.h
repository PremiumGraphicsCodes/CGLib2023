#pragma once
#include "World.h"
#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/Renderer/Renderer/PointRenderer.h"

namespace Crystal{
	namespace UI {

class Renderer : public Crystal::UI::IRenderer
{
public:
	explicit Renderer(World* world) :
		world(world)
	{}

	void init() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

	Crystal::Renderer::PointRenderer* getPointRenderer() { return &point; }

	//Crystal::Renderer::LineRenderer* getLineRenderer() { return &line; }

	//Crystal::Renderer::TriangleRenderer* getTriangleRenderer() { return &triangle; }

private:
	World* world;

	Crystal::Renderer::PointRenderer point;
	//Crystal::Renderer::LineRenderer line;
	//Crystal::Renderer::TriangleRenderer triangle;
};

	}
}
