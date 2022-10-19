#pragma once

#include "Crystal/Renderer/IRenderer.h"
#include "CGLib/Shader/TextureObject.h"

namespace Crystal {
	namespace Renderer {

class BilateralFilterRenderer : public IRenderer
{
public:
	struct Buffer {
		Shader::TextureObject* texture;
	};

	void link() override;

	void render() override;

	Buffer buffer;
};

	}
}