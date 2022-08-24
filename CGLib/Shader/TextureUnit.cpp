#include "TextureUnit.h"

using namespace Crystal::Shader;

TextureUnit::TextureUnit(const GLint number) :
	number(number)
{
}

void TextureUnit::bind()
{
	glActiveTexture(GL_TEXTURE0 + number);
}

void TextureUnit::unbind()
{
	glActiveTexture(GL_TEXTURE0);
}


