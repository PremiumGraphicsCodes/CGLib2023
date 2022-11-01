#pragma once

#include "SceneBase.h"
#include "TriangleMeshPresenter.h"

#include "CGLib/Shape/TriangleMesh.h"

#include <vector>
#include <memory>

namespace Crystal {
	namespace Scene {

class TriangleMeshScene : public SceneBase
{
public:
	void setShape(std::unique_ptr<Shape::TriangleMesh> shape) { this->shape = std::move(shape); }

	Shape::TriangleMesh* getShape() { return shape.get(); }

	void setPresenter(std::unique_ptr<TriangleMeshPresenter> p) { this->presenter = std::move(p); }

	Math::Box3df getBoundingBox() const override { return shape->getBoundingBox(); }

	IPresenter* getPresenter() override { return presenter.get(); }

private:
	std::unique_ptr<Shape::TriangleMesh> shape;
	std::unique_ptr<TriangleMeshPresenter> presenter;
};

	}
}