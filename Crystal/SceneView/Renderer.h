#pragma once
#include "World.h"
#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/Renderer/PointRenderer.h"
#include "Crystal/Renderer/LineRenderer.h"
#include "Crystal/Renderer/TriangleRenderer.h"

namespace Crystal{
	namespace UI {

class Renderer : public Crystal::UI::IRenderer
{
public:
	enum class Target
	{
		Main,
		Id,
	};

	explicit Renderer(World* world);

	void setTarget(const Target t) { this->target = t; }

	void init() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

	Crystal::Renderer::PointRenderer* getPointRenderer() { return &point; }

	Crystal::Renderer::LineRenderer* getLineRenderer() { return &line; }

	Crystal::Renderer::TriangleRenderer* getTriangleRenderer() { return &triangle; }

private:
	World* world;
	Target target;
	Crystal::Renderer::PointRenderer point;
	Crystal::Renderer::LineRenderer line;
	Crystal::Renderer::TriangleRenderer triangle;

	void renderMain(const Graphics::Camera& camera, const int width, const int height);

	void renderId(const Graphics::Camera& camera, const int width, const int height);
};

	}
}
