#pragma once

#include "../Scene/SceneBase.h"
#include "../Volume/Volume.h"
#include "SparseVolumePresenter.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace Volume {

		class VolumeScene : public Scene::SceneBase
		{
		public:
			VolumeScene() {}

			void setShape(std::unique_ptr<Volumef> shape) { this->shape = std::move(shape); }

			void setPresenter(std::unique_ptr<SparseVolumePresenter> p) { this->presenter = std::move(p); }

			Volumef* getShape() { return shape.get(); }

			Scene::IPresenter* getPresenter() override { return presenter.get(); }

			Math::Box3df getBoundingBox() const override { return shape->getBoundingBox(); }

		private:
			std::unique_ptr<Volumef> shape;
			std::unique_ptr<SparseVolumePresenter> presenter;

		};

	}
}