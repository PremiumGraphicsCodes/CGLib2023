#pragma once

#include "../PBRenderer/PBLightRenderer.h"

#include "CGLib/Graphics/Camera.h"
#include "IScreenShader.h"

namespace Crystal {
	namespace Renderer {

class PBLightShader : public IScreenShader
{
public:
	void build() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	Renderer::PBLightRenderer renderer;
	Shader::VertexBufferObject positions;
	Shader::VertexBufferObject normals;
};

	}
}