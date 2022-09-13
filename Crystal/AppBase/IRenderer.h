#pragma once

#include "CGLib/Graphics/Camera.h"
#include <memory>

namespace Crystal {
	namespace UI {

class ISRenderer
{
public:
	ISRenderer() = default;

	virtual void init() = 0;

	virtual void render(const int width, const int height) = 0;
};


	}
}