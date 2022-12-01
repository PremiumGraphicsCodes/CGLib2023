#pragma once

#include "Crystal/Renderer/Renderer/IRenderer.h"
#include "CGLib/Shader/TextureObject.h"

namespace Crystal {
	namespace Renderer {

class SSAbsorptionRenderer : public IRenderer
{
public:
	struct Buffer {
		Shader::TextureObject* volumeTexture;
	};

	void link() override;

	void render() override;

	Buffer buffer;
};

	}
}