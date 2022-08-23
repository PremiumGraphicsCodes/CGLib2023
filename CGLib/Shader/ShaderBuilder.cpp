#include "ShaderBuilder.h"

using namespace Crystal::Shader;

void ShaderBuilder::compile(const std::string& source, const ShaderUnit::Stage stage)
{
	auto unit = std::make_unique<ShaderUnit>(stage);
	unit->create();

	const GLchar* strPtr[1];
	strPtr[0] = source.c_str();
	glShaderSource(unit->getHandle(), 1, strPtr, NULL);

	glCompileShader(unit->getHandle());

	GLint success;
	glGetShaderiv(unit->getHandle(), GL_COMPILE_STATUS, &success);
	GLchar infoLog[2048];
	glGetShaderInfoLog(unit->getHandle(), 2048, NULL, infoLog);
	log += infoLog;
	//assert( success != 0 );
	//return ( success != 0 );

	if (success == 0) {
		isOk = false;
	}

	if (glGetError() != GL_NO_ERROR) {
		isOk = false;
	}

	units.push_back(std::move(unit));
}
	
bool ShaderBuilder::link()
{
	return false;
}
