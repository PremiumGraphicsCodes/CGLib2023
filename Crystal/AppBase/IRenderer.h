#pragma once

#include "CGLib/Graphics/Camera.h"

#include "Crystal/Renderer/PointRenderer.h"
#include "Crystal/Renderer/LineRenderer.h"

#include <memory>

namespace Crystal {
	namespace UI {

class IRenderer
{
public:
	IRenderer() = default;

	void init();

	virtual void onInit() = 0;

	virtual void render(const int width, const int height) = 0;

	Crystal::Renderer::PointRenderer point;
	Crystal::Renderer::LineRenderer line;

};


	}
}