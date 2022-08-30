#pragma once

#include "../Renderer/PointRenderer.h"

#include "CGLib/Graphics/Camera.h"
#include "IScreenShader.h"

namespace Crystal {
	namespace Renderer {

		class PointShader : public IScreenShader
		{
		public:
			void build() override;

			void render(const Graphics::Camera& camera, const int width, const int height) override;

		private:
			Renderer::PointRenderer renderer;
			Shader::VertexBufferObject positions;
			Shader::VertexBufferObject colors;
			Shader::VertexBufferObject sizes;
		};

	}
}