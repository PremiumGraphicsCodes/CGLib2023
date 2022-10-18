#pragma once

#include "Crystal/AppBase/RendererBase.h"

namespace Crystal {
	namespace UI {

class Renderer : public IRenderer
{
public:
	void init() override {}

	void render(const int width, const int height) override {}
};
	}
}