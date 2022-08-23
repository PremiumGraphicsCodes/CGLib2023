#pragma once

#include <vector>
#include "IGLObject.h"
#include "glew.h"

namespace Crystal {
	namespace Shader {

class VertexBufferObject : public IGLObject
{
public:
	VertexBufferObject();

	~VertexBufferObject();

	void create() override;

	void remove() override;

	void send(const std::vector<int>& values);

	void send(const std::vector<float>& values);

	GLuint getHandle() const { return handle; }

	void bind() const;

	void unbind() const;

private:
	GLuint handle;
};

	}
}