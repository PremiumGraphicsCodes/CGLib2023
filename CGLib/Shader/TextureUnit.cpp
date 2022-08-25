#include "TextureUnit.h"
#include "TextureObject.h"

using namespace Crystal::Shader;

void TextureUnit::bind() const
{
	glActiveTexture(GL_TEXTURE0 + unit);
	texture->bind();
}

void TextureUnit::unbind() const
{
	glActiveTexture(GL_TEXTURE0 + unit);
	texture->unbind();
}
