#include "RenderBufferObject.h"

using namespace Crystal::Shader;

RenderBufferObject::~RenderBufferObject()
{
	remove();
}

void RenderBufferObject::create()
{
	glGenRenderbuffers(1, &handle);
}

void RenderBufferObject::remove()
{
	glDeleteRenderbuffers(1, &handle);
}

void RenderBufferObject::bind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, handle);
}

void RenderBufferObject::unbind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
