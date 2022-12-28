#pragma once

#include "Crystal/Scene/Scene/SceneBase.h"
#include "../Fluid/IMVPFluid.h"
#include "MVPFluidPresenter.h"

namespace Crystal {
	namespace Physics {

class MVPFluidScene : public Scene::SceneBase
{
public:
	MVPFluidScene();

	void setFluid(std::unique_ptr<IMVPFluid> fluid) { this->fluid = std::move(fluid); }

	IMVPFluid* getFluid() { return fluid.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<IMVPFluid> fluid;
};

	}
}