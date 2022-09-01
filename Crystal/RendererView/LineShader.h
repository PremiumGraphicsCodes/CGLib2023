#pragma once

#include "../Renderer/LineRenderer.h"

#include "CGLib/Graphics/Camera.h"
#include "IScreenShader.h"

namespace Crystal {
	namespace Renderer {

		class LineShader : public IScreenShader
		{
		public:
			void build() override;

			void render(const Graphics::Camera& camera, const int width, const int height) override;

		private:
			Renderer::LineRenderer renderer;
			Shader::VertexBufferObject positions;
			Shader::VertexBufferObject colors;
			Shader::VertexBufferObject sizes;
		};

	}
}