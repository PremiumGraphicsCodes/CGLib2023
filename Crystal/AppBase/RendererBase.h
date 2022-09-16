#pragma once

#include "CGLib/Graphics/Camera.h"

#include "Crystal/Renderer/PointRenderer.h"
#include "Crystal/Renderer/LineRenderer.h"

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

	Crystal::Graphics::Camera* getCamera() { return &camera; }

	Crystal::Renderer::PointRenderer point;
	Crystal::Renderer::LineRenderer line;

private:
	IWorld* world;
	Crystal::Graphics::Camera camera;

};


	}
}