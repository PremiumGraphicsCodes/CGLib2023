#pragma once

#include "SceneBase.h"
#include "PolygonMeshPresenter.h"

#include "CGLib/Shape/PolygonMesh.h"

#include <vector>

namespace Crystal {
	namespace Scene {

class PolygonMeshScene : public SceneBase
{
public:
	void setShape(std::unique_ptr<Shape::PolygonMesh> shape) { this->shape = std::move(shape); }

	Shape::PolygonMesh* getShape() { return shape.get(); }

	void setPresenter(std::unique_ptr<PolygonMeshPresenter> p) { this->presenter = std::move(p); }

	IPresenter* getPresenter() override { return presenter.get(); }

private:
	std::unique_ptr<Shape::PolygonMesh> shape;
	std::unique_ptr<PolygonMeshPresenter> presenter;
};

	}
}