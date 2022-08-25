#include "VertexAttribute.h"

using namespace Crystal::Shader;

void VertexAttribute::sendVertexAttribute1df(const std::vector<float>& data)
{
	glVertexAttribPointer(location, 1, GL_FLOAT, GL_FALSE, 0, data.data());
	//glEnableVertexAttribArray(location);
}

void VertexAttribute::sendVertexAttribute2df(const std::vector<float>& data)
{
	glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, data.data());
}

void VertexAttribute::sendVertexAttribute3df(const std::vector<float>& data)
{
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, data.data());
}

void VertexAttribute::sendVertexAttribute4df(const std::vector<float>& data)
{
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 0, data.data());
}

void VertexAttribute::sendVertexAttribute1di(const std::vector<int>& data)
{
	glVertexAttribIPointer(location, 1, GL_INT, 0, data.data());
}

void VertexAttribute::sendVertexAttribute1di(const VertexBufferObject& vbo)
{
	vbo.bind();
	glEnableVertexAttribArray(location);
	glVertexAttribIPointer(location, 1, GL_INT, 0, (GLvoid*)0);
	vbo.unbind();
}

void VertexAttribute::sendVertexAttribute1df(const VertexBufferObject& vbo)
{
	vbo.bind();
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void VertexAttribute::sendVertexAttribute2df(const VertexBufferObject& vbo)
{
	vbo.bind();
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void VertexAttribute::sendVertexAttribute3df(const VertexBufferObject& vbo)
{
	vbo.bind();
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void VertexAttribute::sendVertexAttribute4df(const VertexBufferObject& vbo)
{
	vbo.bind();
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void VertexAttribute::enableVertexAttribute()
{
	glEnableVertexAttribArray(location);
}

void VertexAttribute::disableVertexAttribute()
{
	glDisableVertexAttribArray(location);
}
