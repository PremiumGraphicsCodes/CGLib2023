#pragma once

#include "Crystal/Renderer/IRenderer.h"
#include "CGLib/Shader/TextureObject.h"

namespace Crystal {
	namespace Renderer {

class SSCompositeRenderer : public IRenderer
{
public:
	struct Buffer {
		Shader::TextureObject* depthTexture;
		Shader::TextureObject* surfaceTexture;
		Shader::TextureObject* reflectionTexture;
		Shader::TextureObject* refractionTexture;
		Shader::TextureObject* absorptionTexture;
		Shader::TextureObject* backGroundTexture;
	};

	void link() override;

	void render() override;

	Buffer buffer;
private:
};

	}
}