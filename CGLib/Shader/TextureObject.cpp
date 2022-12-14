#include "TextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TextureObject::~TextureObject()
{
	remove();
}

void TextureObject::create()
{
	glGenTextures(1, &handle);
}

void TextureObject::remove()
{
	if (handle != 0) {
		glDeleteTextures(1, &handle);
	}
}

void TextureObject::bind() const
{
	glBindTexture(GL_TEXTURE_2D, handle);
}

void TextureObject::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureObject::send(const Imageuc& image)
{
	this->width = image.getWidth();
	this->height = image.getHeight();

	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getValues().data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	glBindTexture(GL_TEXTURE_2D, 0);
	assert(GL_NO_ERROR == glGetError());
}

void TextureObject::setParameter(const GLenum type, const GLuint value)
{
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexParameteri(GL_TEXTURE_2D, type, value);
	glBindTexture(GL_TEXTURE_2D, 0);
	assert(GL_NO_ERROR == glGetError());
}

void TextureObject::send(const Imagef& image)
{
	this->width = image.getWidth();
	this->height = image.getHeight();

	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, 0);
	assert(GL_NO_ERROR == glGetError());
}

Imageuc TextureObject::toImageuc() const
{
	std::vector<unsigned char> values;
	values.resize(width * height * 4);

	//glActiveTexture(GL_TEXTURE0);
	//texture->bind();

	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, values.data());

	//texture->unbind();
	return Imageuc(width, height, values);
}
