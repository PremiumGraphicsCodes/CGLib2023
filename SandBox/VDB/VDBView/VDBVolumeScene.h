#pragma once

#include "Crystal/Scene/Scene/SceneBase.h"
#include <memory>

namespace Crystal {
	namespace VDB {
		class VDBVolume;

class VDBVolumeScene : public Scene::SceneBase
{
public:
	VDBVolumeScene() = default;

	void setShape(std::unique_ptr<VDBVolume>&& shape) { this->shape = std::move(shape); }

	VDBVolume* getShape() { return shape.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<VDBVolume> shape;
};

	}
}