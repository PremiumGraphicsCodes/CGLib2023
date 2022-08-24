#pragma once

#include <memory>
#include "../Shader/ShaderObject.h"

namespace Crystal {
	namespace UI {

class IRenderer
{
public:
	void setShader(std::unique_ptr<Shader::ShaderObject> shader) { this->shader = std::move(shader); }

	virtual void build() = 0;

	virtual void render() = 0;

protected:
	std::unique_ptr<Shader::ShaderObject> shader;

};

	}
}