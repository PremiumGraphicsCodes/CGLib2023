#pragma once

#include "../Shader/ShaderObject.h"
#include <memory>

namespace Crystal {
	namespace UI {

class Renderer
{
public:
	void build();

private:
	std::unique_ptr<Shader::ShaderObject> shader;
};

	}
}