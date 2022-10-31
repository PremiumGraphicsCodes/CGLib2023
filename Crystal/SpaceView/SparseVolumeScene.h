#pragma once

#include "../Scene/SceneBase.h"
#include "../Space/SparseVolume.h"
#include "SparseVolumePresenter.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace Space {

class SparseVolumeScene : public Scene::SceneBase
{
public:
	SparseVolumeScene();

	void setShape(std::unique_ptr<SparseVolumef> shape) { this->shape = std::move(shape); }

	void setPresenter(std::unique_ptr<SparseVolumePresenter> p) { this->presenter = std::move(p); }

	SparseVolumef* getShape() { return shape.get(); }

	Scene::IPresenter* getPresenter() override { return presenter.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<SparseVolumef> shape;
	std::unique_ptr<SparseVolumePresenter> presenter;

};

	}
}