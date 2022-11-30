#pragma once

#include "Crystal/Scene/SceneBase.h"
#include "PolygonMeshPresenter.h"

#include "../Mesh/PolygonMesh.h"

#include <vector>

namespace Crystal {
	namespace Scene {

		class PolygonMeshScene : public SceneBase
		{
		public:
			void setShape(std::unique_ptr<Shape::PolygonMesh> shape) { this->shape = std::move(shape); }

			Shape::PolygonMesh* getShape() { return shape.get(); }

		private:
			std::unique_ptr<Shape::PolygonMesh> shape;
		};

	}
}