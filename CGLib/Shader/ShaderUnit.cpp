#include "ShaderUnit.h"

#include <cassert>

using namespace Crystal::Shader;

ShaderUnit::ShaderUnit(const Stage stage) :
	stage(stage)
{}

ShaderUnit::~ShaderUnit()
{
	remove();
}

void ShaderUnit::create()
{
	if (stage == ShaderUnit::Stage::VERTEX) {
		id = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (stage == ShaderUnit::Stage::FRAGMENT) {
		id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else if (stage == ShaderUnit::Stage::GEOMETRY) {
		id = glCreateShader(GL_GEOMETRY_SHADER);
	}
	else if (stage == ShaderUnit::Stage::COMPUTE) {
		id = glCreateShader(GL_COMPUTE_SHADER);
	}
	else {
		assert(false);
	}
}

void ShaderUnit::remove()
{
	if (id != -1) {
		glDeleteShader(id);
	}
}