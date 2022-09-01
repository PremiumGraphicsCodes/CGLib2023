#pragma once

#include "IGLObject.h"
#include "glew.h"

namespace Crystal {
	namespace Shader {

class RenderBufferObject : public IGLObject
{
public:
	~RenderBufferObject();

	void create() override;

	void remove() override;

	void bind() const override;

	void unbind() const override;

	GLuint getHandle() const override { return handle; }

private:
	GLuint handle;
};

	}
}