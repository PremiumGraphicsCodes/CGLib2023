#include "PickUICtrl.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

PickUICtrl::PickUICtrl(TextureObject* texture) :
	texture(texture)
{
}

void PickUICtrl::onLeftButtonDown(const Vector2df& position)
{
	std::vector<unsigned char> outBuffer;
	outBuffer.resize(texture->getWidth()* texture->getHeight() * 4);

	glActiveTexture(GL_TEXTURE0);
	texture->bind();
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture->getHandle());

	glGetTexImage(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		outBuffer.data());

	texture->unbind();
}
