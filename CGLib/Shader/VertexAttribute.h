#pragma once

#include "glew.h"
#include "VertexBufferObject.h"
#include <vector>

namespace Crystal {
	namespace Shader {

class VertexAttribute
{
public:
	VertexAttribute() = default;

	explicit VertexAttribute(const GLuint location) :
		location(location)
	{}

	void sendVertexAttribute1df(const std::vector<float>& data);

	void sendVertexAttribute2df(const std::vector<float>& data);

	void sendVertexAttribute3df(const std::vector<float>& data);

	void sendVertexAttribute4df(const std::vector<float>& data);

	void sendVertexAttribute1di(const std::vector<int>& data);

	void sendVertexAttribute1di(const VertexBufferObject& vbo);

	void sendVertexAttribute1df(const VertexBufferObject& vbo);

	void sendVertexAttribute2df(const VertexBufferObject& vbo);

	void sendVertexAttribute3df(const VertexBufferObject& vbo);

	void sendVertexAttribute4df(const VertexBufferObject& vbo);

	void bind();

	void unbind();

private:
	GLuint location;
};

	}
}