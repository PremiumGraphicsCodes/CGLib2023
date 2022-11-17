#include "FrameBufferObject.h"

//#include "glew.h"
#include "TextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

FrameBufferObject::~FrameBufferObject()
{
	remove();
}

void FrameBufferObject::create()
{
	glGenFramebuffers(1, &frameBuffer);
}

void FrameBufferObject::setRenderBuffer(const GLenum attachment, RenderBufferObject* rbo)
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbo->getHandle());
}


/*
void FrameBufferObject::build(int width, int height)
{
	this->width = width;
	this->height = height;
	glGenFramebuffers(1, &frameBuffer);


	assert(GL_NO_ERROR == glGetError());
}
*/

void FrameBufferObject::remove()
{
	//glDeleteRenderbuffers(1, &depthBuffer);
	glDeleteFramebuffers(1, &frameBuffer);
}

void FrameBufferObject::setTexture(const ITextureObject& texture)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getHandle(), 0);

	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameBufferObject::setTexture(const ITextureObject& texture, unsigned int number)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + number, GL_TEXTURE_2D, texture.getHandle(), 0);
}

void FrameBufferObject::setTexture(const ITextureObject& texture, const GLenum attachment, const GLenum target)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, target, texture.getHandle(), 0);
}

void FrameBufferObject::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//glBindTexture(GL_TEXTURE_2D, texture.getId());
	assert(GL_NO_ERROR == glGetError());
}

void FrameBufferObject::unbind() const
{
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	assert(GL_NO_ERROR == glGetError());
}

/*
Image FrameBufferObject::toImage() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<unsigned char> values(width * height * 4);

	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return Image(width, height, values);
}
*/

ColorRGBAuc FrameBufferObject::getColor(const int x, const int y) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<unsigned char> values(4);

	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return ColorRGBAuc(values[0], values[1], values[2], values[3]);
}