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
	//glActiveTexture(GL_TEXTURE0);
	texture->bind();

	const auto x = static_cast<int>( position.x * texture->getWidth() );
	const auto y = static_cast<int>( position.y * texture->getHeight() );

	const auto image = texture->toImageuc();
	const auto c = image.getColor(x, y);

	texture->unbind();
}
