#include "ShaderBuilder.h"

#include <fstream>

using namespace Crystal::Shader;

namespace {
	std::string getStrFromFile(const std::string& file)
	{
		std::ifstream stream(file);
		if (stream.fail()) {
			assert(false);
			return "";
		}
		std::istreambuf_iterator<char> it(stream);
		std::istreambuf_iterator<char> last;
		return std::string(it, last);
	}
}

ShaderBuilder::ShaderBuilder() :
	isOk(true)
{
}

void ShaderBuilder::build(const std::string& vsSource, const std::string& fsSource)
{
	units.clear();

	shader = std::make_unique<ShaderObject>();
	shader->create();

	compile(vsSource, ShaderUnit::Stage::VERTEX);
	compile(fsSource, ShaderUnit::Stage::FRAGMENT);

	link();
}

void ShaderBuilder::buildFromFile(const std::string& vsFilePath, const std::string& fsFilePath)
{
	const auto vsSource = ::getStrFromFile(vsFilePath);
	const auto fsSource = ::getStrFromFile(fsFilePath);
	build(vsSource, fsSource);
}

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
	
void ShaderBuilder::link()
{
	for (const auto& s : units) {
		glAttachShader(shader->getHandle(), s->getHandle());
	}

	GLint success;
	glLinkProgram(shader->getHandle());
	glGetProgramiv(shader->getHandle(), GL_LINK_STATUS, &success);

	GLchar infoLog[2048];
	glGetProgramInfoLog(shader->getHandle(), 2048, NULL, infoLog);
	log += infoLog;

	if (success == 0) {
		isOk = false;
	}

	assert(glGetError() == GL_NO_ERROR);
}
