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

	void setPresenter(std::unique_ptr<MVPFluidPresenter> p) { this->presenter = std::move(p); }

	MVPFluid* getFluid() { return fluid.get(); }

	Scene::IPresenter* getPresenter() override { return presenter.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<MVPFluid> fluid;
	std::unique_ptr<MVPFluidPresenter> presenter;
};

	}
}