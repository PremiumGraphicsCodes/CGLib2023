#pragma once

#include "Crystal/Renderer/Renderer/IRenderer.h"
#include "CGLib/Shader/TextureObject.h"

namespace Crystal {
	namespace Renderer {

class SSNormalRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Math::Matrix4dd projectionMatrix;
		Shader::TextureObject* depthTexture;
	};

	void link() override;

	void render() override;

	Buffer buffer;
private:
};

	}
}