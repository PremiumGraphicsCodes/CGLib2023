#pragma once

#include "glew.h"
#include "IGLObject.h"
#include "RenderBufferObject.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Shader {
		class ITextureObject;

class FrameBufferObject : public IGLObject
{
public:
	~FrameBufferObject();

	void create() override;

	void remove() override;

	void setTexture(const ITextureObject& texture);

	void setTexture(const ITextureObject& texture, unsigned int number);

	void setTexture(const ITextureObject& texture, const GLenum attachment, const GLenum target);

	void bind() const override;

	void unbind() const override;

	GLuint getHandle() const { return frameBuffer; }

	void setRenderBuffer(const GLenum attachment, RenderBufferObject* rbo);

	Graphics::ColorRGBAuc getColor(const int x, const int y) const;

private:
	GLuint frameBuffer;
	//GLuint depthBuffer;
};

	}
}