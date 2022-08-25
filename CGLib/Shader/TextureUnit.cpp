#include "TextureUnit.h"
#include "TextureObject.h"

using namespace Crystal::Shader;

TextureUnit::TextureUnit(const GLint unit, TextureObject* texture) :
	unit(unit),
	texture(texture)
{
	bind();
}

TextureUnit::~TextureUnit()
{
	unbind();
}

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
