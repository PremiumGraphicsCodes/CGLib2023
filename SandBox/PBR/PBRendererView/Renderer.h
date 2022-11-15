#pragma once

#include "Crystal/AppBase/IRenderer.h"

#include "DFPolygonShader.h"
#include "IBLShader.h"
#include "PBLightShader.h"

namespace Crystal {
	namespace UI {
		class World;

class Renderer : public IRenderer
{
public:
	enum Target {
		DFPolygon,
		IBL,
		PBLight,
	};

	explicit Renderer(World* world) :
		world(world)
	{}

	void init() override;

	void setTarget(const Target target);

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	World* world;
	Crystal::Renderer::IScreenShader* active;
	Crystal::Renderer::DFPolygonShader polygon;
	Crystal::Renderer::IBLShader ibl;
	Crystal::Renderer::PBLightShader pbLight;
};
	}
}