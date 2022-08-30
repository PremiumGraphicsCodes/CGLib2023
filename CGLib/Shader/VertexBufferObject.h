#pragma once

#include <vector>
#include "IGLObject.h"
#include "glew.h"

namespace Crystal {
	namespace Shader {
		template<typename T>
		class VertexBuffer;

class VertexBufferObject : public IGLObject
{
public:
	VertexBufferObject();

	~VertexBufferObject();

	void create() override;

	void remove() override;

	void send(const std::vector<int>& values);

	void send(const std::vector<float>& values);

	void send(const VertexBuffer<float>& vb);

	GLuint getHandle() const { return handle; }

	void bind() const;

	void unbind() const;

private:
	GLuint handle;
};

	}
}