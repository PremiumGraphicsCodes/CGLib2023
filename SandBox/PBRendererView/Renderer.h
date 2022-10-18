#pragma once

#include "Crystal/AppBase/IRenderer.h"

#include "DFPolygonShader.h"
#include "IBLShader.h"
#include "PBLightShader.h"

namespace Crystal {
	namespace UI {

class Renderer : public IRenderer
{
public:
	void init() override;

	void render(const int width, const int height) override {}

private:
	Crystal::Renderer::DFPolygonShader polygon;
	Crystal::Renderer::IBLShader ibl;
	Crystal::Renderer::PBLightShader pbLight;
};
	}
}