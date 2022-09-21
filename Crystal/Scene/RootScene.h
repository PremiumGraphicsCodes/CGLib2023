#pragma once

#include "IScene.h"

namespace Crystal {
	namespace Scene {

class RootScene : public IScene
{
public:
	Math::Box3df getBoundingBox() const override;
};
	}
}