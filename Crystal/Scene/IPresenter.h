#pragma once

#include "CGLib/Graphics/Camera.h"

namespace Crystal {
	namespace Scene {

class IPresenter
{
public:
	virtual ~IPresenter() = default;

	virtual void build() = 0;

	virtual void send() = 0;

	virtual void render(const Graphics::Camera& camera) = 0;

};
	}
}
