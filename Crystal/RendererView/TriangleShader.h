#pragma once

#include "../Renderer/TriangleRenderer.h"

#include "CGLib/Graphics/Camera.h"
#include "IScreenShader.h"

namespace Crystal {
	namespace Renderer {

class TriangleShader : public IScreenShader
{
public:
	void build() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	Renderer::TriangleRenderer renderer;
	Shader::VertexBufferObject positions;
	Shader::VertexBufferObject colors;
};

	}
}