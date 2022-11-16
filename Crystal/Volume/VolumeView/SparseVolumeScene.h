#pragma once

#include "../Volume/SparseVolume.h"
#include "Crystal/Scene/SceneBase.h"
#include "SparseVolumePresenter.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace Volume {

class SparseVolumeScene : public Scene::SceneBase
{
public:
	SparseVolumeScene() {}

	void setShape(std::unique_ptr<SparseVolumef> shape) { this->shape = std::move(shape); }

	SparseVolumef* getShape() { return shape.get(); }

	Math::Box3df getBoundingBox() const override { return shape->getBoundingBox(); }

private:
	std::unique_ptr<SparseVolumef> shape;
};

	}
}