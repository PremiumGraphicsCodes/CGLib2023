#pragma once

#include "Crystal/Scene/SceneBase.h"
#include "CSPHFluidPresenter.h"
#include "../Fluid/CSPHFluid.h"

namespace Crystal {
	namespace Physics {

class CSPHFluidScene : public Scene::SceneBase
{
public:
	CSPHFluidScene();

	void setFluid(std::unique_ptr<CSPHFluid> fluid) { this->fluid = std::move(fluid); }

	void setPresenter(std::unique_ptr<CSPHFluidPresenter> p) { this->presenter = std::move(p); }

	CSPHFluid* getFluid() { return fluid.get(); }

	Scene::IPresenter* getPresenter() override { return presenter.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<CSPHFluid> fluid;
	std::unique_ptr<CSPHFluidPresenter> presenter;
};

	}
}