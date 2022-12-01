#pragma once

#include "SceneBase.h"

namespace Crystal {
	namespace Scene {

class SceneGroup : public SceneBase
{
public:
	Math::Box3df getBoundingBox() const override;

	/*
	void step() const {
		for (auto c : children) {
			c->step();
		}
	}
	*/
};
	}
}