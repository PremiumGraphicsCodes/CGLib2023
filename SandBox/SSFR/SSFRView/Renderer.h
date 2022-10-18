#pragma once

#include "Crystal/AppBase/IRenderer.h"

#include "../FluidRenderer/ParticleDepthRenderer.h"
#include "../FluidRenderer/SSThicknessRenderer.h"
#include "../FluidRenderer/SSReflectionRenderer.h"
#include "../FluidRenderer/SSFluidRenderer.h"

namespace Crystal {
	namespace UI {

class World;

class Renderer : public Crystal::UI::IRenderer
{
public:
	explicit Renderer(World* world) :
		world(world)
	{}

	void init() override;

	void render(const int width, const int height) override;

private:
	World* world;

	Crystal::Renderer::ParticleDepthRenderer particleDepth;
	Crystal::Renderer::SSThicknessRenderer thickness;
	Crystal::Renderer::SSReflectionRenderer reflection;
	Crystal::Renderer::SSFluidRenderer fluid;
};

	}
}
