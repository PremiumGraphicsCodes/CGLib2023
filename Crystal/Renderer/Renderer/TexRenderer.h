#pragma once

#include "IRenderer.h"
#include "CGLib/Shader/TextureObject.h"

namespace Crystal {
	namespace Renderer {

class TexRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::TextureObject* tex;
	};

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}