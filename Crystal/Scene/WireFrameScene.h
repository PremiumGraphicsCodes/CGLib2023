#pragma once

#include "SceneBase.h"
#include "CGLib/Shape/WireFrame.h"
#include "WireFramePresenter.h"
#include <vector>

namespace Crystal {
	namespace Scene {

class WireFrameScene : public SceneBase
{
public:
	//WireFrameScene()

	void setShape(std::unique_ptr<Shape::WireFrame> shape) { this->shape = std::move(shape); }

	void setPresenter(std::unique_ptr<WireFramePresenter> p) { this->presenter = std::move(p); }

	Shape::WireFrame* getShape() { return shape.get(); }

	IPresenter* getPresenter() override { return presenter.get(); }

private:
	std::unique_ptr<Shape::WireFrame> shape;
	std::unique_ptr<WireFramePresenter> presenter;
};

	}
}