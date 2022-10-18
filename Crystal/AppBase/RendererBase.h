#pragma once

#include "CGLib/Graphics/Camera.h"

#include "Crystal/Renderer/PointRenderer.h"
#include "Crystal/Renderer/LineRenderer.h"
#include "Crystal/Renderer/TriangleRenderer.h"

#include <memory>

namespace Crystal {
	namespace UI {
		class WorldBase;

class IRenderer
{
public:
	~IRenderer() = default;

	virtual void init() = 0;

	virtual void render(const int width, const int height) = 0;
};

	}
}