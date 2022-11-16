#pragma once

#include "Crystal/Scene/SceneBase.h"
#include "TriangleMeshPresenter.h"

#include "TriangleMesh.h"

#include <vector>
#include <memory>

namespace Crystal {
	namespace Scene {

class TriangleMeshScene : public SceneBase
{
public:
	void setShape(std::unique_ptr<Shape::TriangleMesh> shape) { this->shape = std::move(shape); }

	Shape::TriangleMesh* getShape() { return shape.get(); }

	Math::Box3df getBoundingBox() const override { return shape->getBoundingBox(); }

private:
	std::unique_ptr<Shape::TriangleMesh> shape;
};

	}
}