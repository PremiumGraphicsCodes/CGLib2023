#pragma once

#include "Crystal/Scene/SceneBase.h"
#include "Crystal/Volume/Volume/SparseVolume.h"
#include "SPHVolumePresenter.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace Physics {

class SPHVolumeScene : public Scene::SceneBase
{
public:
	SPHVolumeScene() {}

	void setShape(std::unique_ptr<Volume::SparseVolumef> shape) { this->shape = std::move(shape); }

	void setPresenter(std::unique_ptr<SPHVolumePresenter> p) { this->presenter = std::move(p); }

	Volume::SparseVolumef* getShape() { return shape.get(); }

	Scene::IPresenter* getPresenter() override { return presenter.get(); }

	Math::Box3df getBoundingBox() const override { return shape->getBoundingBox(); }

private:
	std::unique_ptr<Volume::SparseVolumef> shape;
	std::unique_ptr<SPHVolumePresenter> presenter;

};

	}
}