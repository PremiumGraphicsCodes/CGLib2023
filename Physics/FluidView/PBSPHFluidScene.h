#pragma once

#include "Crystal/Scene/SceneBase.h"
#include "../Fluid/PBSPHFluid.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace Physics {

class PBSPHFluidScene : public Scene::SceneBase
{
public:
	PBSPHFluidScene();

	void setFluid(std::unique_ptr<PBSPHFluid> fluid) { this->fluid = std::move(fluid); }

	PBSPHFluid* getFluid() { return fluid.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<PBSPHFluid> fluid;
};

	}
}