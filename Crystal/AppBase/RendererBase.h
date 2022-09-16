#pragma once

#include "CGLib/Graphics/Camera.h"

#include "Crystal/Renderer/PointRenderer.h"
#include "Crystal/Renderer/LineRenderer.h"
#include "Crystal/Renderer/TriangleRenderer.h"

#include <memory>

namespace Crystal {
	namespace UI {
		class IWorld;

class IRenderer
{
public:
	~IRenderer() = default;

	virtual void init() = 0;

	virtual void render(const int width, const int height) = 0;
};

class RendererBase : public IRenderer
{
public:
	RendererBase(IWorld* world);

	~RendererBase() = default;

	void init() override;

	virtual void onInit() = 0;

	virtual void render(const int width, const int height) override;

	Graphics::Camera* getCamera() { return &camera; }

	Renderer::PointRenderer* getPointRenderer() { return &point; }

	Renderer::LineRenderer* getLineRenderer() { return &line; }

	Renderer::TriangleRenderer* getTriangleRenderer() { return &triangle; }

private:
	IWorld* world;
	Graphics::Camera camera;
	Renderer::PointRenderer point;
	Renderer::LineRenderer line;
	Renderer::TriangleRenderer triangle;
};


	}
}