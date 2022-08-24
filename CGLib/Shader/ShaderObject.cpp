#include "ShaderObject.h"
//#include "TextureObject.h"

#include <cassert>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "glew.h"

#include "VertexBufferObject.h"
#include "TextureObject.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

ShaderObject::ShaderObject(void) :
	handle(-1),
	isBuildOk(false)
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

void ShaderObject::findAttribLocation(const std::string& str)
{
	const auto location = glGetAttribLocation(handle, str.c_str());
	assert(location != -1);
	attribMap[str] = location;
}

unsigned int ShaderObject::getAttribLocation(const std::string& str)
{
	assert(attribMap.find(str) != attribMap.end());
	return attribMap[str];
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

void ShaderObject::sendUniform(const GLuint location, const Matrix3df& matrix)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderObject::sendUniform(const GLuint location, const Matrix4df& matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderObject::sendUniform(const GLuint location, const Vector3df& v)
{
	glUniform3fv(location, 1, &v[0]);
}

void ShaderObject::sendUniform(const GLuint location, const int value)
{
	glUniform1i(location, value);
}

void ShaderObject::sendUniform(const GLuint location, const float value)
{
	glUniform1f(location, value);
}

void ShaderObject::sendVertexAttribute1df(const std::string& name, const std::vector<float>& data)
{
	const auto location = getAttribLocation(name);
	glVertexAttribPointer(location, 1, GL_FLOAT, GL_FALSE, 0, data.data());
	//glEnableVertexAttribArray(location);
}

void ShaderObject::sendVertexAttribute2df(const std::string& name, const std::vector<float>& data)
{
	const auto location = getAttribLocation(name);
	glVertexAttribPointer(getAttribLocation(name), 2, GL_FLOAT, GL_FALSE, 0, data.data());
}

void ShaderObject::sendVertexAttribute3df(const std::string& name, const std::vector<float>& data)
{
	const auto location = getAttribLocation(name);
	glVertexAttribPointer(getAttribLocation(name), 3, GL_FLOAT, GL_FALSE, 0, data.data());
	//	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
}

void ShaderObject::sendVertexAttribute4df(const std::string& name, const std::vector<float>& data)
{
	const auto location = getAttribLocation(name);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 0, data.data());
	//glEnableVertexAttribArray(location);
}

void ShaderObject::sendVertexAttribute1di(const std::string& name, const std::vector<int>& data)
{
	const auto location = getAttribLocation(name);
	glVertexAttribIPointer(getAttribLocation(name), 1, GL_INT, 0, data.data());
	//	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
}

void ShaderObject::sendVertexAttribute1di(const std::string& name, const VertexBufferObject& vbo)
{
	vbo.bind();
	auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
	glVertexAttribIPointer(location, 1, GL_INT, 0, (GLvoid*)0);
	vbo.unbind();
}

void ShaderObject::sendVertexAttribute1df(const std::string& name, const VertexBufferObject& vbo)
{
	vbo.bind();
	auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void ShaderObject::sendVertexAttribute2df(const std::string& name, const VertexBufferObject& vbo)
{
	vbo.bind();
	auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void ShaderObject::sendVertexAttribute3df(const std::string& name, const VertexBufferObject& vbo)
{
	vbo.bind();
	auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void ShaderObject::sendVertexAttribute4df(const std::string& name, const VertexBufferObject& vbo)
{
	vbo.bind();
	auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void ShaderObject::enableVertexAttribute(const std::string& name)
{
	const auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
}

void ShaderObject::disableVertexAttribute(const std::string& name)
{
	const auto location = getAttribLocation(name);
	glDisableVertexAttribArray(location);
}

void ShaderObject::enableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void ShaderObject::disableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}

void ShaderObject::enablePointSprite()
{
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void ShaderObject::disablePointSprite()
{
	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
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