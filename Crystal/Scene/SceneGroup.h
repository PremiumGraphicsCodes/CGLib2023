#pragma once

#include "SceneBase.h"

namespace Crystal {
	namespace Scene {

class SceneGroup : public SceneBase
{
public:
	Math::Box3df getBoundingBox() const override;
};
	}
}