#pragma once

#include "Crystal/Scene/Scene/SceneBase.h"
#include <memory>

namespace Crystal {
	namespace VDB {
		class VDBMesh;

class VDBMeshScene : public Scene::SceneBase
{
public:
	VDBMeshScene() = default;

	void setShape(std::unique_ptr<VDBMesh>&& shape) { this->shape = std::move(shape); }

	VDBMesh* getShape() { return shape.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<VDBMesh> shape;
};

	}
}