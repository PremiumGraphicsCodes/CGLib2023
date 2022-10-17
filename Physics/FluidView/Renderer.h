#pragma once
#include "World.h"
#include "Crystal/AppBase/RendererBase.h"
#include "../FluidRenderer/SSFR.h"
#include "../FluidRenderer/ParticleDepthRenderer.h"
#include "../FluidRenderer/ThicknessRenderer.h"

namespace Crystal{
	namespace UI {

		class Renderer : public Crystal::UI::RendererBase
		{
		public:
			explicit Renderer(World* world) :
				RendererBase(world)
			{}

			void onInit() override;

			Crystal::Renderer::PointRenderer* getPointRenderer() { return &point; }

			Crystal::Renderer::LineRenderer* getLineRenderer() { return &line; }

			Crystal::Renderer::TriangleRenderer* getTriangleRenderer() { return &triangle; }

		private:
			Crystal::Renderer::PointRenderer point;
			Crystal::Renderer::LineRenderer line;
			Crystal::Renderer::TriangleRenderer triangle;

			Crystal::Renderer::SSFRenderer ssfr;
			Crystal::Renderer::ParticleDepthRenderer particleDepth;
			Crystal::Renderer::ThicknessRenderer thickness;
		};
	}
}
