#pragma once

#include "glew.h"
#include "IGLObject.h"

#include "../Graphics/Image.h"

namespace Crystal {
	namespace Shader {
		class ITextureObject;

class FrameBufferObject : public IGLObject
{
	//private:
	//	FrameBufferObject() {};

public:
	void create() override;

	void remove() override;

	void setTexture(const ITextureObject& texture);

	void setTexture(const ITextureObject& texture, unsigned int number);

	void bind();

	void unbind();

private:
	GLuint frameBuffer;
	GLuint depthBuffer;
};

	}
}