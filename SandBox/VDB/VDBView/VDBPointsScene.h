#pragma once

#include "Crystal/Scene/SceneBase.h"
#include <memory>

namespace Crystal {
	namespace VDB {
		class VDBPoints;

class VDBPointsScene : public Scene::SceneBase
{
public:
	VDBPointsScene() = default;

	void setShape(std::unique_ptr<VDBPoints>&& shape) { this->shape = std::move(shape); }

	VDBPoints* getShape() { return shape.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<VDBPoints> shape;
};

	}
}