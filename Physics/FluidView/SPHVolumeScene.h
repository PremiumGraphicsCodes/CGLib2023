#pragma once

#include "Crystal/Scene/Scene/SceneBase.h"
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

	Volume::SparseVolumef* getShape() { return shape.get(); }

	Math::Box3df getBoundingBox() const override { return shape->getBoundingBox(); }

private:
	std::unique_ptr<Volume::SparseVolumef> shape;
};

	}
}