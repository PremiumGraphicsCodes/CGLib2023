#pragma once

#include "../Math/Matrix4d.h"
#include "../Shader/TextureObject.h"
#include "../Shader/ShaderObject.h"
#include <memory>

namespace Crystal {
	namespace UI {

class TexRenderer
{
public:
	struct Buffer
	{
		Shader::TextureObject* tex;
	};

	void build();

	void render();

	Buffer buffer;

private:
	std::unique_ptr<Shader::ShaderObject> shader;
};

	}
}