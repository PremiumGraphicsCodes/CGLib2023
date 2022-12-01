#pragma once

#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/Renderer/Renderer/PointRenderer.h"
#include "Crystal/Renderer/Renderer/TriangleRenderer.h"

namespace Crystal {
	namespace UI {
		class World;

class Renderer : public IRenderer
{
public:
	explicit Renderer(World* world);

	void init() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

	Crystal::Renderer::PointRenderer* getPointRenderer() { return &point; }

	Crystal::Renderer::TriangleRenderer* getTriangleRenderer() { return &triangle; }

private:
	World* world;
	Crystal::Renderer::PointRenderer point;
	Crystal::Renderer::TriangleRenderer triangle;
};

	}
}