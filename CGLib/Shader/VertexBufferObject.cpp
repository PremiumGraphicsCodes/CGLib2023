#include "VertexBufferObject.h"

#include "glew.h"
#include <cassert>

using namespace Crystal::Shader;

VertexBufferObject::VertexBufferObject() :
	handle(0)
{}

VertexBufferObject::~VertexBufferObject()
{
	remove();
}

void VertexBufferObject::create()
{
	assert(handle == 0);
	glGenBuffers(1, &handle);
}

void VertexBufferObject::remove()
{
	if (handle != 0) {
		glDeleteBuffers(1, &handle);
	}
}

void VertexBufferObject::send(const std::vector<int>& values)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(values[0]) * values.size(), values.data(), GL_STATIC_DRAW);
}

void VertexBufferObject::send(const std::vector<float>& values)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(values[0]) * values.size(), values.data(), GL_STATIC_DRAW);
}

void VertexBufferObject::bind() const
{
	assert(handle != 0);
	glBindBuffer(GL_ARRAY_BUFFER, handle);
}

void VertexBufferObject::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}