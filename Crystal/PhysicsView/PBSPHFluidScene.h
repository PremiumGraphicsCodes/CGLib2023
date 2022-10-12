#pragma once

#include "Crystal/Scene/SceneBase.h"
#include "../Physics/PBSPHFluid.h"
#include "PBSPHFluidPresenter.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace Physics {

class PBSPHFluidScene : public Scene::SceneBase
{
public:
	PBSPHFluidScene();

	void setFluid(std::unique_ptr<PBSPHFluid> fluid) { this->fluid = std::move(fluid); }

	void setPresenter(std::unique_ptr<PBSPHFluidPresenter> p) { this->presenter = std::move(p); }

	PBSPHFluid* getFluid() { return fluid.get(); }

	Scene::IPresenter* getPresenter() override { return presenter.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<PBSPHFluid> fluid;
	std::unique_ptr<PBSPHFluidPresenter> presenter;
};

	}
}