#pragma once

#include "CGLib/Graphics/Camera.h"
#include "../Renderer/SkyBoxRenderer.h"
#include "IScreenShader.h"

namespace Crystal {
	namespace Renderer {

class SkyBoxShader : public IScreenShader
{
public:
	void build() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	Renderer::SkyBoxRenderer skyBoxRenderer;
	std::unique_ptr<Shader::CubeMapTextureObject> cubeMapTexture;
};

	}
}