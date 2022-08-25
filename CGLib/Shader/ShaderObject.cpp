#include "ShaderObject.h"
//#include "TextureObject.h"

#include <cassert>
#include <stdlib.h>

#include "glew.h"

#include "VertexBufferObject.h"
#include "TextureObject.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

ShaderObject::ShaderObject(void) :
	handle(-1)
{
}

ShaderObject::~ShaderObject(void)
{
	remove();
}

void ShaderObject::create()
{
	handle = glCreateProgram();
}

void ShaderObject::remove()
{
	//glUseProgram(0);
	if (handle != -1) {
		glDeleteProgram(handle);
	}
}

GLuint ShaderObject::findUniformLocation(const std::string& str)
{
	const auto location = glGetUniformLocation(handle, str.c_str());
	assert(location != -1);
	return location;
}

GLuint ShaderObject::findAttribLocation(const std::string& str)
{
	const auto location = glGetAttribLocation(handle, str.c_str());
	assert(location != -1);
	return location;
}

void ShaderObject::bind()
{
	glUseProgram(getHandle());
}

void ShaderObject::unbind()
{
	glUseProgram(0);
}

void ShaderObject::enable(GLenum e)
{
	glEnable(e);
}

void ShaderObject::disable(GLenum e)
{
	glDisable(e);
}

void ShaderObject::drawPoints(const int count)
{
	glDrawArrays(GL_POINTS, 0, count);
}

void ShaderObject::drawLines(const std::vector<unsigned int>& indices)
{
	glDrawElements(GL_LINES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
}

void ShaderObject::drawLines(const int count)
{
	glDrawArrays(GL_LINES, 0, count);
}

void ShaderObject::drawTriangles(const int count)
{
	glDrawArrays(GL_TRIANGLES, 0, count);
}

void ShaderObject::drawTriangles(const std::vector<unsigned int>& indices)
{
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
}

void ShaderObject::drawQuads(const int count)
{
	glDrawArrays(GL_QUADS, 0, count);
}

void ShaderObject::bindOutput(const std::string& name)
{
	auto str = name.c_str();
	glBindFragDataLocation(getHandle(), 0, str);
}

void ShaderObject::bindOutput(const std::string& name, unsigned int number)
{
	auto str = name.c_str();
	glBindFragDataLocation(getHandle(), number, str);
}

void ShaderObject::setLineWidth(const float width)
{
	glLineWidth(width);
}