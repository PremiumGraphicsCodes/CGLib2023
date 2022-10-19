#pragma once

#include "CGLib/Graphics/Camera.h"

namespace Crystal {
	namespace Renderer {

		class IScreenShader
		{
		public:
			virtual ~IScreenShader() = default;

			virtual void build() = 0;

			virtual void render(const Graphics::Camera& camera, const int width, const int height) = 0;
		};

	}
}
