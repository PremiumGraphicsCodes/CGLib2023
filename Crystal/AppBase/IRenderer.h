#pragma once

#include "CGLib/Graphics/Camera.h"

namespace Crystal {
	namespace UI {

class IRenderer
{
public:
	~IRenderer() = default;

	virtual void init() = 0;

	virtual void render(const Graphics::Camera& camera, const int width, const int height) = 0;
};

	}
}