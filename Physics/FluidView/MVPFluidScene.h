#pragma once

#include "Crystal/Scene/SceneBase.h"
#include "MVPFluidPresenter.h"
#include "../Fluid/MVPFluid.h"

namespace Crystal {
	namespace Physics {

class MVPFluidScene : public Scene::SceneBase
{
public:
	MVPFluidScene();

	void setFluid(std::unique_ptr<MVPFluid> fluid) { this->fluid = std::move(fluid); }

	MVPFluid* getFluid() { return fluid.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<MVPFluid> fluid;
};

	}
}