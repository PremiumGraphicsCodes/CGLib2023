#pragma once

#include "../Renderer/TexRenderer.h"

#include "CGLib/Graphics/Camera.h"
#include "IScreenShader.h"

namespace Crystal {
	namespace Renderer {

class TexShader : public IScreenShader
{
public:
	void build() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	Renderer::TexRenderer renderer;
	Shader::TextureObject tex;
};

	}
}