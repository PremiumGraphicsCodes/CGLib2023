#pragma once

#include "Crystal/Scene/Scene/SceneBase.h"
#include "PolygonMeshPresenter.h"

#include "../Mesh/PolygonMesh.h"

#include <vector>

namespace Crystal {
	namespace Mesh {

		class PolygonMeshScene : public Scene::SceneBase
		{
		public:
			void setShape(std::unique_ptr<PolygonMesh> shape) { this->shape = std::move(shape); }

			PolygonMesh* getShape() { return shape.get(); }

			Math::Box3df getBoundingBox() const override { return shape->getBoundingBox(); }

		private:
			std::unique_ptr<PolygonMesh> shape;
		};

	}
}