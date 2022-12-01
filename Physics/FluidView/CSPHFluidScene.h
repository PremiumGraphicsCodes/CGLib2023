#pragma once

#include "Crystal/Scene/Scene/SceneBase.h"
#include "CSPHFluidPresenter.h"
#include "../Fluid/CSPHFluid.h"

namespace Crystal {
	namespace Physics {

class CSPHFluidScene : public Scene::SceneBase
{
public:
	CSPHFluidScene();

	void setFluid(std::unique_ptr<CSPHFluid> fluid) { this->fluid = std::move(fluid); }

	CSPHFluid* getFluid() { return fluid.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<CSPHFluid> fluid;
};

	}
}