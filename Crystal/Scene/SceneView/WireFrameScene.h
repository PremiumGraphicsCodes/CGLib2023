#pragma once

#include "Crystal/Scene/Scene/SceneBase.h"
#include "WireFrame.h"
#include "WireFramePresenter.h"
#include <vector>

namespace Crystal {
	namespace Scene {

class WireFrameScene : public SceneBase
{
public:
	//WireFrameScene()

	void setShape(std::unique_ptr<Shape::WireFrame> shape) { this->shape = std::move(shape); }

	Shape::WireFrame* getShape() { return shape.get(); }

	Math::Box3df getBoundingBox() const override { return shape->getBoundingBox(); }

private:
	std::unique_ptr<Shape::WireFrame> shape;
};

	}
}