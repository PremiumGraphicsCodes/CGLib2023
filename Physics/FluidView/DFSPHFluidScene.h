#pragma once

#include "Crystal/Scene/Scene/SceneBase.h"
#include "../Fluid/DFSPHFluid.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace Physics {

class DFSPHFluidScene : public Scene::SceneBase
{
public:
	DFSPHFluidScene();

	void setFluid(std::unique_ptr<DFSPHFluid>&& fluid) { this->fluid = std::move(fluid); }

	DFSPHFluid* getFluid() { return fluid.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<DFSPHFluid> fluid;
};

	}
}