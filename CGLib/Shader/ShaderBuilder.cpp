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

void ShaderBuilder::build()
{
	shader = std::make_unique<ShaderObject>();
	shader->create();

	vertexShader.create();
	compile(fsSource, vertexShader.getHandle());

	fragmentShader.create();
	compile(vsSource, fragmentShader.getHandle());
}
	
bool ShaderBuilder::compile(const std::string& source, const GLuint id)
{
	const GLchar* strPtr[1];
	strPtr[0] = source.c_str();
	glShaderSource(id, 1, strPtr, NULL);

	glCompileShader(id);

	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	GLchar infoLog[2048];
	glGetShaderInfoLog(id, 2048, NULL, infoLog);
	log += infoLog;
	//assert( success != 0 );
	//return ( success != 0 );

	if (success == 0) {
		return false;
	}

	if (glGetError() != GL_NO_ERROR) {
		return false;
	}
	return true;

}

bool ShaderBuilder::link()
{
	assert(glGetError() == GL_NO_ERROR);

	glAttachShader(shader->getHandle(), vertexShader.getHandle());
	glAttachShader(shader->getHandle(), fragmentShader.getHandle());

	GLint success;
	glLinkProgram(shader->getHandle());
	glGetProgramiv(shader->getHandle(), GL_LINK_STATUS, &success);

	GLchar infoLog[2048];
	glGetProgramInfoLog(shader->getHandle(), 2048, NULL, infoLog);
	log += infoLog;

	if (success == 0) {
		return false;
	}

	assert(glGetError() == GL_NO_ERROR);

	return true;
}
