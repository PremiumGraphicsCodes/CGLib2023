#pragma once

#include "Crystal/Scene/SceneBase.h"
#include "PointCloudPresenter.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace Scene {

class PointCloudScene : public SceneBase
{
public:
	PointCloudScene();

	void setPresenter(std::unique_ptr<PointCloudPresenter> p) { this->presenter = std::move(p); }

	//Shape::ParticleSystem* getShape() { return shape.get(); }

	IPresenter* getPresenter() override { return presenter.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::vector<Math::Vector3df> positions;
	std::unique_ptr<PointCloudPresenter> presenter;
};

	}
}