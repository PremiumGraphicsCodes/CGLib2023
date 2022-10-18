#pragma once

#include "Crystal/AppBase/IRenderer.h"

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