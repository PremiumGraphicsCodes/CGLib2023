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
	ShaderBuilder();

	void build(const std::string& vsSource, const std::string& fsSource);

	void buildFromFile(const std::string& vsFilePath, const std::string& fsFilePath);

private:
	void compile(const std::string& source, const ShaderUnit::Stage stage);

	void link();

	std::vector< std::unique_ptr<ShaderUnit> > units;

	std::unique_ptr<ShaderObject> shader;

	bool isOk;
	std::string log;
};

	}
}