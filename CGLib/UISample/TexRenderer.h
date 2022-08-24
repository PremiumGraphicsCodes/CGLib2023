#pragma once

#include "IRenderer.h"
#include "../Math/Matrix4d.h"
#include "../Shader/TextureObject.h"
#include "../Shader/ShaderObject.h"
#include <memory>

namespace Crystal {
	namespace UI {

class TexRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::TextureObject* tex;
	};

	void build() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}