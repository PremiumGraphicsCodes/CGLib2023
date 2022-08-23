#pragma once

#include "IGLObject.h"
#include "glew.h"
#include "ShaderObject.h"
#include <string>
#include <memory>

namespace Crystal {
	namespace Shader {

class ShaderBuilder
{
public:
	void build();

private:
	void compile(const std::string& source, const ShaderUnit::Stage stage);

	bool link();

	std::vector< std::unique_ptr<ShaderUnit> > units;

	std::unique_ptr<ShaderObject> shader;

	bool isOk;
	std::string log;
};

	}
}