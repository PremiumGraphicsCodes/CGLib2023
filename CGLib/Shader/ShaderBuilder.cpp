#include "ShaderBuilder.h"

using namespace Crystal::Shader;

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
	remove();
}

void VertexShader::create()
{
	id = glCreateShader(GL_VERTEX_SHADER);
}

void VertexShader::remove()
{
	if (id != -1) {
		glDeleteShader(id);
	}
}

FragmentShader::FragmentShader()
{
	id = glCreateShader(GL_FRAGMENT_SHADER);
}

FragmentShader::~FragmentShader()
{
	if (id != -1) {
		glDeleteShader(id);
	}
}

void FragmentShader::create()
{
	id = glCreateShader(GL_VERTEX_SHADER);
}

void FragmentShader::remove()
{
	if (id != -1) {
		glDeleteShader(id);
	}
}

GeometryShader::GeometryShader()
{
}

GeometryShader::~GeometryShader()
{
	remove();
}

void GeometryShader::create()
{
	id = glCreateShader(GL_GEOMETRY_SHADER);
}

void GeometryShader::remove()
{
	if (id != -1) {
		glDeleteShader(id);
	}
}

ComputeShader::ComputeShader()
{
}

ComputeShader::~ComputeShader()
{
	remove();
}

void ComputeShader::create()
{
	id = glCreateShader(GL_COMPUTE_SHADER);
}

void ComputeShader::remove()
{
	if (id != -1) {
		glDeleteShader(id);
	}
}